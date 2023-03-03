namespace Leviathan
{
	/// <summary>The base class for all game instances.</summary>
	public abstract class Game
	{
		/// <summary>Called when the application starts.</summary>
		public abstract void Open();
		/// <summary>Called when the application is closed.</summary>
		public abstract void Close();
	}
}