from django.shortcuts import render

# Create your views here.
from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from django.http import JsonResponse
from datetime import date

from django.core.paginator import Paginator

from .models import *
import json
from django.views.decorators.csrf import csrf_exempt

def index(request):
    # check tournament's date
    def deadline_pass(t):
        return t.date < date.today()

    # update tournaments due in the past
    all = tournament.objects.all()
    tournaments_past_due = [t for t in all if deadline_pass(t)]
    for t in tournaments_past_due:
        t.full = True
        t.save()

    tournaments = tournament.objects.filter(full=False)
    tournaments = [t for t in tournaments if t not in tournaments_past_due]
    p = Paginator(tournaments, 10)
    page = request.GET.get('page_num') or 1
    tournaments_final = p.get_page(page)
    return render(request, "chesstourney/index.html", {
        'tournaments': tournaments_final
    })


def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(request, "chesstourney/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "chesstourney/login.html")


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(request, "chesstourney/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "chesstourney/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "chesstourney/register.html")

def tournament_details(request, tournament_id):
    tournament_selected = tournament.objects.get(pk=tournament_id)
    participants_id = tournament_user.objects.filter(tournament=tournament_selected).values_list('participant',flat=True)
    participants = []
    for id in participants_id:
        participants.append(User.objects.get(pk=id).username)
    slot_left = tournament_selected.slots-tournament_selected.participants
    if not request.user.is_anonymous:
        is_logged_in = True
        if tournament_user.objects.filter(tournament=tournament_selected, participant=request.user).exists():
            registered = True
        else:
            registered = False
    else:
        is_logged_in = False
        registered = None
        
    return render(request, "chesstourney/tournament.html", {
        'tournament': tournament_selected,
        'slots_remaining':slot_left,
        'is_registered':registered, 
        'participants':participants,
        'is_logged_in':is_logged_in
    })

def results(request):
    results = []
    closed_tournaments = tournament.objects.filter(full=True)
    for tour in closed_tournaments:
        try:
            tour_result = result.objects.get(tournament_result=tour)
        except:
            tour_result = None
        if tour_result is not None:
            results.append(tour_result)

    p = Paginator(results, 10)
    page = request.GET.get('page_num') or 1
    
    results_final = p.get_page(page)
    return render(request, "chesstourney/results.html", {
        'results': results_final
    })

def tour_result(request, tournament_id):
    tour = tournament.objects.get(pk=tournament_id)
    tour_result = result.objects.get(tournament_result=tour)

    participants_scores = tournament_user.objects.filter(tournament=tour).order_by("-total_score")

    return render(request, "chesstourney/tournament_result.html", {
        'result': tour_result,
        'scores': participants_scores
    })

def register_tournament(request):
    if request.method == "POST":
        title = request.POST["title"]
        image = request.POST["image"]
        prize = request.POST["desc"]
        players = request.POST["slots"]
        date = request.POST["date"]
        location = request.POST["location"]
        num_rounds = request.POST["rounds"]
        time_total = request.POST["time-control"]
        org = User.objects.get(username=request.user)
        # all tournament details
        new_tournament = tournament(name=title, organizer=org, slots=players,
        participants=0, prizes=prize,date=date, image=image, location=location, number_of_rounds=num_rounds,
        time_control=time_total)
        new_tournament.save()
        return HttpResponseRedirect(reverse('index'))
    return render(request, "chesstourney/tournament_register.html")

def upload_result(request, user_id):
    user = User.objects.get(pk=user_id)
    tournaments = tournament.objects.filter(organizer=user, full=True)
    results_published = result.objects.all().values_list('tournament_result', flat=True)
    published = []
    for id in results_published:
        published.append(tournament.objects.get(pk=id))

    tournaments = [x for x in tournaments if x not in published]
    tournaments = [x for x in tournaments if x.participants > 2]

    is_tournament = True
    if not tournaments:
        is_tournament = False
    return render(request, "chesstourney/upload_result.html", {
        'tournaments': tournaments,
        'is_tournament': is_tournament
    })

@csrf_exempt
def submit_result(request, user_id):
    if request.method == "POST":
        data = json.loads(request.body)
        participants = data.get("players", "")
        scores = data.get("participants_score","")
        tour_id = data.get("tournament","")
        tour = tournament.objects.get(pk=tour_id);
        for i in range(len(participants)):
            participant_id = participants[i]['id']
            participant = User.objects.get(pk=participant_id)
            score = scores[i]
            individual_result = tournament_user.objects.get(tournament=tour, participant=participant)
            individual_result.total_score = score
            individual_result.save()

        top_3 = tournament_user.objects.filter(tournament=tour).order_by('-total_score')[0:3]
        final_result = result(tournament_result=tour, winner=top_3[0], second=top_3[1], third=top_3[2])
        final_result.save()

    return JsonResponse({"message": "Results Added"}, status=201)

def get_participants(request, tournament_id):
    participants = []
    tour = tournament.objects.get(pk=tournament_id)

    tour_participants = tournament_user.objects.filter(tournament=tour).values_list('participant', flat=True)
    for participant in tour_participants:
        participants.append(User.objects.get(pk=participant))

    print([part.serialize for part in participants])
    return JsonResponse([part.serialize() for part in participants], safe=False)

def add_participant(request, tournament_id, participant_id):
    tour = tournament.objects.get(pk=tournament_id)
    participant = User.objects.get(pk=participant_id)
    tour_participant = tournament_user(tournament=tour, participant=participant, total_score=0)
    tour_participant.save()
    tour.participants += 1
    if tour.slots - tour.participants == 0:
        tour.full = True
    tour.save()
    return HttpResponseRedirect(reverse('index'))

def close_tourn(request, tournament_id):
    tour = tournament.objects.get(pk=tournament_id)
    tour.full = True
    tour.save()

    return HttpResponseRedirect(reverse('index'))    