#include"pul.h"

extern void gotpkt(struct puldb*,const struct pcap_pkthdr*,const u_char*);

void* line(struct puldb* mydb)
{
	char cmdbuf[40];
	sprintf(cmdbuf,"ifconfig %s up",mydb->interface);
	system(cmdbuf);
	
	//  ** set up all the pcap goodness **
	
	pcap_t* handle;
	char    errbuf[PCAP_ERRBUF_SIZE];
	struct  bpf_program filter;
	char    filterstring[30]; // the bpf filter

	bpf_u_int32 mask;
	bpf_u_int32 net;

	struct pcap_pkthdr header;
	u_char* packet;

	fprintf(stderr,"\n**  listening on '%s'",mydb->interface);
	pcap_lookupnet(mydb->interface,&net,&mask,errbuf);

	if(handle=pcap_open_live(mydb->interface,BUFSIZ,1,0,errbuf));
	else printf("** error: %s\n",errbuf);
	
	strncpy(filterstring,"tcp",8);
	pcap_compile(handle,&filter,filterstring,0,net);
	pcap_setfilter(handle,&filter);

	while(1) // begin to slowly gather the data (slow==safe)
	{
		pcap_loop(handle,1,gotpkt,mydb); // get a packet
		//sleep(1);                                  // wait a second
	}
}
