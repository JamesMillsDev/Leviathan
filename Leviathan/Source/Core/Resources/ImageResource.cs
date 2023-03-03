using Raylib_CsLo;

namespace Leviathan.Resources
{
	/// <summary>The implementation for Images in the Resource system.</summary>
	public class ImageResource : Resource<Image>
	{
		/// <summary>The constructor for an image resource which calls the base constructor passing in Raylib's Load and Unload Image functions.</summary>
		/// <param name="_path">The path to the image that is being loaded.</param>
		public ImageResource(string _path) : base(Raylib.LoadImage, Raylib.UnloadImage, _path) { }
		/// <summary>Returns true if the width of the image is not 0.</summary>
		protected override bool IsLoaded => resource.width != 0;
	}
}