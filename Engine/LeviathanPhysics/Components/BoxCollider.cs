using Leviathan.Debugging;
using Leviathan.Mathematics;

namespace Leviathan.Physics.Components
{
	public class BoxCollider : Collider, IPhysicsHandler
	{
		internal override CollisionFunctions.Shape Shape => CollisionFunctions.Shape.Box;

		public Vector2 center = Vector2.Zero;
		public Vector2 extents = Vector2.One;

		private Color color = Color.Green;

		public override void Tick()
		{
			base.Tick();
			
			if(GameObject is { Transform: { } })
			{
				center = GameObject.Transform.Position;
				extents = GameObject.Transform.Scale / 2;
			}
		}

		public override void OnRenderGizmos()
		{
			if(GameObject is { Transform: { } })
			{
				Gizmos.DrawWireRectangle(new Rectangle(center, extents * 2), color, GameObject.Transform.Rotation);
			}
		}

		public void OnTriggerEnter(Collider _collider)
		{
			color = Color.Red;
		}

		public void OnTriggerStay(Collider _collider)
		{
			color = Color.Blue;
		}

		public void OnTriggerExit(Collider _collider)
		{
			color = Color.Green;
		}

		internal bool CheckCorners(ref BoxCollider _box, ref Vector2 _contact, ref int _numContacts, ref float _overlap, ref Vector2 _edgeNormal)
		{
			if(GameObject is { Transform: { } })
			{
				float minX = 0, maxX = 0, minY = 0, maxY = 0;

				float boxW = _box.extents.x * 2.0f;
				float boxH = _box.extents.y * 2.0f;

				int numLocalContacts = 0;
				Vector2 localContact = Vector2.Zero;

				bool first = true;

				for(float x = -_box.extents.x; x < boxW; x += boxW)
				{
					for(float y = -_box.extents.y; y < boxH; y += boxH)
					{
						Vector2 p = _box.center + x * _box.localXAxis + y * _box.localYAxis;

						Vector2 p0 = new Vector2(Vector2.Dot(p - center, localXAxis), Vector2.Dot(p - center, localYAxis));

						if(first || p0.x < minX) minX = p0.x;
						if(first || p0.x > maxX) maxX = p0.x;
						if(first || p0.y < minY) minY = p0.y;
						if(first || p0.y > maxY) maxY = p0.y;

						if(p0.x >= -extents.x && p0.x <= extents.x &&
						   p0.y >= -extents.y && p0.y <= extents.y)
						{
							numLocalContacts++;
							localContact += p0;
						}

						first = false;
					}
				}

				if(maxX <= -extents.x || minX >= extents.x ||
				   maxY <= -extents.y || minY >= extents.y)
					return false;

				if(numLocalContacts == 0)
					return false;

				bool result = false;

				_contact += center + (localContact.x * localXAxis + localContact.y * localYAxis) / numLocalContacts;
				_numContacts++;

				float overlap0 = extents.x - minX;
				if(overlap0 > 0 && (overlap0 < _overlap || _overlap == 0))
				{
					_edgeNormal = localXAxis;
					_overlap = overlap0;
					result = true;
				}

				overlap0 = maxX + extents.x;
				if(overlap0 > 0 && (overlap0 < _overlap || _overlap == 0))
				{
					_edgeNormal = localXAxis * -1;
					_overlap = overlap0;
					result = true;
				}

				overlap0 = extents.y - minY;
				if(overlap0 > 0 && (overlap0 < _overlap || _overlap == 0))
				{
					_edgeNormal = localYAxis;
					_overlap = overlap0;
					result = true;
				}

				overlap0 = maxY + extents.y;
				if(overlap0 > 0 && (overlap0 < _overlap || _overlap == 0))
				{
					_edgeNormal = localYAxis * -1;
					_overlap = overlap0;
					result = true;
				}

				return result;
			}

			return false;
		}
	}
}