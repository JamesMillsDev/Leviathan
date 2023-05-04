#include "TestGame.h"

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TextureComponent.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

IGameObject* textured = nullptr;

void TestGame::Load()
{
	textured = new IGameObject("textured");
	textured->Transform()->SetScale({ 500, 500 });
	textured->Transform()->SetPosition({ 250, 250 });

	TextureComponent* t = textured->AddComponent<TextureComponent>();
	t->SetTexture("textures/test");

	GameObjectManager::Spawn(textured);
}

void TestGame::Unload()
{
	GameObjectManager::Destroy(textured);
}
