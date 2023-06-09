#include <Leviathan/UI/RectTransform.h>

#include <Leviathan/Core/Application.h>

RectTransform::RectTransform()
	: anchorMin({ .5f, .5f }), anchorMax({ .5f, .5f }), anchoredPos({ 0.f, 0.f }),
	offsetMin({ 0.f, 0.f }), offsetMax({ 0.f, 0.f }), m_parent(nullptr)
{
}

RectTransform::operator Rectangle()
{
	vec2 asMin = { 0.f, 0.f };
	vec2 asMax = { 0.f, 0.f };
	CalculateAnchorLocations(&asMin, &asMax);

	vec2 pos = CalculatePosition(&asMin, &asMax);
	vec2 size = CalculateSize(&asMin, &asMax);

	return { pos.x, pos.y, size.x, size.y };
}

vec2 RectTransform::CalculateSize(vec2* _asMin, vec2* _asMax)
{
	return 
	{
		(_asMax->x - _asMin->x) + offsetMax.x,
		(_asMax->y - _asMin->y) + offsetMax.y
	};
}

vec2 RectTransform::CalculatePosition(vec2* _asMin, vec2* _asMax)
{
	return *_asMin;
}

void RectTransform::CalculateAnchorLocations(vec2* _aMin, vec2* _aMax)
{
	vec2 min = { 0.f, 0.f };
	vec2 max = { 0.f, 0.f };

	if (m_parent != nullptr)
	{
		vec2 pMin = { 0.f, 0.f };
		vec2 pMax = { 0.f, 0.f };
		m_parent->CalculateAnchorLocations(&pMin, &pMax);

		min = (pMin * anchorMin) + pMin;
		max = (pMin * anchorMax) + pMin;
	}
	else
	{
		int w = 0, h = 0;
		Application::GetWindowSize(w, h);
		min = vec2{ (float)w, (float)h } * anchorMin;
		max = vec2{ (float)w, (float)h } * anchorMax;
	}

	*_aMin = min + offsetMin;
	*_aMax = max + offsetMax;
}

RectTransform*& RectTransform::Parent()
{
	return m_parent;
}

void RectTransform::SetParent(RectTransform* _parent)
{
	if (_parent == nullptr)
	{
		if (m_parent != nullptr)
			m_parent->RemoveChild(this);
	}
	else
	{
		_parent->AddChild(this);
	}
}

void RectTransform::AddChild(RectTransform* _child)
{
	m_listUpdates.emplace_back([=](RectTransform* _c)
		{
			if (_c->m_parent != nullptr)
				_c->m_parent->RemoveChild(_c);

			_c->m_parent = this;
			m_children.push_back(_c);
		}, _child);
}

void RectTransform::RemoveChild(RectTransform* _child)
{
	m_listUpdates.emplace_back([=](RectTransform* _c)
		{
			if (_c->m_parent == this)
			{
				_c->m_parent = nullptr;

				auto iter = std::ranges::find(m_children, _c);
				if (iter != m_children.end())
					m_children.erase(iter, iter);
			}
		}, _child);
}

void RectTransform::Tick()
{
	for (auto& u : m_listUpdates)
		u.first(u.second);

	m_listUpdates.clear();
}
