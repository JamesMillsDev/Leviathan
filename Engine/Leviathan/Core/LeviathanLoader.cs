using System.Reflection;

namespace Leviathan
{
	public static class LeviathanLoader
	{
		internal static bool HasLoaded { get; set; }

		internal static readonly List<Assembly> modules = new();

		public static void Load()
		{
			HasLoaded = true;

			IEnumerable<string> modulePaths = GetModules();

			foreach(string path in modulePaths)
				modules.Add(Assembly.LoadFile(path));
		}

		private static IEnumerable<string> GetModules()
		{
			List<string> modules = new();

			foreach(string module in Directory.GetFiles(Directory.GetCurrentDirectory(), "*.dll").Where(IsValidModuleFile))
				modules.Add(module);

			return modules;
		}

		private static bool IsValidModuleFile(string _id)
		{
			FileInfo info = new(_id);

			return info.Name.Contains("Leviathan") && info.Name != "Leviathan.dll";
		}
	}
}