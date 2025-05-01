#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
#include<conio.h>
#include<cstdio>
#include<map>

using namespace std;

ofstream fout;
ifstream fin;
void hmenu();
void smenu();
void login();

 
int choice; 
bool cinfail;
int confirmation; 
string username, password, password2;
// Using map to store username and password
map<string, string>userDb;
//global variable declaration
int k=7,r=0,flag=0;
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


struct date
{
    int mm,dd,yy;
};

void writetofile(string username){
    ofstream writefile;
    string file = username+".txt";
    writefile.open(file.c_str());
    writefile << password;
    writefile.close();
    hmenu();
	}
    
void login()
{
    cout<<"\n\t\t Enter your username: ";
    //cin>>username;
    getline(cin, username);
    //cin.ignore(10000,'\n');     // Ignores newline character left by cin
    cout<<"\t\t Enter your password: ";
    //cin>>password;
    getline(cin, password);
    // Checks if the username exists in the database
    /*if (userDb.find(username) == userDb.end()) 
	{
        cout<<"\n\t\t Invalid USER NAME or PASSWORD!\n\n"<<endl; //i.e. unregistered username
        cout<<"\t\tPlease Enter any key to Continue..\n\t\t";
        //login();
        getch();
        hmenu();
    }
    // Check if the password matches the username}
    if (userDb[username] != password) 
	{
        cout<<"\n\t\t  Invalid password!"<<endl;
        cout<<"\t\tPlease Enter any key to Continue..\n\t\t";
        getch();
        hmenu();
        //login()};*/
	
    
    // Login successful
    cout<<"\n\t\tLogin successful."<<endl;
    cout<<"\n\t\tPlease Enter any key to Continue..\n\t\t";
	getch();
    smenu();
	}
	
void registerpassword()
{
    cout << "\n\n\t\tEnter your password Please: ";
    cin >> password;
    cout << "\t\tConfirm your password Please: ";
    cin >> password2;
    if (password == password2)
	{
		cin.clear();
        cin.ignore(10000,'\n');
        writetofile(username);
        // Adds the new user to the database
    	//userDb[username] = password;
    	cout << "\n\n\t\tNew User created successfully.\n\n" << endl;
    	cout<<"\n\t\tPlease Enter any key to Continue..\n\t\t";
        cin.clear();
        cin.ignore(10000,'\n');
		
		//getch();
        hmenu();
    }
    else{
        cout << "\n\t\tSorry! Invalid password.." << endl;
        //1 to register password 2 to go back to h menu
        
        registerpassword();
    	}
	}
void registerme()
{  
    cout<<"\n\n\t\tPlease enter your username: ";
    getline(cin, username);
    cin.ignore(10000,'\n');
    cout << "\n\n\t\tUsername \""<< username << "\" Confirm? \n\t\t[1] Yes\t\t\t[2] No\n\t\t";
    //cout << "\n\n\t\tConfirm Username? \n\t\t[1] Yes\t\t\t[2] No\n\t\t";
    cin >> confirmation;
    cin.ignore(10000,'\n');
            
            /*fstream userDb;
			userDb.open("userDb.dat",ios::binary|ios::app);  //userDb.open("userDb.dat", ios::out); same thing
			userDb << "Guru99";
			userDb.close();
            */

	//{	// Check if the username already exists
    	/*if (userDb.find(username) != userDb.end()) 
		{
        	cout << "Username already exists." << endl;
        return;
    	}*/
       
    	switch (confirmation) 
		{
            case 1:
                if (confirmation == 1)
                     registerpassword();
                break;
            case 2:
                cout << "\n\n\t\tSorry!.. User name cancelled..\n\n" << endl;
       	   		cout << "\n\n\t\tPlease Press any to Continue...\n\t\t";
       	   		getch();
        	   /*cin.clear();
        	   	 cin.ignore(10000,'\n'); -- both lines works as getch() but has other job as well*/
        	   	hmenu();
                break;
            default:
                cout<<"\n\t\t  Please enter valid choice!\n\n"<<endl;
                cout << "\n\t\tPlease Press any key to Continue...\n\t\t";
                getline(cin, username);
    			cin.ignore(10000,'\n');
	   			hmenu();
                break;
        }
	}
	
