#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>


typedef struct client
{
    char name[30];
    char username[10];
    char password[30];
    char phone[20];
    char email[30];
}client;

typedef struct bus
{
    int busNo;
    char destination[15];
    char day[10];
    char time[8];
    int seats;
}bus;

typedef struct reservation
{
    char fname[30];
    int busNo;
    int ticket;
}reservation;

void login(client *c, int l);
int signup(client **c, int *l);
int menu();
int emailCheck(char *email);
int usernameCheck(char *user);
int phoneCheck(char *phone);
int loginCheck(client *c, int l, char *user, char *pwd);
int search(bus *b, int l, int n);
int stringLength(char *a);
void copy(char *fromHere, char *toHere);
void quit(bus *b, client *c, reservation *r, int bl, int rl);
int overAgain();
void info(bus *b, int l);
void gotoxy(int column, int l);
int clientIp(client **c, char *fName, int *l);
int busIp(bus **b, char *fName, int *l);
int reservationIp(reservation **r, char *fName, int *l);
void booking(bus *b, reservation **r, int *l, int bl);
void display();
void displayBus(bus *b, int len);
void bookingSearch(reservation *r, int l);
int cancel(bus *b, reservation *r, int bl, int rl);
void displaytitle();

int main()
{
    client *clients = NULL; bus *b = NULL; reservation *reserved = NULL;
    char fileName[100]; int clength = 0, blength = 0, rlength = 0; int again, a;

    printf("~~~~~~~~~~~~~~~Bus Reservation System~~~~~~~~~~~~~~~\n");

    while(again = clientIp(&clients, fileName, &clength))
	{
 	 if(again == 2){ return 0; }
	}

	while(again = busIp(&b, fileName, &blength))
	{
 	 if(again == 2){ return 0; }
	}

	while(again = reservationIp(&reserved, fileName, &rlength))
	{
 	 if(again == 2){ return 0; }
	}

    login(clients, clength);

	while(1)
    {
        switch(menu())
        {
            case 1: info(b, blength); break;
            case 2: booking(b, &reserved, &rlength, blength); break;
            case 3: bookingSearch(reserved, rlength); break;
            case 4: {a = cancel(b, reserved, blength, rlength);} break;
            case 5:
                {
                    if(a != 0){rlength -= 1;}
                    quit(b, clients, reserved, blength, rlength);
                    return 0;
                }
        }
    }

    return 0;
}

//First page to login before going to the app
void login(client *c, int l)
{
    system("cls");
    char user[10], pwd[30];
    char ans;
    int i = 0;
    printf("\t\t\tPlease Log in to continue!\n");
    printf("Username (No more than 10 characters): "); scanf("%s", user);

    fflush(stdin);
    printf("Password (No more than 30 characters): ");
    do{
        pwd[i]=getch();
        if(pwd[i]!='\r'){
            printf("*");
        }
        i++;
    }while(pwd[i-1]!='\r');
    pwd[i-1]='\0';
    printf("\n");

    if(loginCheck(c, l, user, pwd))
    {
        printf("ERROR: username and password didn't match!!!\n");

        fflush(stdin);
        printf("Do you want to sign up? "); scanf(" %c", &ans);

        if(ans == 'y')
        {
            signup(&c, &l);
            login(c, l);
        }
        else
            exit(0);
    }
    else
    {
        printf("Login Sucessful!!");

    }
}

//calculate every string length
int stringLength(char *a)
{
    int i = 0;
    while(a[i]){i++; }
    return i;
}

//check whether the input has special character
int userCheck(char *user)
{
    for(int i = 0; i < stringLength(user); i++)
    {
        if(isalpha(user[i]) || isdigit(user[i]))
            continue;
        else
            return 1;

    }
    return 0;
}

