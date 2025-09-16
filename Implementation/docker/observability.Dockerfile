FROM python:3.11-slim

# Instalar dependências do sistema necessárias para o Graphviz
RUN apt-get update && apt-get install -y --no-install-recommends \
    graphviz \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copiar requirements e instalar pacotes Python
COPY ../observability/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copiar o código da aplicação
COPY . .

# Configurar PYTHONPATH para reconhecer /app
ENV PYTHONPATH=/app

CMD ["tail", "-f", "/dev/null"]
