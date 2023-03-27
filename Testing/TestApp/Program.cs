using Leviathan;

using TestApp.Resources;

namespace TestApp
{
	public static class Program
	{
		public static readonly ResourceLoader loader = new();
		
		public static void Main()
		{
			loader.Load();
			Application.Run<TestGame>();
			loader.Unload();
		}
	}
}