#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sys/shm.h>
#include <string.h>

#define CHAR_ARRAY_LENGTH 50

int port = 1234;
int max_graczy = 16;

using namespace std;

vector<string> lines;
string passpath = "./Hangman/passwords";

typedef struct 
{
char haslo[CHAR_ARRAY_LENGTH];
char encoded[CHAR_ARRAY_LENGTH];
char tries[CHAR_ARRAY_LENGTH]; int try_it;
char steps2die;
}gameInfo;

gameInfo *gI;
int haslo_length;


void encode(string pom)
{
    for (int i =0; i< haslo_length; i++) //encoding
    {
        gI -> haslo[i] = pom[i];
        if (gI -> haslo[i] == ' ') gI -> encoded[i]= ' ';
        else if (gI -> haslo[i]<= 'Z' && gI -> haslo[i]>='A') gI -> encoded[i]= '-';
    }
}

void makePassword()
{
    //gI -> encoded = "";

    ifstream infile;
    infile.open(passpath.c_str());
    string line;
    while(getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();

    srand(time(NULL));
    string pom = lines[rand()%lines.size()]; //choosing random password
    haslo_length = pom.length();

    encode(pom);


    
}


void Reset()
{
    string pom = lines[rand()%lines.size()];
    haslo_length = pom.length();
    encode(pom);
    gI -> steps2die = '0';
}

bool checkWon(string decoded)
{
    for (int i=0; i< haslo_length; i++)
    {
        if (gI -> haslo[i] != decoded[i]) return false;
    }
    return true;
}

bool decode(char c)
{
    char str[CHAR_ARRAY_LENGTH];
    bool ans = false;
    for (int i = 0; i <  haslo_length; i++)
    {
        if (gI -> haslo[i] == c) {str[i] = gI -> haslo[i]; ans = true;}
        else str[i] = gI -> encoded[i];
    }
    for (int i = 0; i <  haslo_length; i++) gI -> encoded[i] = str[i];

    cout<< "encoded " << gI -> encoded <<endl;
    
    return ans;
}
 
int main(int argc , char *argv[])
{

    int servSck , cliSck ;
    struct sockaddr_in server;
    int MAXi = 150;

    //create socket
    servSck = socket(AF_INET , SOCK_STREAM , 0);
    if (servSck == -1)
    {
        printf("Blad tworzenia socketa");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
	
    const int one = 1;
	setsockopt(servSck, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    //Bind
   if( bind(servSck,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind nie dziala");
	exit(1);
    }
    puts("bind dziala");

    listen(servSck, 10);

   int pamiec_graczy;
   pamiec_graczy = shmget(IPC_PRIVATE, sizeof(gameInfo)*max_graczy, IPC_CREAT | 0600);//Pamiec wspoldzielona dla serwera
   if(pamiec_graczy==-1)
       {printf("Blad przy tworzeniu pamieci dla serwera");}
   gI = (gameInfo*)shmat(pamiec_graczy,NULL,0);
   makePassword();
   cout<< gI -> haslo;


   

   char sendingData[CHAR_ARRAY_LENGTH*2];
   for(int i=0; i<haslo_length; i++) sendingData[i] = gI -> encoded[i];
   sendingData[haslo_length] = '.';
   sendingData[haslo_length+1] = gI -> steps2die;
   sendingData[haslo_length+2] = '1';
   sendingData[haslo_length+3] = ';';

   char buf[CHAR_ARRAY_LENGTH*2]; for(int i=0;i<CHAR_ARRAY_LENGTH*2;i++)buf[i]= sendingData[i];
   char rcvBuf[1] = {'0'};
   int n;
   gI -> steps2die = '0';
   gI -> try_it = 0;

   while(1)
   {
        cliSck = accept(servSck, 0, 0);
        if (fork())
	{
	    gI =  (gameInfo*)shmat(pamiec_graczy,NULL,0);
            cout<< "sending1 " << buf <<endl;
            write(cliSck, buf, MAXi);
	    while(1)
            {

                if((n = read(cliSck, rcvBuf, 1)) > 0 )
                {
		    char aTry = '1';
                    char rcvd = rcvBuf[0];
                    puts("\nnew letter: "); cout<<(rcvd)<<endl; puts("\n");
                    if (rcvd >= 'A' && rcvd <= 'Z')
                    {
                        if (!decode(rcvd)) {gI -> steps2die ++; aTry='0';} 
                        gI -> tries[gI -> try_it] =rcvd; 
                        gI -> try_it += 1;
                        for (int i=0;i<haslo_length;i++ ) sendingData[i] = gI -> encoded[i];
                        sendingData[haslo_length] = '.';
                        sendingData[haslo_length+1] = gI -> steps2die;
                        sendingData[haslo_length+2] = aTry;
                        for (int i= 0; i<= gI->try_it; i++) sendingData[i+haslo_length+3] = gI -> tries[i];
                        sendingData[haslo_length + gI->try_it + 3] = ';';
                        cout << "with ; " << sendingData<<endl;
                    }
                    else if (rcvd >= '0' && rcvd <= '9')
		    {
			cout<< "second option\n";
			int option = rcvd - '0';
			cout<< "option "<<option << endl;
			switch(option)
			{
			    case 1: {
				cout<<"switch\n";
				makePassword();
   				cout<<gI -> haslo<<"\n"<<gI -> encoded<<"\n";

				gI -> steps2die = '0';
                    		for (int i=0;i<haslo_length;i++ ) sendingData[i] = gI -> encoded[i];
                        	sendingData[haslo_length] = '.';
                        	sendingData[haslo_length+1] = gI -> steps2die;
                        	sendingData[haslo_length+2] = '1';
				sendingData[haslo_length+3] = ';';
				memset(&(gI -> tries)[0], 0, sizeof(gI -> tries));
				//for(int i=0;i<gI->try_it;i++) gI->tries[i] = '\0';
				gI -> try_it = 0;

   				//for(int i=0;i<haslo_length+3;i++) buf[i]= sendingData[i];
				for(int i=0;i<CHAR_ARRAY_LENGTH*2;i++)buf[i]= sendingData[i];
                                cout<< "sending2 " << buf <<endl;
				write(cliSck, buf, MAXi);
 				break;} 

			}

                    }
		    for(int i=0;i<CHAR_ARRAY_LENGTH*2;i++)buf[i]= sendingData[i];
		    cout<< "sending3 " << buf <<endl;
		    write(cliSck, buf, MAXi);
                }
		else close(cliSck);
                
		if (gI -> steps2die == '6') break;

		
            }
	
	}
        
   }

}
    

