#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>




// ############################################# EVENT STRUCT ##############################################
struct {

    int event_id        ;        //represents event id to uniquely identify events
    char event_name[50] ;        //represents event name
    char event_date[50] ;        //represents event date
    int numberOfDays    ;        //represents number of days that event will last
    int maxParticipants ;        //represents maximum participants allowed in that event
    int ticketSalePrice ;        //represents ticket selling price
    int ticketCostPrice ;        //represents ticket cost price 

} typedef Event ;



// ############################################# TICKET STRUCT ##############################################
struct{

    int event_id        ;        //represents event for which this ticket is
    char owner_name[50] ;        //represents owner name of ticket
    char number[50]     ;        //represents contact number of owner of this ticket
    char event_date[50] ;        //represents date of event of which this ticket is
    int seat_number     ;        //represents seat number of ground
 
} typedef Ticket ;

// ############################################# DATE STRUCT ##############################################
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

// ##################################### Function to get char[] and returns date #############################
Date convertToDate(char date[])
{
    int d,m,y;
    sscanf(date, "%d-%d-%d", &d,&m,&y);
    //making object of Date
    Date final ;
    final.dd = d ; 
    final.mm = m ;
    final.yyyy = y ;
    return final ;
}


// ##################################### Function to check if date has passed or not #########################
int checkDateHasPassed(Date checkDate)
{
    // return 1 ;
    //getting the current system date
    time_t rawtime;
    struct tm * timeinfo;
    Date currentDate ;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //compose current date
    // years since 1900
    currentDate.yyyy = timeinfo->tm_year+1900;
    // months since January - [0, 11]
    currentDate.mm = timeinfo->tm_mon+1;
    // day of the month - [1,28 or 29 or 30 or 31]
    currentDate.dd = timeinfo->tm_mday;


    if (false)
    {
        return 0;
    }
    else
    {
        if (checkDate.yyyy > currentDate.yyyy)
        {
            return 0;
        }
        else if (checkDate.yyyy < currentDate.yyyy)
        {
            return 1;
        }
        else
        {
            if (checkDate.mm > currentDate.mm)
            {
                return 0;
            }
            else if (checkDate.mm < currentDate.mm)
            {
                return 1;
            }
            else
            {
                return (checkDate.dd >= currentDate.dd)? 0 : 1;
            }
        }
    }
}

// ##################################### Function to get number of current events ############################
int getNumberofEvents()
{
    FILE* fptr = fopen("events.txt","r") ;
    char temp[100] ; int counter = 0 ;
    while (fgets(temp, 100, fptr) != NULL) {
        // printf("%s", temp);
        counter++ ;
    }
    fclose(fptr) ;
    return counter/7 ;
}

// ############################### Function to save all events data in Events array ######################
Event* getEventsData()
{
    char temp[50] ;
    int numberOfEvents = getNumberofEvents() ;
    Event *events = (Event*) malloc(numberOfEvents * sizeof(Event));   //allocating memory for events

    FILE *fptr = fopen("events.txt","r") ;
    for(int i=0; i<numberOfEvents; i++)
    {
        fgets(temp, 50, fptr) ;
        events[i].event_id = atoi(temp) ;
        // printf("%d\n",events[i].event_id) ;

        fgets(events[i].event_name, 50, fptr) ;
        //removing '\n' from event name
        strtok(events[i].event_name, "\n") ;
        // printf("%s",events[i].event_name) ;
        fgets(events[i].event_date, 50, fptr) ;
        //removing '\n' from event date
        strtok(events[i].event_date, "\n") ;
        // printf("%s",events[i].event_date) ;
        
        fgets(temp, 50, fptr) ;
        events[i].numberOfDays = atoi(temp) ;
        // printf("%d\n",events[i].numberOfDays) ;

        fgets(temp, 50, fptr) ;
        events[i].maxParticipants = atoi(temp) ;
        // printf("%d\n",events[i].maxParticipants) ;

        fgets(temp, 50, fptr) ;
        events[i].ticketCostPrice = atoi(temp) ;
        // printf("%d\n",events[i].ticketCostPrice) ;

        fgets(temp, 50, fptr) ;
        events[i].ticketSalePrice = atoi(temp) ;
        // printf("%d\n",events[i].ticketSalePrice) ;
    }
    fclose(fptr) ;                                                     //closing the file
    return events ;
}

