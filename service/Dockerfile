from ubuntu:20.04
run echo "service Dockerfile apt" && \
    apt-get -qq update && apt-get install -qq xinetd


copy amongthem /
run chmod 755 /amongthem

run touch /flag && chmod 644 /flag && echo "FLAG{Green:RedSoSus}" > /flag
copy service.conf /service.conf
copy wrapper /wrapper
copy banner_fail /

expose 31337

cmd ["/usr/sbin/xinetd", "-filelog", "-", "-dontfork", "-f", "/service.conf"]
