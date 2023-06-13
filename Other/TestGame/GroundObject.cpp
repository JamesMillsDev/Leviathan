#include "GroundObject.h"

#include <Leviathan/Core/Application.h>

#include <Leviathan/GameObjects/TextureComponent.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/Physics/BoxCollider.h>

using Leviathan::Application;
using Leviathan::Rigidbody;
using Leviathan::BoxCollider;
using Leviathan::TextureComponent;

GroundObject::GroundObject()
{
	int w = 0, h = 0;
	Application::GetWindowSize(w, h);

	Transform()->TRS({ w * 0.5f, (float)h }, 0.f, { (float)w, 5.f });

	Rigidbody* rb = AddComponent<Rigidbody>();
	rb->SetStatic(true);

	BoxCollider* collider = AddComponent<BoxCollider>();
	collider->SetExtents({ (float)w, 5.f });

	TextureComponent* texture = AddComponent<TextureComponent>();
	texture->SetTexture("textures/test");
}
