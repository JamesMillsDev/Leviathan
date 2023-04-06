using Leviathan.Mathematics;
using Leviathan.Physics.Components;

namespace Leviathan.Physics
{
	internal static class CollisionFunctions
	{
		internal enum Shape
		{
			Circle,
			Box,
			Max
		}

		internal static readonly Action<Collider, Collider>[] collisionFunctions =
		{
			CircleCircle, CircleBox,
			BoxCircle, BoxBox
		};

		private static void CircleCircle(Collider _a, Collider _b)
		{
			
		}

		private static void CircleBox(Collider _circle, Collider _box)
		{
			
		}

		private static void BoxBox(Collider _a, Collider _b)
		{
			if(_a is BoxCollider aBox && _b is BoxCollider bBox)
			{
				Vector2 normal = Vector2.Zero;
				Vector2 contact = Vector2.Zero;
				float overlap = 0;
				int numContacts = 0;

				aBox.CheckCorners(ref bBox, ref contact, ref numContacts, ref overlap, ref normal);
				if(bBox.CheckCorners(ref aBox, ref contact, ref numContacts, ref overlap, ref normal))
				{
					normal *= -1;
				}

				if(overlap > 0)
				{
					Collision collision = new()
					{
						normal = normal,
						point = contact,
						delta = overlap
					};
					
					_a.ResolveCollision(_b, collision);
				}
			}
		}

		private static void BoxCircle(Collider _box, Collider _circle)
		{
			
		}
	}
}