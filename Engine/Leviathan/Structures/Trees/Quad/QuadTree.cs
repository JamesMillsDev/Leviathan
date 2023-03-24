using Leviathan.Extensions;
using Leviathan.GameObjects;
using Leviathan.Mathematics;

using Raylib_cs;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Structures.Trees.Quad
{
	public class QuadTree<VALUE>
	{
		protected const int MAX_DEPTH = 5;
		protected const int MAX_DATA_PER_NODE = 15;

		public bool IsLeaf => children.Count == 0;

		public int NumObjects
		{
			get
			{
				Reset();
				int objectCount = contents.Count;
				for(int i = 0; i < objectCount; i++)
					contents[i].flag = true;

				Queue<QuadTree<VALUE>> process = new();
				process.Enqueue(this);

				while(process.Count > 0)
				{
					QuadTree<VALUE> processing = process.Dequeue();

					if(!processing.IsLeaf)
					{
						foreach(QuadTree<VALUE> node in processing.children)
							process.Enqueue(node);
					}
					else
					{
						foreach(QuadTreeData<VALUE> data in processing.contents.Where(_data => !_data.flag))
						{
							objectCount++;
							data.flag = true;
						}
					}
				}

				Reset();

				return objectCount;
			}
		}

		protected readonly List<QuadTree<VALUE>> children = new();
		protected readonly List<QuadTreeData<VALUE>> contents = new();
		protected readonly Rectangle bounds;

		protected int currentDepth;

		public QuadTree(Rectangle _bounds)
		{
			bounds = _bounds;
			currentDepth = 0;
		}

		public QuadTreeData<VALUE>? Insert([NotNull] QuadTreeData<VALUE>? _data)
		{
			if(!bounds.Contains(_data!.Bounds))
				return default;

			if(IsLeaf && contents.Count + 1 > MAX_DATA_PER_NODE)
				Split();

			if(IsLeaf)
			{
				contents.Add(_data);
			}
			else
			{
				foreach(QuadTree<VALUE> node in children)
					node.Insert(_data);
			}

			return _data;
		}

		public void Remove(QuadTreeData<VALUE> _data)
		{
			if(IsLeaf)
			{
				int removeIndex = -1;

				for(int i = 0; i < contents.Count; i++)
				{
					if(contents[i].value == null)
						continue;

					if(contents[i].value!.Equals(_data.value))
					{
						removeIndex = i;

						break;
					}
				}

				if(removeIndex != -1)
				{
					contents.RemoveAt(removeIndex);
				}
				else
				{
					foreach(QuadTree<VALUE> child in children)
						child.Remove(_data);
				}

				Shake();
			}
		}

		public void Update(QuadTreeData<VALUE> _data)
		{
			Remove(_data);
			Insert(_data);
		}

		public void Shake()
		{
			if(!IsLeaf)
			{
				int numObjects = NumObjects;
				if(numObjects == 0)
				{
					children.Clear();
				}
				else if(numObjects < MAX_DATA_PER_NODE)
				{
					Queue<QuadTree<VALUE>> process = new();
					process.Enqueue(this);

					while(process.Count > 0)
					{
						QuadTree<VALUE> processing = process.Dequeue();

						if(!processing.IsLeaf)
						{
							foreach(QuadTree<VALUE> node in processing.children)
								process.Enqueue(node);
						}
						else
						{
							contents.AddRange(processing.contents);
						}
					}

					children.Clear();
				}
			}
		}

		public void Split()
		{
			if(currentDepth + 1 >= MAX_DEPTH)
				return;

			Vector2 min = bounds.Min();
			Vector2 max = bounds.Max();

			Vector2 center = min + (max - max) * 0.5f;
			Rectangle[] childBounds =
			{
				RayRectangleExtensions.FromMinMax(min, center),
				RayRectangleExtensions.FromMinMax(new Vector2(center.x, min.y), new Vector2(max.x, center.y)),
				RayRectangleExtensions.FromMinMax(center, max),
				RayRectangleExtensions.FromMinMax(new Vector2(min.x, center.y), new Vector2(center.x, max.y))
			};

			for(int i = 0; i < childBounds.Length; i++)
			{
				children.Add(new QuadTree<VALUE>(childBounds[i]));
				children[i].currentDepth = currentDepth + 1;
			}

			for(int i = 0; i < contents.Count; i++)
				children[i].Insert(contents[i]);

			contents.Clear();
		}

		public void Reset()
		{
			if(IsLeaf)
			{
				foreach(QuadTreeData<VALUE> data in contents)
					data.flag = false;
			}
			else
			{
				foreach(QuadTree<VALUE> child in children)
					child.Reset();
			}
		}

		public List<VALUE> Query(Rectangle _area)
		{
			List<VALUE> result = new();

			if(!bounds.Contains(_area))
				return result;

			if(IsLeaf)
			{
				foreach(QuadTreeData<VALUE> data in contents)
				{
					if(data.Bounds.Contains(_area))
						result.Add(data.value);
				}
			}
			else
			{
				// ReSharper disable once ForeachCanBePartlyConvertedToQueryUsingAnotherGetEnumerator
				foreach(QuadTree<VALUE> child in children)
				{
					List<VALUE> recurse = child.Query(_area);
					if(recurse.Count > 0)
					{
						result.AddRange(recurse);
					}
				}
			}

			return result;
		}
	}
}