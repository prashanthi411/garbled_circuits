run alice_server from the command line of the device that needs to send the numbers.

A port number should be provided as a command line argument.

Example

	./alice_server <port>

This will allow the program to accept connections on port number <port> of the device.

Client:-

Run bob_client from the command line of the device that needs to receive the numbers.

The ip address of the device running the server and the port number it as accepting connections on should be provided as comand line arguments.

Example

	./bob_client <ip address> <port>

This will allow the program to connect to the given port of the given ip address.

ip address should be 127.0.0.1 when both the connections are being run on the same device.

Both server and clients will be asked to input seeds for random number generation.

The client will be asked to enter b (either 0 or 1) which will indicate their choice.

Sources: 
AES -- https://github.com/kokke/tiny-AES-c/
SHA3 -- https://github.com/mjosaarinen/tiny_sha3
