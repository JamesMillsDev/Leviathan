#pragma once

#include <Leviathan/Leviathan.h>

#include <raylib/raylib.h>

#include <Leviathan/Resources/Resource.h>

namespace Leviathan
{
	class TextureResource : public Resource<Texture2D>
	{
	public:
		DLL TextureResource(string _path);

	};
}