// ################################# Function to save events data to file ###########################
void saveEventsData(Event* events)
{
    int numberOfEvents = getNumberofEvents() ;
    FILE *fptr = fopen("events.txt","w") ;
    for(int i=0; i<numberOfEvents; i++)
    {
        fprintf(fptr,"%d\n",events[i].event_id)        ;
        fprintf(fptr,"%s\n",events[i].event_name)      ;
        fprintf(fptr,"%s\n",events[i].event_date)      ;
        fprintf(fptr,"%d\n",events[i].numberOfDays)    ;
        fprintf(fptr,"%d\n",events[i].maxParticipants) ;
        fprintf(fptr,"%d\n",events[i].ticketCostPrice) ;
        fprintf(fptr,"%d\n",events[i].ticketSalePrice) ;
    }
    fclose(fptr) ;
}



// ################################# Function to compare dates #############################
bool isDateEqual(char d1[], char d2[])
{
    for(int i=0; i<10; i++)
    {
        if(d1[i]!=d2[i])
        {
            return false ;
        }
    }
    return true ;
}


// ################################# Function to check if given date already exists or not ############################
bool isDateExists(char date[])
{
    Event *events = getEventsData() ;
    int numberOfEvents = getNumberofEvents() ;
    
    for(int i=0;i<numberOfEvents;i++)
    {
        //checking if given date is present
        if(isDateEqual(date,events[i].event_date))
        {
            return true ;
        }
    }
    return false ;
}

//################################## Function to display all events #############################
void displayEventsData()
{
    int numberOfEvents = getNumberofEvents() ;
    Event *events = getEventsData() ;

    // printf("==========================================================================================================================================================") ;
    printf("\n\n%s \t %-15s \t %-15s \t %-15s \t %-15s \t %-15s \t %-15s","Event ID","Event Name","Event Date","Days","Participants","Ticket Costprice","Ticket Saleprice\n") ;
    printf("=========================================================================================================================================================\n\n") ;
    for(int i=0; i<numberOfEvents; i++)
    {
        printf("%d \t %18s \t %18s \t %10d \t %25d \t %20d \t %20d\n",events[i].event_id,events[i].event_name,events[i].event_date,events[i].numberOfDays,events[i].maxParticipants,events[i].ticketCostPrice,events[i].ticketSalePrice) ;
    }
}


//################################## Function to check if event id is valid ######################
bool isEventIDValid(int id)
{
    Event *events = getEventsData() ;
    int numberOfEvents = getNumberofEvents() ;
    for(int i=0; i<numberOfEvents; i++)
    {
        if(id==events[i].event_id)
        {
            return true ;
        }
    }
    return false ;
}

//################################## Function to input all event information from user ################################
Event inputEvent()
{
    Event final ;
    printf("Enter Event Name: ") ;
    scanf("%s",final.event_name) ;
    printf("Enter Event Date:(DD-MM-YYYY) ") ;
    scanf("%s",final.event_date) ;

    //validating if some event is already booked on this date
    while(isDateExists(final.event_date))
    {
        printf("Sorry, An event is already booked at this date!\n\n") ;
        printf("Enter Event Date:(DD-MM-YYYY) ") ;
        scanf("%s",final.event_date) ;
    }


    printf("Enter Number Of Days: ") ;
    scanf("%d",&final.numberOfDays) ;

    //input validation for number of days
    while(final.numberOfDays<=0)
    {
        printf("Enter valid number of days!\n\n") ;
        printf("Enter Number Of Days: ") ;
        scanf("%d",&final.numberOfDays) ;
    }

    printf("Enter Maximum Participants: ") ;
    scanf("%d",&final.maxParticipants) ;

    //input validation for maximum participants
    while(final.maxParticipants<=0 || final.maxParticipants>34567)
    {
        printf("Enter valid number of participants!\n\n") ;
        printf("Enter Maximum Participants: ") ;
        scanf("%d",&final.maxParticipants) ;
    }

    printf("Enter Cost Price Of Ticket: ") ;
    scanf("%d",&final.ticketCostPrice) ;

    while(final.ticketCostPrice<=0)
    {
        printf("Enter valid ticket cost price!\n\n") ;
        printf("Enter Cost Price Of Ticket: ") ;
        scanf("%d",&final.ticketCostPrice) ;
    }



    printf("Enter Sale Price Of Ticket: ") ;
    scanf("%d",&final.ticketSalePrice) ;

    //input validation for ticket sale price
    while(final.ticketSalePrice<=0)
    {
        printf("Enter valid ticket sale price!\n\n") ;
        printf("Enter Sale Price Of Ticket: ") ;
        scanf("%d",&final.ticketSalePrice) ;
    }

    //returning the final event
    return final ;
}

