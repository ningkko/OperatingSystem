// This is nearly the smallest C program in the world.
#if 0
  this works as comment.
#endif

//when #indeclde, copy paste from anotehr file.
//if in another file, just type #include "guessingGame.c", it will also be a guessing game.

//There is no scoping.
//C does not have boolean til 1999, now it still doesn't, but it has a file that defines booleans.
//Like 
//#define true 1
//define false 0


#include <stdio.h>
#include <stdbool.h>

// get access to the system and generate random
#include <time.h>
#include <stdlib.h>
// void is here because no argument means going to take infinite many arguments
int main(void) {

    srand(time(NULL));
    int secret=rand()%100;
  puts("Welcome to the guessing game");
  
  while(true){
    // print a prompt
    printf("Type your guess and press ENTER\n");

    //fflush() is typically used for output stream only.
    //Its purpose is to clear (or flush) the output buffer and move the buffered data to console (in case of stdout) or disk (in case of file output stream).
    fflush(stdout);

    //create and fill a guess variable

    int guess =0;
    int status =scanf("%d",&guess);

    if(status!=1) break;
    
    printf("Your guess: %d\n",guess);

    if(secret==guess){
      puts("Congrats! You got it");
      break;
    } else if (secret < guess){
      puts("Too high");
    } else{
      puts("Too low!");
    }
  }
  return 0;
}
