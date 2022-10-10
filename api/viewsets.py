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
        item = models.Item.objects.filter(rfid__exact=request.data['rfid'])
        if not(item.exists()):
            return Response('Item nao cadastrado no sistema').status_code(404)
        order = models.Order.objects.filter(status__icontains='COMPRANDO', customer__exact=request.data['customer'])
        if not(order.exists()):
           models.Order(code=uuid4(), data=datetime.now(), customer=request.data['customer'], status='COMPRANDO').save()
           order = models.Order.objects.filter(status__icontains='COMPRANDO', customer__exact=request.data['customer'])
        models.ItemOrder(item=item.id, order=order.id).save()
        
    
class CustomerViewSet(ModelViewSet):
    serializer_class = serializers.CustomerSerializer
    queryset = models.Customer.objects.all()

    def create(self, request):
        customer = models.Customer.objects.create(name=request.data['name'])
        customer.save()
        return Response(serializers.CustomerSerializer(customer).data)
 