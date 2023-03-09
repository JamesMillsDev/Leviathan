using Raylib_cs;

namespace Leviathan.Resources
{
	/// <summary>The implementation for Textures in the Resource system.</summary>
	public class TextureResource : Resource<Texture2D>
	{
		/// <summary>The constructor for a texture resource which calls the base constructor passing in Raylib's Load and Unload texture functions.</summary>
		/// <param name="_path">The path to the texture that is being loaded.</param>
		public TextureResource(string _path) : base(Raylib.LoadTexture, Raylib.UnloadTexture, _path) { }
		/// <summary>Returns true if the width of the texture is not 0.</summary>
		protected override bool IsLoaded => resource.width != 0;

		public int Width => Value.width;
		public int Height => Value.height;
	}
}