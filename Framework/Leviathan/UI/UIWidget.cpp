#include <Leviathan/UI/UIWidget.h>

#include <Leviathan/Core/Application.h>

UIWidget::UIWidget() : m_transform(new RectTransform())
{
	
}

UIWidget::~UIWidget()
{
	if (m_transform != nullptr)
	{
		delete m_transform;
		m_transform = nullptr;
	}
}

RectTransform* UIWidget::Transform() const
{
	return m_transform;
}
