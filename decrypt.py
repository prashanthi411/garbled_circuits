#!/usr/bin/env python
'''key-generator program'''
import random  
def sqmmodular(x, y, p): 
	print ("entering sqmm")
	binrep = []
	size = 0
	while(y!=0):
		binrep.append(y%2)
		y = int(y/2)
		size+=1
	#binrep.reverse()
	exp = 1

	for i in range(size-1, -1, -1):
		exp = ((exp%p)*(exp%p))%p
		if (binrep[i]==1):
			exp = ((exp%p)*(x%p))%p

	return exp

def decrypt(c, d, n):
	m = sqmmodular(c, d, n)
	return m

#driver function
FIle = open("ciphertext.txt", "r")
fh = open("deciphertext.txt", "w")
file_key = open("private_key.txt", "r")
tes = []
with open("public_key.txt") as my_file:
    tes = my_file.readlines()
enc = int(FIle.read())
d = int(file_key.read())
n = int(tes[1])
dec = decrypt(enc,d,n)
print ("decrypted message = ", dec)
fh.write(str(dec))
fh.close()
FIle.close()

