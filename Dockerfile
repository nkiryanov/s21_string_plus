FROM ubuntu:latest
RUN apt-get update && \
    apt-get install -y \
    git make check lcov pkg-config fish valgrind
COPY .  /code
WORKDIR /code/src
CMD fish