class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        cout<<"\n\t\tItem No                        : ";
        cin>>itemno;
        cout<<"\n\t\tName of the item               : ";
        cin>>name;  //gets(name);
        cout<<"\n\t\tManufacturing Date(dd-mm-yy)   : ";
        cin>>d.mm>>d.dd>>d.yy; //gets(date)
    }
    void show()
    {
        cout<<"\n\t\tItem No                        : ";
        cout<<itemno;
        cout<<"\n\t\tName of the item               : ";
        cout<<name;
        cout<<"\n\t\tManufacturing Date(dd-mm-yy)   : ";
        cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    int retno()
    {
        return(itemno);
    }
};
class amount: public item
{
    float price,qty,tax,gross,dis,netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;
void amount::add()
{
    item::add();
    cout<<"\n\t\tPrice: ";
    cin>>price;
    cout<<"\n\t\tQuantity: ";
    cin>>qty;
    cout<<"\n\t\tTax percent: ";
    cin>>tax;
    cout<<"\n\t\tDiscount percent: ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross=price+(price*(tax/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\t\tNet amount: ";
    cout<<netamt;
    fin.close();
}
void amount::report()
{
    item::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(44,k);
    cout<<tax;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS any key to CONTINUE...";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}
void amount::pay()
{
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************\n";
    show();
    cout<<"\n\t\tPRICE                          : "<<price;
    cout<<"\n\t\tQUANTITY                       : "<<qty;
    cout<<"\n\t\tTAX PERCENTAGE                 : "<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE            : "<<dis;
    cout<<"\n\t\tNET AMOUNT                   Rs. "<<netamt;
    cout<<"\n\t\t*********************************************";
}
void hmenu()
{ 
 		int choice;
 		system("cls"); 
    	system("color F1"); 
    menu:
         cout<<"\n";
         cout<<"\n\t\t************************************"; 
         cout<<"\n\t\t*    SUPERMARKET BILLING SYSTEM    *"; 
  		 cout<<"\n\t\t************************************"; 
  		 cout<<"\n\n\n                                  "; 
  		 cout<<"\n\t\t    -------  MAIN MENU  --------   ";
    	 cout<<"\n                                   ";
  		 cout<<"\n\t\t\t[1] LOGIN  \n\t\t\t  [2] SIGN UP\t"; 
  		 cout<<"\n\t\t\t    [3] Cancel\n"<<endl;
  		 cout<<"\n"; 
  		 cout<<"\n\t\t Enter any of the option: ";
  		 cin>>choice; 
  		 do{
    		cinfail = cin.fail();
    		cin.clear();
    		cin.ignore(10000,'\n');

    		}while(cinfail == true);
			{
        switch (choice) 
		{
            case 1:
                login();
                break;
            case 2:
                registerme();
                break;
            case 3:
                	cout<<" \n\t\t Are you sure to Cancel (Y/N)? \n \t\t";
        		char yn;
        		cin>>yn;
        		if((yn=='Y')||(yn=='y'))
         		{
            	cout<<" \n\n\t        *******  CHEER-UP BUDD... *******\n\n\n";
            	exit(0);
        		}
        		else if((yn=='N')||(yn=='n'))
            		{
            			goto menu;
					}
        		else
        			{
            		  goto menu;
        			}
                break;
            default:
                cout<<"\n\t\t  Please enter valid choice!\n\n"<<endl;
                goto menu;
                break; 
				}
        }
	}
void smenu()
{
	cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"    Super-Market Billing ";
    gotoxy(25,3);
    cout<<"===========================\n\n"<<endl;
    cout<<"\n\t\t[1] Bill Report\n\n";
    cout<<"\t\t[2] Add/Remove/Edit Item\n\n";
    cout<<"\t\t[3] Show Item Details\n\n";
    cout<<"\t\t[4] Logout\n\n";
    cout<<"\n\t\t Please Enter Any Option: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"  Bill Report";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t[1] Invoice\n\n";
        cout<<"\t\t[2] Previous menu\n\n";
        cout<<"\n\t\t Please Enter any Option: ";
        int cho, tdr;
    	float chg;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" INVOICE ";
            gotoxy(30,4);
            cout<<"===========";
            gotoxy(3,6);
            cout<<"ITEM NO";
            gotoxy(13,6);
            cout<<"NAME";
            gotoxy(23,6);
            cout<<"PRICE";
            gotoxy(33,6);
            cout<<"QUANTITY";
            gotoxy(44,6);
            cout<<"TAX %";
            gotoxy(52,6);
            cout<<"DISCOUNT %";
            gotoxy(64,6);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            //q=total quantity ;
            //cout<<"Quantity: \""<<q<<"\"\t\t\t\t\t\tGrand Total 				= "<<gtotal;
            cout<<"\t\t\t\tGrand Total	"<<gtotal;
            cout<<"\n\n\n\t\t\tTender 			: "<<tdr;
            cin>>tdr;
            chg = tdr-gtotal;
            cout<<"\t\t\tChange 			: "<<chg;
            cout<<"\n\t\t\tCashier 		: "<<username;
            cout<<"\n\n\t\t\tTime 			: "<<__TIME__;
            cout<<"\n\t\t\tDate 			: "<<__DATE__;
			cout<<"\n\n\n\n\t\t\tPlease Press any Key to Continue..\n\n";
            getch();
            fin.close();
            /*
void shopping::receipt()
{

    fstream data;
    int arrc[1000];
    int arrq[1000];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;
    cout << "\n\n\t\t\tList of Products            ";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Empty database !!!!!!";
    }
    else
    {
        data.close();
        list();
        cout << "\n___________________________________________________________\n";
        cout << "\n___________________________________________________________\n";
        cout << "\n                   Please place the order                  \n";
        cout << "\n___________________________________________________________\n";
        cout << "\n___________________________________________________________\n";
        do
        {
        m:
            cout << "Enter Product code :";
            cin >> arrc[c];
            cout << "\n\n Enter the product quantity : ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\n Duplicate product code. Please try again";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Do you want to buy another product? if yes then press y else no : \t\t\n\n";
            cin >> choice;
        } while (choice == 'y');
       
        time_delay(5);
        system("cls");
        cout << "\n\n_________________________________________RECEIPT___________________________________________\n";
        cout << "\nProduct No \t Product Name\t product quantity\tprice\t\tAmount\t\tAmount with discount\n";
        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    dis = amount - (amount * dis / 100);
                    total = total + dis;

                    cout << "\n"
                         << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
    }
    cout << "\n\n____________________________________________________________________________________________";
    cout << "\n                                Total Amount :" << total << endl;
    cout << "\n\n";*/
    
    
            goto ss;
        }
        if(cho==2)
        {
            goto menu;
        }
        if(cho!=1 || cho!=2)
		{
		   cout<<"\n\t\t Please Enter Valid Option!\n\n\t\t";
		   cout<<"\n\t\tPlease Press any key to Continue..";
		   getch();
		   goto ss;	
		}
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Editor";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t[1] Add Item Details\n\n";
        cout<<"\t\t[2] Edit Item Details\n\n";
        cout<<"\t\t[3] Delete Item Details\n\n";
        cout<<"\t\t[4] Previous Menu\n\n ";
        cout<<"\n\t\tPlease Enter Any Option: ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\tItem Added Successfully!";
            cout<<"\n\n\t\tPlease Press any key to Continue..";
            getch();
            goto db;
        case 2:
            int ino;
            flag=0;
            cout<<"\n\t\tEnter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\t\tFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\t  Current Detail";
                        cout<<"\n\t\t=================";
                        amt.show();
                        cout<<"\n\n\n\t\t  Enter New Detail";
                        cout<<"\n\t\t====================";
                        amt.add();
                        cout<<"\n\n\n\t\t  Editted Item Detail";
                        cout<<"\n\t\t=======================";
                        fin.open("itemstore.dat",ios::binary);
                        amt.show();
                        cout<<"\n\n\t\tPlease Press any key to Continue..";
                		getch();
                		goto db;
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tItem No does not exist!..";
                cout<<"\n\t\tPlease Press any key to Continue..";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;
        case 3:
            flag=0;
            cout<<"\n\t\tEnter Item Number to be deleted :";
            cin>>ino;
            
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\t\tFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
               {cout<<"\n\t\tItem Deleted Succesfully..";
                cout<<"\n\n\t\tPlease Press any key to Continue..";}
            else if (flag==0){
                cout<<"\n\t\tItem does not Exist!";
                cout<<"\n\n\t\tPlease Press any key to Continue..";}
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\t\tPlease enter valid option!";
            cout<<"\n\n\t\tPlease Press any key to Continue..";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        /*flag=0;
        int ino;
        cout<<"\n\t\tEnter Item Number :";
        cin>>ino;*/
        
        
        /*fstream Purchase_history;
        fstream Purchase_details;
        fstream item_details;
		item_details.open("item_details", ios::out);
		
		my_file.close(); */
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\t\tFile Not Found...\n\t\tProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        /*while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tItem does not exist...";*/
            cout<<"\n\n\n\t\tPlease Press any key to Continue..\n\n"<<endl;
        	getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"ARE YOU SURE TO LOGOUT (Y/N)?\n\t\t    ";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"\n\n\n\n\t\t------------------------------";
            cout<<"\n";
            cout<<"\n\t\t    ****** THANK YOU ******";
            cout<<"\n";
            cout<<"\n\t\t------------------------------\n\n";
            cout<<"\n\n\n\t\tPlease Press any key to Continue..\n\n"<<endl;
            getch();
            hmenu();
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tInvalid Option...";
        cout<<"\n\t\t    Please Enter Valid Option";
        getch();
        goto menu;
    }
};
int main()
{ 
  hmenu();
  smenu(); 
 
  return 0;
}
