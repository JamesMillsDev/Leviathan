namespace Leviathan.Physics.Components
{
	public interface IPhysicsHandler
	{
		public virtual uint Mask => 0;

		public void OnTriggerEnter(Collider _collider) { }
		
		public void OnTriggerStay(Collider _collider) { }
		
		public void OnTriggerExit(Collider _collider) { }
		
		public void OnCollisionEnter(Collision _collision) { }
		
		public void OnCollisionStay(Collision _collision) { }
		
		public void OnCollisionExit(Collision _collision) { }
	}
}