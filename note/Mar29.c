class Lock{
	boolean isUse;
	public Lock(){
		this.isUse = false;
	}


	void lock(){
		while(inUse){
			inUse = true
			yield(); // atomic		
			Thread.sleep(1);// Interrupted exception
		}		
	}

	void unlock(){
		isUse = FALSE;
	}
}

// EASIEST 
disable interupts();// not safe

//critical situation

enable interupts();
void lockWithinterupts();
while(true){
	disable();
	if (!inUse){
		inUse=true;
		break;
	}
	enable();
	yield();
}

// *oldPointer is an address in use
// new is a boolean
int TestAndSet(int *oldPointer, int new){

	// grab the old value
	int old = *oldPointer;
	// set to new
	*oldPointer = new;

	// return f it is used
	return *oldPointer;
}

while(TestAndSet(this.inUse, true) == true){
	yield();
}


// the type is int because int in C is jst the register
int CompareAndSwap(int *ptr, int expected, int new){
	int actual = *ptr;
	if (actual = expected)
	{
		*ptr = new;
	}// invalidate variable in all caches and registers.

	return actual;
}


while(CompareAndSwap(this.inUse,0,1) == 1){
	yield();
}


//cmpswap @7 0,1

register int x;
volatile int x;
// msut use addresses for these variables.
// now C basically ignores these keywords



// LoadLinked, SotoreConditional
// both atomic

//Works like a debugger.
// memory breakpoint 
int LoadLinked(int *ptr){
	return *ptr;
}


// Using the debug functionality to make it happen
int SotoreConditional(int *ptr, int value){
 if (no one has touched this ptr since te last call to LoadLinked){
 	*ptr = value;
 	return 1; // yield change
 }
 else{
 	return 0; // no
 }
}


class TLock(){
	int ticket;
	//int turn;
	//safer to be atomic
	volatile int turn;
}

public Lock(){
	ticket = 0;
	turn = 0;
}



int FetchAndAdd(int *ptr){
	"""
	This's pretty much like java's AtomicInteger()
	.getAndAdd()
	"""
	int old = *ptr; 
	*ptr++;
	return old;
}


void Lock(){

	// int myTicket = ticket++;
	// this has some problem with it. Concurrency!
	int myTicket = FetchAndAdd(this.ticket);
	// thsi is better, whihc is an atomic.
	while(myTicket!=this.turn){
		yield();
	}

	void unlock(){
		turn++;
	}
}


// inpythion
try{
	m.unlock()
}catc{

}finally{
	m.unlock()
	close()
}
// can also wrap up 
// __enter__() and __exit__()



// in java
class TloCK implements Closable{

}
// and when you know that ou want to close it, call close
void close(){
	this.unlock();
}


// in C
void doStuff(void){
	lock(m);

	if (condition){
		goto cleanup;
	}

	doCriticalStuff();
	

	cleanup:
		unclock(m);
		return;

	error:
		printf("...");
		goto cleanup;
}
