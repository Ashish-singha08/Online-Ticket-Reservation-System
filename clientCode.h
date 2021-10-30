#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<time.h>
#include"struct.h"

;void mainMenu(int);
void adminMenu(int);
////////////////////////////////////////// ADMIN SECTION////////////////////////////////////////////////////////////////////

// ###################################### ADD TRAIN ########################################################
void addTrain(int sd){
  int train;
  printf("Enter train Number:\n");
  scanf("%d",&train);
  
  int seats;
  printf("Enter NUmber of seats:\n");
  scanf("%d",&seats);
  
  write(sd,&train,sizeof(train));
  write(sd,&seats,sizeof(seats));
  int check;
  read(sd,&check,sizeof(check));
  
  if(check==-1)
  printf("Train Already Added");
  else
  printf("Train Successfully Added");
  adminMenu(sd);
}



// ###################################### DELETE TRAIN ########################################################
void deleteTrain(int sd){
  int train;
  printf("Enter train Number:\n");
  scanf("%d",&train);
  
  write(sd,&train,sizeof(train));
  int ans;
  read(sd,&ans,sizeof(ans));
  
  if(ans==0)
  printf("TRAIN ALREADY DELETED\n");
  else if(ans==1)
  printf("TRAIN DELETED\n");
  else 
  printf("TRAIN NOT FOUND");
  adminMenu(sd);
}

// ###################################### MODIFY TRAIN ########################################################
void modifyTrain(int sd){
   int train;
  printf("Enter train Number:\n");
  scanf("%d",&train);
  
  int seats;
  printf("Enter NUmber of seats:\n");
  scanf("%d",&seats);
  
  write(sd,&train,sizeof(train));
  write(sd,&seats,sizeof(seats));
  int flag ;
  read(sd,&flag,sizeof(flag));
  if(flag==1)
  printf("Train Seats Modified\n");
  else
  printf("Train NOt Found\n");
  adminMenu(sd);
}
// ###################################### SHOW TRAINS ########################################################
void showTrain(int sd){
  
  struct train t1;
  read(sd,&t1,sizeof(struct train));
  while(t1.number != -1){
     printf("Train Number is %d, seats available is %d, status is %d\n",t1.number,t1.seats,t1.status);
     read(sd,&t1,sizeof(struct train));
  }
  
  
  adminMenu(sd);
}
// ###################################### SHOW USER ########################################################
void showUser(int sd){
  
  struct normal user;
  read(sd,&user,sizeof(struct normal));
  while(user.acc_id != -1){
     printf("User Name is %s, pswrd  is %s, id is %d, user status is %d\n",user.uname,user.pass,user.acc_id,user.status);
     read(sd,&user,sizeof(struct normal));
  }
  
  
  adminMenu(sd);
}
// ###################################### DELETE USER ########################################################

void deleteUser(int sd){
  int user;
  printf("Enter user id :\n");
  scanf("%d",&user);
  
  write(sd,&user,sizeof(user));
  int ans;
  read(sd,&ans,sizeof(ans));
  
  if(ans==0)
  printf("USER ALREADY DELETED\n");
  else if(ans==1)
  printf("USER DELETED\n");
  else 
  printf("USER NOT FOUND");
  adminMenu(sd);}

// ###################################### ADMIN MENU ########################################################

void adminMenu(int sd){
   int choice;
     printf("1.ADD TRAIN \n2.DELETE TRAIN\n3.MODIFY TRAIN \n4.DELETE USER\n5.SHOW USER\n6.SHOW TRAINS\n7.EXIT \n");
	
	printf("Enter your choice: ");
	scanf("%d",&choice);
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
	
		case 1: addTrain(sd);
				break;
		case 2: deleteTrain(sd);
				break;
		case 3: modifyTrain(sd);
				break;
		case 4: deleteUser(sd);
				break;
		case 5: showUser(sd);
		            break;
		case 6: showTrain(sd);
		default : exit(0);
		          break;

	}
}

// ###################################### ADMIN LOGIN ########################################################

void adminLogin(int sd){
  char pass[3];
  
  printf("Enter ADMIN PASSWORD\n");
  scanf("%s",pass);
  write(sd, pass,sizeof(pass));
  

  int num;
  read(sd,&num,sizeof(num));
  
  
  if(num==-1)
  printf("--LOGIN FAILED--\n");
  else{
   printf("--LOGIN SUCCESSSFULL--\n");
   adminMenu(sd);
  }
  mainMenu(sd);
}

////////////////////////////////////////// NORMAL USER SECTION//////////////////////////////////////////////////////////////

// ###################################### UPDATE BOOKING ########################################################

void updateBooking(int sd){
   printf("TO UPDATE BOOKING YOU CAN CANCEL YOUR TICKET AND RE BOOK IT! THANK YOU!!\n");
}


// ###################################### CANCEL BOOKING ########################################################
void cancelBooking(int sd){
  int ticket;
  printf("Enter Ticket Number you wanna cancel\n");
  scanf("%d",&ticket);
  
  write(sd,&ticket,sizeof(ticket));
  
  char buf[20];
  
  read(sd,buf,sizeof(buf));
  
  printf("%s",buf);
}

