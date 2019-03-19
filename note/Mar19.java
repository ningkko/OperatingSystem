// Some ways to deal with synchronizing
// Mutex (lock) , Semaphore ( lock + counter ) for C/C++/Java
// Monitors for java

// Lock: Free Data Structures
// Atomic instructions and lots of theory
// Singly linked list. Only has one pointer, can change the head without anybody stepping in and interuot.

// Synchronized means only one piece of code can run at one time

public void startThreads(){
    final int N = 100000;
    GFX app = this;
    Runnable upTask = () -> {
        for (int i = 0; i<N; i++) {

            // without synchronized, other code pieces will interrupt, and the final number will not end at 0.
            synchronized (app){
                count+=1;
            }
            sleep(0);
       , }
    };

    Runnable downTask = () -> {
        for (int i = 0 ; i<N; i++) {
            synchronized(app){
                count-=1;
            }
        }
        sleep(0);
    }

}

// Another way to solve this

AtomicInteger counter = new AtomicInteger();

// We can also push synchronized in the method
// it's the same as synchronized(this).
// The program will run slower since it makes sure that everything is synchronized in every step.

public synchronized startThreads(){
    final int N = 100000;
    GFX app = this;
    Runnable upTask = () -> {
        for (int i = 0; i<N; i++) {
            count+=1;
        }
        sleep(0);
}

// Channels <-> Buffers. Google Go!
// Actors. Erlang,


// Concurrent Hasmap
