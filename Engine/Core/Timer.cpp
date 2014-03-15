//
//  Timer.cpp
//  Renderer
//
//  Created by Narendra Umate on 5/5/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Timer.h"

namespace Engine
{
	
	Timer::Timer()
	{
#ifdef WIN32
		QueryPerformanceFrequency(&m_frequency);
		m_startCount.QuadPart = 0;
		m_endCount.QuadPart = 0;
#else
		m_startCount.tv_sec = m_startCount.tv_usec = 0;
		m_endCount.tv_sec = m_endCount.tv_usec = 0;
#endif
		
		m_stopped = false;
		m_startTimeInMicroSec = 0;
		m_endTimeInMicroSec = 0;
	}
	
	Timer::~Timer()
	{}
	
	void Timer::initialize()
	{
		m_stopped = false; // reset stop flag
#ifdef WIN32
		QueryPerformanceCounter(&m_startCount);
#else
		gettimeofday(&m_startCount, NULL);
#endif
	}
	
	void Timer::shutdown()
	{
		m_stopped = true; // set timer stopped flag
#ifdef WIN32
		QueryPerformanceCounter(&m_endCount);
#else
		gettimeofday(&m_endCount, NULL);
#endif
	}
	
	double Timer::getElapsedTime()
	{
#ifdef WIN32
		if (!m_stopped)
		{
			QueryPerformanceCounter(&m_endCount);
		}
		
		m_startTimeInMicroSec = m_startCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
		m_endTimeInMicroSec = m_endCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#else
		if (!m_stopped)
		{
			gettimeofday(&m_endCount, NULL);
		}
		m_startTimeInMicroSec = (m_startCount.tv_sec * 1000000.0) + m_startCount.tv_usec;
		m_endTimeInMicroSec = (m_endCount.tv_sec * 1000000.0) + m_endCount.tv_usec;
#endif
		
		return m_endTimeInMicroSec - m_startTimeInMicroSec;
	}
	
}
