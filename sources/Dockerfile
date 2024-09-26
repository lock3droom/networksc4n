FROM gcc:latest

WORKDIR /usr/src/app

COPY ip_scanner.cpp .

RUN apt-get update && apt-get install -y iproute2

RUN g++ -o ip_scanner ip_scanner.cpp -pthread

CMD ["./ip_scanner"]
