#ifndef WFTIME_H
#define WFTIME_H
typedef struct wftm{//to store time
	int day; //ranges over 0 to 31
	int month; // ranges over 1 to 12
	int year; //ranges over integer values
	int hour; //ranges over 0 to 23 or 0 to 11 according to format
	int minute; //ranges over 0 to 59
	int second; //ranges over 0 to 59
	int daytime;//0 for 24H format 1 for a.m. 2 for p.m.
}wftime;
#endif
