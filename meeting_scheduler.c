#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

const int M = 2;
const int N = 5;

int meeting_size;

//structure to store time details
struct time
{
  int hour, minutes;
};

//structure to store employee details
struct employee
{
  int employee_id;
  char employee_name[30];
};

//structure to store meeting details
struct meeting
{
  long meeting_id;
  int organiser_id, room_no;
  struct time start_time, end_time;
};

struct meeting meetings[48*M];
struct employee employees[N];

//function to initialize employee details
void employee_initialization()
{
  employees[0].employee_id = 1;
  strcpy(employees[0].employee_name,"Goku");

  employees[1].employee_id = 2;
  strcpy(employees[1].employee_name,"Naruto");

  employees[2].employee_id = 3;
  strcpy(employees[2].employee_name,"Natsu");

  employees[3].employee_id = 4;
  strcpy(employees[3].employee_name,"Izuku");

  employees[4].employee_id = 5;
  strcpy(employees[4].employee_name,"Shinichi");
}

//function to display employee details
void employee_details()
{
  int i;

  for(i=0; i<N; i++)
  {
    printf("Employee ID: %d\n", employees[i].employee_id);
    printf("Employee Name: %s\n", employees[i].employee_name);
    printf("\n");
  }

  printf("Press ENTER to return to main menu\n");
  getchar();
  getchar();
}

//function to book meeting
void book(int organiser_id, struct time start_time, struct time end_time)
{

  int i,free_rooms[M], organiser_available, free_room_cnt, proposed_meeting_start_time, proposed_meeting_end_time, meeting_start_time, meeting_end_time;
  proposed_meeting_start_time = (start_time.hour * 60) + (start_time.minutes);
  proposed_meeting_end_time = (end_time.hour * 60) + (end_time.minutes);
  free_room_cnt = M;
  organiser_available = 1;

  for(i=0; i<M; i++)
  {
    free_rooms[i] = 0;
  }

  if(meeting_size>0)
  {
    for(i=0; i<meeting_size; i++)
    {
      meeting_start_time = (meetings[i].start_time.hour * 60) + (meetings[i].start_time.minutes);
      meeting_end_time = (meetings[i].end_time.hour * 60) + (meetings[i].end_time.minutes);
      if(meeting_start_time <= proposed_meeting_start_time && proposed_meeting_start_time <= meeting_end_time)
      {
        free_rooms[meetings[i].room_no] = 1;
        free_room_cnt--;
        if(organiser_id == meetings[i].organiser_id)
          organiser_available = 0;
      }
      else if(meeting_start_time <= proposed_meeting_end_time && proposed_meeting_end_time <= meeting_end_time)
      {
        free_rooms[meetings[i].room_no] = 1;
        free_room_cnt--;
        if(organiser_id == meetings[i].organiser_id)
          organiser_available = 0;
      }
    }
  }

  if(free_room_cnt == 0 || organiser_available == 0)
  {
    if(free_room_cnt == 0)
      printf("No room is available\n");
    else if(organiser_available == 0)
      printf("Organiser is not available\n");
    printf("Meeting booking failed\n");
  }
  else if(free_room_cnt > 0 && organiser_available == 1)
  {
    for(i=0; i<M; i++)
    {
      if(free_rooms[i]==0)
      {
        meetings[meeting_size].meeting_id = (1000000 * start_time.hour) + (10000 * start_time.minutes) + (100 * end_time.hour) + end_time.minutes;
        meetings[meeting_size].organiser_id = organiser_id;
        meetings[meeting_size].room_no = i;
        meetings[meeting_size].start_time.hour = start_time.hour;
        meetings[meeting_size].start_time.minutes = start_time.minutes;
        meetings[meeting_size].end_time.hour = end_time.hour;
        meetings[meeting_size].end_time.minutes = end_time.minutes;
        printf("Employee %d: ", meetings[meeting_size].organiser_id);

        if(meetings[meeting_size].start_time.minutes < 10)
          printf("(%d:0%d", meetings[meeting_size].start_time.hour, meetings[meeting_size].start_time.minutes);
        else
          printf("(%d:%d", meetings[meeting_size].start_time.hour, meetings[meeting_size].start_time.minutes);

        printf(" - ");

        if(meetings[meeting_size].end_time.minutes < 10)
          printf("%d:0%d", meetings[meeting_size].end_time.hour, meetings[meeting_size].end_time.minutes);
        else
          printf("%d:%d", meetings[meeting_size].end_time.hour, meetings[meeting_size].end_time.minutes);

        printf(" at Room %d) success\n", meetings[meeting_size].room_no);
        meeting_size++;
        break;
      }
    }
  }

  printf("Press ENTER to return to main menu\n");
  getchar();
  getchar();
}

