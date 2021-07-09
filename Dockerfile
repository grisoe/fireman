FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update
RUN apt-get install -y libncurses5* libncursesw5* build-essential && \
    rm -rf /var/lib/apt/lists/* && \
    apt clean

WORKDIR /home/f

COPY . /home/f

RUN make

ENTRYPOINT ["/home/f/fireman"]
