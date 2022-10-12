release: python market_api/manage.py migrate
web: cd market_api && gunicorn market_api.config.wsgi --log-file=-
