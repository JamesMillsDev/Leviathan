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
		TObjectPtr(const TObjectPtr& _other);
		TObjectPtr(const TObjectPtr&& _other);
		~TObjectPtr();

		T* Get();
		bool IsValid();
		void SetCopied(bool _copied);

	public:
		T* operator->();
		T& operator*();
		operator T*();
		TObjectPtr<T> operator=(T* _other);

		void* operator new(size_t _data);
		static void operator delete(void* _data);

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
	inline TObjectPtr<T>::TObjectPtr(const TObjectPtr& _other)
		: m_owned(_other.m_owned), m_copied(true)
	{
	}

	template<typename T>
	inline TObjectPtr<T>::TObjectPtr(const TObjectPtr&& _other)
		: m_owned(_other.m_owned), m_copied(true)
	{
	}

	template<typename T>
	inline TObjectPtr<T>::~TObjectPtr()
	{
		if (m_owned != nullptr && !m_copied)
		{
			delete m_owned;
		}
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
	inline void TObjectPtr<T>::SetCopied(bool _copied)
	{
		m_copied = _copied;
	}

	template<typename T>
	T* TObjectPtr<T>::operator->()
	{
		return m_owned;
	}

	template<typename T>
	T& TObjectPtr<T>::operator*()
	{
		return *m_owned;
	}

	template<typename T>
	TObjectPtr<T>::operator T*()
	{
		return m_owned;
	}

	template<typename T>
	inline TObjectPtr<T> TObjectPtr<T>::operator=(T* _other)
	{
		this->m_owned = _other;

		return *this;
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