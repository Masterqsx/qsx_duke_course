from django.conf.urls import url
from . import views

app_name = 'polls'
urlpatterns = [
    url(r'^$', views.LoginView, name='login'),
    url(r'^loginhandle$', views.LoginHandleView, name='loginhandle'),
    url(r'^(?P<user_id>[0-9]+)/event/$', views.EventView, name='event'),
    url(r'^(?P<user_id>[0-9]+)/eventcreate/$', views.EventCreateView, name='eventcreate'),
    url(r'^(?P<user_id>[0-9]+)/eventmodify/$', views.EventModifyView, name='eventmodify'),
    url(r'^questionFor(?P<event_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.QuestionView, name='question'),
    url(r'^questioncreateFor(?P<event_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.QuestionCreateView, name='questioncreate'),
    url(r'^questionmodifyFor(?P<event_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.QuestionModifyView, name='questionmodify'),
    url(r'^answerFor(?P<event_id>[0-9]+)/(?P<question_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.AnswerView, name='answer'),
    url(r'^answercreateFor(?P<event_id>[0-9]+)/(?P<question_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.AnswerCreateView, name='answercreate'),
    url(r'^answermodifyFor(?P<event_id>[0-9]+)/(?P<question_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.AnswerModifyView, name='answermodify'),
    url(r'^clearanswerFor(?P<event_id>[0-9]+)/(?P<question_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.ClearAnswerView, name='clearanswer'),
    url(r'^eventuserFor(?P<event_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.EventUserView, name='eventuser'),
    url(r'^eventusercreateFor(?P<event_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.EventUserCreateView, name='eventusercreate'),
    url(r'^eventusermodifyFor(?P<event_id>[0-9]+)/(?P<user_id>[0-9]+)/$', views.EventUserModifyView, name='eventusermodify'),
               
]
