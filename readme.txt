public_key.txt contains n in the first line and e in the second line
private_key.txt contains n in the first line and d in the second line
rsa.h contains common functions required for rsa implementation using gmp
1. run keygen.c to generate e,d and n

2. run alice_ot1.c to generate x_0 and x_1
randomx.txt is the file to store randomly generated x_0 and x_1 (on separate lines).
the executable for alice_ot1 is alice1

3. run bob_ot1.c to generate Bob's private key k, the bit b, and c
bob_c.txt is the file where c is generated --> c = (x_b + k^e) mod n
bob_private.txt is the file that stores the private key k and the bit b 
the executable for bob_ot1 is bob1

4. now run alice_ot2.c to calculate v_0 (v_0 = (c – x_0)^d mod n) and v_1 (v_1 = (c – x_0)^d mod n) and encrypted messages m’_0 and m’_1 such that m’_0 = (m_0 – v_0) and m’_1 = (m_1 – v_1)
strings.txt contains two strings (m_0 and m_1, one of which is to be shared by oblivious transfer)
enc_messages.txt should contain m'_0 (m'_0 = m_0 - v_0) and m'_1 (m'_1 = m_1 - v_1)
the executable for alice_ot2.c is alice2

5. now run bob_ot2.c to get the final message, m_b (m_b = m’_b + k)
bob_message.txt contains the final message that Bob receives
the executable for bob_ot2.c is bob2
