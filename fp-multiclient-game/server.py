from socket import *
from thread import *
import json
import sys
from curses import KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN
import curses
import socket


class Player():
    """
    A player class to manage data
    """
    def __init__(self):
        self.connection = None
        self.address = None
        self.data = None


listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = ''
port = 8881
server_ip = socket.gethostbyname(host)
has_p2 = False

snake1_position = [[4,10], [4,9], [4,8]]
snake2_position = [[14,10], [14,9], [14,8]]

# initial data
initial_data1 = {
    'position': snake1_position,
    'score': 0,
    'lose': False,
    "food": [10,20],
    'key': KEY_RIGHT,
    'has_p2': False
}
initial_data2 = {
    'position': snake2_position,
    'score': 0,
    'lose': False,
    "food": [10,20],
    'key': KEY_RIGHT,
    'has_p2': False
}
try:
    server.bind((host, port))

except socket.error as e:
    print(str(e))

server.listen(2)
print("Waiting for connection...")

# create 2 players with no data
global players
players = [Player(), Player()]


def threaded_client(conn):

    try:
        playerid = 1 if players[0].connection == conn else 2

        while True:
            # keep fetching data
            data = conn.recv(2048)
            data = json.loads(data.decode("utf-8"))
            data["has_p2"] = has_p2
            data = bytes(json.dumps(data),"utf-8")

            if not data:
                print("Data missing from player", str(playerid))
                # break

            else:
            	if has_p2:
                    # send data to player 2 if the data is from player 1
                    if playerid == 1:
                        server.sendto(data, players[1].address)

                    # send to p1 if from p2
                    elif playerid == 2:
                        server.sendto(data, players[0].address)

                else: 
                    print("Opponent Left.")


    finally:
        print("Connection Closed")
        conn.close()




while True:

    """Waits for 2 clients to connect"""
    conn, address = server.accept()
    print("Connected to: ", address)


    if not players[0].connection:
        # initialize the first player when there is one connection
        players[0].connection = conn
        players[0].address = address
        players[0].data = initial_data1

        data1 = json.dumps(initial_data1)
        server.sendto(data1.encode("utf-8"),players[0].address)

        print("Player 1 connected.")

    # initialize p2
    elif players[0].connection and not players[1].connection:

        players[1].connection = conn
        players[1].address = address
        players[1].data = initial_data2

        data2 = json.dumps(initial_data2)
        server.sendto(data2.encode("utf-8"),players[1].address)

        print("Player 2 connected.")

        # if both connected, start new threads
        if players[0].connection and players[1].connection:
            has_p2 = True
            start_new_thread(threaded_client, (conn,))
            start_new_thread(threaded_client, (conn,))

            print("Game start.")
            break;


