from django.db import models
from uuid import uuid4

class Item(models.Model):
    id = models.AutoField(primary_key=True, editable=False)
    name = models.CharField(max_length=50)
    price = models.DecimalField(max_digits=5, decimal_places=2)

class Customer(models.Model):
    id = models.AutoField(primary_key=True, editable=False)
    name = models.CharField(max_length=255)
    create_at = models.DateField(auto_now_add=True, editable=False)

class Order(models.Model):
    id = models.AutoField(primary_key=True, editable=False)
    code = models.CharField(max_length=50)
    data = models.DateField()
    customer_id = models.ForeignKey(Customer, on_delete=models.DO_NOTHING, null=False)

