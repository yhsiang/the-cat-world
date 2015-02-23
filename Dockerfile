FROM ubuntu:latest
MAINTAINER YuanHsiang Cheng <lyforever62@hotmail.com>

RUN apt-get update
RUN apt-get install -y build-essential
RUN ln -s /usr/bin/make  /usr/bin/gmake
RUN apt-get install -y bison
RUN apt-get install -y dos2unix
RUN apt-get install -y zlib1g-dev
ADD ./src /srv/mud/the-cat-world/src
ADD ./bin /srv/mud/the-cat-world/bin
ADD ./lib /srv/mud/the-cat-world/lib
WORKDIR srv/mud/the-cat-world/src
RUN cp /srv/mud/the-cat-world/bin/local_options /srv/mud/the-cat-world/src/local_options
RUN ./build.FluffOS
RUN make
RUN make install
EXPOSE 6666
ENTRYPOINT /srv/mud/the-cat-world/bin/driver /srv/mud/the-cat-world/bin/catworld.conf
