# Online-Ticket-Reservation-System
A railway ticket resrvation system, coded in c and built using socket programming.
1. Language used C
2. Socket programming
3. Record locking
4. system call

## HOW TO RUN
1. In terminal write cc server.c -o ser
2. Run server by typing ./ser
3. In other terminal window  cc client.c -o cli
4. Connect client to server by typing ./cli
5. First login as admin , pswrd is "123"
6. Add some train
7. Create account
8. Login into your account
9. Now you are good to go

## FUNCTIONALIES 
### NORMAL USER
1. Book a ticket
2. Booking history (status shows whether ticket is cancelled (0) or not(1)
3. Cancel booking
4. Update booking

### ADMIN
1. Add train
2. Delete train
3. Show train
4. Show users
5. Modify train (change the number of seats)
6. Delete user

### AGENT
Simuntaneous login are managed through record locking
1. Book a ticket
2. Booking history (status shows whether ticket is cancelled (0) or not(1)
3. Cancel booking
4. Update booking

## SOME HIDDEN CHECKS 
1. You can't pick a username that already exists
2. Can't book a train that is cancelled
3. Can't book seats more than availabe seats
4. You can only confirm a ticket by pressing 0
5. If a ticket is cancelled, the seats get updated in the database
6. You will not be able to login if admin has deleted your account
7. Simuntaneous login of agent is prohibited
8. Admin can't add two train with same train number

## ABOUT FILES
1. client.c - It contains the client side code to connect to server
2. server.c - It contains the server side code
3. clientCode.h - It contains different functions code to execute on the client side
4. serverCode.h - It contains different functions code to be executed on server
5. struct.h - Different structure which is used for our database.
