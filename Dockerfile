FROM gcc:8.2.0
MAINTAINER sashidhar guntury <sguntury@gmail.com>

COPY . /usr/src/app
WORKDIR /usr/src/app

RUN make

CMD ["./myapp"]
