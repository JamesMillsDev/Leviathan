namespace Leviathan.Structures
{
	public static class LeviathanTasks
	{
		public static async Task WhenComplete(Func<bool> _completionCheck)
		{
			while(!_completionCheck())
			{
				await Task.Delay(25);
			}
		}
	}
}