//################################## Function to update an event ########################################
void updateEvent()
{
    int numberOfEvents = getNumberofEvents() ;
    Event *events = getEventsData() ;

    //displaying all the data to user
    displayEventsData() ;   
    printf("\n\n") ;

    int id ;
    printf("Enter id you want to update: ") ;
    scanf("%d",&id) ;

    //checking if id is valid
    while(isEventIDValid(id)==false)
    {
        printf("Enter valid event id!\n\n") ;
        printf("Enter id you want to update: ") ;
        scanf("%d",&id) ;
    }

    //now taking input from user event details
    Event updatedEvent = inputEvent() ;

    //asking the user whether he wants to save the changes
    char sure[50] ;
    printf("\nAre you sure you want to save changes?(Y/N)\n") ;
    scanf("%s",sure) ;
    if(strcmp(sure,"Y")==0 || strcmp(sure,"y")==0)
    {
        //now updating the values of that event
        for(int i=0; i<numberOfEvents; i++)
        {
            if(id==events[i].event_id)
            {
                strcpy(events[i].event_name,updatedEvent.event_name) ;
                strcpy(events[i].event_date,updatedEvent.event_date) ;
                events[i].numberOfDays = updatedEvent.numberOfDays ;
                events[i].maxParticipants = updatedEvent.maxParticipants ;
                events[i].ticketCostPrice = updatedEvent.ticketCostPrice ;
                events[i].ticketSalePrice = updatedEvent.ticketSalePrice ;
            }
        }
        //updating event data in file
        saveEventsData(events) ;
        printf("\nEvent data has been updated successfully!\n\n") ;
        displayEventsData() ; //displaying the updated data
    }
    else
    {
        printf("Changes not saved!\n\n") ;
    }
}





// ######################################### Function to get last event's id ##################################
int getLastEventID()
{
    char id[10] ;
    FILE *fptr = fopen("eventID.txt","r") ;
    fscanf(fptr, "%[^\n]", id);
    fclose(fptr) ;
    return atoi(id) ; //returning the id
}

// ###################################### Function to update last event's id ###############################
void updateLastEventID(int id)
{
    FILE *fptr = fopen("eventID.txt","w") ;
    fprintf(fptr,"%d\n",id) ;
    fclose(fptr) ;
}


//########################################## Function to save event in file ####################################
void saveEventToFile(Event event)
{

    //getting last event id
    int lastID = getLastEventID() ;
    int newID = lastID+1 ;
    event.event_id = newID ;
    //updating new id in eventID file
    updateLastEventID(newID) ; 

    FILE *fptr = fopen("events.txt","a");                          //opening the file
    if(fptr!=NULL)                                                    
    {
        fprintf(fptr,"%d\n",event.event_id)        ;
        fprintf(fptr,"%s\n",event.event_name)      ;               //writing all event data to file
        fprintf(fptr,"%s\n",event.event_date)      ;
        fprintf(fptr,"%d\n",event.numberOfDays)    ;
        fprintf(fptr,"%d\n",event.maxParticipants) ;
        fprintf(fptr,"%d\n",event.ticketCostPrice) ;
        fprintf(fptr,"%d\n",event.ticketSalePrice) ;
        fclose(fptr) ;                                             //closing the file
    }
    else
    {
        printf("Error in opening event file!\n\n") ;
    }
    //if event has not passed, then make revenue file
    Date date = convertToDate(event.event_date) ;
    if(checkDateHasPassed(date)==false)
    {
        //making revenue file for this event
        char ID[50] ;
        itoa(event.event_id, ID, 50);
        char revenueFileName[50] ;
        strcpy(revenueFileName,ID) ;
        strcat(revenueFileName,"Revenues.txt") ;
        //making file of this event's ticket revenue
        FILE *revenueFile = fopen(revenueFileName,"w") ;
        fprintf(fptr,"%d",0);
        fclose(revenueFile) ;
    }
}


