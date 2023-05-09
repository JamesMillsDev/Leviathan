#include "TestGame.h"

#include <Leviathan/Application.h>
#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TextureComponent.h>
#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/Physics/Rigidbody.h>

GameObject* textured = nullptr;

void TestGame::Load()
{
	textured = new GameObject("textured");
	textured->Transform()->SetScale({ 200, 200 });
	textured->Transform()->SetPosition({ 250, 250 });
	textured->Transform()->SetRotation(35);

	TextureComponent* t = textured->AddComponent<TextureComponent>();
	t->SetTexture("textures/test");

	Rigidbody* rb = textured->AddComponent<Rigidbody>();
	rb->SetEnabled(false);

	GameObjectManager::Spawn(textured);
}

void TestGame::Unload()
{
	GameObjectManager::Destroy(textured);
}

void TestGame::Tick()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		if (Rigidbody* rb = textured->GetComponent<Rigidbody>())
		{
			rb->SetEnabled(!rb->IsEnabled());
		}
	}
}
