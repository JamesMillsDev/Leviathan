#include <Leviathan/UI/ButtonWidget.h>

#include <Leviathan/Third Party/raygui.h>

namespace Leviathan
{
	void ButtonWidget::Render()
	{
		if (GuiButton(*m_transform, label.empty() ? nullptr : label.c_str()))
		{
			for (auto& callback : m_onClick)
				callback->Call();
		}
	}

	void ButtonWidget::Tick()
	{
		for (auto& update : m_listUpdates)
			update();

		m_listUpdates.clear();
	}

	void ButtonWidget::RemoveListener(list<Callback*>::iterator _callback)
	{
		m_listUpdates.push_back([=]()
			{
				if (_callback != m_onClick.end())
				{
					delete *_callback;
					m_onClick.erase(_callback); 
				}
			});
	}
}
