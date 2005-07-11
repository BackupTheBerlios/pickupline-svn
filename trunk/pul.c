/*
		This is the main function in the program.  It runs the whole show.
		If you follow along with the comments, it should all be pretty clear
		how the program works.
 */


#include"pul.h"

int main()
{
	//  ** make sure you have all the permissions **
	
	setuid(0);
	if(getuid())
	{
		printf("error: you must be root to run this program\n");
		return 0;
	}

	
	//  ** create the database **
	
	struct puldb* mydb;                 // name the database
	mydb=malloc(sizeof(struct puldb));  // allocate the database
	puldbinit(mydb);                // initalize the database

	
	//  ** set the dropline **
	

	int retval; // this is the identifier for the thread
	retval=0;
	
	pthread_t dropline;           // name the dropline thread
	pthread_attr_t sametime;      // name the thread attributes
	pthread_attr_init(&sametime); // init the thread attributes

	pthread_attr_setschedpolicy(&sametime,PTHREAD_INHERIT_SCHED);
		// set the sametime attribute to mean "execute the threads
		// at the same time"
	
	//pthread_create(&dropline,&sametime,line,(void*)mydb); (now a command)
		// start the dropline thread, which will execute the function "line"
		// at the same time as the rest of the program, and pass it a
		// pointer to the pickupline database
	
		
	//  ** await commands **
	
	char buffer[80]; // the input buffer
	

	printf("\npickupline version 0.3.0 (DEFCON edition)\n");
	printf("warning: this version of the code is highly alpha\n");
	printf("for a current release, goto web.pdx.edu/~piercede/cs.pickupline.html\n\n");
	
	while(1)
	{
		printf("> ");            // print the prompt
		fgets(buffer,75,stdin);  // ask for input
		if(strlen(buffer)<3)continue;
		
		if(!strncmp(buffer,"exit\n",10))return 0;
		
		// thread related commands
		else if(!strncmp(buffer,"start\n",10))
		{
			if(retval)printf("**  line has already been dropped\n");
			else retval=pthread_create(&dropline,&sametime,line,(void*)mydb);
		}
		else if(!strncmp(buffer,"stop\n",10))
		{
			printf("\n**  line removed");
			pthread_exit(retval);
			retval=0;
		}
		
		// other stuff
		else if(!strncmp(buffer,"list\n",10))list(mydb);
		else if(!strncmp(buffer,"spoof\n",10))spoof(mydb);
		else if(!strncmp(buffer,"resolvegw\n",15))resolvegw(mydb);
		
		// setting related commands
		else if(!strncmp(buffer,"settings\n",10))settings(mydb);
		else if(!strncmp(buffer,"interface\n",15))interface(mydb);
		//else if(!strncmp(buffer,"gateway\n",15))gateway(buffer,mydb);
		//else if(!strncmp(buffer,"ssid\n",10))interface(buffer,mydb);

		
		// the help command and the error command
		else if(!strncmp(buffer,"help\n",10))help();
		else printf("error: command not found (type 'help' if you need it)\n");
	}
}
