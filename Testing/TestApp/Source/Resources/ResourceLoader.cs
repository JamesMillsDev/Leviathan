using Leviathan.Events;

namespace TestApp.Resources
{
	public class ResourceLoader : IEventHandler
	{
		private readonly Dictionary<string, Animation?> animations = new();

		public Animation? GetAnimation(string _id) => animations[_id];
		
		public void Load() => EventBus.RegisterObject(this);

		public void Unload() => EventBus.RemoveObject(this);

		[SubscribeEvent]
		public void OnResourceManagerLoad(ResourceManagerLoadEvent _event)
		{
			_event.resourceManager.LocateFiles("spritesheets", "xml");
			
			foreach(KeyValuePair<string, string> file in LocateFiles("animations", "xml"))
			{
				animations.Add(file.Key, new Animation(file.Value));
			}
		}

		private static Dictionary<string, string> LocateFiles(string _path, string _extension)
		{
			Dictionary<string, string> paths = new();

			// Make sure the directory exists, if not, just return as we don't need to load files that we don't have.
			string path = $"{Directory.GetCurrentDirectory()}{Path.Combine("\\assets\\", _path)}";

			if(!Directory.Exists(path))
				return paths;

			// Get all files within the directory with the extension considering sub-folders.
			foreach(string file in Directory.GetFiles(path, $"*.{_extension}", SearchOption.AllDirectories))
			{
				// Construct the file name (ID) using the full path
				string fileName = string.Concat($"{_path}/", file.AsSpan(file.LastIndexOf(_path, StringComparison.Ordinal) + _path.Length + 1));
				fileName = fileName.Replace($".{_extension}", "").Replace('\\', '/');

				paths.Add(fileName, file);
			}

			return paths;
		}
	}
}