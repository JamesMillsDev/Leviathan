using Leviathan.Events;
using Leviathan.Mathematics;

using Raylib_CsLo;

using Color = Leviathan.Mathematics.Color;

namespace Leviathan.Physics
{
	internal class PhysicsModule : ILeviathanModule, IEventHandler
	{
		public void Load()
		{
			Physac.InitPhysics();
			Physac.SetPhysicsGravity(0, 0.1f);
		}

		public void Tick() => Physac.UpdatePhysics();

		public unsafe void OnDrawGizmos()
		{
			int count = Physac.GetPhysicsBodiesCount();
			for(int i = 0; i < count; i++)
			{
				PhysicsBodyData* body = Physac.GetPhysicsBody(i);
				if(body != null)
				{
					int vertexCount = Physac.GetPhysicsShapeVerticesCount(i);
					for(int j = 0; j < vertexCount; j++)
					{
						Vector2 vertexA = Physac.GetPhysicsShapeVertex(body, j);
						
						int jj = j + 1 < vertexCount ? j + 1 : 0;   // Get next vertex or first to close the shape
						Vector2 vertexB = Physac.GetPhysicsShapeVertex(body, jj);

						Raylib.DrawLineV(vertexA, vertexB, Color.Green);     // Draw a line between two vertex positions
					}
				}
			}
		}

		public void Unload() => Physac.ClosePhysics();
	}
}