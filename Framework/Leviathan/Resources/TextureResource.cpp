#include <Leviathan/Resources/TextureResource.h>

TextureResource::TextureResource(string _path) :
    Resource<Texture2D>(LoadTexture, UnloadTexture, _path)
{
}
