#pragma once

#include <functional>
#include <string>

using std::function;
using std::string;

template<typename T>
class Resource
{
public:
	T Get();
	void Dispose();

	operator T() { return Get(); }

protected:
	T* m_resource;

protected:
	Resource(function<T(const char*)> _load, function<void(T)> _unload, string _path);
	~Resource();

private:
	friend class Resources;

	string m_path;

	function<T(const char*)> m_loadFnc;
	function<void(T)> m_unloadFnc;

};

template<typename T>
inline T Resource<T>::Get()
{
	if (m_resource == nullptr)
	{
		m_resource = new T();
		*m_resource = m_loadFnc(m_path.c_str());
	}

	return *m_resource;
}

template<typename T>
inline void Resource<T>::Dispose()
{
	if (m_resource != nullptr)
	{
		m_unloadFnc(*m_resource);
		delete m_resource;
		m_resource = nullptr;
	}
}

template<typename T>
inline Resource<T>::Resource(function<T(const char*)> _load, function<void(T)> _unload, string _path)
	: m_path(_path), m_resource(nullptr), m_loadFnc(_load), m_unloadFnc(_unload)
{
}

template<typename T>
inline Resource<T>::~Resource()
{
	Dispose();
}