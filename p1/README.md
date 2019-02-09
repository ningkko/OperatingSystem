# CSC262P1
Smith College / CSC262 Operating Systems / Cooperative Multitasking Shell in Java

## DEMO

### $ cat test/test.txt
o: unix is great os. unix is opensource. unix is free os.\
o: Unix linux which one you choose.\
o: uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.\
Cat .steps=4 .inputLines=0 .outputLines=4\
ConsolePrinter .steps=4 .inputLines=4 .outputLines=3


### $ pwd
o: /Users/apple/Documents/GitHub/OperatingSystem/p1\
Pwd .steps=1 .inputLines=0 .outputLines=2\
ConsolePrinter .steps=2 .inputLines=2 .outputLines=1


### $ cat test/test.txt | wc 
o: Lines: 3 | Words: 31 | Bytes: 135\
Cat .steps=4 .inputLines=0 .outputLines=4\
WordCount .steps=4 .inputLines=4 .outputLines=2\
ConsolePrinter .steps=5 .inputLines=2 .outputLines=1


### $ echo hello
o: hello\
Echo .steps=1 .inputLines=0 .outputLines=2\
ConsolePrinter .steps=2 .inputLines=2 .outputLines=1


### $ head 2 test/test.txt
o: unix is great os. unix is opensource. unix is free os.\
o: Unix linux which one you choose.\
Head .steps=1 .inputLines=0 .outputLines=3\
ConsolePrinter .steps=3 .inputLines=3 .outputLines=2


### $ tail 2 test/test.txt
o: uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.\
o: Unix linux which one you choose.\
Tail .steps=1 .inputLines=0 .outputLines=3\
ConsolePrinter .steps=3 .inputLines=3 .outputLines=2


### $ cat test/test2.txt
o: satish\
o: harsh\
o: divyam\
o: chitransh\
o: abhishek\
o: rajan\
o: naveen \
Cat .steps=8 .inputLines=0 .outputLines=8\
ConsolePrinter .steps=8 .inputLines=8 .outputLines=7

### $ sort test/test2.txt
o: abhishek\
o: chitransh\
o: divyam\
o: harsh\
o: naveen\
o: rajan\
o: satish\
Sort .steps=1 .inputLines=0 .outputLines=8\
ConsolePrinter .steps=8 .inputLines=8 .outputLines=7

### sort -r test/test2.txt
$ $ o: satish\
o: rajan\
o: naveen\
o: harsh\
o: divyam\
o: chitransh\
o: abhishek\
Sort .steps=1 .inputLines=0 .outputLines=8\
ConsolePrinter .steps=8 .inputLines=8 .outputLines=7


### $ simplegrep unix test/test.txt
o: unix is great os. unix is opensource. unix is free os.\
o: uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.\
SimpleGrep .steps=4 .inputLines=0 .outputLines=3\
ConsolePrinter .steps=4 .inputLines=3 .outputLines=2


### $ regexgrep .nix test/test.txt
o: unix is great os. unix is opensource. unix is free os.\
o: Unix linux which one you choose.\
o: uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.\
RegexGrep .steps=4 .inputLines=0 .outputLines=4\
ConsolePrinter .steps=4 .inputLines=4 .outputLines=3


### $  regexgrep linu. test/test.txt
o: Unix linux which one you choose.\
RegexGrep .steps=4 .inputLines=0 .outputLines=2\
ConsolePrinter .steps=4 .inputLines=2 .outputLines=1


### $ ls
o: <-------- files -------->\
o: CoopShell.iml\
o: .DS_Store\
o: pom.xml\
o: README.md\
o: <----- directories ----->\
o: test\
o: target\
o: .idea\
o: src\
ListFile .steps=1 .inputLines=0 .outputLines=11\
ConsolePrinter .steps=11 .inputLines=11 .outputLines=10


### $ setvar x 10
o: 10\
SetVar .steps=1 .inputLines=0 .outputLines=2\
ConsolePrinter .steps=2 .inputLines=2 .outputLines=1


### $ cd ~
### $ pwd\
o: /Users/apple\
Pwd .steps=1 .inputLines=0 .outputLines=2\
ConsolePrinter .steps=2 .inputLines=2 .outputLines=1

### $ 
