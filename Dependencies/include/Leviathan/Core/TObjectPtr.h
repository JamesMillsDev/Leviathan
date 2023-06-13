#pragma once

#include <cstddef>

namespace Leviathan
{
	template<typename T>
	class TObjectPtr
	{
	public:
		TObjectPtr();
		TObjectPtr(T* _data);
		TObjectPtr(TObjectPtr& _other);
		TObjectPtr(TObjectPtr&& _other);

		T* Get();
		bool IsValid();

	public:
		T& operator->();
		T& operator*();

		void* operator new(size_t _data);
		void operator delete(void* _data);

	private:
		T* m_owned;
		bool m_copied;

	};

	template<typename T>
	inline TObjectPtr<T>::TObjectPtr()
		: m_owned(nullptr), m_copied(false)
	{

	}

	template<typename T>
	inline TObjectPtr<T>::TObjectPtr(T* _data)
		: m_owned(_data), m_copied(false)
	{
	}

	template<typename T>
	inline TObjectPtr<T>::TObjectPtr(TObjectPtr& _other)
		: m_owned(_other->m_owned), m_copied(true)
	{
	}

	template<typename T>
	inline TObjectPtr<T>::TObjectPtr(TObjectPtr&& _other)
		: m_owned(_other->m_owned), m_copied(true)
	{
	}

	template<typename T>
	inline T* TObjectPtr<T>::Get()
	{
		return m_owned;
	}

	template<typename T>
	inline bool TObjectPtr<T>::IsValid()
	{
		return m_owned != nullptr;
	}

	template<typename T>
	T& TObjectPtr<T>::operator->()
	{
		return *m_owned;
	}

	template<typename T>
	T&  TObjectPtr<T>::operator*()
	{
		return *m_owned;
	}

	template<typename T>
	void* TObjectPtr<T>::operator new(size_t _data)
	{
		return new TObjectPtr<T>(new T());
	}

	template<typename T>
	void TObjectPtr<T>::operator delete(void* _data)
	{
		TObjectPtr<T>* ptr = static_cast<TObjectPtr<T>*>(_data);
		if (ptr != nullptr && !ptr->m_copied)
		{
			return delete static_cast<T*>(ptr->m_owned);
		}
	}
}