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
    queryset = models.Order.objects.all()

    def list(self, request):
        status = request.query_params.get('status')
        customer_id =  request.query_params.get('customer')
        if (status != None and customer_id != None):
            customer = models.Customer.objects.get(pk=customer_id)
            orders = models.Order.objects.filter(status__exact=status, customer__exact=customer)
            if (orders.exists()):
                 return Response(serializers.OrderSerializer(orders.first()).data)
            return Response(f'Nenhum pedido com status {status}')
        return super().list(request)
    
    def create(self, request):
        customer = models.Customer.objects.get(pk=request.data['customer'])
        order = models.Order(code=uuid4(), data=datetime.now().date(), customer=customer, status='COMPRANDO')
        order.save()
        return Response(serializers.OrderSerializer(order).data)

class ItemOrderViewSet(ModelViewSet):
    serializer_class = serializers.ItemOrderSerializer
    queryset = models.ItemOrder.objects.all()

    def create(self, request):
        items = models.Item.objects.filter(rfid__exact=request.data['rfid'])
        if not(items.exists()):
            return Response('Item nao cadastrado no sistema ' + request.data['rfid'], 404)
        customer = models.Customer.objects.get(pk=request.data['customer'])
        orders = models.Order.objects.filter(status__exact='COMPRANDO', customer__exact=customer)
        if not(orders.exists()):
           models.Order(code=uuid4(), data=datetime.now(), customer=customer, status='COMPRANDO').save()
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
 