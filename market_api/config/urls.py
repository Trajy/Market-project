"""market_api URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from api import viewsets
from rest_framework import routers

route = routers.DefaultRouter()
route.register(r'items', viewsets.ItemViewSet, basename='items')
route.register(r'orders', viewsets.OrderViewSet, basename='0rders')
route.register(r'items-orders', viewsets.ItemOrderViewSet, basename='items-orders')
route.register(r'customers', viewsets.CustomerViewSet, basename='customers')

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include(route.urls))
]
