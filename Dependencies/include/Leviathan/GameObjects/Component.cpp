#include "Component.h"

#include <Leviathan/GameObjects/GameObject.h>

namespace Leviathan
{
	const TObjectPtr<GameObject> Component::GetOwner() const
	{
		TObjectPtr<GameObject> ptr = TObjectPtr<GameObject>(m_owner);
		ptr.SetCopied(true);

		return ptr;
	}
}
