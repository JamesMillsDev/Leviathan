using System.Runtime.CompilerServices;

[assembly: InternalsVisibleTo("Leviathan.UI")]
[assembly: InternalsVisibleTo("Leviathan.Input")]
[assembly: InternalsVisibleTo("Leviathan.Physics")]

namespace Leviathan
{
	internal interface ILeviathanModule
	{
		public void Load();
		public void Render() { }
		public void Tick() { }
		public void OnDrawGizmos() { }
		public void Unload();
	}
}