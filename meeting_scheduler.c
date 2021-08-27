#include<stdio.h>
#include<time.h>

const int M = 1;
const int N = 5;

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
  int meeting_id, organiser_id, room_no;
  struct time start_time, end_time;
} *meetings;

void book(int organiser_id, struct time start_time, struct time end_time)
{
  int i,size,free_rooms[M];
  for(i=0; i<M; i++)
  {
    if(free_rooms[i]==0)
    {
      size = sizeof(meetings)/sizeof(struct meeting);
      meetings[size].meeting_id = size;
      meetings[size].organiser_id = organiser_id;
      meetings[size].room_no = i;
      meetings[size].start_time.hour = start_time.hour;
      meetings[size].start_time.minutes = start_time.minutes;
      meetings[size].end_time.hour = end_time.hour;
      meetings[size].end_time.minutes = end_time.minutes;
      printf("Employee %d: (%d:%d - %d:%d at Room %d) success\n",  meetings[size].organiser_id, meetings[size].start_time.hour, meetings[size].start_time.minutes, meetings[size].end_time.hour, meetings[size].end_time.minutes, meetings[size].room_no);
      break;
    }
  }
}

void cancel(int employee_id, int meeting_id)
{

}

int main()
{
  return 0;
}
