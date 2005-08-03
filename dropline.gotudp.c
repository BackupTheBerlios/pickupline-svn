#include"pul.h"

void gotudp(struct puldb* mydb,const struct pcap_pkthdr* header,const u_char* pkt)
{
	// TODO this can be changed to grab UDP offers as well as acks
	
	if(mydb->gotnetmask==1)return;
	if(pkt[42]!=2)return; // make sure this is from the gateway
	
	//fprintf(stderr,"%d\n",pkt[278]);
	//if(pkt[294]==5); // this is a dhcp ack
	//else return;

	u_char netmask[4];
	u_char gwip[4];
	
	netmask[0]=pkt[311];
	netmask[1]=pkt[312];
	netmask[2]=pkt[313];
	netmask[3]=pkt[314];
	
	gwip[0]=pkt[317];
	gwip[1]=pkt[318];
	gwip[2]=pkt[319];
	gwip[3]=pkt[320];
	
	fprintf(stderr,"\n** got the netmask (%u.%u.%u.%u)",
			netmask[0],netmask[1],netmask[2],netmask[3]);
	memcpy(mydb->netmask,netmask,4);
	mydb->gotnetmask=1;

	if(mydb->gotgwip==1)return;
	fprintf(stderr,"\n** got the gateway IP (%u.%u.%u.%u)",
			gwip[0],gwip[1],gwip[2],gwip[3]);
	memcpy(mydb->gwip,gwip,4);
	mydb->gotgwip=1;
}
