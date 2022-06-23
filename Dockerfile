FROM ubuntu:16.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    xcb \
    xcb-proto \
    libxcb-ewmh-dev \
    libxcb-icccm4-dev \
    libxcb-util0-dev

VOLUME /app
WORKDIR /app
