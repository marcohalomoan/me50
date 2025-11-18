from pydoc import visiblename
from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("wiki/<str:name>", views.page, name="page"),
    path("visit_random", views.visit_random, name="random"),
    path("new_page", views.newPage, name="newPage"),
    path("search", views.search, name="search"),
    path("edit/<str:name>", views.edit, name="edit"),
    path("not_found", views.not_found, name="not_found"),
    path("page_exists/<str:name>", views.existed, name="exists")
]
