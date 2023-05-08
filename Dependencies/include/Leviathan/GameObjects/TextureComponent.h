#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/GameObjects/Component.h>

class TextureComponent : public Component
{
public:
	DLL TextureComponent(class GameObject* _owner);
	DLL ~TextureComponent();

	void SetTexture(const char* _id) { m_id = _id; }

protected:
	DLL virtual void Load() override;
	DLL virtual void Render() override;

private:
	friend class GameObject;

	class TextureResource* m_texture;
	const char* m_id;

};