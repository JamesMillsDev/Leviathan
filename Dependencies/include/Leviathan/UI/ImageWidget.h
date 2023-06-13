#pragma once

#include <Leviathan/UI/UIWidget.h>

namespace Leviathan
{
	class ImageWidget : public UIWidget
	{
	public:
		DLL virtual void Load() override;
		DLL virtual void Render() override;

	};
}