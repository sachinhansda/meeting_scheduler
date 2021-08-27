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
};

int main()
{
  return 0;
}
