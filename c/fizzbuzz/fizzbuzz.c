#include <stdio.h>

// Fizz-Buzz is a famous interview problem.
// We will do it to learn how to write a text file in C.
//
//
// Print the numbers from 0 to 100 (inclusive) to the file "fizzbuzz.txt" EXCEPT:
//  - If the number is divisible by 3, print "Fizz".
//  - If the number is divisible by 5, print "Buzz".
//  - If the number is divisible by both, print "FizzBuzz".
// Do not output blank lines.
//
int main(void) {
  const int N = 100;
  int i=0;
  // Open a file for writing.                                                   
  FILE* out = fopen("fizzbuzz.txt", "w");
  while(1){
    if(i>N){
      break;
    }
    if(i%3==0&&i%5==0){
      fprintf(out,"%d FizzBuzz\n",i);
    }else if(i%3==0){
      fprintf(out,"%d Fizz\n",i);
    }else if(i%5==0){
      fprintf(out,"%d Buzz\n",i);
    }else{
      fprintf(out,"%d\n",i);
    }
    i++;
  }

  // We need to close the file we're writing to, otherwise we may lose data.
  fclose(out);
  // Tell the shell/terminal that we were successful.
  return 0;
}
