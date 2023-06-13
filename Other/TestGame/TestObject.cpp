#include "TestObject.h"

#include <Leviathan/GameObjects/TextureComponent.h>

#include <Leviathan/Physics/Rigidbody.h>
#include <Leviathan/Physics/BoxCollider.h>

using Leviathan::TextureComponent;
using Leviathan::Rigidbody;
using Leviathan::BoxCollider;

TestObject::TestObject()
{
	Transform()->TRS({ 250, 250 }, 35.f, { 100.f, 100.f });

	TextureComponent* texture = AddComponent<TextureComponent>();
	texture->SetTexture("textures/test");

	Rigidbody* rb = AddComponent<Rigidbody>();
	rb->SetEnabled(false);

	BoxCollider* collider = AddComponent<BoxCollider>();
	collider->SetExtents({ 50, 50 });
}
