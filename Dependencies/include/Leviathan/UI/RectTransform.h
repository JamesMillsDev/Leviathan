#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <raylib/raylib.h>
#include <glm/vec2.hpp>

#include <list>
#include <functional>

using glm::vec2;

using std::list;
using std::function;
using std::pair;

class RectTransform
{
public:
	vec2 anchorMin;
	vec2 anchorMax;

	vec2 anchoredPos;

	vec2 offsetMin;
	vec2 offsetMax;

public:
	DLL RectTransform();

	DLL operator Rectangle();

	DLL RectTransform*& Parent();
	DLL void SetParent(RectTransform* _parent);

private:
	DLL vec2 CalculateSize(vec2* _asMin, vec2* _asMax);
	DLL vec2 CalculatePosition(vec2* _asMin, vec2* _asMax);

	DLL void CalculateAnchorLocations(vec2* _aMin, vec2* _aMax);

	DLL void AddChild(RectTransform* _child);
	DLL void RemoveChild(RectTransform* _child);

	DLL void Tick();

private:
	friend class UIManager;

	RectTransform* m_parent;
	list<RectTransform*> m_children;
	list<pair<function<void(RectTransform*)>, RectTransform*>> m_listUpdates;

};