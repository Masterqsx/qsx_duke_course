from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.urls import reverse
from django import forms
from .forms import UserRegistrationForm
from django.contrib.auth.models import User
from .models import Package, Delivery
import re
import psycopg2 as py2

# Create your views here.
def index(request):
  return render(request, 'package_info/index.html', {});

def addr_trans(x, y):
  if x >= 900:
    x = 899;
  if x <= -900:
    x = -899;
  if y >= 900:
    y = 899;
  if y <= -900:
    y = -899;
  x = int((x + 900)/200);
  y = int((y + 900)/200);
  return (x * 9 + y + 1);

def map(request):
  l = [i+1 for i in range(81)];
  conn = py2.connect(database='ups', user='postgres', password='passw0rd', host='127.0.0.1', port=''); 
  cur = conn.cursor();
  cur.execute('select truck_id, x, y from truck;'); 
  rows = cur.fetchall();
  d = {i+1: '' for i in range(81)};
  for row in rows:
    d[addr_trans(row[1], row[2])] += str(row[0]) + ', '; 
  return render(request, 'package_info/map.html', {
    'index': l,
    'd': d.items,
  });

def userView(request):
  err = 'None';
  user_name = request.user.username;
  if request.method == 'POST' and 'modify' in request.POST and ('new_x' + request.POST['modify']) in request.POST and ('new_y' + request.POST['modify']) in request.POST and len(request.POST['new_x' + request.POST['modify']]) > 0 and len(request.POST['new_y' + request.POST['modify']]) > 0:
    conn = py2.connect(database='ups', user='postgres', password='passw0rd', host='127.0.0.1', port=''); 
    cur = conn.cursor();
    cur.execute('select status from package where package_id = ' + request.POST['modify'] + ' for update;');
    rows = cur.fetchall();
    for row in rows:
      if row[0] != -1:
        err = 'The status does not allowed change the info of delivery';
        break;
      else:
        cur.execute('update delivery set x = ' + request.POST['new_x'+request.POST['modify']] + ', y = ' + request.POST['new_y'+request.POST['modify']] + ' where package_id = ' + request.POST['modify'] + ';');
        err = 'Successfully change address to (' + request.POST['new_x'+request.POST['modify']] + ', ' + request.POST['new_y'+request.POST['modify']] + ')';
        if ('pri' + request.POST['modify']) in request.POST:
          cur.execute('update package set pri = 1 where package_id = ' + request.POST['modify'] + ';');
          err += '\n Successfully change to priority delivery';
    conn.commit();
    conn.close();
  package_list = Package.objects.filter(user_id = user_name);
  delivery_list = Delivery.objects.all();
  return render(request, 'package_info/userView.html', {
    'package_list': package_list,
    'user_name': user_name,
    'delivery_list': delivery_list,
    'err': err,
    });

def track(request):
  if request.method == 'POST' and 'tracking_number' in request.POST and len(request.POST['tracking_number']) > 0 and re.match(r'^[-]?\d+$', request.POST['tracking_number']) is not None:
      package_list = Package.objects.filter(package_id = request.POST['tracking_number']);
      return render(request, 'package_info/index.html', {
      'package_list': package_list,
      });
  else:
    return render(request, 'package_info/index.html', {});

def register(request):
  if request.method == 'POST':
    form = UserRegistrationForm(request.POST)
    if form.is_valid():
      userObj = form.cleaned_data
      username = userObj['username']
      email =  userObj['email']
      password =  userObj['password']
      if not (User.objects.filter(username=username).exists() or User.objects.filter(email=email).exists()):
        User.objects.create_user(username, email, password)
        user = authenticate(username = username, password = password)
        login(request, user)
        return HttpResponseRedirect('/')
      else:
        raise forms.ValidationError('Looks like a username with that email or password already exists')
  
  else:
    form = UserRegistrationForm()
    
  return render(request, 'registration/register.html', {'form' : form})
