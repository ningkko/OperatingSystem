
'''
Built from https://gist.github.com/sanchitgangwar/2158089
'''

import curses
from curses import KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN
from random import randint

def main():

    curses.initscr()
    global win
    win = curses.newwin(20, 60, 0, 0)
    win.keypad(1)
    curses.noecho()
    curses.curs_set(0)
    win.border(0)
    win.nodelay(1)

    # snake 1 direction. Initialized to be moving towards right
    key1 = 100  
    # right, snake 2
    key2 = KEY_RIGHT                                             
    
    score1 = 0
    score2 = 0
    snake1 = [[4,10], [4,9], [4,8]]                                  
    snake2 = [[14,10], [14,9], [14,8]]                                     

    global food
    food = [10,20]                                                     

    win.addch(food[0], food[1], '*')                                

    global move
    move = True                                             


    win.timeout(int(150 - (3/5 + 3/10)%120))                              

    while key1 != 27 and key2 != 27:      
                                            
        win.border(0)
        win.addstr(0, 2, 'Score1 : ' + str(score1) + ' ')                
        win.addstr(0, 47, 'Score2 : ' + str(score2) + ' ')                
        win.addstr(0, 27, ' SNAKE ')     

        prevKey1 = key1
        prevKey2 = key2

        key = win.getch()
        #key = key if event == -1 else event 

        if key in [97, 65, 119,87, 115,83,100 ,68]:     
            
            key1 = key
            key2 = prevKey2

        elif key in [KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN]:
            
            key2 = key
            key1 = prevKey1

        elif key == ord(' '):                                            
            key,key1,key2 = -1 

            while key != ord(' '):
                key = win.getch()
            key1 = prevKey1
            key2 = prevKey2
            continue

        else:
            key1 = prevKey1
            key2 = prevKey2
        
        score1 = move_snake(snake1, key1, 1, score1)
        score2 = move_snake(snake2, key2, 2, score2)

    curses.endwin()

    print(
Score1 -  + str(score1))
    print(
Score2 -  + str(score2))

def move_snake(snake,key,snake_num,score):

    global win
    global food
    global move


    if snake_num == 1:
        snake.insert(0, [snake[0][0] + ((key == 115 or key == 83) and 1) + ((key == 119 or key == 87) and -1), snake[0][1] + ((key == 97 or key == 65) and -1) + ((key == 100 or key ==68) and 1)])


    elif snake_num == 2:
        snake.insert(0, [snake[0][0] + (key == KEY_DOWN and 1) + (key == KEY_UP and -1), snake[0][1] + (key == KEY_LEFT and -1) + (key == KEY_RIGHT and 1)])

    # If snake crosses the boundaries, make it enter from the other side
    if snake[0][0] == 0: snake[0][0] = 18
    if snake[0][1] == 0: snake[0][1] = 58
    if snake[0][0] == 19: snake[0][0] = 1
    if snake[0][1] == 59: snake[0][1] = 1

    # If snake runs over itself
    if snake[0] in snake[1:]: 
            win.addstr(0, 27, 'You Lose')  
            move = False

    if move:
        if snake[0] == food:   
            curses.beep()                                        
            food = []
            score += 1
            while food == []:
                food = [randint(1, 18), randint(1, 58)]                
                if food in snake: food = []
            win.addch(food[0], food[1], '*')

        else:  
            last = snake.pop()                                         
            win.addch(last[0], last[1], ' ')

        win.addch(snake[0][0], snake[0][1], '#')

    return score

main()
