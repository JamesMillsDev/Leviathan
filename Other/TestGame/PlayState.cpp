#include "PlayState.h"

#include <Leviathan/Core/GameManagers.h>
#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include <raylib/raylib.h>
#include <iostream>

#include "TestObject.h"
#include "GroundObject.h"

TestObject* textured = nullptr;
GroundObject* ground = nullptr;

PlayState::PlayState() : IGameState("PLAY")
{
}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	textured = CreateObject<TestObject>("textured");
	ground = CreateObject<GroundObject>("ground");

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