//check if both username and password match with the ones in db or not
int loginCheck(client *c, int l, char *user, char *pwd)
{
    int userLength = stringLength(user);
    int pwdLength = stringLength(pwd);
    int i, j;
    for(i = 0; i < l; i++)
	{
		if((userLength == stringLength(c[i].username)) && (pwdLength == stringLength(c[i].password)))
		{
			return strcmp(user, c[i].username) + strcmp(user, c[i].username);
		}
	}
	return 1;
}

//if there is no username and pwd match with db, this will ask user
//to sign up and save new client info
int signup(client **c, int* l)
{
    char name[30], username[10], password[30], phone[20], email[30];

    printf("\t\t\t---SIGN UP---\n");
    printf("Full Name(Do not include whitespace):"); scanf("%s", name);

    fflush(stdin);
    printf("Username(No more than 10 characters):"); scanf("%s", username);
    if(userCheck(username))
	{
	 printf("ERROR: It shouldn't contain special characters!\n");
	 if(!(overAgain())){ return 1; }else{ return 0; }
	}

	fflush(stdin);
    printf("Password (No more than 30 characters): ");
    int i = 0;
    do{
        password[i]=getch();
        if(password[i]!='\r'){
            printf("*");
        }
        i++;
    }while(password[i-1]!='\r');
    password[i-1]='\0';
    printf("\n");

    fflush(stdin);
    printf("Phone Number\t:"); scanf("%s", phone);
    if(phoneCheck(phone))
	{
	 printf("ERROR: phone number is invalid!\n");
	 if(overAgain()){ return 1; }else{ return 0; }
	}

	fflush(stdin);
	printf("Email\t\t\t:"); scanf("%s", email);
    if(emailCheck(email))
	{
	 printf("ERROR: Email is invalid!\n");
	 if(overAgain()){ return 1; }else{ return 0; }
	}

    copy(name, (*c)[*l-1].name);

    copy(username, (*c)[*l-1].username);

    copy(password, (*c)[*l-1].password);

	copy(email, (*c)[*l-1].email);

	copy(phone, (*c)[*l-1].phone);

    FILE *output = fopen("clientList.txt", "a");
	fprintf(output, "%-20s%-15s%-15s%-20s%10s\n", (*c)[*l-1].name, (*c)[*l-1].username, (*c)[*l-1].password, (*c)[*l-1].phone, (*c)[*l-1].email);

	fclose(output);
	return 1;
}

//copy function to put it to structure
void copy(char *fromHere, char *toHere){
	int i = 0;
	while(fromHere[i]){	toHere[i] = fromHere[i]; i++;	}
	toHere[i] = 0;
}

//check if the email is vaild or not eg: "****@yahoo.com"
int emailCheck(char *email)
{
    int i = 0, dotIndex, atIndex, numberOfDots = -1, numberOfAts = -1, diff;

	while(email[i])
	{
		if(email[i] == '.'){	dotIndex = i; numberOfDots++;	}
		if(email[i] == '@'){	atIndex = i; numberOfAts++;	}
		i++;
	}

	if((diff = dotIndex - atIndex) < 0)
        return 1;
	if(numberOfDots || numberOfAts)
        return 1;
	if(!dotIndex || !atIndex || dotIndex == i-1 || atIndex == i-1 || diff == 1)
        return 1;


	return 0;
}

//to check if the phone number is valid or not
int phoneCheck(char *phone)
{
    int i = 0;

	while(phone[i])
	{
		if(phone[i] < '0' || phone[i] > '9')
            return 1;
        i++;
	}
	return 0;
}

//Main Menu after logging in
int menu()
{
    system("cls");
    int choice;
    gotoxy(17, 5);
    printf("~~~~~~~~~~~~~~~Bus Reservation System~~~~~~~~~~~~~~~");

    gotoxy(17, 18);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(22, 8);
    printf("1. Buses Information");

    gotoxy(22, 10);
    printf("2. Bus Reservation");

    gotoxy(22, 12);
    printf("3. Reservation status search");

    gotoxy(22, 14);
    printf("4. Cancel Reservation");

    gotoxy(22, 16);
    printf("5.Exit");

    gotoxy(22, 20);
    printf("Enter your choice: "); scanf("%d", &choice);
    return choice;
}