//##################################### Funtion to delete an event ##############################
void deleteEvent()
{
    int id ;
    //displaying all the events to user
    displayEventsData() ;
    printf("\n\n") ;
    printf("Enter Event ID you want to delete: ") ;
    scanf("%d",&id) ;

    //validating the event id
    while(isEventIDValid(id)==false)
    {
        printf("\nEnter Valid event ID!\n\n") ;
        printf("Enter Event ID you want to delete: ") ;
        scanf("%d",&id) ;
    }

    //asking the user whether he wants to save the changes
    char sure[50] ;
    printf("\nAre you sure you want to save changes?(Y/N)\n") ;
    scanf("%s",sure) ;
    if(strcmp(sure,"Y")==0 || strcmp(sure,"y")==0)
    {
        int numberOfEvents = getNumberofEvents() ;
        Event *oldEvents = getEventsData() ;
        Event *newEvents = (Event*) malloc((numberOfEvents-1) * sizeof(Event)) ; int index = 0 ;
        for(int i=0; i<numberOfEvents; i++)
        {
            if(id!=oldEvents[i].event_id)
            {
                //saving data to new events
                newEvents[index].event_id = oldEvents[i].event_id ;
                strcpy(newEvents[index].event_name,oldEvents[i].event_name) ;
                strcpy(newEvents[index].event_date,oldEvents[i].event_date) ;
                newEvents[index].numberOfDays = oldEvents[i].numberOfDays ;
                newEvents[index].maxParticipants = oldEvents[i].maxParticipants ;
                newEvents[index].ticketCostPrice = oldEvents[i].ticketCostPrice ;
                newEvents[index].ticketSalePrice = oldEvents[i].ticketSalePrice ;
                index ++ ;
            }
        }
        //saving data to file
        FILE *fptr = fopen("events.txt","w") ;
        for(int i=0; i<numberOfEvents-1; i++)
        {
            fprintf(fptr,"%d\n",newEvents[i].event_id)        ;
            fprintf(fptr,"%s\n",newEvents[i].event_name)      ;
            fprintf(fptr,"%s\n",newEvents[i].event_date)      ;
            fprintf(fptr,"%d\n",newEvents[i].numberOfDays)    ;
            fprintf(fptr,"%d\n",newEvents[i].maxParticipants) ;
            fprintf(fptr,"%d\n",newEvents[i].ticketCostPrice) ;
            fprintf(fptr,"%d\n",newEvents[i].ticketSalePrice) ;
        }
        fclose(fptr) ;

        printf("\nEvent has been deleted successfully!\n") ;
        displayEventsData() ;
    }
    else
    {
        printf("Changes not saved!\n\n") ;
    }
}


//#################################  Function to check if given date is reserved or not #####################
void checkDate()
{
    char date[50] ;
    printf("Enter date you want to check: ") ;
    scanf("%s",date) ;
    if(isDateExists(date)==true)
    {
        printf("Sorry! This date is already reserved!\n\n") ;
    }
    else
    {
        printf("This date is free! You can reserve this one!\n\n") ;
    }
}

// ################################# Function which displays the events which have passed ###############
void displayPassedEvents()
{
    int numberOfEvents = getNumberofEvents() ;
    Event* events = getEventsData() ;
    for(int i=0; i<numberOfEvents; i++)
    {
        //converting current event' date to Date type
        Date tempDate = convertToDate(events[i].event_date) ;
        //checking if this date has been passed
        if(checkDateHasPassed(tempDate))
        {
            //printing the current event
            printf("\n\nEvent iD: %d\n",events[i].event_id) ;
            printf("Event Name: %s\n",events[i].event_name) ;
            printf("Event Date: %s\n",events[i].event_date) ;
            printf("Event Days: %d\n",events[i].numberOfDays) ;
            printf("Event Participants: %d\n",events[i].maxParticipants) ;
            printf("Event CostPrice: %d\n",events[i].ticketCostPrice) ;
            printf("Event Name: %d\n\n",events[i].ticketSalePrice) ;
        }
    }
}

