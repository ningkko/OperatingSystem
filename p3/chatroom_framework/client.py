import sys
import select
import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

HOST = "localhost"
PORT = 12345
# HOST = input("HOST IP: ")
# PORT = int(input("PORT: "))

server.connect((HOST, PORT))

try:
    while True:

        # Get message from the user and send it to the host
        raw_input = input('<You> ')
        if raw_input == "ek":
            server.sendall(bytes("Client left", 'utf-8'))
            server.close()

        data = bytes(raw_input, 'utf-8')

        server.sendall(data)

        # Recv and print return message from host
        data = server.recv(1024)
        print('<Server>  ', data.decode(encoding="ascii", errors="ignore"))

        # Close the socket and connection
finally:
    print("finally:")
    server.close();
