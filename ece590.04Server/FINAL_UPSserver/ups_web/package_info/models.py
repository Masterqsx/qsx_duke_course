# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey has `on_delete` set to the desired behavior.
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from __future__ import unicode_literals

from django.db import models

class Package(models.Model):
    package_id = models.BigIntegerField(blank=True, null=True)
    user_id = models.CharField(max_length=100, blank=True, null=True)
    info = models.CharField(max_length=1000, blank=True, null=True)
    status = models.IntegerField(blank=True, null=True)
    pri = models.IntegerField(blank=True, null=True)
    ship_id = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'package'

class Delivery(models.Model):
    truck_id = models.IntegerField(blank=True, null=True)
    package_id = models.BigIntegerField(blank=True, null=True)
    #package_id = models.ForeignKey(Package, on_delete=models.CASCADE)
    x = models.IntegerField(blank=True, null=True)
    y = models.IntegerField(blank=True, null=True)
    status = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'delivery'



class Pickup(models.Model):
    truck_id = models.IntegerField(blank=True, null=True)
    package_id = models.BigIntegerField(blank=True, null=True)
    wh_id = models.IntegerField(blank=True, null=True)
    status = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'pickup'


class Truck(models.Model):
    truck_id = models.AutoField(primary_key=True)
    x = models.IntegerField(blank=True, null=True)
    y = models.IntegerField(blank=True, null=True)
    status = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'truck'
