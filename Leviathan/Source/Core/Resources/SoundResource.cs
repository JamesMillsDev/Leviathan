using Raylib_CsLo;

namespace Leviathan.Resources
{
	/// <summary>The implementation for Sounds in the Resource system.</summary>
	public class SoundResource : Resource<Sound>
	{
		/// <summary>The constructor for a sound resource which calls the base constructor passing in Raylib's Load and Unload sound functions.</summary>
		/// <param name="_path">The path to the sound that is being loaded.</param>
		public SoundResource(string _path) : base(Raylib.LoadSound, Raylib.UnloadSound, _path) { }
		/// <summary>Returns true if the frame count of the sound is not 0.</summary>
		protected override bool IsLoaded => resource.frameCount != 0;

		public AudioStream Stream => resource.stream;
	}
}