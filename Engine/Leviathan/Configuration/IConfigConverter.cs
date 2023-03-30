using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration
{
	/// <summary>An interface that can be used to convert the type from a <see cref="JObject"/></summary>
	/// <typeparam name="TYPE"></typeparam>
	public interface IConfigConverter<TYPE>
	{
		/// <summary>The function that can be used to convert from the <see cref="JObject"/> to <see cref="TYPE"/>.</summary>
		/// <param name="_jObject">The Json Object we are trying to convert to the passed type.</param>
		/// <returns>The converted object.</returns>
		public TYPE? Convert(JObject _jObject);
	}
}