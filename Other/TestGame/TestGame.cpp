#include "TestGame.h"

#include <Leviathan/Resources/TextureResource.h>
#include <Leviathan/Resources/Resources.h>

TextureResource* texture = nullptr;

void TestGame::Load()
{
	texture = Resources::Find<Texture2D, TextureResource>("textures/test");
}

void TestGame::Render()
{
	Texture2D test = texture->Get();

	DrawTexture(test, 0, 0, RAYWHITE);
}
