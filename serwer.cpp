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

int port = 1234;

using namespace std;

string haslo;
string encoded;
vector<string> lines;
string passpath = "./Hangman/passwords";
char steps2die = '0';


void makePassword()
{
    encoded = "";

    ifstream infile;
    infile.open(passpath.c_str());
    string line;
    while(getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();

    srand(time(NULL));
    haslo = lines[rand()%lines.size()]; //choosing random password

    cout<< "encoding a password\n";
    for (int i =0; i< haslo.length(); i++) //encoding
    {
        if (haslo[i] == ' ') encoded += ' ';
        else if (haslo[i]<= 'Z' && haslo[i]>='A') encoded += '-';
    }

    
}


void Reset()
{
    haslo = lines[rand()%lines.size()];
    encoded ="";
    steps2die = '0';
}

bool checkWon(string decoded)
{
    if (haslo == decoded) return true;
    return false;
}

bool decode(char c)
{
    string str = "";
    bool ans = false;
    for (int i = 0; i < haslo.length(); i++)
    {
        if (haslo[i] == c) {str += haslo[i]; ans = true;}
        else str += encoded[i];
    }
    encoded = str;
    return ans;
}
 
int main(int argc , char *argv[])
{

    int servSck , cliSck , c;
    struct sockaddr_in server , client;
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


   makePassword();
   cout<<haslo<<"\n"<<encoded<<"\n";

   string steps = ""; steps += steps2die;
   string sendingData = encoded + "." + steps + "1";

   const char *buf= sendingData.c_str();
   string tries = "";
   char rcvBuf[1] = {'0'};
   int n;

   while(1)
   {
        cliSck = accept(servSck, 0, 0);
        if (fork())
	{
            write(cliSck, buf, MAXi);
	    while(1)
            {

                if((n = read(cliSck, rcvBuf, 1)) > 0 )
                {
		    string aTry = "1";
                    cout<<n<< " "<<rcvBuf <<endl; 
                    char rcvd = rcvBuf[0];
                    if (rcvd >= 'A' && rcvd <= 'Z')
                    {
                        if (!decode(rcvd)) {steps2die ++; aTry="0";} 
                        tries+=rcvd;
			sendingData = encoded;
                        string steps = ""; steps += steps2die;
			sendingData += ('.'+steps+aTry+tries+';');
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
   				cout<<haslo<<"\n"<<encoded<<"\n";

				steps2die = '0';
   				steps = ""; steps += steps2die;
   				sendingData = encoded + "." + steps + "1";

   				buf= sendingData.c_str();
   				tries = "";
				write(cliSck, buf, MAXi);
 				break;} //reset

			}

                    }
		    

                }
		else close(cliSck);
		write(cliSck, buf, MAXi);
		if (steps2die == '6') break;

		
            }
	
	}
        
   }

}
    

