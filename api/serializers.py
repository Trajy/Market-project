from rest_framework.serializers import ModelSerializer
from api import models

class ItemSerializer(ModelSerializer):
    class Meta:
        model = models.Item
        fields = '__all__'

class OrderSerializer(ModelSerializer):
    class Meta:
        model = models.Order
        fields = '__all__'

class OrderSerializer(ModelSerializer):
    class Meta:
        model = models.ItemOrder
        fields = '__all__'

class CustomerSerializer(ModelSerializer):
    class Meta:
        model = models.Customer
        fields = '__all__'