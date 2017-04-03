from django.db import models
from django.utils import timezone
import datetime

# Create your models here.
class Event(models.Model):
    e_name = models.CharField(max_length=200)
    e_time = models.DateTimeField('event')
    e_date = models.CharField(max_length=200, default='Unknown')
    def __str__(self):
        return self.e_name

class Question(models.Model):
    event = models.ForeignKey(Event, on_delete=models.CASCADE)    
    q_time = models.DateTimeField('question published')
    q_text = models.CharField(max_length=200)
    q_type = models.IntegerField(default=0)
    def __str__(self):
        return self.q_text

class Answer(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    a_time = models.DateTimeField('answer posted')
    a_text = models.CharField(max_length=200)
    a_vote = models.IntegerField(default=0)
    a_type = models.IntegerField(default=0)
    def __str__(self):
        return self.a_text

class User(models.Model):
    #u_type = models.IntegerField(default=1)
    u_email = models.CharField(max_length=200, default='null')
    u_name = models.CharField(max_length=200)
    def __str__(self):
        return self.u_name

class Pri_Event(models.Model):
    u = models.ForeignKey(User, related_name='peu_set', on_delete=models.CASCADE)
    e = models.ForeignKey(Event, related_name='pee_set', on_delete=models.CASCADE)
    pe_type = models.IntegerField(default=1)

class Pri_Answer(models.Model):
    u = models.ForeignKey(User, related_name='pau_set', on_delete=models.CASCADE)
    a = models.ForeignKey(Answer, related_name='paa_set', on_delete=models.CASCADE)
    pa_type = models.IntegerField(default=1)
