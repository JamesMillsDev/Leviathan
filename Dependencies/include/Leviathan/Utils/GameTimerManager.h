#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <Leviathan/Utils/Singleton.h>

#include <map>

using std::map;

struct TimerHandle
{
public:
	DLL TimerHandle();
	DLL ~TimerHandle();

	DLL bool IsValid() const;
	DLL unsigned int GetHandle() const;

private:
	friend class GameTimerManager;

	unsigned int m_handle;

};

class GameTimerManager final : public Singleton<GameTimerManager>
{
public:
	GameTimerManager() = default;

	template<typename T>
	static void Set(TimerHandle& _timer, void(T::* _callback)(), T* _owner, float _duration);

	DLL static void Cancel(TimerHandle& _timer);

private:
	struct Timer
	{
	public:
		DLL Timer(float _duration, TimerHandle _handle);

		virtual void Call() = 0;
	
	private:
		friend GameTimerManager;

		TimerHandle m_handle;
		float m_duration;
		float m_time;

	private:
		DLL void Tick();

	};

	template<typename T>
	struct TemplateTimer : public Timer
	{
	public:
		void(T::*callback)();
		T* owner;
	
	public:
		TemplateTimer(float _duration, TimerHandle _handle);

		void Call() override;
	
	};

private:
	friend class Application;

	map<TimerHandle*, Timer*> m_timers;

private:
	DLL static void Tick();
	DLL static unsigned int FindValidHandle();
	DLL static GameTimerManager* GetInstance();

};

template<typename T>
void GameTimerManager::Set(TimerHandle& _timer, void(T::* _callback)(), T* _owner, float _duration)
{
	if (_timer.IsValid())
		return;

	_timer.m_handle = FindValidHandle();
	TemplateTimer<T>* timer = new TemplateTimer<T>(_duration, _timer);
	timer->callback = _callback;
	timer->owner = _owner;
	GetInstance()->m_timers[&_timer] = timer;
}

template<typename T>
GameTimerManager::TemplateTimer<T>::TemplateTimer(float _duration, TimerHandle _handle)
	: Timer(_duration, _handle) 
{
}

template<typename T>
void GameTimerManager::TemplateTimer<T>::Call()
{
	std::invoke(callback, owner);
}
