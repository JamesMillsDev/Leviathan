using Leviathan.Mathematics;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Structures.Trees.Quad
{
	public abstract class QuadTree<VALUE, DATA, TREE>
		where DATA : QuadTreeData<VALUE>
		where TREE : QuadTree<VALUE, DATA, TREE>
	{
		protected const int MAX_DEPTH = 5;
		protected const int MAX_DATA_PER_NODE = 15;

		protected bool IsLeaf => children.Count == 0;

		public int NumObjects
		{
			get
			{
				Reset();
				int objectCount = contents.Count;
				for(int i = 0; i < objectCount; i++)
					contents[i].flag = true;

				Queue<TREE> process = new();
				process.Enqueue((TREE)this);

				while(process.Count > 0)
				{
					TREE processing = process.Dequeue();

					if(!processing.IsLeaf)
					{
						foreach(TREE quadTree in processing.children)
						{
							process.Enqueue(quadTree);
						}
					}
					else
					{
						foreach(DATA data in processing.contents.Where(_data => !_data.flag))
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

		protected readonly List<TREE> children = new();
		protected readonly List<DATA> contents = new();
		protected readonly Rectangle bounds;

		protected int currentDepth;

		protected QuadTree(Rectangle _bounds)
		{
			bounds = _bounds;
			currentDepth = 0;
		}

		public abstract DATA? Insert([NotNull] DATA? _data);

		public void Remove(DATA _data)
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
					foreach(TREE child in children)
						child.Remove(_data);
				}

				Shake();
			}
		}

		public void Update(DATA _data)
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
					Queue<TREE> process = new();
					process.Enqueue((TREE)this);

					while(process.Count > 0)
					{
						TREE processing = process.Dequeue();

						if(!processing.IsLeaf)
						{
							foreach(TREE quadTree in processing.children)
								process.Enqueue(quadTree);
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

		public abstract void Split();

		public void Reset()
		{
			if(IsLeaf)
			{
				foreach(DATA data in contents)
					data.flag = false;
			}
			else
			{
				foreach(TREE child in children)
					child.Reset();
			}
		}

		public abstract List<VALUE?> Query(Rectangle _area);

		public void Visualise()
		{
			Queue<TREE> toProcess = new();
			toProcess.Enqueue((TREE)this);

			while(toProcess.Count > 0)
			{
				TREE processing = toProcess.Dequeue();

				Visualise(processing);
				
				foreach(TREE child in processing.children)
				{
					toProcess.Enqueue(child);
				}
			}
		}

		protected abstract void Visualise(TREE _tree);
	}
}