//function to cancel a meeting
void cancel(int employee_id, long meeting_id)
{
  int i;

  for(i=0; i<meeting_size; i++)
  {
    if(meetings[i].meeting_id == meeting_id)
    {
      if(meetings[i].organiser_id != employee_id)
      {
        printf("You are not the organizer of this meeting, hence you cannot cancel the meeting\n");
      }
      else
      {
        meetings[i].meeting_id = meetings[meeting_size-1].meeting_id;
        meetings[i].organiser_id = meetings[meeting_size-1].organiser_id;
        meetings[i].room_no = meetings[meeting_size-1].room_no;
        meetings[i].start_time.hour = meetings[meeting_size-1].start_time.hour;
        meetings[i].start_time.minutes = meetings[meeting_size-1].start_time.minutes;
        meetings[i].end_time.hour = meetings[meeting_size-1].end_time.hour;
        meetings[i].end_time.minutes = meetings[meeting_size-1].end_time.minutes;
        meeting_size--;
        printf("Success, meeting canceled\n");
        break;
      }
    }
  }

  printf("Press ENTER to return to main menu\n");
  getchar();
  getchar();
}

//function to display details of all the meetings
void show()
{
  int i;

  if(meeting_size==0)
  {
    printf("There is no meeting scheduled\n");
  }
  else if(meeting_size>0)
  {
    for(i=0; i<meeting_size; i++)
    {
      printf("Meeting ID: %li\n", meetings[i].meeting_id);
      printf("Organiser ID: %d\n", meetings[i].organiser_id);
      printf("Room No.: %d\n", meetings[i].room_no);
      printf("Timing: ");

      if(meetings[meeting_size].start_time.minutes < 10)
        printf("%d:0%d", meetings[meeting_size].start_time.hour, meetings[meeting_size].start_time.minutes);
      else
        printf("(%d:%d", meetings[meeting_size].start_time.hour, meetings[meeting_size].start_time.minutes);

      printf(" to ");

      if(meetings[meeting_size].end_time.minutes < 10)
        printf("%d:0%d", meetings[meeting_size].end_time.hour, meetings[meeting_size].end_time.minutes);
      else
        printf("%d:%d", meetings[meeting_size].end_time.hour, meetings[meeting_size].end_time.minutes);

      printf("\n\n");
    }
  }

  printf("Press ENTER to return to main menu\n");
  getchar();
  getchar();
}

//driver function
int main()
{

  struct time stime, etime;
  long id;
  char c;
  int choice, eid;
  meeting_size = 0;

  employee_initialization();

  do {
    system("clear");
    printf("Enter\n1 to book a meeting\n2 to cancel a meeting\n3 to show all meetings\n4 to show employee details\n0 to exit\n");
    scanf("%d", &choice);

    switch (choice) {
      case 0: system("clear");
              printf("Exiting the app\n");
              break;

      case 1: system("clear");
              printf("Enter employee id\n");
              scanf("%d", &eid);
              printf("Enter time in 24 hour format\n");
              printf("Enter meeting start time\n");
              scanf("%d %c %d", &stime.hour, &c, &stime.minutes);
              printf("Enter meeting end time\n");
              scanf("%d %c %d", &etime.hour, &c, &etime.minutes);
              book(eid,stime,etime);
              break;

      case 2: system("clear");
              if(meeting_size == 0)
              {
                printf("There is no meeting scheduled\n");
              }
              else if(meeting_size > 0)
              {
                printf("Enter employee id\n");
                scanf("%d", &eid);
                printf("Enter meeting id\n");
                scanf("%li", &id);
              }
              cancel(eid,id);
              break;

      case 3: system("clear");
              show();
              break;

      case 4: system("clear");
              employee_details();
              break;

      default:system("clear");
              printf("Invalid Choice\n");
              break;
    }
  } while(choice!=0);

  return 0;
}
