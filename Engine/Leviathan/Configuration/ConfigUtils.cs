namespace Leviathan.Configuration
{
	/// <summary>A collection of utility functions for the <see cref="Config{DATA}"/>class.</summary>
	public static class ConfigUtils
	{
		/// <summary>Attempts to get a value from the passed config dictionaries.</summary>
		/// <param name="_key">The key for the config value we are trying to get.</param>
		/// <param name="_datas">The collection of ConfigData associated with the config class.</param>
		/// <param name="_converter">The converter that can be used if the type requires it.</param>
		/// <typeparam name="T">The type of data we are trying to get.</typeparam>
		/// <returns>The config value associated with the passed key.</returns>
		/// <exception cref="KeyNotFoundException">Thrown if a config value cannot be found for the passed key.</exception>
		public static T? TryGetValue<T>(string _key, ConfigData[] _datas, IConfigConverter<T>? _converter = default)
		{
			// Iterate through all data in the config collection
			for(int index = 0; index < _datas.Length; index++)
			{
				// Attempt to get the config value from the list. If successful, return the value
				if(_datas[index].TryGet(_key, out T? val, _converter))
					return val;
			}

			// If we made it to this point, the config value we are trying to get doesn't exist.
			throw new KeyNotFoundException($"Key: {_key} not found in any dictionary");
		}
	}
}