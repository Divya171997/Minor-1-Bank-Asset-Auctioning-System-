#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#define LEN 150
#define NAME_LEN 60
#include<windows.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

COORD coord={0,0};
void gotoxy(int x,int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void hline(int x1,int x2,int y)
{
  int i;
  for(i=x1;i<=x2;i++)
  {
    gotoxy(i,y);
    printf("%c",219);
  }
}
void vline(int y1,int y2,int x)
{
 int i;
 for(i=y1;i<=y2;i++)
 {
  gotoxy(x,i);
  printf("%c",179);
 }
}

 void box()
 { int i;
 	for(i=5;i<165;i++)
 	{
 		gotoxy(i,0);
 		printf("%c",219);
 		
 		gotoxy(i,40);
 		printf("%c",219);
	 }
	 for(i=0;i<40;i++)
	 {
	 	gotoxy(5,i);
 		printf("%c",219);
 		
 		gotoxy(164,i);
 		printf("%c",219);
	 }
 }


// FUNCTION TO FETCH THE TIME OF SYSTEM
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// STRUCTURE FOR BANK
struct bank
{
    int account_number;
    char first_name[NAME_LEN+1];
    int Balance;
} enter;

struct bidding
{
    char name[20];
    int bidvalue;
} bid;

void create();
void viewAccounts();
void withdraw();
void deposit();



//CREATE NEW ACCOUNT
void create()
{
 FILE *fp;
 fp = fopen("bank1.txt", "a");
 gotoxy(7,2);
  printf(ANSI_COLOR_RED"CREATE NEW ACCOUNT"ANSI_COLOR_RESET);
  hline(5,164,3);
 gotoxy(7,5);
 printf("Enter the Account.NO.  :");
 box();
 gotoxy(35,5);
 scanf("%d", &enter.account_number);
 gotoxy(7,7);
 printf("Enter the Name of Account Holder     :");
 box();
 gotoxy(50,7);
 scanf("%s", &enter.first_name);
 gotoxy(7,9);
 printf("Enter the Amount  :");
 box();
 gotoxy(30,9);
 scanf("%d", &enter.Balance);
 fwrite(&enter, sizeof(enter), 1, fp);
 fclose(fp);
 box();
}
//    FUNCTION TO DISPLAY ACCOUNTS
void viewAccounts()
{
	int i=7;
 FILE *fp1;
 fp1 = fopen("bank1.txt", "r");
  gotoxy(7,2);
    printf(ANSI_COLOR_RED"ACCOUNT DETAILS"ANSI_COLOR_RESET);
  hline(5,164,3);
  gotoxy(7,5);
 printf("Account.NO.\tName of Account Holder\tBalance\n\n");

 while (fread(&enter, sizeof(enter), 1, fp1))
  {
  gotoxy(7,i);
 i++;
 printf("  %d\t\t%s\t\t%d\n", enter.account_number, enter.first_name, enter.Balance);
}
 fclose(fp1);
 box();
}
// FUNCTION TO DEPOSIT THE MONEY
void deposit()
{

    int acc_no;
    
  box();
  gotoxy(7,2);
  printf(ANSI_COLOR_RED"DEPOSIT PAGE"ANSI_COLOR_RESET);
  hline(5,164,3);
    gotoxy(7,7);
    printf("Enter The Account Number of the Account You Would Like To Deposit To : ");
    gotoxy(87,7);
    scanf("%d", &acc_no);

    FILE *fp1 = fopen("bank1.txt", "r");
    FILE *newFile = fopen("BankTemp.txt", "w");
    fscanf(fp1, "Account Number : %d", enter.account_number);
    fscanf(fp1, "Account Holder Name : %s", enter.first_name);
    fscanf(fp1, "Balance : %d", enter.Balance);

    if (acc_no == enter.account_number)
    {
        int balance;
        gotoxy(7,9);
        printf("Enter The Amount You Would Like To Deposit : ");
        gotoxy(50,9);
        scanf("%d", &balance);
        enter.Balance = balance + enter.Balance;
        fwrite(&enter, sizeof(enter), 1, newFile);
        fclose(newFile);
        fclose(fp1);
        remove("Bank1.txt");
        rename("BankTemp.txt", "bank1.txt");
    }

    if(acc_no != enter.account_number)
    {
    	gotoxy(7,13);
        printf("Account Number Doesn't Exist\n");
        fclose(fp1);
        fclose(newFile);
        remove("BankTemp.txt");
    }

}

//FUNCTION TO WITHDRAW THE MONEY
void withdraw()
{
	int acc_no;
	box();
     gotoxy(7,2);
  printf(ANSI_COLOR_RED"WITHDRAW PAGE"ANSI_COLOR_RESET);
  hline(5,164,3);
    gotoxy(7,5); 
    printf("Enter The Account Number of the Account You Would Like To Withdraw From : ");
    gotoxy(87,5);
    scanf("%d", &acc_no);

    FILE *fp1 = fopen("bank1.txt", "r");
    FILE *newFile = fopen("BankTemp.txt", "w");
    fscanf(fp1, "Account Number : %d", enter.account_number);
    fscanf(fp1, "Account Holder Name : %s", enter.first_name);
    fscanf(fp1, "Balance : %f", enter.Balance);

    if (acc_no == enter.account_number)
    {
        int balance;
            gotoxy(7,7); 
        printf("Enter The Amount You Would Like To Withdraw : ");
        scanf("%d", &balance);
        enter.Balance = enter.Balance - balance;
        fwrite(&enter, sizeof(enter), 1, newFile);
        fclose(newFile);
        fclose(fp1);
        remove("Bank1.txt");
        rename("BankTemp.txt", "bank1.txt");
    }

    if(acc_no != enter.account_number)
    {
    	    gotoxy(7,9); 

        printf("Account Number Doesn't Exist\n");
        fclose(fp1);
        fclose(newFile);
        remove("BankTemp.txt");
    }	
    box();
}


//bank account final function
void bankaccount()
{
    int ch;
     
    while(1)
        {
    	 gotoxy(7,2);
             printf(ANSI_COLOR_RED"WELCOME TO THE BANK"ANSI_COLOR_RESET);
           hline(5,164,3);
           box();
           gotoxy(7,20);
            printf("1 : Create Account\n");
           gotoxy(7,21);
           printf("2 : View Accounts\n");
           gotoxy(7,22);
            printf("3 : Deposit \n");
           gotoxy(7,23);
            printf("4 : Withdraw \n");
           gotoxy(7,24);
            printf("5 : Exit \n\n");
          gotoxy(7,25);
            printf("\t please enter choice : ");
          
          gotoxy(40,25);
			scanf("%d", &ch);
          box();
            switch(ch)
            {
               case 1: 
			  system("cls");
			   create();
                        break;
                case 2: 
						  system("cls");
				viewAccounts();
                        break;
                case 3: 
					  system("cls");
				deposit();
                        break;
                case 4: 
				      system("cls");
				withdraw();
                        break;
                case 5: exit(0);
                        default: printf("\t\tEnter 1-5 Only");
                        getch();
            }
        }
}

//FUNCTION OF QUICK SORT

void quicksort(int number[25],int first,int last)
  {
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

      }
   }
   
   //FUNCTION TO SEARCH FOR THE HIGHEST BIDDER
  void avlbid(int rno)
{
 FILE *fp;
 
 fp = fopen("bid.txt", "r");
 while (!feof(fp))
 {
  fread(&bid, sizeof(bid), 1, fp);

  if (rno == bid.bidvalue)
  {
      printf("%s",bid.name);
      fclose(fp);
  }
  fclose(fp);
 }
}

