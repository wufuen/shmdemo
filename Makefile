LDFLAGS = -lrt
shm_rb : shm_rb.o
	gcc shm_rb.o -o shm_rb $(LDFLAGS)

all : shm_rb
	echo "compile"
clean :
	rm shm_rb
