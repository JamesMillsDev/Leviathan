using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Vector3"/>.</summary>
	public class Vec3Converter : IConfigConverter<Vector3>
	{
		public Vector3 Convert(JObject _jObject) => new((int) _jObject["x"]!, (int) _jObject["y"]!, (int) _jObject["z"]!);
	}
}