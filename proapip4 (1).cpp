//Program for processing flight data by Arush Gupta and MVS Aditya, 16th January 2015


#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;
int opt1;
char PASS[6]={'A','R','U','S','H'};  //to be memorized by all    
void pass_word();
ifstream FF1("Flighttest.txt");
ofstream FF2("temp.txt");   
int i;

void fileshift();


class flight
{
		
		 int DepTime;                           //departure time
        char Flightcode[15];
		char Airline[30];
        char Dest[20];                       //Destination
        char Equip[15];

  public:


		int getDepTime()
		{
		 return DepTime;
		}
		

		char*getFlightcode()
		{
		 return Flightcode;
		}



		void infoinput()
		{

		  cout<<"\nDepTime:- ";      cin>>DepTime;               cin.ignore();
		  cout<<"\nFlightcode:- ";   cin.getline(Flightcode,15);          
		  cout<<"\nAirline:- ";      cin.getline(Airline,30);                          
          cout<<"\nDest:- ";         cin>>Dest; 
		  cout<<"\nEquip:- ";        cin>>Equip;

		}


		void showrec()
		{

			cout<<"\nDepTime:- ";      cout<<DepTime;
			cout<<"\nFlightcode:- ";   cout<<Flightcode;
			cout<<"\nAirline:- ";      cout<<Airline;
			cout<<"\nDest:- ";         cout<<Dest; 
			cout<<"\nEquip:- ";        cout<<Equip;
			cout<<"\n\n\n";

		}
}F1,F2;

int findflag=0;

		void findrec(char*Flightcode)                                                    //using flightcode
		{
			cout<<"\nreading from file"<<endl;
			while(FF1)
			{
               FF1.read((char*)&F1,sizeof(F1));
		    	
			  if(!(strcmp(F1.getFlightcode(),Flightcode)))
			  {
				 FF1.seekg(-sizeof(F1),ios::cur);                                                //syntax of cur
				 cout<<"\ninside findrec"<<endl;
				 findflag=1;
				 return;

				 
			  }
			}
			 
		}

        void findrec(int DepTime)                                              //between time interval entered by user
        {
           while(FF1)
			{
                          FF1.read((char*)&F1,sizeof(F1));
                    if(F1.getDepTime()>=DepTime)
                    {
                        F1.showrec();

                    }
			}
        }


		void modifyrec()
		{
			char Flightcode[6];
			cout<<"\nFor modification of record: ";
			cout<<"\nenter flight code: ";cin>>Flightcode;
			cout<<"\nenter details of new record: ";
			F2.infoinput();
            while(FF1)
			{
				 FF1.read((char*)&F1,sizeof(F1));
				 if(strcmp(F1.getFlightcode(),Flightcode))
						FF2.write((char*)&F1,sizeof(F1));
				 else
				 {
					 FF2.write((char*)&F2,sizeof(F2));
				 }
			}
			fileshift();
			F2.showrec();
			cout<<"\nThe record has been modified as above";
		}


		void fileshift()
		{
			FF1.close();
			FF2.close();
			remove("Flighttest.txt");                                                      //extension
			rename("temp.txt","Flighttest.txt");                                           //extension
			FF1.open("Flighttest.txt");   //extension
			FF2.open("temp.txt");

        }
		void insertrec()
		{
			 cout<<"\nFor inserting a record: ";
			 cout<<"\nenter details of record to be inserted: ";
			 F2.infoinput();
			 int DeptTime=F2.getDepTime();
			while(FF1)
			{
				 FF1.read((char*)&F1,sizeof(F1));
				 if(F1.getDepTime()<DeptTime)
						FF2.write((char*)&F1,sizeof(F1));
				 else
						{
							FF2.write((char*)&F2,sizeof(F2));
							break;
				        }
			}
			while(FF1)
			{
				 FF1.read((char*)&F1,sizeof(F1));
				 FF2.write((char*)&F1,sizeof(F1));
			}
			F2.showrec();
			cout<<"\nThe above record has been inserted";
			
			
			fileshift();
		}

		void deleterec()
		{
			char Flightcode[6];
			cout<<"\nFor deleting a record: ";
			cout<<"\nenter flight code: ";cin>>Flightcode;
			while(FF1)
			{
				 FF1.read((char*)&F1,sizeof(F1));
				 if(strcmp(F1.getFlightcode(),Flightcode))
						FF2.write((char*)&F1,sizeof(F1));
				 else
				 {
					 F1.showrec();
					 cout<<"\nThe above record has been deleted";
				 }
			}
			
			
			fileshift();
		}

		void STAT()
		{
            char Flightcode[7];
			int flag=0;
			cout<<"\nenter flightcode:";
			cin.ignore();
			cin.getline(Flightcode,7);
			cout<<"Flightcode is: "<<Flightcode;
			findrec(Flightcode);
			FF1.read((char*)&F1,sizeof(F1));
			if(findflag==1)
			F1.showrec();
			else
				cout<<"\n!!!record doesn't exist\n";
		}


int flag=0;


void pass_word()
{
	char pw[6];
	cout<<"\nEnter password:- ";
	for(int i=0;i<5;i++)
	{
		pw[i]=getch();
		cout<<"*";
	}
	pw[5]='\0';
	cout<<"\npassword:-"<<pw;
	/*cout<<"\nPASS:-"<<PASS;*/
	getch();
	if(!strcmp(pw,PASS))
        flag=1;
}





   	                                                                                //extension
void main()                                                                         //extension
{
  int opt1;
  system("cls");
  cout<<"Welcome to the Flight database";
  cout<<"\n1.Administrator";
  cout<<"\n2.User";
  int ctr=0;
  cin>>opt1;
   if(opt1==1)
   {
		  pass_word();
          if(flag!=1) 	    
	
				 cout<<"\n Invalid password! Diverting to user \n";
		       
   }
  cout<<"\n1.flight search";
  if(flag==1)
 {
     cout<<"\n2.flight data modification";
     cout<<"\n3.flight data insertion";
     cout<<"\n4.flight data deletion";
 }
 
   
 
  
  int opt2;
  cin>>opt2;
   
   
  switch(opt2)
  { 
   case 1:STAT();
          break;
   case 2:if(flag==1)
           modifyrec();
	      cout<<"\nafter modifyrec";
          break; 
   case 3:if(flag==1)
             insertrec();
         break;
   case 4:if(flag==1)
             deleterec();
         break;
 
   }
 


  getch();
 
}


	
	

