using Leviathan.Events;

using Newtonsoft.Json;

namespace Leviathan.Configuration
{
	/// <summary>The generic config class that can be used to read configuration data easily.</summary>
	/// <typeparam name="DATA">The <see cref="IConfigData"/> type that is stored within the json config file.</typeparam>
	public class Config<DATA> : IEventHandler where DATA : IConfigData, new()
	{
		public ref DATA? Data => ref data;
		
		/// <summary>The full config file path for this json config file.</summary>
		private string ConfigPath
		{
			get
			{
				// Combine the default config path with the config file name
				string path = Path.Combine("assets\\config", name);
				FileInfo info = new(path);
				
				// Validate that the config directory exists
				if(!Directory.Exists(info.DirectoryName))
					Directory.CreateDirectory(info.DirectoryName!);

				// Return the generated path + the file extension
				return $"{path}.json";
			}
		}
		
		/// <summary>The config data that was stored inside the json file.</summary>
		private DATA? data;
		/// <summary>The converter that gets used to write and read the json config file.</summary>
		private readonly ConfigConverter converter;
		/// <summary>The name of the config. This is used inside <see cref="ConfigPath"/> to generate the file path to the actual json file.</summary>
		private readonly string name;

		/// <summary>The constructor for the class that loads the data and assigns the reconfigure callback.</summary>
		/// <param name="_name">The actual name of the config / config json file.</param>
		public Config(string _name)
		{
			name = _name;
			data = new DATA();
			converter = new ConfigConverter();
			
			EventBus.RegisterObject(this);
			
			Load();
		}

		~Config() => EventBus.RemoveObject(this);

		/// <summary>Attempts to retrieve a value from the config file using the key provided.</summary>
		/// <param name="_key">The config key for the configuration value that is being requested.</param>
		/// <param name="_converter">A converter that can change the passed type from a JObject if necessary.</param>
		/// <typeparam name="T">The type of data that is being retrieved.</typeparam>
		/// <returns>The value pulled from the config data.</returns>
		/// <exception cref="NullReferenceException">Throws this if the <see cref="data"/> hasn't yet been set.</exception>
		public T? GetValue<T>(string _key, IConfigConverter<T>? _converter = default)
		{
			// If the data hasn't been set yet, throw a NullReferenceException... This shouldn't be possible, but it's a safety measure.
			if(data == null)
				throw new NullReferenceException("Config data is not yet generated");

			return data.Get<T?>(_key, _converter!);
		}

	#if CONFIG_GENERATION
		/// <summary>Generates a default config file with default values.</summary>
		public void Generate()
		{
			string json = JsonConvert.SerializeObject(data, Formatting.Indented, converter);
			File.WriteAllText(ConfigPath, json);
		}
	#endif

		/// <summary>Reads the json file and converts it to the <see cref="IConfigData"/> type specified by <typeparamref name="DATA"/>.</summary>
		private void Load()
		{
			string json = File.ReadAllText(ConfigPath);
			data = JsonConvert.DeserializeObject<DATA>(json, converter);
		}

		[SubscribeEvent]
		private void OnConfigReload(ConfigReloadEvent _event) => Load();
	}
}