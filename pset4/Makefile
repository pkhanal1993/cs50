#
# Makefile
#
# Computer Science 50
# Problem Set 4
#

breakout: breakout.c Makefile
	clang -ggdb3 -Ispl/include -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o breakout breakout.c -Lspl/lib -lcs -lm

testfile: testfile.c Makefile
	clang -ggdb3 -Ispl/include -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o testfile testfile.c -Lspl/lib -lcs -lm
    
clean:
	rm -f *.o core breakout
