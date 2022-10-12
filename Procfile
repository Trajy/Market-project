release: python market_api/manage.py migrate
web: gunicorn market_api.config.wsgi --log-file=-
