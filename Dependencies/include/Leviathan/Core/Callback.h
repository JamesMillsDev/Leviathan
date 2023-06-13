#pragma once

namespace Leviathan
{
	struct Callback
	{
	public:
		virtual void Call() = 0;
	};

	template<typename T>
	struct TemplateCallback : public Callback
	{
	public:
		void(T::* callback)();
		T* owner;

		void* m_configValues;

		void Call() override;

	};

	template<typename T, typename P0>
	struct TemplateCallbackOneParam : public Callback
	{
	public:
		void(T::* callback)(P0*);
		T* owner;

		P0* param0;

		void* m_configValues;

	public:
		void Call() override;

	};

	template<typename T, typename P0, typename P1>
	struct TemplateCallbackTwoParam : public Callback
	{
	public:
		void(T::* callback)(P0*, P1*);
		T* owner;

		P0* param0;
		P1* param1;

		void* m_configValues;

	public:
		void Call() override;

	};

	template<typename T, typename P0, typename P1, typename P2>
	struct TemplateCallbackThreeParam : public Callback
	{
	public:
		void(T::* callback)(P0*, P1*, P2*);
		T* owner;

		P0* param0;
		P1* param1;
		P2* param2;

		void* m_configValues;

	public:
		void Call() override;

	};

	template<typename T>
	inline void TemplateCallback<T>::Call()
	{
		(owner->*callback)();
	}

	template<typename T, typename P0>
	inline void TemplateCallbackOneParam<T, P0>::Call()
	{
		(owner->*callback)(param0);
	}

	template<typename T, typename P0, typename P1>
	inline void TemplateCallbackTwoParam<T, P0, P1>::Call()
	{
		(owner->*callback)(param0, param1);
	}

	template<typename T, typename P0, typename P1, typename P2>
	inline void TemplateCallbackThreeParam<T, P0, P1, P2>::Call()
	{
		(owner->*callback)(param0, param1, param2);
	}
}