//FUNCTION TO BID

void bidding()
{
	int i=0, count=0, number[25],f;
    FILE *fp;
 fp = fopen("bid.txt", "a");
    char name[20]; 
    int bidvalue;
    char ch;
     gotoxy(7,2);
     printf(ANSI_COLOR_RED"WELCOME TO THE BIDDING WINDOW"ANSI_COLOR_RESET);
     hline(5,164,3);
    gotoxy(7,7);
    printf("Do you want to bid?(Y/N)");
    scanf("%s",&ch);
    
  
    if(ch=='Y')
    {
 
 do{
       if (fp == NULL)
    {
        printf("File does not exists \n");
        return;
    }
        system("cls");
        box();
    	gotoxy(7,9);
     printf("Enter the name:");
     scanf("%s", &name);

	 gotoxy(7,11);
     printf("Enter the bidding value:");
     scanf("%d", &bidvalue);
     fwrite(&bid, sizeof(bid), 1, fp);
     fclose(fp);
	 gotoxy(7,14);  
	 printf("Do You wants to bid more?(Y/N)");
	 count++;
	 number[i]=bidvalue;
	 i++;
     quicksort(number,0,count-1);
     gotoxy(40,7);
	 printf("THE HIGHEST BID TILL NOW IS %d: ",number[count-1]); 
     scanf("%s",&ch);
     
   }while(ch=='Y');
    
	quicksort(number,0,count-1);
	    int j=number[count-1];
      system("cls");
      box();
       gotoxy(7,2);
             printf(ANSI_COLOR_RED"WINNER WINDOW"ANSI_COLOR_RESET);
             hline(5,164,3);
             
          
      
	  gotoxy(50,7);

      printf("WINNER IS:");
  
      avlbid(j);
      printf(" \t\t with the value %d",number[count-1]);
	  
	  gotoxy(7,38);
	  printf("THANK YOU");      
       
	  
}
    
    else
    {
    	fclose(fp);
	}
}

