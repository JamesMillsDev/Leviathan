#include "TestGame.h"

#include <Leviathan/Application.h>
#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TextureComponent.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Box2D/Box2D.h>

GameObject* textured = nullptr;

b2World* world = nullptr;
b2Body* ground = nullptr;
b2Body* tBod = nullptr;

const float TIME_STEP = 1.f / 60.f;
int32 velocityIterations = 6;
int32 positionIterations = 6;

void TestGame::Load()
{
	world = new b2World({ 0, 10.f });

	int w = 0, h = 0;
	Application::GetWindowSize(w, h);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(w / 2, h);

	ground = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(w / 2, 0);

	ground->CreateFixture(&groundBox, 0);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(250, 250);
	bodyDef.angle = 45.1f * DEG_2_RAD;
	tBod = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(100, 100);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	tBod->CreateFixture(&fixtureDef);

	textured = new GameObject("textured");
	textured->Transform()->SetScale({ 200, 200 });

	TextureComponent* t = textured->AddComponent<TextureComponent>();
	t->SetTexture("textures/test");

	GameObjectManager::Spawn(textured);
}

void TestGame::Unload()
{
	GameObjectManager::Destroy(textured);
}

void TestGame::Tick()
{
	world->Step(TIME_STEP, velocityIterations, positionIterations);

	b2Vec2 pos = tBod->GetPosition();
	textured->Transform()->SetPosition(pos.x, pos.y);
	textured->Transform()->SetRotation(tBod->GetAngle() * RAD_2_DEG);
}
