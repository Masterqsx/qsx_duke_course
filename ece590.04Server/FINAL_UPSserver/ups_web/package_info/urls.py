from django.conf.urls import url
from django.contrib.auth import views as auth_views
from . import views

app_name = 'package_info'
urlpatterns = [
  url(r'^$', views.index, name='index'),
  url(r'^map/$', views.map, name='map'),
  url(r'^userView/$', views.userView, name='userView'),
  url(r'^track/$', views.track, name='track'),
  url(r'^login/$', auth_views.login, name='login'),
  url(r'^logout/$', auth_views.logout, name='logout'),
  url(r'^register/$', views.register, name='register'),
]
