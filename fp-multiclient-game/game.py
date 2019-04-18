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

        # set up network and windows
        self.net = Network()
        self.win = curses.newwin(20, 60, 0, 0)
        self.food = [0,0]
        # initial positions of two snakes
        self.snake1 = Snake([[4,10], [4,9], [4,8]])
        self.snake2 = Snake([[14,10], [14,9], [14,8]])

        self.key = KEY_RIGHT

        self.snake1.position, self.snake1.score, self.snake1.lose, self.food = self.parse_data(self.send_data())



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

        try:
            # it's the escape key
            while self.key != 27:      
                                                
                # what to draw on the windows
                self.win.border(0)
                self.win.addstr(0, 2, 'Player1 : ' + str(self.snake1.score) + ' ')
                self.win.addstr(0, 47, 'Player2 : ' + str(self.snake2.score) + ' ')
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
                self.snake2.position, self.snake2.score, self.snake2.lose, self.food , p2_key= self.parse_data(self.send_data())
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
        reply = self.net.send(data)
        return reply

    @staticmethod
    def parse_data(data):
        curses.endwin()

        """parse what you get back from thr server"""
        try:

            print("RAW: ", data)
            d = json.loads(data)
            print(d)
            return d['position'], d['score'], d['lose'], d['food'] ,d['key']

        except:
            return [[0,0],[1,0],[2,0]], 0, False, [0,0]
