using Leviathan.Configuration;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan
{
	/// <summary>The config data for all aspects of the base application.</summary>
	[SuppressMessage("ReSharper", "FieldCanBeMadeReadOnly.Global")]
	[SuppressMessage("ReSharper", "CollectionNeverUpdated.Global")]
	public class ApplicationConfigData : IConfigData
	{
		/// <summary>Contains the values for the application itself.</summary>
		public Dictionary<string, object> application;
		/// <summary>Contains the values for the debug part of the application.</summary>
		public Dictionary<string, object> debug;
		/// <summary>Contains the values for the window including the size and clear color.</summary>
		public Dictionary<string, object> window;

		/// <summary>Creates the default values for the config values.</summary>
		public ApplicationConfigData()
		{
			application = new Dictionary<string, object>();
			debug = new Dictionary<string, object>();
			window = new Dictionary<string, object>();
		}

		/// <summary>Constructs the collection of config data that is used to try and get the values.</summary>
		/// <returns>The collection of config data.</returns>
		public ConfigData[] GetConfigData() => new[]
		{
			new ConfigData(application, nameof(application)), 
			new ConfigData(debug, nameof(debug)), 
			new ConfigData(window, nameof(window))
		};
	}
}