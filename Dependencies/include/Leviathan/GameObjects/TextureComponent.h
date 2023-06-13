#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <Leviathan/GameObjects/Component.h>

namespace Leviathan
{
	class TextureComponent final : public Component
	{
	public:
		DLL TextureComponent(class GameObject* _owner);
		DLL ~TextureComponent() override;

		void SetTexture(const char* _id) { m_id = _id; }

	protected:
		DLL void Load() override;
		DLL void Render() override;

	private:
		friend class GameObject;

		class TextureResource* m_texture;
		const char* m_id;

	};
}