// ################################# Function which displays the incoming events ###############
void displayIncomingEvents()
{
    int numberOfEvents = getNumberofEvents() ;
    Event* events = getEventsData() ;
    for(int i=0; i<numberOfEvents; i++)
    {
        //converting current event' date to Date type
        Date tempDate = convertToDate(events[i].event_date) ;
        //checking if this date has been passed
        if(checkDateHasPassed(tempDate)==false)
        {
            //printing the current event
            printf("\n\nEvent iD: %d\n",events[i].event_id) ;
            printf("Event Name: %s\n",events[i].event_name) ;
            printf("Event Date: %s\n",events[i].event_date) ;
            printf("Event Days: %d\n",events[i].numberOfDays) ;
            printf("Event Participants: %d\n",events[i].maxParticipants) ;
            printf("Event CostPrice: %d\n",events[i].ticketCostPrice) ;
            printf("Event Name: %d\n\n",events[i].ticketSalePrice) ;
        }
    }
}


// ######################### Function to store the ticket information in file ################
void addTicketToFile(int eventID,Ticket ticket)
{
    char ID[50] ;
    itoa(eventID, ID, 50);
    char ticketsFileName[50] ;
    strcpy(ticketsFileName,ID) ;
    strcat(ticketsFileName,"Tickets.txt") ;
    //creating file
    FILE *fptr = fopen(ticketsFileName,"a") ;
    fprintf(fptr,"%d\n",ticket.event_id) ;
    fprintf(fptr,"%s\n",ticket.event_date) ;
    fprintf(fptr,"%s\n",ticket.owner_name) ;
    fprintf(fptr,"%s\n",ticket.number) ;
    fprintf(fptr,"%d\n",ticket.seat_number) ;
    fclose(fptr) ;
}

// ################################# Function to input ticket data ###########################
Ticket inputTicket(Event e)
{
    Ticket final ;
    final.event_id = e.event_id ;
    strcpy(final.event_date,e.event_date) ;
    printf("\nEnter Your name: ") ;
    scanf("%s",final.owner_name) ;
    printf("Enter your number: ") ;
    scanf("%s",final.number) ;
    printf("Enter seat number: ") ;
    scanf("%d",&final.seat_number) ;
    //validating the seat number
    while(final.seat_number<0)
    {
        printf("\nEnter Valid Ticket number!\n\n") ;
        printf("Enter seat number: ") ;
        scanf("%d",final.seat_number) ;
    }
    return final ;
}

//################################## Function to add ticket to revenue file ######################
void addTicketToRevenue(Event e)
{
    char ID[50] ;
    itoa(e.event_id, ID, 50);
    char revenueFileName[50] ;
    strcpy(revenueFileName,ID) ;
    strcat(revenueFileName,"Revenues.txt") ;
    //making file of this event's ticket revenue
    char tempRevenue[50] ;
    int oldRevenue ;
    FILE *fptr = fopen(revenueFileName,"r") ;
    fgets(tempRevenue, 50, fptr) ;
    oldRevenue = atoi(tempRevenue) ;
    fclose(fptr) ;
    //now calculating new revenue
    int newRevenue = e.ticketSalePrice-e.ticketCostPrice ;
    newRevenue += oldRevenue ;
    //now writing this new revenue to file
    fptr = fopen(revenueFileName,"w") ;
    fprintf(fptr,"%d",newRevenue) ;
    fclose(fptr) ; 
}

// ################################# Function to register ticket #############################
void registerTicket()
{
    Event* events = getEventsData() ;
    int numberOfEvents = getNumberofEvents() ;
    //displaying all the data to user
    displayEventsData() ;   
    printf("\n\n") ;

    int id ;
    printf("Enter id you want to get ticket for: ") ;
    scanf("%d",&id) ;

    //checking if id is valid
    while(isEventIDValid(id)==false)
    {
        printf("Enter valid event id!\n\n") ;
        printf("Enter id you want to get ticket for: ") ;
        scanf("%d",&id) ;
    }

    //getting the event for which ticket is being purchased
    Event presentEvent ;
    for(int i=0; i<numberOfEvents; i++)
    {
        if(id==events[i].event_id)
        {
            presentEvent = events[i] ;
        }
    }
    //checking if this event date has passed or not
    Date eventDate = convertToDate(presentEvent.event_date) ;
    if(checkDateHasPassed(eventDate))
    {
        printf("\nSorry! This event has been passed!\n\n") ;
    }
    else
    {
        //asking ticket details
        Ticket ticket = inputTicket(presentEvent);
       char sure[50] ;
        printf("\nAre you sure you want to save changes?(Y/N)\n") ;
        scanf("%s",sure) ;
        if(strcmp(sure,"Y")==0 || strcmp(sure,"y")==0)
        {
            //saving this event's ticket details to file
            addTicketToFile(id,ticket) ;
            //making revenue file for this event
            addTicketToRevenue(presentEvent) ;
        }
        else
        {
            printf("Changes not saved!\n\n") ;
        }
    }
}

