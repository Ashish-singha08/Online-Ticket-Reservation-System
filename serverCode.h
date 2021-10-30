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


;void userLogin(int);
void agentLogin(int);
void createAccount(int);
void adminLogin(int);
void adminMenu(int);
// ########################################################   MAIN MENU ########################################################
void mainMenu(int sd)
{
	int choice;
	
	read(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
	
		case 1: userLogin(sd);
				break;
		case 2: agentLogin(sd);
				break;
		case 3: adminLogin(sd);
				break;
		case 4: createAccount(sd);
				break;
		case 5: break;

	}
}

////////////////////////////////////////// ADMIN SECTION////////////////////////////////////////////////////////////////////

// ###################################### ADD TRAIN ########################################################
void addTrain(int sd){
   int train_number;
   int seats;
   
   read(sd,&train_number,sizeof(train_number));
   read(sd,&seats,sizeof(seats));
   
   int fd1 = open("trains.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
   
   int check =-1 ;
   struct train t;
   while(read(fd1,&t,sizeof(struct train ))){
     if(t.number == train_number){
       write(sd,&check,sizeof(check));
       return;
     }
   }
   check =0;
   write(sd,&check,sizeof(check));
   lseek(fd1,0,SEEK_END);
   
   struct train t1;
   
   t1.number = train_number;
   t1.seats = seats;
   t1.status=1;
   
   write(fd1,&t1,sizeof(struct train));
   
   close(fd1);
   adminMenu(sd);
}



// ###################################### DELETE TRAIN ########################################################
void deleteTrain(int sd){
  int train;
  
  
  read(sd,&train,sizeof(train)); 
  int fd1 = open("trains.dat", O_CREAT | O_RDWR , 0666);
  
  struct train t1;
  int ans =-1;
  int count=0;
  while(read(fd1,&t1,sizeof(struct train))){
     
     if(t1.number == train && t1.status==1){
        t1.status=0;
        int fd2 = open("trains.dat", O_CREAT |O_RDWR , 0666);
        lseek(fd2,count*(sizeof(struct train)),SEEK_SET);
        write(fd2,&t1,sizeof(struct train));
        close(fd2);
        ans =1;
        break;
     }
     else if(t1.number==train && t1.status==0){
       ans =0;
       break;
     }
     count++;
     
  }
  write(sd,&ans,sizeof(ans));
  close(fd1);
  adminMenu(sd);
}

// ###################################### MODIFY TRAIN ########################################################
void modifyTrain(int sd){
   int train_number;
   int seats;
   
   read(sd,&train_number,sizeof(train_number));
   read(sd,&seats,sizeof(seats));
   
   int fd1 = open("trains.dat", O_CREAT|O_RDWR , 0666);
  int flag=0;
  struct train t1;
  int count=0;
  while(read(fd1,&t1,sizeof(struct train))){
     
     if(t1.number == train_number ){
        t1.seats=seats;
        flag=1;
        int fd2 = open("trains.dat", O_CREAT |O_RDWR , 0666);
        lseek(fd2,count*(sizeof(struct train)),SEEK_SET);
        write(fd2,&t1,sizeof(struct train));
        close(fd2);
       break;
     }
     
    count++;
     
  }
  write(sd,&flag,sizeof(flag));
   close(fd1); 
   adminMenu(sd);
}
// ###################################### SHOW TRAINS ########################################################void 
void showTrain(int sd){
  int fd1 = open("trains.dat", O_CREAT | O_RDWR , 0666);
  struct train t1;
  while(read(fd1,&t1,sizeof(struct train ))){
     write(sd,&t1,sizeof(struct train));
  }
  t1.number =-1;
  write(sd,&t1,sizeof(struct train ));
  close(fd1);
  
  adminMenu(sd);
}
// ###################################### SHOW USER ########################################################void 
void showUser(int sd){
  int fd1 = open("Accounts.dat", O_CREAT | O_RDWR , 0666);
  struct normal user;
  while(read(fd1,&user,sizeof(struct normal ))){
     write(sd,&user,sizeof(struct normal));
  }
  user.acc_id =-1;
  write(sd,&user,sizeof(struct normal ));
  close(fd1);
  
  adminMenu(sd);
}
// ###################################### DELETE USER ########################################################

void deleteUser(int sd){
   int user;
  
  
  read(sd,&user,sizeof(user)); 
  int fd1 = open("Accounts.dat", O_CREAT | O_RDWR , 0666);
  
  struct normal u;
  int ans =-1;
  int count=0;
  while(read(fd1,&u,sizeof(struct normal))){
     
     if(u.acc_id == user && u.status==1){
        u.status=0;
        int fd2 = open("Accounts.dat", O_CREAT |O_RDWR , 0666);
        lseek(fd2,count*(sizeof(struct normal)),SEEK_SET);
        write(fd2,&u,sizeof(struct normal));
        close(fd2);
        ans =1;
        break;
     }
     else if(u.acc_id == user && u.status==0){
       ans =0;
       break;
     }
     count++;
     
  }
  write(sd,&ans,sizeof(ans));
  close(fd1);
  adminMenu(sd);
}

// ###################################### ADMIN MENU ########################################################

void adminMenu(int sd){
   int choice;
	
	read(sd, &choice, sizeof(choice));
	
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
  
  read(sd, pass,sizeof(pass));
  int num  = 1;
  
  if( strcmp(pass, "123")==0  ){
    write(sd,&num,sizeof(num));
    
    adminMenu(sd);
    
  }
  else{
  num =-1;
   
  write(sd,&num,sizeof(num));
  
  }
  mainMenu(sd);
}

////////////////////////////////////////// NORMAL USER SECTION//////////////////////////////////////////////////////////////

// ###################################### UPDATE BOOKING ########################################################
void updateBooking(int sd){
  
   return;

  
}
void update(int train, int seats){
  
  int fd1 = open("trains.dat", O_CREAT|O_RDWR , 0666);
  
  struct train t1;
  int count=0;
  while(read(fd1,&t1,sizeof(struct train))){
     
     if(t1.number == train ){
        t1.seats=t1.seats + seats;
        
        int fd2 = open("trains.dat", O_CREAT |O_RDWR , 0666);
        lseek(fd2,count*(sizeof(struct train)),SEEK_SET);
        write(fd2,&t1,sizeof(struct train));
        close(fd2);
       break;
     }
     
    count++;
     
  }
   close(fd1); 
   
}
// ###################################### CANCEL BOOKING ########################################################
void cancelBooking(int sd,int id){
   int ticket;
   read(sd,&ticket,sizeof(ticket));
   
   
   int fd1 = open("bookings.dat", O_CREAT | O_RDWR , 0666); 
   struct booking b;
   int count=0;
   
   while(read(fd1, (char *)&b, sizeof(struct booking)))
	{
		if(b.customer_id == id && b.ticket_number==ticket )
			{
			   b.status = 0;
			   write(sd,"--TICKET CANCELLED--", 20);
			   int fd2 = open("bookings.dat", O_CREAT |O_RDWR , 0666);
                          lseek(fd2,count*(sizeof(struct booking)),SEEK_SET);
                          write(fd2,&b,sizeof(struct booking));
                          update(b.train_number,b.seats);
                          close(fd2);
			   close(fd1);
			   return ;
			}
		count++;		
	}
  	
	write(sd,"--TICKET NOT FOUND--", 20);
}


// ########################################################    ALL BOOKING ########################################################
void bookings(int sd,int id){
   struct flock lock;
	int fd= open("bookings.dat", O_CREAT | O_RDWR , 0666); 
	
	
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start =0;
	lock.l_len=0;
	lock.l_pid = getpid();
	fcntl(fd,F_SETLKW,&lock);
	   int fd1 = open("bookings.dat", O_CREAT | O_RDWR , 0666); 
	   struct booking b;
	   
	   
	   while(read(fd1, (char *)&b, sizeof(struct booking)))
		{
			if(b.customer_id == id )
				write(sd, &b, sizeof(struct booking));
					
		}
	   
	      b.customer_id=0;
	      b.ticket_number=0;
	      b.train_number=0;
	      b.seats=0;
	      b.status=0;
	      write(sd,&b,sizeof(struct booking));
	   close(fd1);
	   lock.l_type = F_UNLCK;
	   fcntl(fd,F_SETLK,&lock);
	   close(fd);
	   mainMenu(sd);  
}


// ########################################################   TICKET GENERATION ########################################################
int ticket(int id, int train, int seats){
        struct flock lock;
	int fd= open("bookings.dat", O_CREAT | O_RDWR , 0666); 
	
	
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start =0;
	lock.l_len=0;
	lock.l_pid = getpid();
	fcntl(fd,F_SETLKW,&lock);
	   int tick;
	   
	   int fd1 = open("bookings.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
	   
	   struct booking b;
	   int num =0;
	   while(read(fd1,&b,sizeof(struct booking))){
	     
	     num = b.ticket_number;
	     
	    
	     
	  }
	  b.customer_id = id;
	  b.ticket_number= num+13;
	  b.train_number =train;
	  b.seats = seats;
	  b.status= 1;
	  
	  write(fd1,&b,sizeof(struct booking));
	  close(fd1);
	lock.l_type = F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);
	  return num+13;
	   
	   

   
   
}
// ########################################################   TICKET BOOKING ########################################################

void bookTicket(int sd, int id){
   
   
   int train_number;
   
   
   read(sd,&train_number,sizeof(train_number));
   
   int num_seats =-1; // findSeat(train_number,t1);
   ////IMPLEMENT FIND SEATS
   
    int fd1 = open("trains.dat", O_CREAT | O_RDWR , 0666);
 
  struct train t1;
  int count =0;
  int status =1;
  while(read(fd1,&t1,sizeof(struct train))){
     
     if(t1.number == train_number ){
        num_seats =t1.seats;
        status= t1.status;
        if(status ==0) num_seats=-2; 
       break;
     }
     
    count++;
     
  }
   
  
   write(sd,&num_seats,sizeof(num_seats));
   
   if(num_seats==-1)
   return ;
   
   int book;
   read(sd,&book,sizeof(book));
    write(sd,"waiting for lock\n",18);
   int result ;
    
      struct flock lock;
        lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = count*sizeof(struct train);
	lock.l_len=  sizeof(struct train);
	lock.l_pid = getpid();
	
	int fd = open("trains.dat", O_CREAT | O_RDWR , 0666);
	
	struct train my ;
	
	fcntl(fd,F_SETLKW,&lock);
	
        write(sd,"press 0 for payment:",21);
        int zero;
        read(sd,&zero,sizeof(zero));
        
        if(zero==0){
          lseek(fd,count*sizeof(struct train),SEEK_SET);
	  read(fd,&my,sizeof(struct train));
          my.seats = my.seats-book;
          lseek(fd,count*sizeof(struct train),SEEK_SET);
          write(fd,&my,sizeof(struct train));
	  result = ticket(id,train_number,book);
        }
        else result =-1;
	lock.l_type = F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close (fd);
    
   write(sd,&result,sizeof(result));
   
  
   close(fd1);
   
}


// ########################################################   MENU FOR USER ########################################################
void menu(int sd, struct normal user){
   int choice;
	
	read(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
				
		case 1: bookTicket(sd,user.acc_id);
				break;
		case 2: bookings(sd,user.acc_id);
				break;
		case 3: updateBooking(sd);
				break;
		case 4: cancelBooking(sd,user.acc_id);
				break;
		default: exit(0);
		         break;
	       

	}
	
	mainMenu(sd);
}




// ########################################################   USER LOGIN ########################################################
void userLogin(int sd){

    char uname[20], pass[20];

	read(sd, uname, sizeof(uname));
	read(sd, pass, sizeof(pass));

	struct normal user;
	int flag=1;

	int fd1 = open("Accounts.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
	
	while(read(fd1, (char *)&user, sizeof(struct normal)))
	{

		if(!strcmp(user.uname, uname) && !strcmp(user.pass, pass) && user.status==1)
			{
				write(sd, &flag, sizeof(flag));
				write(sd, "----Login Successful----",25);
				menu(sd,user);
				close(fd1);
			
				return;		
			}
		if(!strcmp(user.uname, uname) && !strcmp(user.pass, pass) && user.status==0)
			{
			        flag=2;
				write(sd, &flag, sizeof(flag));
				write(sd, "--Login NOT Successful--",25);
				menu(sd,user);
				close(fd1);
			
				return;		
			}
	}

	close(fd1);
	flag=0;
	write(sd, &flag, sizeof(flag));
	write(sd, "Invalid Credentials", 19);
	mainMenu(sd);	

}





// ########################################################   AGENT LOGIN ########################################################

void agentLogin(int sd){
  char uname[20], pass[20];

	read(sd, uname, sizeof(uname));
	read(sd, pass, sizeof(pass));

	struct normal user;
	int flag=1;

	int fd1 = open("Accounts.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
	int count =0;
	while(read(fd1, (char *)&user, sizeof(struct normal)))
	{

		if(!strcmp(user.uname, uname) && !strcmp(user.pass, pass) && user.status==1)
			{
				
				write(sd, &flag, sizeof(flag));
				
				
				struct flock lock;
				lock.l_type = F_WRLCK;
				lock.l_whence = SEEK_SET;
				lock.l_start = count*sizeof(struct normal);
				lock.l_len=  sizeof(struct normal);
				lock.l_pid = getpid();
				
				int fd = open("Accounts.dat", O_CREAT | O_RDWR , 0666);
				
				struct normal my ;
				
				fcntl(fd,F_SETLKW,&lock);
				write(sd, "----Login Successful----",25);
				menu(sd,user);
				close(fd);
				
				lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				
				close (fd1);
				
			
				return;		
			}
		if(!strcmp(user.uname, uname) && !strcmp(user.pass, pass) && user.status==0)
			{
			        flag=2;
				write(sd, &flag, sizeof(flag));
				write(sd, "--Login NOT Successful--",25);
				menu(sd,user);
				close(fd1);
			
				return;		
			}
			
			count++;
	}

	close(fd1);
	flag=0;
	write(sd, &flag, sizeof(flag));
	write(sd, "Invalid Credentials", 19);
	mainMenu(sd);	
}


// ########################################################   FETCHING ID  ########################################################
int fetch_id(char *uname){
  //print("%s",uname);
  int ans;
  int fd1 = open("Accounts.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
  
  struct normal user;
  
  while(read(fd1, (char *)&user, sizeof(struct normal))){
   if(strcmp(user.uname, uname)==0){
    close(fd1);
    return -1;
   }
   
   ans  = user.acc_id;
  }
  
  close(fd1);
  return ans;
  
}



// ########################################################   ACCOUNT CREATION  ########################################################
void createAccount(int sd){
        
        struct normal user;
	read(sd, user.uname, sizeof(user.uname));
	read(sd, user.pass, sizeof(user.pass));
	
	
	
	int fd1 = open("Accounts.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
	
	int id  = fetch_id(user.uname);
	
	//user.uname = (char *)uname;
        //user.pass = (char *)pass;
	user.status =1;
	user.acc_id = id+17;
        
        int flag  = 1;
        lseek(fd1, 0, SEEK_END);
        if(id==-1){
         flag=0;
         write(sd,&flag, sizeof(flag));
        }
        else if(write(fd1, (char *)&user, sizeof(struct normal))==-1){
          perror("Error is: \n");
          flag ==-1;
          write(sd,&flag, sizeof(flag));
        }
        else
        write(sd,&flag, sizeof(flag));
        close(fd1);
        mainMenu(sd);
}



