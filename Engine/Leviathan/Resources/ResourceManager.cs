using Leviathan.Configuration;
using Leviathan.Events;

using Newtonsoft.Json.Linq;

using Raylib_cs;

namespace Leviathan.Resources
{
	/// <summary>A global manager used to manage all sorts of assets for the game.</summary>
	public class ResourceManager : Singleton<ResourceManager>
	{
		public class ResourcesConfigData : IConfigData
		{
			public Dictionary<string, object> extensions;

			public ResourcesConfigData()
			{
				extensions = new Dictionary<string, object>();
			}

			public ConfigData[] GetConfigData() => new[]
			{
				new ConfigData(extensions, nameof(extensions))
			};
		}

		/// <summary>Attempts to find the resource associated with the id.</summary>
		/// <param name="_id">The id of the resource we want. This includes the type such as 'textures'.</param>
		/// <typeparam name="RESOURCE">The managed resource type such as '<see cref="TextureResource"/>'.</typeparam>
		/// <typeparam name="ASSET">The actual asset type such as '<see cref="TextureResource"/>'.</typeparam>
		/// <returns>The managed resource for the passed ID. This can return null if the type does not exist.</returns>
		public static RESOURCE? Find<RESOURCE, ASSET>(string _id)
			where RESOURCE : Resource<ASSET>
		{
			if(Instance == null)
				throw new NullReferenceException("Resource Manager not yet setup!");

			return (RESOURCE?) Convert.ChangeType(TryGetResource<RESOURCE, ASSET>(_id, Instance.resourcePaths, Instance.resources), typeof(RESOURCE));
		}

		/// <summary>A generic function that can be used to find a resource from any dictionary.</summary>
		/// <param name="_id">The resource ID that is being retrieved.</param>
		/// <param name="_paths">The collection of paths for the specific resource type.</param>
		/// <param name="_resources">The actual resource collection.</param>
		/// <typeparam name="T">The type of managed resource.</typeparam>
		/// <typeparam name="R">The internal Raylib resource type.</typeparam>
		private static object? TryGetResource<T, R>(string _id, Dictionary<string, string> _paths, Dictionary<string, object?> _resources)
			where T : Resource<R>
		{
			if(Instance == null)
				return null;
			
			string path = GetPathFromId(_id, _paths);
			if(!string.IsNullOrEmpty(path))
			{
				if(!Instance.HasResource(_id))
					_resources.Add(_id, (T) Activator.CreateInstance(typeof(T), path)!);

				return (T?)_resources[_id];
			}

			return null;
		}

		/// <summary>Initialised the system by locating all types of resources and populating their corresponding dictionaries.</summary>
		protected override void OnCreate()
		{
			Config<ResourcesConfigData> config = new("resources");

			// Attempt to get the config data, and if successful, iterate through the extensions
			if(config.Data != null)
			{
				foreach(KeyValuePair<string, object> type in config.Data.extensions)
				{
					// Get the extension's array value from the config and iterate through it
					foreach(JToken token in config.GetValue<JArray>($"extensions.{type.Key}")!)
					{
						// Get the value from the array and if it isn't null, attempt to locate the files associated with it
						string? value = token.Value<string>();
						if(value != null)
							LocateFiles(type.Key, value, resourcePaths);
					}
				}
			}
			
			EventBus.Raise(new ResourceManagerLoadEvent(this));
		}

		/// <summary>Clears all the memory contained within the system.</summary>
		protected override void OnDestroy()
		{
			ClearMemoryFor<TextureResource?, Texture2D>(resources, resourcePaths);
			ClearMemoryFor<FontResource?, Font>(resources, resourcePaths);
			ClearMemoryFor<ImageResource?, Image>(resources, resourcePaths);
			ClearMemoryFor<SoundResource?, Sound>(resources, resourcePaths);
			
			EventBus.Raise(new ResourceManagerCleanupEvent(this));
		}

		/// <summary>Retrieves the corresponding file path for the passed ID.</summary>
		/// <param name="_id">The ID of the resource we are trying to retrieve.</param>
		/// <param name="_paths">The collection of paths for the resource type.</param>
		/// <returns>The path for the resource if it is in the system, otherwise an empty string.</returns>
		private static string GetPathFromId(string _id, Dictionary<string, string> _paths) => _paths.ContainsKey(_id) ? _paths[_id] : string.Empty;

		/// <summary>Finds all files within the folder with the passed extension.</summary>
		/// <param name="_path">The path to the folder we are locating files in.</param>
		/// <param name="_extension">The extension for the files we are trying to load. This acts as a filter.</param>
		/// <param name="_paths">The collection that gets populated with the located files.</param>
		private static void LocateFiles(string _path, string _extension, Dictionary<string, string> _paths)
		{
			// Make sure the directory exists, if not, just return as we don't need to load files that we don't have.
			string path = $"{Directory.GetCurrentDirectory()}{Path.Combine("\\assets\\", _path)}";

			if(!Directory.Exists(path))
				return;

			// Get all files within the directory with the extension considering sub-folders.
			foreach(string file in Directory.GetFiles(path, $"*.{_extension}", SearchOption.AllDirectories))
			{
				// Construct the file name (ID) using the full path
				string fileName = string.Concat($"{_path}/", file.AsSpan(file.LastIndexOf(_path, StringComparison.Ordinal) + _path.Length + 1));
				fileName = fileName.Replace($".{_extension}", "").Replace('\\', '/');

				_paths.Add(fileName, file);
			}
		}

		/// <summary>Unloads all files within the passed dictionary and empties the dictionaries.</summary>
		/// <param name="_resources">The managed resource dictionary that we are unloading.</param>
		/// <param name="_paths">The dictionary of paths for the file type.</param>
		private static void ClearMemoryFor<RESOURCE, ASSET>(Dictionary<string, object?> _resources, Dictionary<string, string> _paths)
			where RESOURCE : Resource<ASSET>?
		{
			foreach(KeyValuePair<string, object?> pair in _resources)
				((RESOURCE?)pair.Value)?.Dispose();

			_resources.Clear();
			_paths.Clear();
		}

		//@cond
		private readonly Dictionary<string, string> resourcePaths = new();
		private readonly Dictionary<string, object?> resources = new();

		public void LocateFiles(string _path, string _extension) => LocateFiles(_path, _extension, resourcePaths);
		
		private bool HasResource(string _id) => resources.ContainsKey(_id);
		//@endcond
	}
}