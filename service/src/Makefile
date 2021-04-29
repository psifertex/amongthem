release: amongthem.c xxtea.c payload.c
	gcc -o amongthem -D_FORTIFY_SOURCE=2 -O1 -no-pie -fno-stack-protector amongthem.c payload.c xxtea.c
	strip amongthem

debug: amongthem.c xxtea.c payload.c
	gcc -o amongthem -g -Wall amongthem.c payload.c xxtea.c 

payload.c: encryptor.c xxtea.c
	gcc -o encryptor encryptor.c xxtea.c  -Wall
	./encryptor > payload.c

clean:
	rm -f amongthem payload.c encryptor
