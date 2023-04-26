#include <Leviathan/Resources/TextureResource.h>

TextureResource::TextureResource(string _path) :
    Resource<Texture>(LoadTexture, UnloadTexture, _path)
{
}