void bookings(int sd){
   
   printf("Your Previous bookings are ....\n");
   
   struct booking b;
   
   read(sd,&b,sizeof(b));
   
   while(b.customer_id!=0){
   
       printf(" Train number is %d ## Ticket Number is %d ## Number of seats is %d ## status is %d\n",b.train_number,b.ticket_number,b.seats,b.status);
       read(sd,&b,sizeof(b));
   }
   
   
   
}

// ###################################### TICKET BOOKING ########################################################
void bookTicket(int sd){
   int train_number;
   printf("Enter Train Number:\n");
   scanf("%d",&train_number);
   
   write(sd,&train_number,sizeof(train_number));
   
   int num_seats;
   
   read(sd,&num_seats,sizeof(num_seats));
   if(num_seats==-1)
   {
     printf("-------Train Not Found-----\n");
     return ;
   }
   if(num_seats==-2)
   {
     printf("-------Train Cancelled-----\n");
     return ;
   }
   printf("There are %d seats available for booking\n",num_seats);
   
   printf("Enter the number of seats you want to book:\n");
   int book;
   
   scanf("%d",&book);
   while(book<=0){
    printf("----Invalid seats-----\n");
    printf("Enter again: ");
    scanf("%d",&book);
   }
   write(sd,&book,sizeof(book));
   char buff1[18];
   read(sd,buff1, sizeof(buff1));
   printf("%s",buff1);
   char buff2[21];
   read(sd,buff2, sizeof(buff2));
   printf("%s",buff2);
   int zero;
   scanf("%d",&zero);
   write(sd,&zero,sizeof(zero));
   
   
   int result ;
   read(sd,&result,sizeof(result));
   
   
   if(result == -1)
   printf("Required number of seats not available Or you have not completed the payment\n");
   else 
   printf("Congrats!! your ticket is booked and ticket number is %d\n",result);
   
  
}

// ###################################### MENU USER ########################################################
void menu(int sd){
   int option;

	printf("\n1. Book Ticket \n2. View Previous Bookings\n3. Update Booking \n4.Cancel Booking\n");
	
	printf("Enter your choice: ");
	
	scanf("%d",&option);

	write(sd, &option, sizeof(option));
	
	switch(option)
	{
				
		case 1: bookTicket(sd);
				break;
		case 2: bookings(sd);
				break;
		case 3: updateBooking(sd);
				break;
		case 4: cancelBooking(sd);
				break;
		default: exit(0);
		         break;
	       

	}
	mainMenu(sd);
}
// ###################################### USER LOGIN ########################################################
void userLogin(int sd){
       char buffera[25];
	char uname[20],pass[20];
	int flag;

	printf("Enter username: ");
	scanf(" %s",uname);
	printf("Enter password: ");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));

	read(sd, &flag, sizeof(flag));
	read(sd, buffera, sizeof(buffera));
	printf("%s\n",buffera);

	if(flag==1)
		menu(sd);
       else if(flag==2)
       {
        printf("ADMIN HAS DELETED YOUR ACCOUNT\n");
        mainMenu(sd);
       }
	else
		mainMenu(sd);
}
////////////////////////////////////////// AGENT SECTION //////////////////////////////////////////////////////////////

// ###################################### AGENT LOGIN ########################################################
void agentLogin(int sd){
 char buffera[25];
	char uname[20],pass[20];
	int flag;

	printf("Enter Your Agent Username: ");
	scanf(" %s",uname);
	printf("Enter password: ");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));
        
        printf("Waiting to be logged in........\n"); 
	read(sd, &flag, sizeof(flag));
	
	read(sd, buffera, sizeof(buffera));
	printf("%s\n",buffera);

	if(flag==1)
		menu(sd);
       else if(flag==2)
       {
        printf("####### ADMIN HAS DELETED YOUR ACCOUNT  ########\n");
        mainMenu(sd);
       }
	else
		mainMenu(sd);
}



////////////////////////////////////////// ACCOUNT CREATION //////////////////////////////////////////////////////////////
void createAccount(int sd){
    
    char t_name[15];
    char t_pswrd[15];
    printf("Enter your user name:\n");
    scanf("%s",t_name);
    printf("Enter your pswrd:\n");
    scanf("%s",t_pswrd);
    
    write(sd, t_name, sizeof(t_name));
    write(sd, t_pswrd, sizeof(t_pswrd));
    
    int flag ;
    read(sd, &flag, sizeof(flag));
    if(flag==0)
    printf("Oops!! USER NAME ALREADY EXISTS\n");
    else if(flag==1)
    printf("Account Successfully Created !!\n");
    else
    printf("Error!!!\n");
    
    mainMenu(sd);
   
}

////////////////////////////////////////// MAIN MENU //////////////////////////////////////////////////////////////
void mainMenu(int sd)
{
	int option;
        printf("WELCOME TO ONLINE RAILWAY TICKET RESERVATION SYSTEM->->->-> CODED BY ASHISH SINGHAL\n");
	printf("1.USER LOGIN \n2.AGENT LOGIN\n3.ADMIN LOGIN\n4.CREATE ACCOUNT\n5.EXIT\n");
	
	printf("Enter your choice: ");
	
	scanf("%d",&option);

	write(sd, &option, sizeof(option));

	switch(option)
	{
				
		case 1: userLogin(sd);
				break;
		case 2: agentLogin(sd);
				break;
		case 3: adminLogin(sd);
				break;
		case 4: createAccount(sd);
				break;
		case 5: exit(0);
		         break;
	       

	}
}

