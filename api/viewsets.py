from rest_framework.viewsets import ModelViewSet
from rest_framework.response import Response
from api import models, serializers

class ItemViewSet(ModelViewSet):
    serializer_class = serializers.ItemSerializer
    queryset = models.Item.objects.all()

class OrderViewSet(ModelViewSet):
    serializer_class = serializers.OrderSerializer
    queryset = models.Order.objects.all()

class ItemOrderViewSet(ModelViewSet):
    serializer_class = serializers.OrderSerializer
    queryset = models.ItemOrder.objects.all()

class CustomerViewSet(ModelViewSet):
    serializer_class = serializers.CustomerSerializer
    queryset = models.Customer.objects.all()

    def create(self, request):
        customer = models.Customer.objects.create(name=request.data['name'])
        customer.save()
        return Response(serializers.CustomerSerializer(customer).data)
 