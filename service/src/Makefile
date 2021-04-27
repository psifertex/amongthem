

amongthem: amongthem.c xxtea.c payload.c
	gcc -o amongthem amongthem.c payload.c xxtea.c -Wall

payload.c: encryptor.c
	gcc -o encryptor encryptor.c xxtea.c -Wall
	./encryptor > payload.c
