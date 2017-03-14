.PHONY:all
all:pro_con pro_con2
pro_con:pro_con.c
	gcc -o $@ $^ -pthread
pro_con2:pro_con2.c
	gcc -o $@ $^ -pthread
.PHONY:clean
clean:
	rm -f pro_con pro_con2
