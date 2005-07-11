CC = gcc -g
OBJS = cmd.help.o cmd.interface.o cmd.list.o cmd.resolvegw.o cmd.settings.o cmd.spoof.c puldb.init.o line.addtarget.o line.gotpacket.o line.o pul.o
LIBS = -lpcap -lpthread
OFLAGS = -O3

pul: $(OBJS)
	$(CC) -g $(OFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f *.o pul

install: 
	cp -v pul /usr/sbin/

poop:
	printf "poop!\n"
