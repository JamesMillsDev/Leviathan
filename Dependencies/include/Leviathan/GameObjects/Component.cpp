#include "Component.h"

#include <Leviathan/GameObjects/GameObject.h>

namespace Leviathan
{
	TObjectPtr<GameObject> Component::GetOwner()
	{
		TObjectPtr<GameObject> ptr = TObjectPtr<GameObject>(m_owner);
		ptr.SetCopied(true);

		return TObjectPtr<GameObject>(ptr);
	}
}
