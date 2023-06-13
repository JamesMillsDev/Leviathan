#include <Leviathan/UI/UIManager.h>

#define RAYGUI_IMPLEMENTATION
#include <Leviathan/Third Party/raygui.h>

#include <Leviathan/UI/UIWidget.h>

void UIManager::AddWidget(UIWidget* _widget)
{
	m_listUpdates.emplace_back([=](UIWidget* _w)
		{
			const auto iter = std::find(m_widgets.begin(), m_widgets.end(), _w);

			if (iter == m_widgets.end())
			{
				_w->Load();
				m_widgets.push_back(_w);
			}
		}, _widget);
}

void UIManager::RemoveWidget(UIWidget* _widget)
{
	m_listUpdates.emplace_back([=](UIWidget* _w)
		{
			const auto iter = std::find(m_widgets.begin(), m_widgets.end(), _w);

			if (iter != m_widgets.end())
			{
				_w->Unload();
				m_widgets.erase(iter);
				delete _w;
			}
		}, _widget);
}

UIManager::~UIManager()
{
	for (auto& w : m_widgets)
		delete w;

	m_widgets.clear();
}

void UIManager::Tick()
{
	for (auto& u : m_listUpdates)
		u.first(u.second);

	m_listUpdates.clear();

	for (auto& w : m_widgets)
	{
		if (w->m_transform->Parent() == nullptr)
			w->m_transform->Tick();

		w->Tick();
	}
}

void UIManager::Render()
{
	for (auto& w : m_widgets)
		w->Render();
}