#include "PerfCounter.h"

#include <iostream>

using namespace std;

LARGE_INTEGER PerfCounter::s_freq;
bool PerfCounter::s_initilized = false;

PerfCounter::PerfCounter()
{
	if (!s_initilized)
	{
		if (!QueryPerformanceFrequency(&s_freq))
		{
			cerr << "Couldn't retrieve frequency." << endl;
			s_initilized = true;
		}
	}
}

void PerfCounter::Start()
{
	if (!QueryPerformanceCounter(&m_start))
	{
		cerr << "Error in QueryPerforamanceCounter" << endl;
	}
}

void PerfCounter::Stop()
{
	if (!QueryPerformanceCounter(&m_stop))
	{
		cerr << "Error in QueryPerforamanceCounter" << endl;
	}
}

long long PerfCounter::GetElapsedMs() const
{
	LARGE_INTEGER elapsed;
	elapsed.QuadPart = m_stop.QuadPart - m_start.QuadPart;

	return elapsed.QuadPart * 1000 / s_freq.QuadPart;
}

double PerfCounter::GetElapsedSec() const
{
	return GetElapsedMs() / 1000.0;
}