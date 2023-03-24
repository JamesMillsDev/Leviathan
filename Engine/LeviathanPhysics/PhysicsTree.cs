using Leviathan.Mathematics;
using Leviathan.Physics.Components;
using Leviathan.Structures.Trees.Quad;

using Raylib_cs;

using System.Diagnostics.CodeAnalysis;

using Color = Leviathan.Mathematics.Color;
using Rectangle = Leviathan.Physics.Shapes.Rectangle;

namespace Leviathan.Physics
{
	[SuppressMessage("ReSharper", "PossiblyImpureMethodCallOnReadonlyVariable")]
	public class PhysicsTree : QuadTree<Collider, Rectangle, PhysicsTreeData, PhysicsTree>
	{
		public PhysicsTree(Rectangle _bounds) : base(_bounds) { }

		public override PhysicsTreeData? Insert([NotNull] PhysicsTreeData? _data)
		{
			if(!bounds.Intersects(_data!.bounds))
				return default;

			if(IsLeaf && contents.Count + 1 > MAX_DATA_PER_NODE)
				Split();

			if(IsLeaf)
			{
				contents.Add(_data);
			}
			else
			{
				foreach(PhysicsTree node in children)
					node.Insert(_data);
			}

			return _data;
		}

		public override void Split()
		{
			if(currentDepth + 1 >= MAX_DEPTH)
				return;

			Vector2 min = bounds.Min;
			Vector2 max = bounds.Max;

			Vector2 center = min + (max - max) * 0.5f;
			Rectangle[] childBounds =
			{
				Rectangle.FromMinMax(min, center),
				Rectangle.FromMinMax(new Vector2(center.x, min.y), new Vector2(max.x, center.y)),
				Rectangle.FromMinMax(center, max),
				Rectangle.FromMinMax(new Vector2(min.x, center.y), new Vector2(center.x, max.y))
			};

			for(int i = 0; i < childBounds.Length; i++)
			{
				children.Add(new PhysicsTree(childBounds[i]));
				children[i].currentDepth = currentDepth + 1;
			}

			foreach(PhysicsTree child in children)
			{
				foreach(PhysicsTreeData data in contents)
				{
					child.Insert(data);
				}
			}

			contents.Clear();
		}

		public override List<Collider> Query(Rectangle _area)
		{
			List<Collider> result = new();

			if(!bounds.Intersects(_area))
				return result;

			if(IsLeaf)
			{
				foreach(PhysicsTreeData data in contents)
				{
					if(data.bounds.Intersects(_area))
						result.Add(data.value);
				}
			}
			else
			{
				// ReSharper disable once ForeachCanBePartlyConvertedToQueryUsingAnotherGetEnumerator
				foreach(PhysicsTree child in children)
				{
					List<Collider> recurse = child.Query(_area);
					if(recurse.Count > 0)
					{
						result.AddRange(recurse);
					}
				}
			}

			return result;
		}

		protected override void Visualise(PhysicsTree _tree)
		{
			Raylib.DrawRectangleLines((int) _tree.bounds.Min.x, (int) _tree.bounds.Min.y, (int) _tree.bounds.size.x, (int) _tree.bounds.size.y, Color.Red);
			Raylib.DrawText($"{_tree.contents.Count}", (int) _tree.bounds.Min.x + 5, (int) _tree.bounds.Min.y + 5, 10, Color.Red);
		}
	}
}