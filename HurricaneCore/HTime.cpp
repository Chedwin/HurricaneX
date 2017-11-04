#include "HTime.h"

using namespace Hurricane;

__int64 HTime::m_prevFrame = 0;
__int64 HTime::m_currentFrame = 0;
__int64 HTime::m_freq = 0;
float HTime::m_deltaTime = 0;
float HTime::MAX_REFRESH_TIME = 1.0f / 6.0f;

void HTime::Update()
{
	m_deltaTime = 0.0f;
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentFrame);
	int deltaTicks = (int)(m_currentFrame - m_prevFrame);
	m_deltaTime = ((float)deltaTicks / (float)m_freq);
	m_prevFrame = m_currentFrame;

	if (m_deltaTime < 0.0f)
		m_deltaTime = 0.0f;
	else if (m_deltaTime > MAX_REFRESH_TIME)
		m_deltaTime = MAX_REFRESH_TIME;

}

float HTime::GetDeltaTime()
{
	return m_deltaTime;
}