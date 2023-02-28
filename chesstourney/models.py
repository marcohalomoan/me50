from django.contrib.auth.models import AbstractUser
from django.db import models

# Create your models here.

class User(AbstractUser):
    # followers = models.ForeignKey('self',on_delete=models.CASCADE, related_name="follower")
    def serialize(self):
        return {
            "id": self.id,
            "username": self.username,
        }

class tournament(models.Model):
    name = models.CharField(max_length=100)
    organizer = models.ForeignKey(User, on_delete=models.CASCADE)
    slots = models.IntegerField(default=100)
    participants = models.IntegerField()
    prizes = models.TextField(default='')
    date = models.DateField()
    image = models.URLField()
    location = models.TextField()
    number_of_rounds = models.IntegerField()
    time_control = models.IntegerField()
    full = models.BooleanField(default=False)

class tournament_user(models.Model):
    tournament = models.ForeignKey(tournament, on_delete=models.CASCADE)
    participant = models.ForeignKey(User, on_delete=models.CASCADE)
    total_score = models.DecimalField(decimal_places=1, max_digits=5)

    class Meta:
        unique_together = ['tournament', 'participant']

class result(models.Model):
    tournament_result = models.ForeignKey(tournament, on_delete=models.CASCADE)
    winner = models.ForeignKey(tournament_user, on_delete=models.CASCADE, related_name="winner")
    second = models.ForeignKey(tournament_user, on_delete=models.CASCADE, related_name="second")
    third = models.ForeignKey(tournament_user, on_delete=models.CASCADE, related_name="third")
