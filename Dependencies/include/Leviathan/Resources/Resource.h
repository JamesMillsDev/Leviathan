#pragma once

#include <functional>
#include <string>

using std::function;
using std::string;

template<typename T>
class Resource
{
public:
	T* Get();

	virtual bool IsLoaded() = 0;

protected:
	Resource(function<T(char*)> _load, function<void(T)> _unload, string _path);

private:
	T* m_resource;
	string m_path;

	function<T(char*)> m_loadFnc;
	function<void(T)> m_unloadFnc;

};

template<typename T>
inline T* Resource<T>::Get()
{
	if (!IsLoaded())
	{
		T resource = m_loadFnc(m_path.c_str());
		m_resource = &resource;
	}

	return m_resource;
}

template<typename T>
inline Resource<T>::Resource(function<T(char*)> _load, function<void(T)> _unload, string _path)
	: m_path(_path), m_resource(nullptr), m_loadFnc(_load), m_unloadFnc(_unload)
{
}
