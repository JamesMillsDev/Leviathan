#pragma once

#include <string>

using std::string;

namespace Leviathan
{
    template <typename T>
    class Resource
    {
    public:
        T Get();
        void Dispose();

        operator T() { return Get(); }

    protected:
        T* m_resource;

    protected:
        Resource(T(*_load)(const char*), void(*_unload)(T), string _path);
        ~Resource();

    private:
        friend class Resources;

        string m_path;

        T(*m_loadFnc)(const char*);
        void(*m_unloadFnc)(T);
    };

    template <typename T>
    T Resource<T>::Get()
    {
        if (m_resource == nullptr)
        {
            m_resource = new T();
            *m_resource = m_loadFnc(m_path.c_str());
        }

        return *m_resource;
    }

    template <typename T>
    void Resource<T>::Dispose()
    {
        if (m_resource != nullptr)
        {
            m_unloadFnc(*m_resource);
            delete m_resource;
            m_resource = nullptr;
        }
    }

    template <typename T>
    Resource<T>::Resource(T(*_load)(const char*), void(*_unload)(T), const string _path)
        : m_resource(nullptr), m_path(std::move(_path)), m_loadFnc(_load), m_unloadFnc(_unload)
    {
    }

    template <typename T>
    Resource<T>::~Resource()
    {
        Dispose();
    }

}