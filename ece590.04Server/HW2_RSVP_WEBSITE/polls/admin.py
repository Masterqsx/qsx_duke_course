from django.contrib import admin

from .models import *
# Register your models here.

admin.site.register(Event)
admin.site.register(Question)
admin.site.register(Answer)
admin.site.register(User)
admin.site.register(Pri_Event)
admin.site.register(Pri_Answer)
