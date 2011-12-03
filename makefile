CC=gcc
GTKCOMPILE=`pkg-config --cflags --libs gtk+-2.0`


server:
	$(CC) -ggdb -c $(GTKCOMPILE) src/userInterface/*.c -lpthread -I include/
	$(CC) -ggdb -c $(GTKCOMPILE) src/Database/*.c -lpthread -I include/
	$(CC) -ggdb -c $(GTKCOMPILE) src/networking/*.c -lpthread -I include/ 
	$(CC) -ggdb -c $(GTKCOMPILE) src/*.c -lpthread -I include/
	$(CC) -ggdb  $(GTKCOMPILE) *.o -lpthread -o server -I include/
	echo "USAGE ./server portno"
	rm *.o

client:
	$(CC) -ggdb -c $(GTKCOMPILE) src/userInterface/*.c -lpthread -I include/ -D CLIENT
	$(CC) -ggdb -c $(GTKCOMPILE) src/Database/*.c -lpthread -I include/	-D CLIENT
	$(CC) -ggdb -c $(GTKCOMPILE) src/networking/*.c -lpthread -I include/ -D CLIENT
	$(CC) -ggdb -c $(GTKCOMPILE) src/*.c -lpthread -I include/	-D CLIENT
	$(CC) -ggdb  $(GTKCOMPILE) *.o -lpthread -o client -I include/
	echo "USAGE ./client portno hostname"	
	rm *.o
	
server_debug:
	$(CC) -ggdb -c $(GTKCOMPILE) src/userInterface/*.c -lpthread -I include/ -D DEBUG
	$(CC) -ggdb -c $(GTKCOMPILE) src/Database/*.c -lpthread -I include/	-D DEBUG
	$(CC) -ggdb -c $(GTKCOMPILE) src/networking/*.c -lpthread -I include/ -D DEBUG
	$(CC) -ggdb -c $(GTKCOMPILE) src/*.c -lpthread -I include/	-D DEBUG
	$(CC) -ggdb  $(GTKCOMPILE) *.o -lpthread -o server_debug -I include/
	echo "USAGE ./server portno"
	rm *.o
	
.PHONY:clean
clean:
	rm -f client
	rm -f server_debug
	rm -f server
