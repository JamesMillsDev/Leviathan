#pragma once

#include <Leviathan/Core/Object.h>

#include <Leviathan/UI/RectTransform.h>

namespace Leviathan
{
	class UIWidget : public Object
	{
	public:
		DLL UIWidget();
		DLL virtual ~UIWidget();

		DLL RectTransform* Transform() const;

	protected:
		friend class UIManager;

		RectTransform* m_transform;

	private:
		virtual void Load() {}
		virtual void Tick() {}
		virtual void Render() {}
		virtual void Unload() {}

	};
}