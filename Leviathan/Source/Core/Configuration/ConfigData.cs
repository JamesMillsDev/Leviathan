using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration
{
	/// <summary>A wrapper for a config json object.</summary>
	public readonly struct ConfigData
	{
		/// <summary>The data of the config category.</summary>
		private readonly Dictionary<string, object> data;
		/// <summary>The category of this config data.</summary>
		private readonly string category;

		/// <param name="_data">The data found in the json config object.</param>
		/// <param name="_category">The category for this config object.</param>
		public ConfigData(Dictionary<string, object> _data, string _category)
		{
			data = _data;
			category = _category;
		}

		/// <summary>Attempts to get the value from the config object.</summary>
		/// <param name="_key">The key for the value we are trying to get. This does contain the category.</param>
		/// <param name="_val">The returned value of the config.</param>
		/// <param name="_converter">The converter that can be used to change the data to a custom type.</param>
		/// <typeparam name="T">The type of data we want from the config object.</typeparam>
		/// <returns>Whether or not the value was retrieved from the data.</returns>
		public bool TryGet<T>(string _key, out T? _val, IConfigConverter<T>? _converter = null)
		{
			// Check if the config is actually associated with the passed key.
			if(_key.Contains(category) && data.ContainsKey(_key.Remove(0, category.Length + 1)))
			{
				// Get the value from the config
				object val = data[_key.Remove(0, category.Length + 1)];

				// Check if this value is a json object, if it is, use the passed converter
				if(val is JObject jObject)
				{
					_val = _converter!.Convert(jObject);

					// Successfully retrieved the config value
					return true;
				}

				// Use the default converter for the type.
				_val = (T?) Convert.ChangeType(val, typeof(T));

				// Successfully retrieved the config value
				return true;
			}

			_val = default;

			// Failed to retrieve the config value
			return false;
		}
	}
}