//for finding x,y coordinates
COORD coord = { 0, 0 };

void gotoxy(int column, int l)
{
    coord.X = column; coord.Y = l;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//displaying bus info(will be in the table format)
void info(bus *b, int l)
{
    display();
    gotoxy(5, 7);
    printf("Bus No\t\tDestination\t\tDays\t\tTime\t\tAvailable seat numbers");

    gotoxy(5, 8);
    printf("=================================================================================================");

    gotoxy(5,10);
    for(int i = 0; i < l; i++)
    {
        printf("%-10d\t\t%-10s\t\t%5s\t\t%3s\t\t%2d", b[i].busNo, b[i].destination, b[i].day, b[i].time, b[i].seats);
        printf("\n");
        gotoxy(5, coord.Y + 2);
    }

	printf("\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\nPress any key to return to Main Menu.");

    getch();
}

//book the ticket
void booking(bus *b, reservation **r, int *l, int bl)
{
    int busN, seat, a, tickets, temp, again = 0;
    char conf, fname[30];
    displayBus(b, bl);
    printf("Enter the bus No: ");   scanf("%d", &busN);
    a = search(b, bl, busN);

    //will run until the user enter the bus no that exists
    do
    {
        if(a == -1)
        {
            printf("Error! The bus number you entered doesn't exist!!!!!!");
            printf("Enter the bus No: ");   scanf("%d", &busN);
        }
    }while(a == -1);

    if(b[a].seats == 0)
        printf("Sorry! There was no seat left..\n");
    else
    {
        printf("Available seats: %d\n", b[a].seats);
        fflush(stdin);

        //will ask ticket number and run again if there is no available seats
        do
        {
            printf("Enter the number of tickets you would like to buy:\n"); scanf("%d", &tickets);
            temp = b[a].seats - tickets;
            if(temp < 0)
            {
                printf("Error! The ticket numbers exceed the available seats!!!\n");
                again = overAgain();
            }

            else
            {
                fflush(stdin);
                printf("Enter the full name(Do not include whitespace): "); scanf("%s", fname);
                printf("The total would be: %d ft", tickets * 1000);

                fflush(stdin);
                printf("\nWould you like to confirm?(y/n): "); scanf("%c", &conf);
                if(conf == 'y')
                {
                    if(!(*r = (reservation *)realloc(*r, ++(*l)*sizeof(reservation))))
                    {
                        printf("ERROR: there is no memory enough\n");

                    }
                    b[a].seats = temp;
                    copy(fname, (*r)[*l-1].fname);
                    (*r)[*l-1].busNo = b[a].busNo;
                    (*r)[*l-1].ticket = tickets;


                    printf("Booking confirmed!\n");
                }

            }
        }while(again == 1);
    }
    printf("\nPress any key to return to Main Menu.");

    getch();
}

//Use the name entered by user and output the matched booking
void bookingSearch(reservation *r, int l)
{
    char name[30];
    int i, j, n = 0, again = 0;
    int namelength = 0;
    do
    {
        display();
        gotoxy(5, 7);
        fflush(stdin);
        printf("Enter the full name you used to book ticket: "); scanf("%s", name);
        namelength = stringLength(name);
        system("cls");

        gotoxy(5, 7);
        printf("\t\t~~~~~~~~~~SEARCH RESULTS~~~~~~~~~~\n");
        printf("\t===================================================");
        displaytitle();
        for(i = 0; i < l; i++)
        {
            if(namelength == stringLength(r[i].fname))
            {
                if((strcmp(name, r[i].fname)) == 0)
                {
                    printf("%-10s\t\t%-10d\t\t%5d", r[i].fname, r[i].busNo, r[i].ticket);
                    gotoxy(5, coord.Y + 2);
                    n++;
                }
            }

        }

        if(n == 0)
        {
            printf("\nError!!! There is no booking made with the name you entered!\n");
            fflush(stdin);
            again = overAgain();
        }
    }while(again);

    printf("\nPress any key to return to Main Menu.");
    getch();
}

//cancel the booking using the name and busNo
int cancel(bus *b, reservation *r, int bl, int rl)
{
    system("cls");
    char name[30], ans; int bNo, j, n, a = 0;
    char *nullStr = '\0';
    fflush(stdin);
    printf("Enter the name: "); scanf("%s", name);
    printf("Enter the bus Number: "); scanf("%d", &bNo);

    for(int i = 0; i < rl; i++)
    {
        if((strcmp(name, r[i].fname) == 0) && (bNo == r[i].busNo))
        {
            displaytitle();
            printf("%-10s\t\t%-10d\t\t%5d", r[i].fname, r[i].busNo, r[i].ticket);
            gotoxy(5, coord.Y + 2);

            fflush(stdin);
            printf("Are you sure you wanna cancel the reservation? (y/n): "); scanf("%c", &ans);

            if(ans == 'y' || 'Y')
            {
                n = search(b, bl, bNo);
                b[n].seats += r[i].ticket;

                if(i != rl-1)
                {
                    for(j = i; j < rl -1; j++)
                    {
                        strcpy(r[j].fname, r[j+1].fname);
                        r[j].busNo = r[j+1].busNo;
                        r[j].ticket = r[j+1].ticket;
                    }

                }
                a++;
                printf("\nReservation cancelled!!");
                //getch();
            }
        }
    }

    if(a == 0)
        printf("Cannot find the reservation!!!");

    printf("\nPress any key to return to Main Menu.");
    getch();
    return a;
}
//exiting the program and save data into txt file
void quit(bus *b, client *c, reservation *r, int bl, int rl)
{
    FILE *fp, *rfp = NULL; char end; int i;

    fflush(stdin);
    printf("Do you want to save all the changes?(y/n): "); scanf("%c", &end);

    if(end == 'y' || 'Y')
    {
        fp = fopen("busList.txt", "w");
        for(i = 0; i < bl; i++)
            fprintf(fp, "%10d%10s%10s%10s%10d\n", b[i].busNo, b[i].destination, b[i].day, b[i].time, b[i].seats);
        fflush(fp);
        fclose(fp);

        rfp = fopen("reservedList.txt", "w");
        for(i = 0; i < rl; i++)
            fprintf(fp, "%10s%10d%10d\n", r[i].fname, r[i].busNo, r[i].ticket);
        fflush(rfp);
        fclose(rfp);
    }

    free(b); free(c); free(r);

    system("cls");
    printf("Thank you for using our service!!");
}
//run the function again or not
int overAgain(){
 char again;
 printf("Do you want to try again? (y / n) "); scanf(" %c", &again);
 if(again == 'y'){ return 1; }
 else{ return 0; }
}

//inputting clientList data into the program
int clientIp(client **c, char *fName, int *l)
{
	FILE *fp; char ch; int i;
    fName = "clientList.txt";
    fp = fopen(fName, "r");

	if(fp == NULL)
	{
	 printf("ERROR: file cannot be opened. (Its path may be wrong).\n");
	 if(overAgain()){ return 1; }else{ printf("Program exits.\n"); return 2; }
	}

	*c = malloc( sizeof(struct client) * (*l) );

	if( ! (*c) )
    {
        perror( "malloc failed" );
        fclose( fp );
        return 0;
    }

	while((ch = fgetc(fp)) != EOF)
	{
		if(ch == '\n'){ (*l)++; }
	}

	if(!(*c = (struct client *)malloc(*l*sizeof(struct client))))
	{
	 printf("ERROR: there is no memory enough.\n");
	 if(overAgain()){ return 1; }else{ printf("Program exits.\n"); return 2; }
	}

	rewind(fp);

	for(i = 0; i < *l; i++)
	{
		fscanf(fp, "%s%s%s%s%s", (*c)[i].name, (*c)[i].username, (*c)[i].password, (*c)[i].phone, (*c)[i].email);
	}

	fclose(fp);
	return 0;
}

//inputting busList into the program
int busIp(bus **b, char *fName, int *l)
{
	FILE *fp; char ch; int i = 0;
    fName = "busList.txt";

    fp = fopen(fName, "r");
	if(fp == NULL)
	{
	 printf("ERROR: file cannot be opened. (Its path may be wrong).\n");
	 if(overAgain()){ return 1; }else{ printf("Program exits.\n"); return 2; }
	}

	*b = malloc( sizeof(struct bus) * (*l) );

	if( ! (*b) )
    {
        perror( "malloc failed" );
        fclose( fp );
        return 0;
    }
	while((ch = fgetc(fp)) != EOF)
	{
		if(ch == '\n'){ (*l)++; }
	}

	if(!(*b = (struct bus *)malloc(*l*sizeof(struct bus))))
	{
	 printf("ERROR: there is no memory enough.\n");
	 if(overAgain()){ return 1; }else{ printf("Program exits.\n"); return 2; }
	}

	rewind(fp);

	for(i = 0; i < *l; i++)
	{
		fscanf(fp, "%d%s%s%s%d", &(*b)[i].busNo, (*b)[i].destination, (*b)[i].day, (*b)[i].time, &(*b)[i].seats);
	}


	fclose(fp);
	return 0;
}

//inputting the reservation data into program(reservation struct)
int reservationIp(reservation **r, char *fName, int *l)
{
	FILE *fp = NULL; char ch; int i;
    fName = "reservedList.txt";

	if(!(fp = fopen(fName, "r")))
	{
	 printf("ERROR: file cannot be opened. (Its path may be wrong).\n");
	 if(overAgain()){ return 1; }else{ printf("Program exits.\n"); return 2; }
	}

	while((ch = fgetc(fp)) != EOF)
	{
		if(ch == '\n'){ (*l)++; }
	}

	if(!(*r = (reservation *)malloc(*l*sizeof(reservation))))
	{
	 printf("ERROR: there is no memory enough.\n");
	 if(overAgain()){ return 1; }else{ printf("Program exits.\n"); return 2; }
	}

	rewind(fp);

	for(i = 0; i < *l; i++)
	{
		fscanf(fp, "%s%d%d", (*r)[i].fname, &(*r)[i].busNo, &(*r)[i].ticket);
	}

	fclose(fp);
	return 0;
}

//will look for the bus number user entered in the bus struct and return the position
int search(bus *b, int l, int n)
{
    int i;
    for(i = 0; i < l; i++)
    {
        if(n == b[i].busNo)
            return i;
    }
    return -1;
}

void display()
{
    system("cls");
    gotoxy(5, 4);
    printf("\t\t>>>>>>>>>>>>>>>Bus Reservation System<<<<<<<<<<<<<<<");

    gotoxy(5, 6);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}

//for displaying bus number and destination to book tickets
void displayBus(bus *b, int len)
{
    display();
    gotoxy(5, 7);
    printf("Bus No\t\tDestination");
    gotoxy(5, 8);
    printf("======================================================================");

    gotoxy(5,10);
    for(int i = 0; i < len; i++)
    {
        printf("%-10d\t\t%-10s", b[i].busNo, b[i].destination);
        printf("\n");
        gotoxy(5, coord.Y + 2);
    }
}

void displaytitle()
{
    gotoxy(5, 9);
    printf("Full Name\t\tBus Number\t\tNumber of Tickets");
    gotoxy(3, 11);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5, 13);
}
