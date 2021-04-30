from binascii import crc32
from time import time
from random import sample

start = time()

s = "0123456789"
s = list(s)
checksum = 329936096

while True:
    test = bytes(''.join(sample(s, 10)), "utf8")
    if crc32(test) == checksum:
        print(test)
        break
        

end = time()

print(f"Total exection time: {end-start}")
