#ifndef __ABC_H
#define	__ABC_H
/*voice file name*/
typedef enum
{
	GAME_START = 0, GAME_OVER, POOR_SINGAL

}voice_name;

void play_voice(voice_name voice);
#endif
