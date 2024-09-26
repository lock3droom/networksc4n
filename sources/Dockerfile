FROM debian:latest

RUN apt-get update && apt-get install -y \
    g++ \
    iputils-ping \
    iproute2 \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY ./main.cpp .

RUN g++ -o sniff main.cpp

# Exposer un port si nécessaire (ex: 8080)
# EXPOSE 8080

CMD ["./sniff"]
