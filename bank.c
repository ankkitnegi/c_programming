/* PROGRAM RUN & COMPILED ON DEV-C++ 5.11 COMPILER */

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
void insert(FILE *fp);
void check(FILE *fp);
void del(FILE *fp);
int search(FILE *fp,char *name);
int sepswd(FILE *fp,char *name);
void list(FILE *fp);
void modify(FILE *fp);
void withdraw(FILE *fp);
void credit(FILE *fp);
void trans(FILE *fp);
void about(void);
struct bank
{
char name[50],mail[50],add[100],desg[50];
char pswd[50],code[10];
long long bal,phno;	
int d,m,y;
}bank;
char c;
void main()
{
	int ch;
	FILE *fp;
	fp=fopen("account.dat","rb+");
	if(fp==NULL)
	{ fp=fopen("account.dat","wb+");
	   if(fp==NULL)
    {   printf("\nError opening file !!!");
		   exit(0);
	}
    }
    system("cls");                                              //For clear screen, or you can use clrscr();
	printf("\n\n\t******************************************************************************************\n");
	printf("\n\t\t\t\t\t BANK ACCOUNT PROGRAM \t\t\t\t\n");
	printf("\n\t******************************************************************************************\n");
do{    
    	printf("\n\n\n\n\t\t\t\t[1] - INSERT A NEW RECORD.");
		printf("\n\t\t\t\t[2] - CHECK ACCOUNT.");
		printf("\n\t\t\t\t[3] - DELETE A RECORD.");
		printf("\n\t\t\t\t[4] - LIST ALL RECORDS.");
		printf("\n\t\t\t\t[5] - MODIFY A RECORD.");
		printf("\n\t\t\t\t[6] - WITHDRAW MONEY.");
		printf("\n\t\t\t\t[7] - CREDIT MONEY.");
		printf("\n\t\t\t\t[8] - VIEW LAST TRANSACTION.");
		printf("\n\t\t\t\t[9] - ABOUT PROGRAM.");
		printf("\n\t\t\t\t[10] - EXIT MENU PROGRAM.\n\n");
		printf("\n\n\tEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				insert(fp);
				break;
			case 2:
				check(fp);
				break;
			case 3:
				del(fp);
				break;
			case 4:
				list(fp);
				break;
			case 5:
				modify(fp);
				break;
			case 6:
				withdraw(fp);
				break;
			case 7:
				credit(fp);
				break;
			case 8:
			    trans(fp);
			    break;
			case 9:
				about();
				break;
			case 10:
			{ fclose(fp);
			    break;    }
			default:
				printf("\nEnter a valid choice between (1 or 9): \n\n");
        }
		}while(ch>=1 && ch<=8);
		system("cls");
printf("\n\n\n\n\t***************************************************************************************************************\n\n\n");
printf("\n\n\t\t\t\t END OF PROGRAM, THANKS FOR USING BANK APPLICATION ... \t\t\t\t\n\n\n");
printf("\n\n\t***************************************************************************************************************\n");
}
void insert(FILE *fp)
{
	int z=0;
	fseek(fp,0,2);
	system("cls");
	printf("\n\n\n\n\tEnter person name : ");
	scanf("%s",bank.name);
	printf("\n\tEnter person address : ");
	scanf("%s",bank.add);
	printf("\n\tEnter person email : ");
	scanf("%s",bank.mail);
	printf("\n\tEnter person phone number : ");
	scanf("%lld",&bank.phno);
	printf("\n\tEnter person designation : ");
	scanf("%s",bank.desg);
	printf("\n\tEnter person current balance : ");
	scanf("%lld",&bank.bal);
	printf("\n\tEnter person password : ");
    while((c=getch())!=13)
        {
           bank.pswd[z++]=c;
           printf("%c",'*');
        }
    bank.d=0; bank.m=0; bank.y=0;
    strcpy(bank.code,"\0");
	fwrite(&bank,sizeof(bank),1,fp);
	printf("\n\n\tPress anykey to continue...");
	getch();
	system("cls");
}
void check(FILE *fp)
{
char name[50],psswd[50];
int z=0; char c;
system("cls");
printf("\n\n\n\tEnter your name : ");
scanf("%s",name);
if(search(fp,name)==0)
{
 printf("\n\tEnter your password : ");
 while((c=getch())!=13)
    {
           psswd[z++]=c;
           printf("%c",'*');
    } psswd[z]='\0';
 if(sepswd(fp,psswd)==0)
{
printf("\n\n\tPerson name : %s.",bank.name);
printf("\n\tPerson address : %s.",bank.add);
printf("\n\tPerson mail : %s.",bank.mail);
printf("\n\tPerson phone number : %lld.",bank.phno);
printf("\n\tPerson designation : %s.",bank.desg);
printf("\n\tPerson balance : %lld Rs.\n\n",bank.bal);	
}	
}
printf("\n\n\tPress anykey to continue...");
getch();
system("cls");
}
void del(FILE *fp)
{
FILE *fptmp;
int z=0;
char name[50],psswd[50];
system("cls");
printf("\n\n\n\tEnter the name of the person whose record is to be deleted from database : ");
scanf("%s",name);
if(search(fp,name)==0){
printf("\n\tEnter password of the person : ");
while((c=getch())!=13)
        {
           psswd[z++]=c;
           printf("%c",'*');
}          psswd[z]='\0';
if(sepswd(fp,psswd)==0){
fptmp=fopen("tempbank.dat","wb");
rewind(fp);
while(fread(&bank,sizeof(bank),1,fp)==1)
 {
	if(strcmp(name,bank.name)!=0)
	fwrite(&bank,sizeof(bank),1,fptmp);
 } 
	fclose(fp);
	fclose(fptmp);
	remove("account.dat");
	rename("tempbank.dat","account.dat");
	printf("\nRecord deleted...\n\n");
	fp=fopen("account.dat","rb+");	
}
}
printf("\n\n\tPress anykey to continue...");
getch();
system("cls");
}
int search(FILE *fp,char *name)
{
	unsigned flag=1;
	rewind(fp);
	while(fread(&bank,sizeof(bank),1,fp)==1)
	{  if(strcmp(name,bank.name)==0)
		{
			flag=0;
		    break;
		}
	}
	if(flag==1)
	printf("\n\nIncorrect name...\n\n");
	return flag;
}
int sepswd(FILE *fp,char *name)
{
	unsigned flag=1;
	rewind(fp);
	while(fread(&bank,sizeof(bank),1,fp)==1)
	{  if(strcmp(name,bank.pswd)==0)
		{
			flag=0;
		    break;
		}
	}
	if(flag==1)
	printf("\n\nIncorrect password...\n\n");
	return flag;
}
void list(FILE *fp)
{   int i=0;
	rewind(fp);
	system("cls");
	printf("\n\n\n\n\t\tS.No\tName\t\tBalance\t\t\tEmail\t\t\tPhone No.\n\n");
	while(fread(&bank,sizeof(bank),1,fp)==1)
	{   
	    printf("\n\t\t%d",i+1);
  		printf("\t%s",bank.name);
		printf("\t%lld Rs",bank.bal);
		printf("\t%s\t",bank.mail);
		printf("\t%lld\n\n",bank.phno);
		i++;
	}
	printf("\n\n\tPress anykey to continue...");
	getch();
	system("cls");	
}
void modify(FILE *fp)
{
	char name[50],psswd[50],cg;
	int z=0;
	long size=sizeof(bank);
	system("cls");
	printf("\n\n\n\tEnter the name of the person to be modified : ");
	scanf("%s",name);
	if(search(fp,name)==0)
	{
		printf("\n\tEnter your password : ");
        while((c=getch())!=13)
        {
           psswd[z++]=c;
           printf("%c",'*');
        } psswd[z]='\0';
        if(sepswd(fp,psswd)==0)
    {
		printf("\n\n\n\t\tEnter new data -->>>\n");
		printf("\t\tEnter - to not change the values ... \n\n");      //Values will not be modified, So they are not changed.
	    	printf("\nEnter person name : "); 
	    	if((cg=getch())!=45){
				scanf("%s",bank.name);
		    } 
			printf("\nEnter person address : "); 
			if((cg=getch())!=45)
			{  scanf("%s",bank.add);
		    }
			printf("\nEnter person email : "); 
			if((cg=getch())!=45)
		    { scanf("%s",bank.mail);
			}
			printf("\nEnter person phone number : ");
			if((cg=getch())!=45)
			{   scanf("%lld",&bank.phno);
			}
			printf("\nEnter person designation : ");
			if((cg=getch())!=45)
			{
				scanf("%s",bank.desg);
			}
			printf("\nEnter person current balance : ");   
			if((cg=getch())!=45)
			{   scanf("%lld",&bank.bal);
			}
			printf("\nEnter your new password : ");
			if((cg=getch())!=45)
			{  
			scanf("%s",bank.pswd);
	        }
            fseek(fp,-size,1);
		    fwrite(&bank,sizeof(bank),1,fp);
		    printf("\n\n\t\tRecord modified sucessfully ...\n\n");
	}
}
printf("\n\n\tPress anykey to continue...");
getch();
system("cls");
}
void withdraw(FILE *fp)
{
	long long amt; int z=0;
	long size=sizeof(bank);
	char name[50],psswd[50];
	system("cls");
	printf("\n\n\n\tEnter your name : ");
	scanf("%s",name);
	if(search(fp,name)==0)
	{ 
	  printf("\n\tEnter your password : ");
      while((c=getch())!=13)
        {
           psswd[z++]=c;
           printf("%c",'*');
        }psswd[z]='\0';
      if(sepswd(fp,psswd)==0)
    {   
		printf("\n\n\n\tEnter the amount you want to withdraw : ");
		scanf("%lld",&amt);
		if(amt>bank.bal)
		{
		  printf("\n\nInsufficent Balance to Withdraw!!!");
		      exit(0);
		}
		else
		{   printf("\n\tEnter today\'s date : ");
		    scanf("%d/%d/%d",&bank.d,&bank.m,&bank.y);
		    strcpy(bank.code,"DEBIT");
			bank.bal-=amt;
			fseek(fp,-size,1);
			fwrite(&bank,sizeof(bank),1,fp);
		    printf("\n\tAmount successfully withdrawn....\n\n");
		}
	}
}
printf("\n\n\tPress anykey to continue...");
	getch();
system("cls");
}
void credit(FILE *fp)
{
	long long amt; int z=0;
	long size=sizeof(bank);
	system("cls");
	char name[50],psswd[50];
	printf("\n\n\n\tEnter your name : ");
	scanf("%s",name);
	if(search(fp,name)==0)
	{ 
	  printf("\n\tEnter your password : ");
      while((c=getch())!=13)
        {
           psswd[z++]=c;
           printf("%c",'*');
        } psswd[z]='\0';
      if(sepswd(fp,psswd)==0)
    {
		printf("\n\n\n\tEnter the amount you want to save to : ");
		scanf("%lld",&amt);
		printf("\n\tEnter today\'s date : ");
		scanf("%d/%d/%d",&bank.d,&bank.m,&bank.y);
		strcpy(bank.code,"CREDIT");
		bank.bal+=amt;
		fseek(fp,-size,1);
		fwrite(&bank,sizeof(bank),1,fp);
	    printf("\n\nAmount successfully credited....\n\n");
	}
}
printf("\n\n\tPress anykey to continue...");
	getch();
system("cls");
}
void trans(FILE *fp)
{ 
    system("cls");
	int i=1,z=0; char name[50],psswd[50];
	printf("\n\n\n\n\t\tEnter your name : ");
	scanf("%s",name);
	if(search(fp,name)==0)
	{
		printf("\n\t\tEnter your password : ");
		while((c=getch())!=13)
        {
           psswd[z++]=c;
           printf("%c",'*');
        }  psswd[z]='\0';
        if(sepswd(fp,psswd)==0)
        {  rewind(fp);
        
		 while(fread(&bank,sizeof(bank),1,fp)==1)
        	{  
			if(strcmp(bank.name,name)==0) 
			{
        	  printf("\n\n\tName : %s",bank.name);
        	  printf("\tDate : %d/%d/%d ",bank.d,bank.m,bank.y);
        	  printf("\t%s",bank.code);
        	  printf("\tCurrent Balance : %lld\n",bank.bal);
			}
		}
		}
    }
	printf("\n\n\tPress anykey to continue...");
	getch();
	system("cls");
}
void about(void)
{   system("cls");
	printf("\n\n\n\n\n\t\t\t\tPROGRAM TO DISPLAY HOW A SMALL BANK PROGRAM WORKS. ");
	printf("\n\t\t\t\tPROGRAM DESIGNED & DEVELOPED BY AMIT SINGH...");
	printf("\n\t\t\t\tSTUDENT OF SGRRITS, PATEL NAGAR, DEHRADUN, UK, INDIA .");
	printf("\n\t\t\t\t\tBCA Ist SEMESTER (RESPECT THE CODE). ");
	printf("\n\t\t\t\tFOR ANY HELP VISIT AMIT\'S BLOG : http://www.asmitblog.blogspot.com/  ");
	printf("\n\t\t\t\t\tOR KINDLY MAIL HIM AT : asamitdbz@gmail.com  ");
	printf("\n\n\n\t\t\t\t\a***************************************************************\t\t\t\n\n\n");
	printf("\n\n\tPress anykey to continue...");
	getch();
	system("cls");
}
