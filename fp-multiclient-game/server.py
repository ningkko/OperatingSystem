
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
            try:
                # keep fetching data
                data = conn.recv(2048)

                if not data:
                    print("Data missing from player", str(playerid))
                    break

                else:
                    # send data to player 2 if the data is from player 1
                    if playerid == 1:
                        sendto(data, players[1].address)

                    # send to p1 if from p2
                    elif playerid == 2:
                        sendto(data, players[0].address)                    
            
            except:
                break

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

        sendto(json.dumps(initial_data1),players[0].address)

        print("Player 1 connected.")

    # initialize p2
    elif players[0].connection and not players[1].connection:

        players[1].connection = conn
        players[1].address = address
        players[1].data = initial_data2

        sendto(json.dumps(initial_data2),players[1].address)

        print("Player 2 connected."
