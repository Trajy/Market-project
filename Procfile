release: cd market_api && python manage.py migrate
web: gunicorn market_api.config.wsgi --log-file=-
