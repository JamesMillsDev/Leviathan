#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <functional>
#include <list>
#include <vector>

using std::function;
using std::list;
using std::pair;
using std::vector;

class UIManager
{
public:
	DLL void AddWidget(class UIWidget* _widget);
	DLL void RemoveWidget(class UIWidget* _widget);

private:
	friend class GameManagers;

	vector<pair<function<void(class UIWidget*)>, class UIWidget*>> m_listUpdates;
	list<class UIWidget*> m_widgets;

private:
	UIManager() = default;
	UIManager(UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	DLL ~UIManager();

	DLL void Tick();
	DLL void Render();

};