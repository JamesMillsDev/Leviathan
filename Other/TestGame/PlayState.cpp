#include "PlayState.h"

#include <Leviathan/Core/GameManagers.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/UI/UIManager.h>
#include <Leviathan/UI/VerticalLayout.h>
#include <Leviathan/UI/SliderWidget.h>
#include <Leviathan/UI/ButtonWidget.h>

#include <raylib/raylib.h>
#include <iostream>

#include "TestObject.h"
#include "GroundObject.h"

TestObject* textured = nullptr;
GroundObject* ground = nullptr;

using Leviathan::SliderWidget;
using Leviathan::VerticalLayout;
using Leviathan::ButtonWidget;
using Leviathan::Rigidbody;
using Leviathan::ForceMode;
using Leviathan::Constraints;
using Leviathan::Callback;

ButtonWidget* widgetd = nullptr;
list<Callback*>::iterator pos;
list<Callback*>::iterator pos1;

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

	SliderWidget* widget = new SliderWidget();
	SliderWidget* widgetb = new SliderWidget();
	SliderWidget* widgetc = new SliderWidget();
	widgetd = new ButtonWidget();
	widgetd->label = "hello child";

	pos = widgetd->AddListener(&PlayState::ClickTest, this);
	pos1 = widgetd->AddListener(&PlayState::ClickTest2, this);
	
	VerticalLayout* layout = new VerticalLayout();
	layout->Transform()->anchorMin = { .25f, .25f };
	layout->Transform()->anchorMax = { .75f, .75f };
	//layout->spacing = .15f;

	layout->AddElement(widget);
	layout->AddElement(widgetb);
	layout->AddElement(widgetc);
	layout->AddElement(widgetd);

	GetUIManager()->AddWidget(widget);
	GetUIManager()->AddWidget(widgetb);
	GetUIManager()->AddWidget(widgetc);
	GetUIManager()->AddWidget(widgetd);
	GetUIManager()->AddWidget(layout);
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

void PlayState::ClickTest()
{
	std::cout << "On Click!" << std::endl;
	widgetd->RemoveListener(pos);
}

void PlayState::ClickTest2()
{
	std::cout << "On Click! 2" << std::endl;
	widgetd->RemoveListener(pos1);
}
