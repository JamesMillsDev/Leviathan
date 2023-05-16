#include <Leviathan/Resources/TextureResource.h>

TextureResource::TextureResource(const string _path) :
    Resource(LoadTexture, UnloadTexture, _path)
{
}
