#include <Leviathan/Resources/TextureResource.h>

namespace Leviathan
{
	TextureResource::TextureResource(const string _path) :
		Resource(LoadTexture, UnloadTexture, _path)
	{
	}
}
