#pragma once

template<class T>
class Singleton
{
public:
	static void CreateInstance();
	static void DestroyInstance();

	static T*& Get();
	virtual void OnCreate() {}
	virtual void OnDestroy() {}

protected:
	static T* m_instance;

};

template<class T>
T* Singleton<T>::m_instance = nullptr;

template<class T>
inline void Singleton<T>::CreateInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new T();
		m_instance->OnCreate();
	}
}

template<class T>
inline void Singleton<T>::DestroyInstance()
{
	if (m_instance != nullptr)
	{
		m_instance->OnDestroy();
		delete m_instance;
		m_instance = nullptr;
	}
}

template<class T>
inline T*& Singleton<T>::Get()
{
	return m_instance;
}
