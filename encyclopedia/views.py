from random import random
from django.http import HttpResponse, HttpResponseRedirect
from markdown2 import Markdown
from shutil import register_unpack_format
from django.shortcuts import render, redirect
import random
import re

from requests import request
from . import util
from django.urls import reverse
import logging
from django import forms

search_results = []

class NewTaskForm(forms.Form):
    search = forms.CharField(label="Search")

def index(request):
    if request.method == "POST":
        form = NewTaskForm(request.POST)
        if form.is_valid():
            search_result = form.cleaned_data["search"]
            if search_result.upper() in [x.upper() for x in util.list_entries()]:
                page_title = [x for x in util.list_entries() if x.upper() == search_result.upper()][0]
                return HttpResponseRedirect(reverse("page", kwargs={'name': page_title}))
            search_results_temp = [x for x in util.list_entries() if search_result.upper() in x.upper()]
            search_results.clear()
            search_results.extend(search_results_temp)
            if search_results:
                return HttpResponseRedirect(reverse("search"))
            else:
                return HttpResponseRedirect(reverse("not_found"))

    list_of_pages = []
    for element in util.list_entries():
        link = '<a href=/wiki/'+element+'>'+element+'</a>'
        list_of_pages.append(link)
    return render(request, "encyclopedia/index.html", {
        "entries": list_of_pages,
        "form": NewTaskForm()
    })

def page(request, name):
    page = util.get_entry(name)
    if page is None:
        return HttpResponseRedirect(reverse("not_found"))

    html = Markdown().convert(page)
    return render(request, "encyclopedia/page.html", {
        "content": html,
        "title": name,
        "form": NewTaskForm()
    })

def visit_random(request):
    random_page = random.choice(util.list_entries())
    return HttpResponseRedirect(reverse("page", kwargs={'name': random_page}))

def search(request):
    list_of_pages = []
    for element in search_results:
        link = '<a href=/wiki/'+element+'>'+element+'</a>'
        list_of_pages.append(link)
    return render(request, "encyclopedia/search.html", {
        "results": list_of_pages,
        "form": NewTaskForm()
    })

def newPage(request):
    if request.method == "POST":
        if request.POST["title"].upper() in [x.upper() for x in util.list_entries()]:
            return HttpResponseRedirect(reverse("exists", kwargs={'name':request.POST["title"]}))
        util.save_entry(request.POST["title"], request.POST["content"])
        return HttpResponseRedirect(reverse("page", kwargs={'name': request.POST["title"]}))
    return render(request, "encyclopedia/newPage.html", {
        "form": NewTaskForm()
    })

def edit(request, name):
    pre_Content = util.get_entry(name)
    content = re.sub('(\r\r\n)+', '\n', pre_Content)
    if request.method == "POST":
        util.save_entry(name, request.POST["content"])
        return HttpResponseRedirect(reverse("page", kwargs={'name': name}))
    return render(request, "encyclopedia/editPage.html", {
        "title": name,
        "preContent": content,
        "form": NewTaskForm()
    })

def not_found(request):
    return render(request, "encyclopedia/error.html", {
        "form": NewTaskForm()
    })

def existed(request, name):
    return render(request, "encyclopedia/existed.html", {
        "oldname": name,
        "form": NewTaskForm()
    })