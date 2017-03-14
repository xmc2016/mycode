cc=gcc
server=server.c comm.c
client=client.c comm.c
commh=comm.h
.PHONY:all
all:ser cli
ser:$(server) 
	$(cc) -o  $@ $^
cli:$(client) 
	$(cc) -o $@ $^
.PHNOY:clean
clean:
	rm -f ser cli