// ################################### Function to get number of current tickets for an event ######################
int getNumberofTickets(int eventID)
{
    Event* events = getEventsData() ;
    char filename[50] ;
    itoa(eventID, filename, 50);
    strcat(filename,"Tickets.txt") ;
    FILE* fptr = fopen(filename,"r") ;
    char temp[100] ; int counter = 0 ;
    while (fgets(temp, 100, fptr) != NULL) {
        // printf("%s", temp);
        counter++ ;
    }
    fclose(fptr) ;
    return counter/5 ;
}

// ############################### Function to save all Tickets data in Tickets array ######################
Ticket* getTicketsData(int eventID)
{
    char temp[50] ;
    int numberOfTickets = getNumberofTickets(eventID) ;
    Ticket *tickets = (Ticket*) malloc(numberOfTickets * sizeof(Ticket));   //allocating memory for tickets

    Event* events = getEventsData() ;
    char filename[50] ;
    itoa(eventID, filename, 50);
    strcat(filename,"Tickets.txt") ;
    FILE *fptr = fopen(filename,"r") ;
    for(int i=0; i<numberOfTickets; i++)
    {
        fgets(temp, 50, fptr) ;
        tickets[i].event_id = atoi(temp) ;
        // printf("%d\n",events[i].event_id) ;

        fgets(tickets[i].event_date, 50, fptr) ;
        //removing '\n' from event name
        strtok(tickets[i].event_date, "\n") ;
        // printf("%s",events[i].event_name) ;
        fgets(tickets[i].owner_name, 50, fptr) ;
        //removing '\n' from event date
        strtok(tickets[i].owner_name, "\n") ;
        // printf("%s",events[i].event_date) ;
        
        fgets(tickets[i].number, 50, fptr) ;
        //removing '\n' from event date
        strtok(tickets[i].number, "\n") ;

        fgets(temp, 50, fptr) ;
        tickets[i].seat_number = atoi(temp) ;
        // printf("%d\n",events[i].numberOfDays) ;
    }
    fclose(fptr) ;                                                     //closing the file
    return tickets ;
}

//################################## Function to display all tickets #############################
void displayTicketsData()
{
    //displaying all the events 
    displayEventsData() ;
    //asking for event id of which user wants to see tickets for
    int eventID ;
    printf("Enter Event id you want to see tickets for: ") ;
    scanf("%d",&eventID) ;

    //checking if id is valid
    while(isEventIDValid(eventID)==false)
    {
        printf("Enter valid event id!\n\n") ;
        printf("Enter Event id you want to see tickets for: ") ;
        scanf("%d",&eventID) ;
    }

    int numberOfTickets = getNumberofTickets(eventID) ;
    Ticket *tickets = getTicketsData(eventID) ;

    // printf("==========================================================================================================================================================") ;
    printf("\n\n%s \t %-15s \t %-15s \t %-15s \t %-10s","Event ID","Owner Name","Number","Event Date","Seat Number\n") ;
    printf("=======================================================================================================================\n\n") ;
    for(int i=0; i<numberOfTickets; i++)
    {
        printf("%d \t %18s \t %18s \t %18s \t %17d\n",tickets[i].event_id,tickets[i].owner_name,tickets[i].number,tickets[i].event_date,tickets[i].seat_number) ;
    }
}


