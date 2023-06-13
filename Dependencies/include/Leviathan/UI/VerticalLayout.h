#pragma once

#include <Leviathan/UI/UIWidget.h>

#include <vector>

using std::vector;

class VerticalLayout : public UIWidget
{
public:
	float spacing;
	vec2 padding;

public:
	DLL void AddElement(UIWidget* _widget);
	DLL void RemoveElement(UIWidget* _widget);

	DLL virtual void Tick() override;

private:
	vector<RectTransform*> m_children;
	list<pair<function<void(RectTransform*)>, RectTransform*>> m_listUpdates;

private:
	DLL void Layout();

};