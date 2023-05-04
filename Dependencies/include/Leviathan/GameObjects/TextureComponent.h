#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/GameObjects/Component.h>

class TextureComponent : public IComponent
{
public:
	DLL TextureComponent(class IGameObject* _owner);
	DLL ~TextureComponent();

	void SetTexture(const char* _id) { m_id = _id; }

protected:
	DLL virtual void Load() override;
	DLL virtual void Render() override;

private:
	friend class IGameObject;

	class TextureResource* m_texture;
	const char* m_id;

};