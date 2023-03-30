using System.Reflection;

namespace Leviathan
{
	public static class LeviathanLoader
	{
		internal static bool HasLoaded { get; set; }

		internal static readonly List<Assembly> modules = new();

		internal static void Load()
		{
			HasLoaded = true;

			IEnumerable<string> modulePaths = DiscoverModules();

			foreach(string path in modulePaths)
				modules.Add(Assembly.LoadFrom(path));
		}

		private static IEnumerable<string> DiscoverModules()
		{
			List<string> found = new();

			foreach(string module in Directory.GetFiles(Directory.GetCurrentDirectory(), "*.dll").Where(IsValidModuleFile))
				found.Add(module);

			return found;
		}

		private static bool IsValidModuleFile(string _id)
		{
			FileInfo info = new(_id);

			return info.Name.Contains("Leviathan") && info.Name != "Leviathan.dll";
		}
	}
}