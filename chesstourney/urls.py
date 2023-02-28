from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("tournament/<int:tournament_id>", views.tournament_details, name="details"),
    path("results", views.results, name="results"),
    path("result/<int:tournament_id>", views.tour_result, name="tour_result"),
    path("register_tournament", views.register_tournament, name="add_tournament"),
    path("upload_result/<int:user_id>", views.upload_result, name="upload_result"),
    path("submit_result/<int:user_id>", views.submit_result, name="submit_result"),
    path("get_participants/<int:tournament_id>", views.get_participants, name="get_participants"),
    path("add_participant/<int:tournament_id>/<int:participant_id>", views.add_participant, name="add_participant"),
    path("close_tournament/<int:tournament_id>", views.close_tourn, name="close_tournament")
]
