namespace Leviathan.InputSystem.Handlers
{
	public interface IInputHandler
	{
		public HandlerType Type { get; }
		
		public void Poll();
	}
}