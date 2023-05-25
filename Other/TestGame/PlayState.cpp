#include "PlayState.h"

#include <Leviathan/Core/Application.h>
#include <Leviathan/Core/GameManagers.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TextureComponent.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/GameStates/GameStateManager.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/Physics/BoxCollider.h>

#include <raylib/raylib.h>

#include <iostream>

GameObject* textured = nullptr;
GameObject* ground = nullptr;

PlayState::PlayState(GameManagers* _gameManagers)
	: IGameState(_gameManagers, "PLAY")
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

	GetObjectManager()->Spawn(textured);
	GetObjectManager()->Spawn(ground);

	GetTimerManager()->Set(m_timerHandle, &PlayState::DelayTest, this, 2.f);
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

	if (IsKeyPressed(KEY_Q))
	{
		if (Rigidbody* rb = textured->GetComponent<Rigidbody>())
		{
			rb->ToggleConstraint(Constraints::FreezeRotation);
		}
	}
}

void PlayState::Unload()
{
	GetObjectManager()->Destroy(textured);
	GetObjectManager()->Destroy(ground);
}

void PlayState::DelayTest()
{
	std::cout << "Delay call" << std::endl;
}
