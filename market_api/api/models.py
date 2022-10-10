from django.db import models

class Customer(models.Model):
    id = models.AutoField(primary_key=True, editable=False)
    name = models.CharField(max_length=255)
    create_at = models.DateField(auto_now_add=True, editable=False)

class Item(models.Model):
    id = models.AutoField(primary_key=True, editable=False)
    name = models.CharField(max_length=50)
    price = models.DecimalField(max_digits=5, decimal_places=2)
    rfid = models.CharField(max_length=12, unique=True)

class Order(models.Model):
    id = models.AutoField(primary_key=True, editable=False)
    code = models.CharField(max_length=50)
    data = models.DateField()
    customer = models.ForeignKey(Customer, on_delete=models.DO_NOTHING, null=False)
    status = models.CharField(max_length=10 ,null=False)

class ItemOrder(models.Model):
    item = models.ForeignKey(Item, models.DO_NOTHING)
    order = models.ForeignKey(Order, models.DO_NOTHING)
    quantity = models.PositiveIntegerField(null=False)
