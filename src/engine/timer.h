#ifndef _ENGINE_TIMER_H
#define _ENGINE_TIMER_H

#include "SDL2/SDL_timer.h"

typedef unsigned int Uint;

/** NOTE: Only the Engine can set the values in the static Ticks:: class.
 *  TODO: Convert Ticks into a namespace?
**/

class Timer
{
	private:
		Uint startTime;				//original time started			//prob will be implemented as a game timer
		Uint currentTime;			//total time running
		Uint pausedTime;			//loop start time
		bool timerStarted;
		bool isPaused;
	public:
		Timer(): startTime(0), currentTime(0), pausedTime(0), timerStarted(false), isPaused(true){}
		//getters
		const Uint& getGameTime(){return currentTime;}
		const bool& timerIsRunning(){return timerStarted;}
		const bool& timerIsPaused()	{return timerStarted;}
		
		inline void start(){
			if (!timerStarted){
				startTime = SDL_GetTicks();
				timerStarted = true;
				isPaused = false;
			}
		}
		
		inline void update(){
			if ( timerStarted && !isPaused )
				currentTime = SDL_GetTicks() - startTime - pausedTime;
		}
		
		inline void pause(){
			if (timerStarted && !isPaused){
				isPaused = true;
				pausedTime = currentTime;
			}
		}
				
		inline void resume(){
			if (timerStarted && isPaused){
				isPaused = false;
				pausedTime = SDL_GetTicks() - pausedTime - startTime;		
			}
		}
		
		inline void pauseResume(){
			if (timerStarted){
				if (!isPaused)
					pause();
				else resume();
			}
		}
		
		inline void stop()
		{
			timerStarted = false;
			isPaused = true;
			startTime = 0;
			currentTime = 0;
			pausedTime = 0;
		}
		
		/** Returns true if time in 'ms' have passed since your own 
		 *  reference time.
		**/
		inline static bool updateInterval( int ms, Uint& rtime ){
			if (rtime <= SDL_GetTicks() - ms){
				rtime = SDL_GetTicks() - ( SDL_GetTicks() % ms );		//align to nearest 'ms' interval
				return true;
			}
			return false;
		}
		
		/** This increases rtime by the interval time. It is meant to be
		 * 	used to update&catchup by calling it in a while loop.
		 * 	If time in 'ms' haven't passed, it retruns false, therefore
		 *  ending the while loop.
		**/
		inline static bool updateInterval( float ms, float& rtime ){
			if (rtime <= SDL_GetTicks() - ms){
				rtime += ms;
				return true;
			}
			return false;
		}
};


class Ticks
{
	friend class Engine;				//only engine can update and start this timer
	private:
		static Uint startTicks;			//loop start time
		static Uint deltaTicks;			//time the loop took to go around
		static Uint fps;
		static void start(){ startTicks = SDL_GetTicks(); }
		
		inline static void update(){
			deltaTicks = SDL_GetTicks() - startTicks;
			if (!deltaTicks){
				deltaTicks = 1;
				SDL_Delay (1);
			}
			fps = 1000 / deltaTicks;
		}
		
		inline static void capFPS(const Uint& maxfps){
			update();
			if( 1000 / deltaTicks >= maxfps ){
				SDL_Delay( ( 1000 / maxfps) - deltaTicks );
				update();
			}
			//'double precision' FPS capping method ;)
			//Once game gets bigger, this may be uneccessary
			//I should be using a High Resolution Timer
			if( 1000 / deltaTicks >= maxfps ){
				SDL_Delay( ( 1000 / maxfps) - deltaTicks );
				update();
			}
		}
	public:
		//Get the delta time
		inline static const Uint getDeltaTicks(){
			if (!deltaTicks)
				deltaTicks = 1;
			return deltaTicks; }
		//Get the FPS of rendering and logic cycle
		inline static const Uint getFPS(){
			if(!fps) fps=1;
			return fps;
		}
};


#endif
