namespace Leviathan.Structures.Trees
{
	public abstract class TreeData<VALUE>
	{
		public readonly VALUE value;
		public bool flag;

		protected TreeData(VALUE _value)
		{
			value = _value;
		}
	}
}