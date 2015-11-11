#include<unistd.h>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

// Class definition for users 

class user
{
	char fname[50];
	char uname[50];
	char passwd[50];
	char mail[50];
	
	public:
	
	void create()
	{
	    cout<<"Please fill in your sign up details below \n\n";
	    cout<<setw(50)<<"Full name :";
	    cin>>fname;
	    cout<<endl<<setw(50)<<"Username :";
	    cin>>uname;
	    cout<<endl<<setw(50)<<"Password :";
	    cin>>passwd;
	    cout<<endl<<setw(50)<<"E-mail :";
	    cin>>mail;
	    cout<<endl;
	}
	
	void display()
	{
		cout<<"Your profile is described below \n\n";
		cout<<setw(50)<<"Full name :"<<fname;
		cout<<setw(50)<<"Username  :"<<uname;
		cout<<setw(50)<<"Password  :"<<passwd;
		cout<<setw(50)<<"E-mail    :"<<mail<<endl;
	}
	
	char* rfname()
	{
		return(fname);
	}
	
	char* runame()
	{
		return(uname);
	}
	
	char* rmail()
	{
	 	return(mail);
	}
	
	char* rpasswd()
	{
		return(passwd);
	}
};	

// To check if a particular file exists

bool fexists(const char *filename) 
{
	ifstream ifile(filename);
    return ifile;
}

// Performs a search for the entered word

void search()
{
	string dir;
	dir="./Dictionary";
	chdir(dir.c_str());
	cout<<"Enter the word you want to search :";
	char word[50];
	char script[30],path[30];
	cin>>word;
	
	if(fexists(word))
	{
		sprintf(script,"gedit %s",word);
		system(script);
	}
	else
	{
	    dir="..";
	    chdir(dir.c_str());
	    fstream update;
        update.open("update.txt",ios::out|ios::app);
		cout<<"This word is currently not in the database.It will be added soon."<<endl;
		update<<word<<endl;
		update.close();
	}
}

// Adds the entered word to the offline database directory called Dictionary

void add(char* n)
{
	cout<<"The word you want to add is :"<<n;
	char script[20],move[30];
	sprintf(script,"./output %s",n);
	system(script);
	sprintf(move,"mv ./%s ./Dictionary",n);
	system(move);
}

// To display list of most searched words

void list()
{



}

// Admin modules

void admin()
{
    int choice,flag=0;
    label:
	system("clear");
	char temp[40];
	cout<<setw(50)<<"Username :Admin";
	cout<<setw(50)<<"Password :";
	cin>>temp;
	if(strcmp(temp,"dictionary")==0)
	{
		cout<<"Login successful";
		cout<<"1. See list of all Honeycomb users";
		cout<<"2. Update words in database";
		cout<<"3. Log out";
		cin>>choice;
		switch(choice)
		{
			case 1:	user obj;
					fstream disp;
					disp.open("accounts.txt",ios::in);
					while(!disp.eof())
					{
						disp.read((char*) &obj,sizeof(obj));
						obj.display();
					}
					disp.close();
					break;
					
			case 2: char m[50];
					fstream find;
					find.open("update.txt",ios::in);
					while(!find.eof())
					{
						find>>m;
						cout<<m;
						add(m);
					}
					cout<<"Words added to database";
					find.close();
					break;
					
			case 3:	flag=1;
		}
		if(flag!=1)
		{
			goto label;
		}
		else
		{
 			exit(0);
 		}			
    }
    else
    {
    	exit(0);
    }
}				
		
// To check if user account exists and provide login modules

void verify_account()
{
    int i=0,flag=0,choice,flag1=0;
    char temp[50],str[50];
	fstream check;
	user account;
	check.open("accounts.txt",ios::in);
	cout<<endl<<setw(50)<<"Enter the login details";
	cout<<endl<<endl<<endl<<endl<<setw(50)<<"Username :";
	cin>>temp;
	cout<<endl<<setw(50)<<"Password :";
	cin>>str;
	while(!check.eof())
	{
		check.read((char*) &account,sizeof(account));
		if((strcmp(account.runame(),temp)==0)&&(strcmp(account.rpasswd(),str)==0))
		{
			cout<<"Login successful";
		    cout<<endl;
		    flag=1;
		}
	}
	if(flag!=1)
	{
		cout<<"Wrong credentials";
	}
	else
	{
	    begin:
		system("clear");
		cout<<"1. Search for the meaning of a particular word";
		cout<<endl<<"2. Check list of most searched words";
		cout<<endl<<"3. Log out"<<endl;
		switch(choice)
		{
			case 1:	search();
			        break;
			       
			case 2: list();
			        break;
			        
			case 3: flag1=1;
		}
		if(flag1!=1)
		{
			goto begin;
		}
		else
		{
			exit(0);
		}
	}	
}
	
// To add a user's account details

void add_account()
{
    int flag=0;
	fstream add;
	add.open("accounts.txt",ios::in|ios::app|ios::out);
	user account,temp;
	account.create();
	while(!add.eof())
	{
		add.read((char*) &temp,sizeof(temp));
		if((strcmp(account.rfname(),temp.rfname())==0)||(strcmp(account.runame(),temp.runame())==0)||(strcmp(account.rmail(),temp.rmail())==0))
		{
			cout<<"Duplication of data.Your account will not be created"<<endl;
			flag=1;
		}
	}
	if(flag!=1)
	{
		add.write((char*) &account,sizeof(account));
	}
	add.close();
	cout<<endl<<"You will now be redirected to the main screen in 3 seconds"<<endl;
}
		    
// To add a little finesse

void border()
{
	for(int i=0;i<100;i++)
	{
		cout<<"x";
	}
}

// The main function of the program
 
int main()
{
    add("hello");
    search();
	/*int choice;
 	start:
 	system("clear");
 	border();
 	cout<<endl<<"\t\t\t\t Honeycomb the offline dictionary"<<endl;
 	border();
 	cout<<endl<<endl<<endl<<endl;
 	cout<<setw(50)<<"1. Sign up"<<endl<<setw(49)<<"2. Log in"<<endl<<setw(48)<<"3. Admin"<<endl<<endl;
 	border();
 	cout<<endl<<endl<<"Choice :";
 	cin>>choice;
 	switch(choice)
 	{
 		case 1:	add_account();
 	            goto start;
 	        
 		case 2: verify_account();
 		        break;
 		        
 		case 3: admin();
    }			
 		*/
  	return(0);	
}

// remaining is list module
