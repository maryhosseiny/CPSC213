CFLAGS += -std=gnu11 -g 
EXES	= BinaryTree
OBJS = BinaryTree.o

all: $(EXES)
clean:
	rm -f $(OBJS) $(EXES)
tidy:
	rm -f $(OBJS)

BinaryTree: BinaryTree.o
BinaryTree.o: BinaryTree.c

# don't treat all and clean a s file targets
.PHONY: all clean
