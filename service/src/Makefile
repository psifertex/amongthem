

amongthem: amongthem.c xxtea.c payload.c
	gcc -o amongthem -static -Wall amongthem.c payload.c xxtea.c 
	#gcc -o amongthem -D_FORTIFY_SOURCE=2 -O1 -no-pie -static -fno-stack-protector amongthem.c #Harden
	strip amongthem


payload.c: encryptor.c
	gcc -o encryptor encryptor.c xxtea.c  -Wall
	./encryptor > payload.c
