#ifndef ROOMINFO_H
#define ROOMINFO_H
typedef struct { //stores information of a room
	char num[5];//storing room no. (Hereby we assume N i.e. total no. of rooms never exceeds int size)
		    //serves as primary key for a room too .
	char whiteboard;//0 if room don't have white board 1 otherwise
	char pojector;//0 without audio 1 with audio
	char lcd;//0 if room don't have lcd display 1 otherwise
	char soundsys;//0 without mics for audience 1 with mics for audience
	char audiorec;//0 without mics for audience 1 with mics for audience
	char videorec;//0 without mics/camera for audience 1 with mics/camera for audience
	char aircond;//0 if room don't have air conditioning 1 otherwise
}roominfo;
#endif
