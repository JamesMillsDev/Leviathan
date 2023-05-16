#include "PlayState.h"

#include <Leviathan/Application.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TextureComponent.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/Physics/BoxCollider.h>

#include <raylib.h>

GameObject* textured = nullptr;
GameObject* ground = nullptr;

PlayState::PlayState() : IGameState("PLAY")
{
}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	textured = new GameObject("textured");
	textured->Transform()->TRS({ 250, 250 }, 35.f, { 100.f, 100.f });

	TextureComponent* t = textured->AddComponent<TextureComponent>();
	t->SetTexture("textures/test");

	Rigidbody* rb = textured->AddComponent<Rigidbody>();
	rb->SetEnabled(false);

	BoxCollider* collider = textured->AddComponent<BoxCollider>();
	collider->SetExtents({ 50, 50 });

	int w = 0, h = 0;
	Application::GetWindowSize(w, h);

	ground = new GameObject("ground");
	ground->Transform()->TRS({ w * 0.5f, (float)h }, 0.f, { (float)w, 5.f });

	Rigidbody* groundRB = ground->AddComponent<Rigidbody>();
	groundRB->SetStatic(true);

	BoxCollider* groundCollider = ground->AddComponent<BoxCollider>();
	groundCollider->SetExtents({ (float)w, 5.f });

	TextureComponent* groundT = ground->AddComponent<TextureComponent>();
	groundT->SetTexture("textures/test");

	GameObjectManager::Spawn(textured);
	GameObjectManager::Spawn(ground);
}

void PlayState::Tick()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		if (Rigidbody* rb = textured->GetComponent<Rigidbody>())
		{
			rb->SetEnabled(!rb->IsEnabled());
		}
	}

	if (IsKeyPressed(KEY_W))
	{
		if (Rigidbody* rb = textured->GetComponent<Rigidbody>())
		{
			rb->ApplyForce({ 0, 25.f }, ForceMode::Impulse);
		}
	}
}

void PlayState::Unload()
{
	GameObjectManager::Destroy(textured);
	GameObjectManager::Destroy(ground);
}
