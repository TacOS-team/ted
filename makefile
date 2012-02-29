TARGET  := ted
SRCS    := file.c line.c tty.c main.c
OBJS    := ${SRCS:.c=.o} 

CCFLAGS = -Wall -Iinclude/
LDFLAGS = 
LIBS    = 

.PHONY: all clean distclean 
	all:: ${TARGET} 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: source/%.c 
	${CC} ${CCFLAGS} -o $@ -c $< 

clean:: 
	-rm -f ${OBJS} ${TARGET} 

distclean:: clean
