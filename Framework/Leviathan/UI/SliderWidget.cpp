#include <Leviathan/UI/SliderWidget.h>

#include <Leviathan/Third Party/raygui.h>

namespace Leviathan
{
	SliderWidget::SliderWidget()
		: value(0.f), min(0.f), max(1.f)
	{

	}

	void SliderWidget::Load()
	{

	}

	void SliderWidget::Render()
	{
		value = GuiSlider(*m_transform,
			leftLabel.empty() ? nullptr : leftLabel.c_str(),
			rightLabel.empty() ? nullptr : rightLabel.c_str(),
			value, min, max);
	}
}
