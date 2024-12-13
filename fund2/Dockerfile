FROM ubuntu:latest
LABEL authors="xsestech"

RUN apt-get update && apt-get install -y \
    clang cmake build-essential ninja-build gdb strace valgrind
RUN apt-get install -y tree

ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash builder
USER builder



WORKDIR app
COPY . .

#RUN #mkdir -p /tmp/build

#USER root
#RUN chmod 777 /app/scripts/valgrinder.sh
#RUN chown -R builder:builder build
#USER builder

ENTRYPOINT ["./scripts/valgrinder.sh"]
