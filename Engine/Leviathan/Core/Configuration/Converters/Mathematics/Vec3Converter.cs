using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Vec3"/>.</summary>
	public class Vec3Converter : IConfigConverter<Vec3>
	{
		public Vec3 Convert(JObject _jObject) => new((int) _jObject["x"]!, (int) _jObject["y"]!, (int) _jObject["z"]!);
	}
}