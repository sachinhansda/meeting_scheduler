#include<stdio.h>
#include<time.h>

const int M = 1;
const int N = 5;

int meeting_size;

struct time
{
  int hour, minutes;
};

struct employee
{
  int employee_id;
  char employee_name[30];
};

struct meeting
{
  long meeting_id;
  int organiser_id, room_no;
  struct time start_time, end_time;
} *meetings;

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
  for(i=0; i<meeting_size; i++)
  {
    meeting_start_time = (meetings[i].start_time.hour * 60) + (meetings[i].start_time.minutes);
    meeting_end_time = (meetings[i].end_time.hour * 60) + (meetings[i].end_time.minutes);
    if(meeting_start_time <= proposed_meeting_start_time && proposed_meeting_start_time <= meeting_end_time)
    {
      free_rooms[meetings[i].room_no] = 1;
      free_room_cnt--;
      organiser_available = 0;
    }
    else if(meeting_start_time <= proposed_meeting_end_time && proposed_meeting_end_time <= meeting_end_time)
    {
      free_rooms[meetings[i].room_no] = 1;
      free_room_cnt--;
      organiser_available = 0;
    }
  }
  if(free_room_cnt == 0 || organiser_available == 0)
  {
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
        printf("Employee %d: (%d:%d - %d:%d at Room %d) success\n",  meetings[meeting_size].organiser_id, meetings[meeting_size].start_time.hour, meetings[meeting_size].start_time.minutes, meetings[meeting_size].end_time.hour, meetings[meeting_size].end_time.minutes, meetings[meeting_size].room_no);
        break;
      }
    }
  }
}

void cancel(int employee_id, int meeting_id)
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
        meetings[i].meeting_id = meetings[meeting_size].meeting_id;
        meetings[i].organiser_id = meetings[meeting_size].organiser_id;
        meetings[i].room_no = meetings[meeting_size].room_no;
        meetings[i].start_time.hour = meetings[meeting_size].start_time.hour;
        meetings[i].start_time.minutes = meetings[meeting_size].start_time.minutes;
        meetings[i].end_time.hour = meetings[meeting_size].end_time.hour;
        meetings[i].end_time.minutes = meetings[meeting_size].end_time.minutes;
        meeting_size--;
        printf("Success, meeting canceled");
        break;
      }
    }
  }
}

int main()
{
  struct time stime;
  long id;
  char c;
  int choice;
  meeting_size = 0;
  scanf("%d %c %d", &stime.hour, &c, &stime.minutes);
  id = ( 100 * stime.hour ) + stime.minutes;
  printf("%d hours %d minutes\n", stime.hour, stime.minutes);
  printf("id - %li\n", id);
  printf("Enter\n
          1 to book a meeting\n
          2 to cancel a meeting\n");
  scanf("%d", &choice);
  return 0;
}
