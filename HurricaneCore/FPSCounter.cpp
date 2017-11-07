#include "FPSCounter.h"
#include <Windows.h>

using namespace HurricaneEngine;

UNIQUE_PTR(FPSCounter) FPSCounter::_instance(nullptr);

FPSCounter* FPSCounter::GetFPSCounter()
{
	if (_instance.get() == nullptr)
		_instance.reset(new FPSCounter());

	return _instance.get();
}

void FPSCounter::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = GetTickCount();// timeGetTime();
}

void FPSCounter::Frame()
{
	m_count++;

	if (GetTickCount() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;

		m_startTime = GetTickCount();
	}
}