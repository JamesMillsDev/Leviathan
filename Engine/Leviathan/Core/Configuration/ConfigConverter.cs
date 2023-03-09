using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration
{
	/// <summary>An implementation of the Newtonsoft Json converter for config files.</summary>
	public class ConfigConverter : JsonConverter
	{
		/// <summary>
		/// Writes the JSON representation of the object.
		/// </summary>
		/// <param name="_writer">The <see cref="JsonWriter"/> to write to.</param>
		/// <param name="_value">The value.</param>
		/// <param name="_serializer">The calling serializer.</param>
		public override void WriteJson(JsonWriter _writer, object? _value, JsonSerializer _serializer)
		{
			if(_value == null)
				throw new NullReferenceException("Existing data not set!");
				
			JToken token = JToken.FromObject(_value);
			token.WriteTo(_writer);
		}

		/// <summary>This is never called because <see cref="CanRead"/> is false. It will use the default deserializer.</summary>
		public override object ReadJson(JsonReader _reader, Type _objectType, object? _existingValue, JsonSerializer _serializer)
		{
			throw new NotImplementedException("Unnecessary because CanRead is false. The type will skip the converter.");
		}

		/// <summary>Determines whether this instance can convert the specified object type.</summary>
		/// <param name="_objectType">Type of the object.</param>
		/// <returns>
		/// 	<c>true</c> if this instance can convert the specified object type; otherwise, <c>false</c>.
		/// </returns>
		public override bool CanConvert(Type _objectType) => _objectType == typeof(IConfigData);

		/// <summary>Gets a value indicating whether this <see cref="JsonConverter"/> can read JSON.</summary>
		/// <value><c>true</c> if this <see cref="JsonConverter"/> can read JSON; otherwise, <c>false</c>.</value>
		public override bool CanRead => false;
	}
}