import curses
from curses import KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN
from random import randint

class Snake:

    def __init__(self, position):

        self.position = position
        self.score = 0
        self.canMove = True
        self.lose = False

    def move(self, win, food, key):

    
        self.position.insert(0, [self.position[0][0] + (key == KEY_DOWN and 1) + (key == KEY_UP and -1), self.position[0][1] + (key == KEY_LEFT and -1) + (key == KEY_RIGHT and 1)])

        # If snake crosses the boundaries, make it enter from the other side
        if self.position[0][0] == 0: self.position[0][0] = 18
        if self.position[0][1] == 0: self.position[0][1] = 58
        if self.position[0][0] == 19: self.position[0][0] = 1
        if self.position[0][1] == 59: self.position[0][1] = 1


        # Exit if snake crosses the boundaries 
        #if snake[0][0] == 0 or snake[0][0] == 19 or snake[0][1] == 0 or snake[0][1] == 59: 
        #    self.canMove = False
        #    self.lose = True

        # If snake runs over itself
        if self.position[0] in self.position[1:]: 

                # lose and stop moving
                self.lose = True
                self.canMove = False  

        if self.canMove:

            # if the snake head touches the food
            if self.position[0] == food:   
                food = []
                self.score += 1

                # generate a new food
                while food == []:
                    food = [randint(1, 18), randint(1, 58)]                
                    if food in self.position: food = []

                win.addch(food[0], food[1], '*')

            else:

                # pop the tail of the snake
                last = self.position.pop()                                         
                win.addch(last[0], last[1], ' ')

            # add a head to the snake (pretend that it's moving)
            win.addch(self.position[0][0], self.position[0][1], '#')

        return food
