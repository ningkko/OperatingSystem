import socket

class Network:

    def init(self):

        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.host = ""
        self.port = 8880
        self.addr = (self.host, self.port)
        #TODO: add conn
        self.conn=self.connect()



    def connect(self):
        self.client.connect(self.addr)
        return self.client.recv(2048).decode()


    def send(self, data):
        try:
            self.client.send(str.encode(data))
            data = self.client.recv(2048).decode()
            return data
        except socket.error as e:
            return str(e)
    def close(self):
        self.client.close()
