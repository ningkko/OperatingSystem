import curses
from curses import KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN
from random import randint
from snake import Snake
from network import Network
import ast
import json

class Game:
    def __init__(self):

        curses.initscr()
        self.win = curses.newwin(20, 60, 0, 0)
        self.net = Network()
        position, score, food, lose, key, has_p2 = self.parse_data(self.net.data)
        self.key = key
        self.snake1 = Snake(position, score, lose, key)
        self.snake2 = None
        self.local_has_p2 = False
        self.food = [0,0]
        self.setup()

    def setup(self):
        """set up a bunch of stuff"""

        curses.noecho()
        curses.curs_set(0)
        self.win.keypad(1)
        self.win.border(0)
        self.win.nodelay(1)
        self.win.addch(self.food[0], self.food[1], '*')
        self.win.timeout(int(150 - (3/5 + 3/10)%120))         

    def run(self):
        print("here")
        try:
            print("workinghere")
            # it's the escape key
            while self.key != 27:      
                                                
                # what to draw on the windows
                self.win.border(0)
                self.win.addstr(0, 2, 'Player1 : ' + str(self.snake1.score) + ' ')
                score_snake2 = str(self.snake2.score) if self.snake2 else ""
                self.win.addstr(0, 47, 'Player2 : ' + score_snake2 + ' ')
                self.win.addstr(0, 27, ' SNAKE ')     

                # update prekey
                prevKey = self.key
            
                # is there a new key pressed?
                event = self.win.getch()
                self.key = self.key if event == -1 else event 

                # if new key not what we want
                if not self.key in [KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN]:
                    self.key = prevKey

                # if space is pressed
                if self.key == ord(' '):                                            
                    self.key = -1 

                    while self.key != ord(' '):
                        self.key = self.win.getch()
                    self.key = prevKey
                    continue

                # move your snake 
                self.food = self.snake1.move(self.win, self.food, self.key)

                # update the other snake with network
                position, score, food, lose, key, has_p2 = self.parse_data(self.send_data())
                if has_p2:
                    if self.local_has_p2 == False:
                        self.local_has_p2 = True
                        self.snake2 = Snake(position, score, lose, key)
                    # move the other snake
                    self.snake2.move(self.win, self.food, p2_key)

            curses.endwin()

        finally:
            # tell people you quitted
            self.net.send("Player2 is offline...")
            self.net.close()
            print("Exited.")

        # print out results
        print("\nPlayer1 - " + str(self.snake1.score))
        print("\nPlayer2 - " + str(self.snake2.score))


    def send_data(self):
        """
        Send 
             1. snake.position 
             2. snake.score 
             3. snake.lose 
             4. new food location
             5. key
        to the server

        return: None
        """
        data = {
            'position': self.snake1.position,
            'score': self.snake1.score,
            'lose': self.snake1.lose,
            'food': self.food,
            'key': self.key
        }

        data = json.dumps(data)
        reply = self.net.send(data.encode("utf-8"))
        return reply

    @staticmethod
    def parse_data(data):
        curses.endwin()

        """parse what you get back from thr server"""
        try:

            print("RAW: ", data)
            d = json.loads(data.decode("utf-8"))
            print(d)
            return d['position'], d['score'], d['lose'], d['food'], d['key'], d['has_p2']

        except:
            return [[0,0],[1,0],[2,0]], 0, False, [0,0], -1, False


