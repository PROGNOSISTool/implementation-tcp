FROM alpine:latest
RUN apk add --no-cache --update --verbose grep bash autoconf build-base binutils gcc libgcc libtool linux-headers && \
    rm -rf /var/cache/apk/* /tmp/* /sbin/halt /sbin/poweroff /sbin/reboot
WORKDIR /code
COPY server.c .
RUN gcc server.c -o server
RUN chmod ug+x ./server
CMD ["./server"]
