#pragma once

#include <Leviathan/Leviathan.h>

#include <raylib/raylib.h>

#include <Leviathan/Resources/Resource.h>

class TextureResource : public Resource<Texture2D>
{
public:
	DLL TextureResource(string _path);

};