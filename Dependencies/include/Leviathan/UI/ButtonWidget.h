#pragma once

#include <Leviathan/Callback.h>
#include <Leviathan/UI/UIWidget.h>

#include <string>
#include <functional>

using std::string;
using std::function;

namespace Leviathan
{
	class ButtonWidget : public UIWidget
	{
	public:
		string label;

	public:
		DLL virtual void Render() override;
		DLL virtual void Tick() override;

		template<typename T>
		list<Callback*>::iterator AddListener(void(T::* _callback)(), T* _listener);
		DLL void RemoveListener(list<Callback*>::iterator _callback);

	private:
		list<Callback*> m_onClick;
		list<function<void()>> m_listUpdates;

	};

	template<typename T>
	inline list<Callback*>::iterator ButtonWidget::AddListener(void(T::* _callback)(), T* _listener)
	{
		TemplateCallback<T>* c = new TemplateCallback<T>();
		c->callback = _callback;
		c->owner = _listener;

		m_onClick.push_back(c);

		return std::ranges::find(m_onClick, c);
	}
}