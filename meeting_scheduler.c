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
  int meeting_id, organiser_id, room_no;
  struct time start_time, end_time;
} *meetings;

void book(int organiser_id, struct time start_time, struct time end_time)
{
  int i,size,free_rooms[M], free_room_cnt, proposed_meeting_start_time, proposed_meeting_end_time, meeting_start_time, meeting_end_time;
  proposed_meeting_start_time = (start_time.hour * 60) + (start_time.minutes);
  proposed_meeting_end_time = (end_time.hour * 60) + (end_time.minutes);
  free_room_cnt = M;
  for(i=0; i<meeting_size; i++)
  {
    meeting_start_time = (meetings[i].start_time.hour * 60) + (meetings[i].start_time.minutes);
    meeting_end_time = (meetings[i].end_time.hour * 60) + (meetings[i].end_time.minutes);
    if(meeting_start_time <= proposed_meeting_start_time && proposed_meeting_start_time <= meeting_end_time)
    {
      free_rooms[meetings.room_no] = 1;
      free_room_cnt--;
    }
    else if(meeting_start_time <= proposed_meeting_end_time && proposed_meeting_end_time <= meeting_end_time)
    {
      free_rooms[meetings.room_no] = 1;
      free_room_cnt--;
    }
  }
  if(free_room_cnt == 0)
  {
    printf("Meeting booking failed\n");
  }
  else if(free_room_cnt > 0)
  {
    for(i=0; i<M; i++)
    {
      if(free_rooms[i]==0)
      {
        meetings[meeting_size].meeting_id = size;
        meetings[meeting_size].organiser_id = organiser_id;
        meetings[meeting_size].room_no = i;
        meetings[meeting_size].start_time.hour = start_time.hour;
        meetings[meeting_size].start_time.minutes = start_time.minutes;
        meetings[meeting_size].end_time.hour = end_time.hour;
        meetings[meeting_size].end_time.minutes = end_time.minutes;
        printf("Employee %d: (%d:%d - %d:%d at Room %d) success\n",  meetings[size].organiser_id, meetings[size].start_time.hour, meetings[size].start_time.minutes, meetings[size].end_time.hour, meetings[size].end_time.minutes, meetings[size].room_no);
        break;
      }
    }
  }
}

void cancel(int employee_id, int meeting_id)
{
  int i, size;
  size = sizeof(meetings)/sizeof(struct meeting);
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
  meeting_size = 0;
  return 0;
}
