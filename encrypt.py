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

def encrypt(m, e, n):
	c = sqmmodular(m, e, n)
	return c

#driver function
fh = open("plaintext.txt", "r")
FIle = open("ciphertext.txt", "w")
m = int(fh.read())
tes = []
with open("public_key.txt") as my_file:
    tes = my_file.readlines()
print ("e = ", tes[0])
print ("n = ", tes[1])
e = int(tes[0])
n = int(tes[1])
enc = encrypt(m,e,n)
FIle.write(str(enc))
fh.close()
FIle.close()

