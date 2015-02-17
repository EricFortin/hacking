#ifndef _PERF_COUNTER_H_
#define _PERF_COUNTER_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

class PerfCounter
{
public:
	PerfCounter();

	void Start();
	void Stop();

	long long GetElapsedMs() const;
	double GetElapsedSec() const;


	
private:
	static LARGE_INTEGER s_freq;
	static bool s_initilized;

	LARGE_INTEGER m_start;
	LARGE_INTEGER m_stop;
};	

#endif