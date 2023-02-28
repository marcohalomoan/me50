from django.contrib import admin
from .models import *


# Register your models here.
admin.site.register(User)
admin.site.register(tournament)
admin.site.register(tournament_user)
admin.site.register(result)