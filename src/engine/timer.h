#ifndef _ENGINE_TIMER_H
#define _ENGINE_TIMER_H

#include "SDL2/SDL_timer.h"

typedef unsigned int Uint;

/**	This file contains implementations of Timer(32 and 64 bit),
 *	Interval(returns true when _ms_ have passed) and Ticks(FPS control).
 *	
 *	TODO:
 *	Should Ticks be renamed to something like FPS or FPSCounter?
 *	
 *	NOTE:
 *	Convert SDL's time+frequency to a my time+frequency.
 *	localTime = (SDL_GetTicks() * ticksPerSecond) / 1000 ;
 **/
 
template<typename T>
class iTimer
{
private:
	T startTime;		/*	Original starting time.	*/
	T stopTime;			/*	Time when the timer was stopped.	*/
	T currentTime;		/*	Total time running.	*/
	T pausedTime;		/*	Holds the time paused.	*/
	bool started;
	bool paused;
	
	virtual const T getTicks() =0;
public:
	iTimer(): startTime(0), stopTime(0), currentTime(0),
				pausedTime(0), started(false), paused(true){}
	const T& getTime(){ return currentTime; }
	const bool isRunning(){ return ( started && !paused ); }
	const bool isPaused(){ return paused; }
	
	inline void start(){
		if (!started){
			startTime = getTicks();
			started = true;
			paused = false;
		}
	}
	
	inline T& update(){
		if ( started && !paused )
			currentTime = getTicks() - startTime - pausedTime;
		return currentTime;
	}
	
	inline void pause()
	{
		if (started && !paused){
			update();
			paused = true;
			pausedTime = currentTime;
		}
	}
			
	inline void resume(){
		if (started && paused)
		{
			paused = false;
			update();
			pausedTime = currentTime;
			update();
			
		}
	}
	
	inline void pauseResume(){
		if (started){
			if (!paused)
				pause();
			else resume();
		}
	}
	
	inline void stop()
	{
		if ( started )
		{
			stopTime = update();
			started = false;
			paused = true;
			startTime = 0;
			currentTime = 0;
			pausedTime = 0;
		}
	}


};

template<typename T> class Timer;
/*	Timer<Uint32> can *only* run for ~49 days. This is more useful for
 *	simple, non-core timers.
 */
template<> class Timer<Uint32> : public iTimer<Uint32>
{
protected:
	const Uint32 getTicks(){ return SDL_GetTicks(); }
};
/*	Timer<Uint64> is useful for timers that need to be run for long periods
 *	of time, like the game client, or more likely, the Server. Also supports
 * 	higher accuracy.
 */
template<> class Timer<Uint64> : public iTimer<Uint64>
{
protected:
	const Uint64 getTicks(){ return SDL_GetPerformanceCounter(); }
};


/*	Interval is used for anything that needs to be updated in intervals.
 *	e.g. Some interface info could be updated every 1sec, or animation 
 *	could be updated every 70ms.
 *	This could be turned into or bundled with an action and/or event. (or binded within)
 *	Tell it to execute something when the interval passes.(wouldn't be good
 *	for animation because the animation changes too much, it's better if
 *	whatever has the animation and Interval timer controls that program flow.)
 *
 * 	NOTE: Since the reference time is always reset, this is not suitable
 *	for persistant timing because of loss of precision.
 *	There is no support to have the reference time incremented by the
 *	ms to update multiple times. Instead the reference time will be set to the
 *	current tick count.
 */

template<typename T>
class iInterval
{
protected:
	T interval;
	T referenceTime;
	virtual T getTicks() =0;
public:
	iInterval() :referenceTime(0) {}
	iInterval( Uint32 interval ) :interval(interval), referenceTime(0) {}
	
	inline Uint32 get(){ return interval; }
	inline void set(Uint32 interval){ this->interval = interval; }
	inline void resetTime(){ referenceTime = getTicks() - ( getTicks() % interval ); }
	
	inline bool check(const Uint32 interval)
	{
		if ( (referenceTime <= getTicks() - interval) ){
			/*	Align to nearest 'ms' interval	*/
			resetTime();
			if (referenceTime > interval)
				return true;
		}
		return false;
	}
	inline bool check(){ return check(interval); }
	//inline bool catchup(){
		//if ( check() )
			//referenceTime += ms;
	//}
	
	inline bool operator()(){ return check(); }
	inline void operator()(Uint32 interval){ this->interval = interval; }
};

template<typename T> class Interval : public iInterval<Uint32>
{
private:
	inline Uint32 getTicks(){ return SDL_GetTicks(); }
public:
	Interval(){}
	Interval( Uint32 interval ) :iInterval<Uint32>::iInterval(interval) {}
	inline bool operator()(){ return check(); }
	inline void operator()(Uint32 interval){ this->interval = interval; }
};
template<> class Interval<Uint32> : public iInterval<Uint32>
{
private:
	inline Uint32 getTicks(){ return SDL_GetTicks(); }
public:
	Interval(){}
	Interval( Uint32 interval ) :iInterval<Uint32>::iInterval(interval) {}
	inline bool operator()(){ return check(); }
	inline void operator()(Uint32 interval){ this->interval = interval; }
};
template<> class Interval<Uint64> : public iInterval<Uint64>
{
private:
	inline Uint64 getTicks(){ return SDL_GetPerformanceCounter(); }
public:
	Interval(){}
	Interval( Uint64 interval ) :iInterval<Uint64>::iInterval(interval) {}
	inline bool operator()(){ return check(); }
	inline void operator()(Uint32 interval){ this->interval = interval; }
};
typedef Interval<Uint32> Interval32;
typedef Interval<Uint64> Interval64;


/*	High resolution timer for framerate control. Only engine can update
 * 	and start this timer.
 *	TODO:
 * 	Should the getDeltaTicks return deltaTicks / 1000 so its in milliseconds?
 */
class Ticks
{
friend class Engine;
private:
	Uint64 ticksPerSecond;
	Uint64 startTicks;			//loop start time
	Uint64 deltaTicks;			//time the loop took to go around
	Uint32 fps;
	void start(){ startTicks = SDL_GetPerformanceCounter(); }
	
	inline void update(){
		deltaTicks = SDL_GetPerformanceCounter() - startTicks;
		if (!deltaTicks){
			deltaTicks = 1;
			SDL_Delay(1);
		}
		fps = ticksPerSecond / deltaTicks;
	}
	
	inline void capFPS(Uint32 maxfps){
		update();
		if( ticksPerSecond / deltaTicks >= maxfps ){
			SDL_Delay( ( ( ticksPerSecond / maxfps) - deltaTicks  ) / 1000 );
			update();
		}
		if( ticksPerSecond / deltaTicks >= maxfps ){
			SDL_Delay( ( ( ticksPerSecond / maxfps) - deltaTicks  ) / 1000 );
			update();
		}
	}
public:
	Ticks() :ticksPerSecond(SDL_GetPerformanceFrequency()) {}
/*	Get the delta time.	*/
	inline const Uint getDeltaTicks(){
		if ( (deltaTicks)/1000 == 0 )
			return 1;
		return (deltaTicks)/1000;
	}
/*	Get the FPS for the cycle.	*/
	inline const Uint getFPS()
	{
		if( !fps )
			fps=1;
		return fps;
	}
};
#endif /*	_ENGINE_TIMER_H	*/
