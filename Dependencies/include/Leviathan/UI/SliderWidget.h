#pragma once

#include <Leviathan/UI/UIWidget.h>

#include <string>

using std::string;

namespace Leviathan
{
	class SliderWidget : public UIWidget
	{
	public:
		float value;
		float min;
		float max;

		string leftLabel;
		string rightLabel;

	public:
		DLL SliderWidget();

		DLL virtual void Load() override;
		DLL virtual void Render() override;

	};
}