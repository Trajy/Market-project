FROM python:3.8-slim-buster
WORKDIR /app
COPY requirements.txt requirements.txt
RUN apt update && apt install -y libpq-dev python3-dev gcc
RUN pip3 install --upgrade pip && pip3 install -r requirements.txt
COPY . .
CMD python manage.py makemigrations && python manage.py migrate && python manage.py runserver 0.0.0.0:8000 --noreload
