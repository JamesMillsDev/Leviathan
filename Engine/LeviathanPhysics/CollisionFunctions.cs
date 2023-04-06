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

		internal static readonly Func<Collider, Collider, Collision?>[] collisionFunctions =
		{
			CircleCircle, CircleBox,
			BoxCircle, BoxBox
		};

		private static Collision? CircleCircle(Collider _a, Collider _b)
		{
			return null;
		}

		private static Collision? CircleBox(Collider _circle, Collider _box)
		{
			return null;
		}

		private static Collision? BoxBox(Collider _a, Collider _b)
		{
			if(_a is BoxCollider2D aBox && _b is BoxCollider2D bBox)
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

					return collision;
				}
			}
			
			return null;
		}

		private static Collision? BoxCircle(Collider _box, Collider _circle)
		{
			return null;
		}
	}
}