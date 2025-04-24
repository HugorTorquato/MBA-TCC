FROM python:3.11-slim

WORKDIR /app

COPY ../observability/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
COPY . .

ENV PYTHONPATH=/app

CMD ["tail", "-f", "/dev/null"]