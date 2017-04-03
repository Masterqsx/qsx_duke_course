from django.shortcuts import get_object_or_404, render
from django.http import HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.utils import timezone
from .models import Question, Answer, Event, User, Pri_Event, Pri_Answer
from datetime import datetime
from django.core.mail import send_mail
import smtplib

# Create your views here.

def LoginView(request):
    try:
        del request.session['user_id']
    except KeyError:
        pass
    return render(request, 'polls/login.html')

def LoginHandleView(request):
    if ('username' in request.POST and (len(request.POST['username']) > 0)):
        if ('buttonlogin' in request.POST and User.objects.filter(u_name = request.POST['username'])):
            user = get_object_or_404(User, u_name=request.POST['username'])
            request.session['user_id'] = str(user.id)
            return HttpResponseRedirect(reverse('polls:event', args=(user.id, )))
        if ('buttonsign' in request.POST and (not User.objects.filter(u_name = request.POST['username'])) and 'useremail' in request.POST and (len(request.POST['useremail']) > 0)):
            n_user = User(u_email=request.POST['useremail'], u_name=request.POST['username'])
            n_user.save()
    return HttpResponseRedirect(reverse('polls:login', args=()))

def EventView(request, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    event_list = Event.objects.filter(pee_set__u_id=user_id).order_by('-e_time')
    return render(request, 'polls/event.html', {
                  'event_list': event_list,
                  'user_id': user_id,
                  'user_name': get_object_or_404(User, pk=user_id).u_name,
                  'pe_list': get_object_or_404(User, pk=user_id).peu_set.all(),
                  })

def EventCreateView(request, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    user = get_object_or_404(User, pk=user_id)
    if ('eventname_new' in request.POST and (len(request.POST['eventname_new']) > 0)):
        n_event_date = 'Unknown'
        if ('eventdate_new' in request.POST and (len(request.POST['eventdate_new']) > 0)):
            n_event_date = request.POST['eventdate_new']
        n_event = Event(e_name=request.POST['eventname_new'], e_time=timezone.now(), e_date=n_event_date)
        n_event.save()
        n_pe = Pri_Event(u=user, e=n_event, pe_type=0)
        n_pe.save(force_insert=True)
    return HttpResponseRedirect(reverse('polls:event', args=(user_id, )))

def EventModifyView(request, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    user = get_object_or_404(User, pk=user_id)
    for temp in request.POST.items():
        print (temp)
    for e in Event.objects.all():
        if (('eventname' + str(e.id)) in request.POST and (len(request.POST['eventname' + str(e.id)]) > 0) and (get_object_or_404(Pri_Event, u_id=user_id, e_id=e.id).pe_type == 0)):
            e.e_name = request.POST['eventname' + str(e.id)]
        if ('eventdate' + str(e.id)) in request.POST and (len(request.POST['eventdate' + str(e.id)]) > 0) and (get_object_or_404(Pri_Event, u_id=user_id, e_id=e.id).pe_type == 0):
            e.e_date = request.POST['eventdate' + str(e.id)]
        e.save()
    return HttpResponseRedirect(reverse('polls:event', args=(user_id, )))

def QuestionView(request, event_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    event = get_object_or_404(Event, pk=event_id)
    question_list = event.question_set.order_by('-q_time')
    return render(request, 'polls/question.html', {
                  'question_list': question_list,
                  'event_id': event_id,
                  'user_id': user_id,
                  'user_name': get_object_or_404(User, pk=user_id).u_name,
                  'event_name': get_object_or_404(Event, pk=event_id).e_name,
                  })

def QuestionCreateView(request, event_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    user = get_object_or_404(User, pk=user_id)
    event = get_object_or_404(Event, pk=event_id)
    if ('questiontext_new' in request.POST and (len(request.POST['questiontext_new']) > 0) and get_object_or_404(Pri_Event, e_id=event.id, u_id=user.id).pe_type == 0):
        questiontype_new = 0
        if ('questiontype_new' in request.POST and len(request.POST['questiontype_new']) > 0):
            questiontype_new = int(request.POST['questiontype_new'])
        event.question_set.create(q_text=request.POST['questiontext_new'], q_time=timezone.now(), q_type=questiontype_new)
    return HttpResponseRedirect(reverse('polls:question', args=(event_id, user_id, )))


def QuestionModifyView(request, event_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    user = get_object_or_404(User, pk=user_id)
    event = get_object_or_404(Event, pk=event_id)
    for temp in request.POST.items():
        print (temp)
    for q in Question.objects.all():
        if (('questiontext' + str(q.id)) in request.POST and (len(request.POST['questiontext' + str(q.id)]) > 0) and get_object_or_404(Pri_Event, e_id=event.id, u_id=user.id).pe_type == 0):
            mailed_user_set = set()
            for answer in q.answer_set.all():
                for pa in answer.paa_set.all():
                    for mailed_user in User.objects.filter(pau_set__u_id=pa.u_id):
                        mailed_user_set.add(mailed_user)
            for mailed_user in mailed_user_set:
                gmail_user = 'qsxyh123@163.com'
                gmail_pwd = 'ece590rsvp'
                TO = mailed_user.u_email
                SUBJECT = 'Event "' + event.e_name + '" Question "' + q.q_text + '" Change for ' + mailed_user.u_name
                TEXT = 'Question Become ' + request.POST['questiontext' + str(q.id)]
                server = smtplib.SMTP_SSL('smtp.163.com', 465)
                server.login(gmail_user, gmail_pwd)
                BODY = '\r\n'.join(['To: %s' % TO, 'From: %s' % gmail_user,'Subject: %s' % SUBJECT,'', TEXT])
                try:
                    server.sendmail(gmail_user, [TO], BODY)
                except Exception:
                    pass
            q.q_text = request.POST['questiontext' + str(q.id)]
        if (('questiontype' + str(q.id)) in request.POST and len(request.POST['questiontype' + str(q.id)]) > 0 and get_object_or_404(Pri_Event, e_id=event.id, u_id=user.id).pe_type == 0):
            q.q_type = int(request.POST['questiontype' + str(q.id)])
        q.save()
    return HttpResponseRedirect(reverse('polls:question', args=(event_id, user_id, )))

def AnswerView(request, event_id, question_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    question = get_object_or_404(Question, pk=question_id)
    user = get_object_or_404(User, pk=user_id)
    pe = get_object_or_404(Pri_Event, e_id=event_id, u_id=user_id)
    if (pe.pe_type == 0 or pe.pe_type == 1 and question.q_type == 1):
        answer_list = question.answer_set.all()
    elif (pe.pe_type == 1):
        answer_list = question.answer_set.filter(paa_set__u_id=user_id)
    else:
        answer_list = question.answer_set.filter(paa_set__pa_type=2)
    return render(request, 'polls/answer.html', {
                  'event_id': event_id,
                  'question': question,
                  'answer_list': answer_list,
                  'user': user,
                  'pe_type': pe.pe_type,
                  })

def AnswerCreateView(request, event_id, question_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    question = get_object_or_404(Question, pk=question_id)
    pe = get_object_or_404(Pri_Event, e_id=event_id, u_id=user_id)
    user = get_object_or_404(User, pk=user_id)
    if ('answer_text' in request.POST and len(request.POST['answer_text']) > 0 and pe.pe_type == 0):
        n_answer = question.answer_set.create(a_time=timezone.now(), a_text=request.POST['answer_text'], a_vote=1)
        n_pa = Pri_Answer(u=user, a=n_answer, pa_type=pe.pe_type)
        n_pa.save(force_insert=True)
    return HttpResponseRedirect(reverse('polls:answer', args=(event_id, question_id, user_id)))

def AnswerModifyView(request, event_id, question_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    question = get_object_or_404(Question, pk=question_id)
    pe = get_object_or_404(Pri_Event, e_id=event_id, u_id=user_id)
    user = get_object_or_404(User, pk=user_id)
    for a in question.answer_set.all():
        if (('finalize' + str(a.id)) in request.POST):
            a.a_type = 1
        if (('answer_text' + str(a.id)) in request.POST and len(request.POST['answer_text' + str(a.id)]) > 0 and a.a_type == 0):
            a.a_text = request.POST['answer_text' + str(a.id)]
        if (('answer' + str(a.id)) in request.POST and a.a_type == 0):
            a.a_vote += 1
        a.save()
        if (('permission' + str(a.id)) in request.POST):
            n_pa = Pri_Answer(u=user, a=a, pa_type=2)
            n_pa.save(force_insert=True)
    return HttpResponseRedirect(reverse('polls:answer', args=(event_id, question_id, user_id)))

def ClearAnswerView(request, event_id, question_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    question = get_object_or_404(Question, pk=question_id)
    for a in question.answer_set.all():
        a.delete()
    return HttpResponseRedirect(reverse('polls:answer', args=(event_id, question_id, user_id)))

def EventUserView(request, event_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    if get_object_or_404(Pri_Event, e_id=event_id, u_id=user_id).pe_type != 0:
        return HttpResponseRedirect(reverse('polls:event', args=(user_id, )))
    event = get_object_or_404(Event, pk=event_id)
    user_list = User.objects.filter(peu_set__e_id=event_id)
    return render(request, 'polls/user.html', {
                  'user_list': user_list,
                  'event_id': event_id,
                  'user_id': user_id,
                  'pe_list': event.pee_set.all(),
                  })

def EventUserCreateView(request, event_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    event = get_object_or_404(Event, pk=event_id)
    if ('username_new' in request.POST and len(request.POST['username_new']) > 0 and (User.objects.filter(u_name = request.POST['username_new']))):
        added_user = get_object_or_404(User, u_name=request.POST['username_new'])
        added_user_type = 1
        if ('usertype_new' in request.POST and len(request.POST['usertype_new']) > 0):
            added_user_type = int(request.POST['usertype_new'])
        if Pri_Event.objects.filter(u_id=added_user.id, e_id=event_id):
            return HttpResponseRedirect(reverse('polls:eventuser', args=(event_id, user_id)))
        n_pe = Pri_Event(u=added_user, e=event, pe_type=added_user_type)
        n_pe.save(force_insert=True)
    return HttpResponseRedirect(reverse('polls:eventuser', args=(event_id, user_id)))

def EventUserModifyView(request, event_id, user_id):
    if (request.session.get('user_id', 0) != user_id):
        return HttpResponseRedirect(reverse('polls:login', args=()))
    event = get_object_or_404(Event, pk=event_id)
    for u in User.objects.all():
        if (('usertype' + str(u.id)) in request.POST and len(request.POST['usertype' + str(u.id)]) > 0):
            pe = event.pee_set.get(u_id=u.id)
            if (pe.pe_type != int(request.POST['usertype' + str(u.id)])):
                for pa in Pri_Answer.objects.filter(u_id=u.id):
                    pa.delete()
            pe.pe_type = int(request.POST['usertype' + str(u.id)])
            pe.save(force_update=True)
    
    return HttpResponseRedirect(reverse('polls:eventuser', args=(event_id, user_id)))
