//
//  Timer.h
//  Renderer
//
//  Created by Narendra Umate on 5/5/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Renderer__Timer__
#define __Renderer__Timer__

// Reference - High Resolution Timer
// http://www.songho.ca/misc/timer/timer.html

#if defined(__APPLE__)
#include <sys/time.h>
#elif defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <cstddef>
#include <sys/time.h>
#endif

namespace Engine
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void initialize();
		void shutdown();
		double getElapsedTime();
		
	private:
		double	m_startTimeInMicroSec;
		double	m_endTimeInMicroSec;
		bool	m_stopped;
#ifdef _WIN32
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_startCount;
		LARGE_INTEGER m_endCount;
#else
		timeval m_startCount;
		timeval m_endCount;
#endif //_WIN32
	};
}

#endif /* defined(__Renderer__Timer__) */
