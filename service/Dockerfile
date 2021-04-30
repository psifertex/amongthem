from ubuntu:20.04
run echo "service Dockerfile apt" && \
    apt-get -qq update && apt-get install -qq xinetd


copy src/amongthem /
run chmod 755 /amongthem

copy service.conf /service.conf
copy wrapper /wrapper
copy banner_fail /

expose 3535

cmd ["/usr/sbin/xinetd", "-filelog", "-", "-dontfork", "-f", "/service.conf"]
