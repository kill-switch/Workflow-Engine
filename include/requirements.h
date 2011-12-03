#ifndef REQUIREMENT_H
#define REQUIREMENT_H
typedef struct { //stores information of a room
	char whiteboard;//0 if white board not required else 1
	char projector;//0 without audio 1 with audio
	char lcd;//0 if lcd display not required else 1
	char soundsys;//0 without mics for audience 1 with mics for audience
	char audiorec;//0 without mics for audience 1 with mics for audience
	char videorec;//0 without mics/camera for audience 1 with mics/camera for audience
	char aircond;//0 if air conditioning not required else 1
}requirements;
#endif
