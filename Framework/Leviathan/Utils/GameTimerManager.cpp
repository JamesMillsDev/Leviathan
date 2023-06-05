#include <Leviathan/Utils/GameTimerManager.h>

#include <Leviathan/Core/Time.h>

#include <vector>

using std::vector;

bool TimerHandle::IsValid() const
{
	return m_handle != 0;
}

unsigned int TimerHandle::GetHandle() const
{
	return m_handle;
}

TimerHandle::TimerHandle() : m_handle(0)
{
}

TimerHandle::~TimerHandle()
{
	m_handle = 0;
}

GameTimerManager::Timer::Timer(float _duration, TimerHandle _handle)
	: m_handle(_handle), m_duration(_duration), m_time(0)
{
}

void GameTimerManager::Timer::Tick()
{
	m_time += Time::deltaTime;
}

void GameTimerManager::Cancel(TimerHandle& _timer)
{
	TimerHandle* timer = &_timer;
	if (m_timers.contains(timer))
	{
		delete m_timers[timer];
		m_timers.erase(timer);
		timer->m_handle = 0;
	}
}

void GameTimerManager::Tick()
{
	vector<TimerHandle*> handles;
	for (auto& iter : m_timers)
	{
		iter.second->Tick();
		if (iter.second->m_time >= iter.second->m_duration)
		{
			iter.second->Call();
			handles.push_back(iter.first);
		}
	}

	while (!handles.empty())
	{
		TimerHandle* handle = handles[handles.size() - 1];
		handle->m_handle = 0;
		delete m_timers[handle];
		m_timers.erase(handle);

		handles.pop_back();
	}
}

unsigned int GameTimerManager::FindValidHandle()
{
	bool shouldRetry = true;
	int randVal = rand();

	while (shouldRetry)
	{
		shouldRetry = false;

		for (auto& timer : m_timers)
		{
			if (timer.first->GetHandle() == randVal)
			{
				shouldRetry = true;
				break;
			}
		}
	}

	return randVal;
}