.SUFFIXES: .cpp .o

CC=g++


SRCS=main.cpp\
	pub.cpp

OBJS=$(SRCS:.cpp=.o)
EXEC=qqserverd

all: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
	@echo '-------------ok--------------'

.cpp.o:
	$(CC) -Wall -g -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -f core*

