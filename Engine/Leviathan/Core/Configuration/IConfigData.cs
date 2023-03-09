namespace Leviathan.Configuration
{
	/// <summary>Implement this to make a piece of data work with the config system.</summary>
	public interface IConfigData
	{
		/// <summary>Used to get the data from the config class this interface is associated with.</summary>
		/// <param name="_key">The key corresponding to the data of the class. This does not necessarily need to match up with the actual class variable name.</param>
		/// <param name="_converter"> </param>
		/// <typeparam name="T">The type that the data is. This is converted to from the key's type.</typeparam>
		/// <returns>The data corresponding to the passed <see cref="_key"/>.</returns>
		public T? Get<T>(string _key, IConfigConverter<T>? _converter = default) => ConfigUtils.TryGetValue<T>(_key, GetConfigData(), _converter);

		/// <summary>Constructs the collection of config data that is used to try and get the values.</summary>
		/// <returns>The collection of config data.</returns>
		public ConfigData[] GetConfigData();
	}
}