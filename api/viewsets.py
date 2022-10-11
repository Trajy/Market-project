from datetime import datetime
from uuid import uuid4
from rest_framework.viewsets import ModelViewSet
from rest_framework.response import Response
from api import models, serializers

class ItemViewSet(ModelViewSet):
    serializer_class = serializers.ItemSerializer
    queryset = models.Item.objects.all()

class OrderViewSet(ModelViewSet):
    serializer_class = serializers.OrderSerializer
    queryset = models.Order.objects.filter(status__exact='COMPRANDO').all()

class ItemOrderViewSet(ModelViewSet):
    serializer_class = serializers.ItemOrderSerializer
    queryset = models.ItemOrder.objects.all()

    def create(self, request):
        items = models.Item.objects.filter(rfid__exact=request.data['rfid'])
        orders = models.Order.objects.filter(status__exact='COMPRANDO', customer__exact=request.data['customer'])
        if not(items.exists()):
            return Response('Item nao cadastrado no sistema', 404)
        if not(orders.exists()):
           models.Order(code=uuid4(), data=datetime.now(), customer=request.data['customer'], status='COMPRANDO').save()
           orders = models.Order.objects.filter(status__exact='COMPRANDO', customer__exact=request.data['customer'])
        item = items.first()
        order = orders.first()
        itemOrder = models.ItemOrder.objects.create(item=item, order=order, quantity=1)
        return Response(serializers.ItemOrderSerializer(itemOrder).data)

class CustomerViewSet(ModelViewSet):
    serializer_class = serializers.CustomerSerializer
    queryset = models.Customer.objects.all()

    def create(self, request):
        customer = models.Customer.objects.create(name=request.data['name'])
        customer.save()
        return Response(serializers.CustomerSerializer(customer).data)
 