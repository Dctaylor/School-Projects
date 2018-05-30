CC	= g++

all: test exam

# Used for manually testing the functionality of the sequence.
test: bagtest.cxx bintree.h bintree.template bag6.h bag6.template
	$(CC) bagtest.cxx -o test

# Used for automatically evaluates and scores the functionality of the sequence.
exam: bagexam2.cxx bintree.h bintree.template bag6.h bag6.template
	$(CC) bagexam2.cxx -o exam

clean:;	rm -f test exam
