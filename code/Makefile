OBJS = %.o

#실행 파일 이름 
TARGET_SERVER = Server
TARGET_CLIENT = Client

#SUFFIXES : 
.SUFFIXES : .c .o

.PHONY: clean 


all : $(TARGET_SERVER) $(TARGET_CLIENT)

server : 
	$(CC) -c server.c -lpthread
	$(CC) -o $@ server.c -lpthread
#	echo $@  $@ : 현재 Target의 이름

client : 
	$(CC) -c client.c
	$(CC) -o $@ client.c 
	
$(TARGET_SERVER) : server.o 
	$(CC) -o $(TARGET_SERVER) server.c -lpthread

$(TARGET_CLIENT) : client.o
	$(CC) -o $@ client.c


clean_server :
		rm -f server.o  $(TARGET_SERVER)

clean_client : 
		rm -f client.o $(TARGET_CLIENT)
		
clean :
	    rm -f $(OBJS) $(TARGET_SERVER) $(TARGET_CLIENT)


