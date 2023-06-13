#include <Leviathan/UI/VerticalLayout.h>

namespace Leviathan
{
	VerticalLayout::VerticalLayout()
		: spacing(0.f), padding({ 0.f, 0.f })
	{
	}

	void VerticalLayout::AddElement(UIWidget* _widget)
	{
		m_listUpdates.emplace_back([=](RectTransform* _transform)
			{
				if (_transform->Parent() != Transform())
				{
					_transform->SetParent(Transform());
					m_children.emplace_back(_transform);
				}
			}, _widget->Transform());
	}

	void VerticalLayout::RemoveElement(UIWidget* _widget)
	{
		m_listUpdates.emplace_back([=](RectTransform* _transform)
			{
				if (_transform->Parent() == Transform())
				{
					_transform->SetParent(nullptr);
					m_children.erase(std::ranges::find(m_children, _transform));
				}
			}, _widget->Transform());
	}

	void VerticalLayout::Tick()
	{
		for (auto& u : m_listUpdates)
			u.first(u.second);

		m_listUpdates.clear();

		Layout();
	}

	void VerticalLayout::Layout()
	{
		float totalSpacing = spacing * (m_children.size() - 1);
		float elementHeight = ((1.f / m_children.size()) - (padding.y * 2.f)) - totalSpacing;
		float elementWidth = 1.f - (padding.x * 2.f);

		float x = padding.x;
		float y = padding.y;

		for (int i = 0; i < m_children.size(); i++)
		{
			RectTransform* child = m_children[i];

			child->anchorMin = { x, y };
			child->anchorMax = { x + elementWidth, y + elementHeight };

			y += elementHeight + spacing;
		}
	}
}
