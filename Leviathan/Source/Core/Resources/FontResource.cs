using Raylib_CsLo;

namespace Leviathan.Resources
{
	/// <summary>The implementation for Fonts in the Resource system.</summary>
	public class FontResource : Resource<Font>
	{
		/// <summary>The constructor for a font resource which calls the base constructor passing in Raylib's Load and Unload font functions.</summary>
		/// <param name="_path">The path to the font that is being loaded.</param>
		public FontResource(string _path) : base(Raylib.LoadFont, Raylib.UnloadFont, _path) { }
		/// <summary>Returns true if the base size of the font is not 0.</summary>
		protected override bool IsLoaded => resource.baseSize != 0;
	}
}