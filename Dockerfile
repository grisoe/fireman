FROM ubuntu:20.04

RUN apt-get -y update
RUN apt-get install -y libncurses5* libncursesw5* build-essential && \
    rm -rf /var/lib/apt/lists/* && \
    apt clean

WORKDIR /fm

COPY . /fm

RUN make

ENTRYPOINT ["/fm/fireman"]
