FROM registry.ghostcloud.cn/amd64/ubuntu:20.04
WORKDIR /root
COPY build/app app
COPY libs/libsymath.so /usr/local/lib
RUN ldconfig
RUN chmod +x app
ENTRYPOINT ["/root/app"]
