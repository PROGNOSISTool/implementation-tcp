FROM python:3.11-alpine
WORKDIR /code
COPY server.py .
CMD ["python3", "-u", "server.py"]
