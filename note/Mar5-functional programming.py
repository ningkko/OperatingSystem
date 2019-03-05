#map
y = [x*2 for x in range(10)]
#filter
y = [x for x in range(10) is is_even(x)]

#functional programming
range(10).map(x->x*2)


start = 0
[1,2,3].reduce((x,y)->x+y,start)
#returns 6
# f(x,y) is a reducer
list = [1,2,3]
int start = start
int x = list[0]
for (i=start;i<list.size();i++)
	x = f(x,list[:])

# count how many time a word shows up
Map<String,Integer> wordCount(List<String> input){
	Map output;

	for (w in input):
		if w in output:
			output.get(w)+=1
		else:
			output.put(w,1)
}

# Can't just use reduce here
# But we can do use MapReduce
#[a,b,a,c] ->map [(a,1),(b,1),(a,1),(c,1)]
# ->sort [(a,1),(a,1),(b,1),(c,1)]
# ->reduce [(a,2),(b,1),(c,1)]







