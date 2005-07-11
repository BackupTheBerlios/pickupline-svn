struct puldbnode // this contains information on the targets
{
	char ip[4];  // the ip of the target
	char mac[6]; // the mac of the target

	struct puldbnode* next; // this points to the next target in the list
};

struct puldb
{
	char interface[10]; // the default is "eth1"

	int  gotgwmac; // do we have the mac of the gateway?
	int  gotgwip;  // do we have the ip  of the gateway?

	char gwmac[6];    // the mac of the gateway
	char gwmacalt[6]; // another possible mac for the gateway
	char gwip[4];     // the ip of the gateway
	
	struct puldbnode* head; // this is the first in the linked list of tagets
};