//FUNCTION TO PRINT TERMS AND CONDITIONS
void termsandconditions()
{
	 { 
     FILE  *fp ;
     char  ch ;  
	 
	   fp = fopen ( "termscon.C", "r" ) ; 
 
 while ( 1 )
   {   
   ch = fgetc ( fp ) ; 
   if ( ch == EOF ) 
     break ; 
 
  printf ( "%c", ch ) ;
  
   } 
 
 fclose ( fp ) ; 
    } 
}

// STRUCTURE FOR AUCTION PROPERTY

struct auctionproperty
{
 int qty, no;
 char name[30];
 int range;
}property;

//    FUNCTION TO INSERT THE PROPERTY UNDER AUCTION
void insert()
{
 FILE *fp;
 fp = fopen("Record", "a");
 gotoxy(7,1);
 printf(ANSI_COLOR_RED "ADD PROPERTY HERE"ANSI_COLOR_RESET);
 hline(5,164,3);
 gotoxy(7,7);
 printf("Enter the S.NO.  :");
 scanf("%d", &property.no);
 gotoxy(7,8);
 printf("Enter the Name of Property     :");
 scanf("%s", &property.name);
 gotoxy(7,9);
 printf("Enter the Quantity  :");
 scanf("%d", &property.qty);
 gotoxy(7,10);
 printf("Enter the Range      :");
 scanf("%d", &property.range);
 fwrite(&property, sizeof(property), 1, fp);
 fclose(fp);
}
//    FUNCTION TO DISPLAY PROPERTIES
void disp()
{
 FILE *fp1;
 int i=9;
 fp1 = fopen("Record", "r");
 	gotoxy(7,1);
   	printf(ANSI_COLOR_RED"PROPERTIES DETAILS"ANSI_COLOR_RESET);
   	hline(5,164,3);
 gotoxy(7,7);
 printf("S.NO.\tName of Property\tQuantity\tRange");
 
 while (fread(&property, sizeof(property), 1, fp1))
 {
 gotoxy(7,i);
 i++;
 printf(" %d\t\t%s\t\t%d\t%d\n", property.no, property.name, property.qty, property.range);
}
 fclose(fp1);
}
//    FUNCTION TO SEARCH THE PROPERTIES
void search()
{
 FILE *fp2;
 int r, s, avl;
 gotoxy(7,7);
 printf("Enter the Property serial number you want to search  :");
 scanf("%d", &r);
 avl = avlno(r);
 if (avl == 0){

 gotoxy(7,9);
  printf("Serial Number %d is not available in the file\n",r);
}
 else
 {
  fp2 = fopen("Record", "r");
  while (fread(&property, sizeof(property), 1, fp2))
  {
   s = property.no;
   if (s == r)
   {
   	gotoxy(7,9);
   	printf("S.NO = %d", property.no);
   	gotoxy(7,10);
    printf("Name of Property    = %s", property.name);
	gotoxy(7,11);
	printf("Quantity = %d", property.qty);
    gotoxy(7,12);
	printf("Range    = %d\n", property.range);
   }
  }
  fclose(fp2);
 }
}
//    FUNCTION TO UPDATE THE QUANTITY AND RANGE OF THE PROPERTY
void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 gotoxy(7,7);
 printf("Enter Serial number of the property you wants to update to update:");
 scanf("%d", &r);
 avl = avlno(r);
 if (avl == 0)
 {gotoxy(7,9);
  printf("This serial number %d is not Available in the file", r);
 }
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&property, sizeof(property), 1, fpo))
  {
   s = property.no;
   if (s != r)
    fwrite(&property, sizeof(property), 1, fpt);
   else
   {
   	gotoxy(7,1);
   	printf("UPDATION WINDOW");
   	hline(5,164,3);
   	gotoxy(7,9);
    printf("1. Update Quantity of the Property");
    gotoxy(7,10);
    printf("2. Update Range of the property");
    gotoxy(7,11);
    printf("3. Update both Quantity and Range of the Property");
    gotoxy(7,13);
	printf("Enter your choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
    	system("cls");
    	box();
    	gotoxy(7,1);
   	printf("UPDATION WINDOW");
   	hline(5,164,3);
    	gotoxy(7,15);
     printf("Enter Quantity:");
     scanf("%d", &property.qty);
     break;
    case 2:
    	system("cls");
    	box();
    	gotoxy(7,1);
   	printf("UPDATION WINDOW");
   	hline(5,164,3);
    	gotoxy(7,15);
     printf("Enter Range : ");
     scanf("%d", &property.range);
     break;
    case 3:
    	system("cls");
    	box();
    	gotoxy(7,1);
   	printf("UPDATION WINDOW");
   	hline(5,164,3);
    	gotoxy(7,15);
     printf("Enter Quantity: ");
     scanf("%d", &property.qty);
     gotoxy(7,16);
     printf("Enter Range: ");
     scanf("%d", &property.range);
     break;
    default:
    	gotoxy(7,15);
     printf("Invalid Selection");
     break;
    }
    fwrite(&property, sizeof(property), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&property, sizeof(property), 1, fpt))
  {
   fwrite(&property, sizeof(property), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  gotoxy(7,17);
  printf("RECORD UPDATED");
 }
}
//    FUNCTION TO CHECK PROPERTY IS AVAILABLE FOR BIDDING OR NOT
int avlno(int rno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Record", "r");
 while (!feof(fp))
 {
  fread(&property, sizeof(property), 1, fp);

  if (rno == property.no)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}
//FUNCTION TO CHECK THE FILE IS EMPTY OR NOT
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("Record", "r");
 while (fread(&property, sizeof(property), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}

//DELETING THE RECORD FROM THE FILE
void deletefile()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 gotoxy(7,7);
 printf("Enter the no you want to delete :");
 scanf("%d", &r);
 if (avlno(r) == 0)
 {
  gotoxy(7,9);
  printf("no %d is not available in the file\n", r);
}
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&property, sizeof(property), 1, fpo))
  {
     s = property.no;
     if (s != r)
     fwrite(&property, sizeof(property), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&property, sizeof(property), 1, fpt))
  fwrite(&property, sizeof(property), 1, fpo);
  gotoxy(7,11);
  printf("RECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }

}

// MAIN FUNCTION FOR PROPERTY
void detail()
{
 int c, emp;
  hline(5,164,3);
 	gotoxy(7,1);
  printf(ANSI_COLOR_RED "UPDATION WINDOW"ANSI_COLOR_RESET);
  hline(5,164,3);
  printf("\n\t1. INSERT\n\t2. DISPLAY\n\t3. SEARCH");
  printf("\n\t4. UPDATE\n\t5. DELETE\n\t6. EXIT\n");
  
  gotoxy(7,14);
  printf("Enter your choice:");
  gotoxy(30,14);
  scanf("%d", &c);
  printf("\n");
  switch (c)
  {
  case 1:
  	 system("cls");
  	 box();
   insert();
   break;
   
  case 2:
  	 system("cls");
   box();
   emp = empty();
   if (emp == 0)
    printf("\nThe file is EMPTY\n");
   else
    disp();
   break;
  case 3:
  	 system("cls");
     	box();
   search();
   break;
  case 4:
  	 system("cls");
  	box();
   update();
   break;
  case 5:
  	 system("cls");
     	box();
   deletefile();
   break;
  case 6:
   exit(1);
   break;
   default:
   printf("\nYour choice is wrong\nPlease try again...\n");
   break;

  }
 

}
// MANAGER LOGIN FUNCTION
void inputdata()
{
	 FILE *fptr;
     char name[20];
     int phoneno;
     char ch;
     char username1[]="Divya",password1[]="12345",username2[]="Shailendra",password[10];
     int i=0;
     int n=1;
     int a,b,c;
     box();
     gotoxy(7,1);
     printf(ANSI_COLOR_RED"MANAGER WINDOW"ANSI_COLOR_RESET);
     gotoxy(155,2);
        printf(ANSI_COLOR_RED"WELCOME"ANSI_COLOR_RESET);
      hline(5,164,3);
     gotoxy(9,7);
     printf(ANSI_COLOR_BLUE "Do you want to Enter?(Y/N)"ANSI_COLOR_RESET);
     scanf("%s",&ch);
    
     fptr = fopen("manager.rec", "a");
     if(ch=='Y')
      {
 
       if (fptr == NULL)
        {
         printf("File does not exists \n");
         return;
        }
   while(n<=3)
   {
       system("cls");
       box();

            gotoxy(7,1);
     printf(ANSI_COLOR_RED"MANAGER WINDOW"ANSI_COLOR_RESET);
     gotoxy(155,2);
        printf(ANSI_COLOR_RED"WELCOME"ANSI_COLOR_RESET);
      hline(5,164,3);
       gotoxy(7,5);
		printf(ANSI_COLOR_GREEN"Enter the name:"ANSI_COLOR_RESET);
       
        gotoxy(7,7);
		 printf(ANSI_COLOR_GREEN"Enter the password:"ANSI_COLOR_RESET);
		 
         gotoxy(7,9);
         printf(ANSI_COLOR_GREEN"Enter the phone no:"ANSI_COLOR_RESET);
          gotoxy(30,5);
          scanf("%s", &name);
        fprintf(fptr, "Name    = %s\n", name);
       
for(i=0;i<5;i++)
{
ch = getch();
password[i] = ch;
ch = '*' ;
//gotoxy(30,7);
printf("%c",ch);
}
         
        gotoxy(30,7);
        //scanf("%s", &password);
        fprintf(fptr, "password    = %s\n", password);
        gotoxy(30,9);
        
        scanf("%d", &phoneno);
        fprintf(fptr, "phone no  = %d\n", phoneno); 
      a=strcmp(name,username1);
      c=strcmp(name,username2);
      b=strcmp(password,password1);
      if(((a==0)||(c==0))&&b==0) 
      {     system("cls"); 
      box();
      gotoxy(20,10);
      	   printf(ANSI_COLOR_RED"You have logged in successfully."ANSI_COLOR_RESET);
      	   gotoxy(20,13);
           printf(ANSI_COLOR_RED"Press Enter to proceed...!!"ANSI_COLOR_RESET);
           if(getch()==13)
           system("cls");
		   box(); 
           detail();
           break;
      }
      else
      {
      	 system("cls");
      	 box();
      	 gotoxy(7,7);
         printf("Wrong PASSWORD and/or USER ID. Now you have % d more chance/s.",3-n);
      }
      getch();
      n++;
   }
   if(n==4)
      system("cls");
      box();
      gotoxy(8,8);
      printf(ANSI_COLOR_RED "You can't log in."ANSI_COLOR_RESET);
   getch();


        
	
	    fclose(fptr); 
	}
	    
      }

//CUSTOMER LOGIN STRUCTURE AND FUNCTION

struct customer
{
 int pass;
 char name[30];
}cust;

void insertc() 
{
 FILE *fp;
 fp = fopen("authentication.txt", "a");
 system("cls");
 box();
    gotoxy(7,1);
   	printf("CUSTOMER REGISTRATION WINDOW");
   	hline(5,164,3);
gotoxy(7,13);
 printf("Enter the Name of customer  :");
 gotoxy(40,13);
 scanf("%s", cust.name);
 gotoxy(7,14);
 printf("Enter the Password  :");
 gotoxy(40,14);
 scanf("%d", &cust.pass);
 fwrite(&cust, sizeof(cust), 1, fp);
 fclose(fp);
}

void view()  
{
 FILE *fp1;
 fp1 = fopen("authentication.txt", "r");

 printf("\nNAME\tPASSWORD\n\n");
 while (fread(&cust, sizeof(cust), 1, fp1))

 printf("  %s\t%d\n", cust.name, cust.pass);
 fclose(fp1);

}


void searchc()
{
 char n[30];
 int p;
 box();
 gotoxy(7,5);
 printf("Enter the customer name  :");
 gotoxy(35,5);
 scanf("%s", &n);
 gotoxy(7,7);
 printf("Enter the customer password  :");
 gotoxy(35,7);
 scanf("%d", &p);

 FILE *fp;
 fp = fopen("authentication.txt", "r");
 int avl = avln(p);

if (avl == 0)
 {
  gotoxy(15,30);
  printf("not registered");
  gotoxy(15,34);
  printf("First Register Yourself");
  gotoxy(7,17);
  insertc();
  system("cls");
  box();
  gotoxy(7,7);
  searchc();
  exit(0);
 }  

 else
 {
 	system("cls");
 	box();
 }
}

int avln(int rno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("authentication.txt", "r");
 while (!feof(fp))
 {
  fread(&cust, sizeof(cust), 1, fp);

  if (rno == cust.pass)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}

void customerdetails() 
{
 int c;
	 system("cls");
 	  box();
    gotoxy(7,1);
   	printf("CUSTOMER LOGIN WINDOW");
   	hline(5,164,3);
 	gotoxy(7,7);
  printf("---Select your choice---\n");
   	gotoxy(7,9);
  printf("1. REGISTER");
   	gotoxy(7,10);
  printf("2. LOGIN");
   	gotoxy(7,11);
  printf("Enter your choice:");
  gotoxy(30,11);
  scanf("%d", &c);
  printf("\n");
 
  switch (c)
  {
  case 1:
   system("cls");
   box();
   insertc();
   break;
   
  case 2:
     system("cls");
     box();
  	 searchc();  	 
  	 break;
  	 
     default:
     printf("\nYour choice is wrong\nPlease try again...\n");
     break;
 
  }
}

//MAIN FUNCTION

int main() 
{
    int choice,ch;
    char input;
    FILE *fp;
    char m;
    char c;
      
	    char buf[LEN];
        time_t curtime;
        struct tm *loc_time;
        curtime= time(NULL);
        loc_time=localtime(&curtime);
        gotoxy(7,2);
        printf("%s",asctime(loc_time));
       
        hline(5,164,3);
        gotoxy(155,2);
        printf("WELCOME");
        gotoxy(70,2);
        printf("TERMS AND CONDITIONS\n\n\n\n\n\n\n\n");
        
        termsandconditions();
	  
		
		printf("\n\n\n\n\t\t\t\t\t\t\tPRESS ENTER TO CONTINUE");
			box();
			gotoxy(87,25);
		if(getch()==13)   
		  
       system("cls");
       
	   gotoxy(7,1);
        printf(ANSI_COLOR_CYAN"WELCOME TO OUR PAGE"ANSI_COLOR_RESET);
      gotoxy(130,2);
        printf(ANSI_COLOR_RED"THANKYOU FOR VISITING OUR PAGE"ANSI_COLOR_RESET);
      hline(5,164,3);
       box();
       gotoxy(9,8);
       printf(ANSI_COLOR_RED"0-"ANSI_COLOR_RESET ANSI_COLOR_GREEN"Bank\n"ANSI_COLOR_RESET);
       gotoxy(9,9);
	   printf(ANSI_COLOR_RED"1-"ANSI_COLOR_RESET ANSI_COLOR_GREEN"Manager\n"ANSI_COLOR_RESET);
	   gotoxy(9,10);
	   printf(ANSI_COLOR_RED"2-"ANSI_COLOR_RESET ANSI_COLOR_GREEN"Customer\n"ANSI_COLOR_RESET);
	   gotoxy(9,11);
	   printf(ANSI_COLOR_RED"3-"ANSI_COLOR_RESET ANSI_COLOR_GREEN"Quit\n"ANSI_COLOR_RESET);
	   gotoxy(9,15);
	   
        printf("ENTER YOUR CHOICE:\t");
         gotoxy(27,15);
        scanf("%c", &input);
      
        system("cls");
        fp = fopen ( "manager.txt", "a" ) ; 
        scanf("%c", &m);
        scanf("%c", &c);
  		
		  		 fclose(fp);
	   
	   switch(input)
        {
        case'0':
        
			bankaccount();
				box();
        	break;
        	
        case'1':
        	gotoxy(18,1);
            printf(ANSI_COLOR_CYAN"Hello Manager\n"ANSI_COLOR_RESET);
                    gotoxy(155,2);
        printf("WELCOME");
        
             hline(5,164,3);
            gotoxy(9,9);
            printf(ANSI_COLOR_BLUE"Press"ANSI_COLOR_RESET ANSI_COLOR_RED" c "
			 ANSI_COLOR_RESET ANSI_COLOR_BLUE"for continue and"ANSI_COLOR_RESET ANSI_COLOR_RED" e "
			 ANSI_COLOR_RESET ANSI_COLOR_BLUE"for exit\n"ANSI_COLOR_RESET);
            box();
          
		    char m;
		    gotoxy(9,10);
              scanf("%c", &m);
			  
			  switch(m)
            	{
				case 'c':
					 system("cls");  
					 
			     	 inputdata();
			     
				     break;
            	case 'e':        	
                     exit(0);
                     break;
                }
		    break;

        case '2':
        	gotoxy(18,1);
            printf("Welcome Customer\n");
                    gotoxy(155,2);
            printf("WELCOME");
            hline(5,164,3);
            gotoxy(9,9);
            printf(ANSI_COLOR_BLUE"Press"ANSI_COLOR_RESET ANSI_COLOR_RED" c " 
			ANSI_COLOR_RESET ANSI_COLOR_BLUE"for continue and"ANSI_COLOR_RESET ANSI_COLOR_RED" e "
			ANSI_COLOR_RESET ANSI_COLOR_BLUE"for exit\n"ANSI_COLOR_RESET);
            box();
			char c;
			gotoxy(9,10);
              scanf("%c", &c);
            
			  switch(c)
                {
            	case 'c':
            		    system("cls");  
            		    box();
                        customerdetails();
                       
                       	
					    gotoxy(7,2);
                        printf(ANSI_COLOR_RED"WELCOME TO THE BIDDING WINDOW"ANSI_COLOR_RESET);
                        hline(5,164,3);
	                         gotoxy(7,7);
							 printf(ANSI_COLOR_RED"\t1."ANSI_COLOR_RESET ANSI_COLOR_BLUE" DETAIL ABOUT PROPERTIES\n"ANSI_COLOR_RESET);
							 gotoxy(8,8);
							 printf(ANSI_COLOR_RED"2."ANSI_COLOR_RESET ANSI_COLOR_BLUE" PARTICIPATE IN BIDDING\n"ANSI_COLOR_RESET);
							 box();
	                         gotoxy(10,10);
							 printf("ENTER YOUR CHOICE");
	                         box();
	                         gotoxy(30,10);
							 scanf("%d",&choice);
	                         
                             switch(choice)
                            	{
	
	                                 case 1:
		                               system("cls");
		                               box();
                                       disp();
	                                   break;

                                     case 2:
                             system("cls");  
                             box();
                             gotoxy(7,2);
                             printf(ANSI_COLOR_RED"PROPERTIES UNDER BIDDING"ANSI_COLOR_RESET);
                              hline(5,164,3);
                             gotoxy(7,7);
                             printf("1. HOUSES");
                             gotoxy(7,8);
							 printf("2. FLATS");
							 gotoxy(7,9);
							 printf("3. LANDS");
							 gotoxy(7,10);
							 printf("4. E-GADGETS");
							 gotoxy(7,13);
	                         printf("ENTER YOUR CHOICE:");
	                         scanf("%d",&ch);
	                        
	                         switch(choice)
	                         {	
	                                  case 1:
	                                  	system("cls");
	                                    box();
	                                      gotoxy(7,2);
                             printf(ANSI_COLOR_RED"BIDDING FOR HOUSES"ANSI_COLOR_RESET);
                              hline(5,164,3);
									   bidding();
	                                   break;
	                                   
	                                  case 2:
	                                  system("cls");
									  box();
									   gotoxy(7,2);
                             printf(ANSI_COLOR_RED"BIDDING FOR FLATS"ANSI_COLOR_RESET);
                              hline(5,164,3);
									   	bidding();
	                                  	break;
	                                  	
	                                  case 3:
	                                  system("cls");
									  box();
									   gotoxy(7,2);
                             printf(ANSI_COLOR_RED"BIDDING FOR LANDS"ANSI_COLOR_RESET);
                              hline(5,164,3);
	                                  	bidding();
	                                  	break;
	                                  	
	                                  case 4:
	                                  system("cls");
									  box();
									   gotoxy(7,2);
                             printf(ANSI_COLOR_RED"BIDDING FOR E-GADGETS"ANSI_COLOR_RESET);
                              hline(5,164,3);
	                                  	bidding();
	                                  	break;
	                         }
                     
              	                break;
	         }
				 case 'e':        	
                       exit(0);
                       break;
                } 
            
				break;
        
        case '3':
          
		   exit(0);
           break;
           default:
           printf("Invalid Input");
        }
} 
