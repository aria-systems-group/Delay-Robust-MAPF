FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="juko6110@colorado.edu"
LABEL version="1.0"
LABEL description="This is a custom Dockerfile for using OMPL 1.6"

# Disable Prompt During Packages Installation
ARG DEBIAN_FRONTEND=noninteractive 

# libompl-dev \
RUN apt-get update && apt-get install -y build-essential \
                                        cmake \
                                        libeigen3-dev \
                                        libboost-all-dev \
                                        screen \
                                        vim \
                                        valgrind \
                                        git