//################################# Funtion to display revenue of event ###########################
void displayRevenue()
{
    //displaying all the events 
    displayEventsData() ;
    //asking for event id of which user wants to see tickets for
    int eventID ;
    printf("Enter Event id you want to see tickets for: ") ;
    scanf("%d",&eventID) ;

    //checking if id is valid
    while(isEventIDValid(eventID)==false)
    {
        printf("Enter valid event id!\n\n") ;
        printf("Enter Event id you want to see tickets for: ") ;
        scanf("%d",&eventID) ;
    }

    Event *events = getEventsData() ; 
    Date date ;
    int numberOfEvents = getNumberofEvents() ;
    for(int i=0; i<numberOfEvents; i++)
    {
        if(events[i].event_id==eventID)
        {
            date = convertToDate(events[i].event_date) ;
        }
    }
    //checking if date has passed away
    if(checkDateHasPassed(date)==false)
    {
        char fileName[50] ; char temp[50] ;
        itoa(eventID,fileName,50) ;
        strcat(fileName,"Revenues.txt") ;
        //opening the file and reading revenue from this file
        FILE *fptr = fopen(fileName,"r") ;
        fgets(temp, 50, fptr) ;
        fclose(fptr) ;
        //now printing the revenue 
        printf("\nRevenue: %s\n\n",temp) ;
    } 
    else
    {
        printf("\nEvent date has been passed!\n\n") ;
    }
}


//################################## Funtion to display a welcome ############################
void welcome()
{
    printf("\n\n#################################################################################\n\n") ;
    printf("\t\t\tWELCOME TO EVENT MANAGEMENT SYSTEM\n\n") ;
    printf("#################################################################################\n\n") ;
}


//###################################### Function to display e menu ################################
int menu()
{
    int choice ;
    printf("\n1-View Events Data\n") ;
    printf("2-Add An Event\n") ;
    printf("3-Update An Event\n") ;
    printf("4-Delete An Event\n") ;
    printf("5-Check Date Is Available\n") ;
    printf("6-Display Passed Out Events\n") ;
    printf("7-Display Incoming Events\n") ;
    printf("8-Book A Ticket\n") ;
    printf("9-View Tickets Data\n") ;
    printf("10-View Revenues\n") ;
    printf("11-EXIT") ;
    printf("\nEnter your choice(1-11): ") ;
    scanf("%d",&choice) ;
    //validating the choice
    while(choice<1 || choice>11)
    {
        printf("\nEnter Valid Choice!\n\n") ;
        printf("\nEnter your choice(1-11): ") ;
        scanf("%d",&choice) ;
    }
    return choice ;
}

//################################### Function to drive application ##############################
void driver()
{
    welcome() ;
    int choice = 1 ;
    while(choice!=11)
    {
        choice = menu() ;
        if(choice==1)
        {
            displayEventsData() ;
        }
        else if(choice==2)
        {
            Event event = inputEvent() ;  //asking for event data
            //asking the user whether he wants to save the changes
            char sure[50] ;
            printf("\nAre you sure you want to save changes?(Y/N)\n") ;
            scanf("%s",sure) ;
            if(strcmp(sure,"Y")==0 || strcmp(sure,"y")==0)
            {
                saveEventToFile(event)     ;  //saving event to file   
                printf("Changes has been saved!\n\n") ;
            }
            else
            {
                printf("Changes not saved!\n\n") ;
            }
        }
        else if(choice==3)
        {
            updateEvent() ;
        }
        else if(choice==4)
        {
            deleteEvent() ;
        }
        else if(choice==5)
        {
            checkDate() ;
        }
        else if(choice==6)
        {
            displayPassedEvents() ;
        }
        else if(choice==7)
        {
            displayIncomingEvents() ;
        }
        else if(choice==8)
        {
            registerTicket() ;
        }
        else if(choice==9)
        {
            displayTicketsData() ;
        }
        else if(choice==10)
        {
            displayRevenue() ;
        }
    }
}
int main()
{
    // Event e = inputEvent();
    // saveEventToFile(e) ;

    // printf("%d",getNumberofEvents()) ;
    
    // Event* events = getEventsData() ;
    // int n = getNumberofEvents() ;

    // printf("%d",isDateExists("12-12-2022")) ;
    // displayEventsData() ;
    // updateEvent() ;

    // deleteEvent() ;
    // checkDate() ;
    // welcome() ;
    driver() ;
    // printf("%d",getNumberofTickets(1)) ;
    // displayTicketsData() ;
    // addTicketToFile(1) ;

    // convertToDate("11-12-2021") ;
    
    // registerTicket() ;
    

    // printf("%d",isDateEqual("1223","123")) ;

    return  0 ;
}