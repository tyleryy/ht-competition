#ifndef __ABC_H
#define	__ABC_H
/*voice file name*/
typedef enum
{
	GAME_START = 1, WIN_1 = 2, WIN_2 = 3, POOR_SINGAL = 0

} voice_name;

void play_voice(voice_name voice);
void stop_playing(void);
#endif
