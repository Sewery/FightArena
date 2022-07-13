#include "Timer.h"
Timer::Timer() {
	tStartTime = 0;
	tPausedTime = 0;
	tPaused = false;
	tStarted = true;
}
void Timer::start()
{
	tStarted = true;
	tPaused = false;

	tStartTime = SDL_GetTicks();
}
void Timer::pause()
{
	if (tStarted && !tPaused)
	{
		tPaused = true;

		tPausedTime = SDL_GetTicks() - tPausedTime;
		tStartTime = 0;
	}
}
void Timer::unpause()
{
	if (tStarted && tPaused)
	{
		tStarted = true;
		tPaused = false;

		tStartTime = SDL_GetTicks() - tPausedTime;
		tPausedTime = 0;
	}

}
void Timer::stop()
{
	
	tStarted = false;
	tPaused = false;

	tStartTime = 0;
	tPausedTime = 0;
}
int Timer::getTicks()
{
	if (!tStarted)
		return 0;
	if(tPaused)
		return tPausedTime;
	return SDL_GetTicks()- tStartTime;
}