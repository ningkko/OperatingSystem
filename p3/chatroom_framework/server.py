from _thread import *
import socket

HOST = 'localhost'
PORT=12345
#PORT = int(input("PORT: "))

# Create a socket using IPv4, and bind and listen on given port


def on_new_client(conn,addr):

    while True:
        data = conn.recv(1024)
        print('<Client: '+str(addr)+'>: ', data.decode(encoding="ascii", errors="ignore"))

        raw_input = input('<You>: ')
        if raw_input == "ek":
            conn.sendall(bytes("Server left",'utf-8'))
            conn.close()
            break
        data = bytes(raw_input,'utf-8')

        conn.sendall(data)
    conn.close()


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print('Server started!')
print('Waiting for clients...')

server.bind((HOST, PORT))
try:
    while True:

        server.listen(5)

        conn, addr = server.accept()
        start_new_thread(on_new_client,(conn,addr))
finally:
    print("finally:")
    server.close()