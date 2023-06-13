#pragma once

#include <Leviathan/Core/Leviathan.h>
#include <Leviathan/Utils/Singleton.h>

#include <vector>
#include <list>
#include <map>

#include <box2d/b2_math.h>

using std::vector;
using std::list;
using std::pair;
using std::map;

class b2World;
class b2Body;
class b2Fixture;
struct b2BodyDef;

namespace Leviathan
{
	class PhysicsManager : public Singleton<PhysicsManager>
	{
	public:
		DLL PhysicsManager();
		PhysicsManager(PhysicsManager&) = delete;
		DLL ~PhysicsManager();
		DLL virtual void OnCreate() override;
		DLL virtual void OnDestroy() override;
		DLL static vector<class b2Body*> GetBodies();

		DLL static int PolygonCollisionDensity() { return m_instance->m_polygonDensity; }

	private:
		friend class Application;
		friend class Rigidbody;
		friend class Collider;
		friend class ContactListener;

		const float TIME_STEP = 1.f / 60.f;

		b2World* m_world;
		class Config* m_config;
		/*class ContactListener* m_contactListener;*/
		int m_velocityIterations;
		int m_positionIterations;
		map<b2Body*, class Rigidbody*> m_bodies;
		map<b2Fixture*, class Collider*> m_colliders;

		int m_polygonDensity;

	private:
		DLL static void Tick();

		DLL static class b2Body* CreateBody(b2BodyDef* _bodyDef);

		DLL static void ObserveBody(class Rigidbody* _body);
		DLL static void StopObservingBody(class Rigidbody* _body);

		DLL static void ObserveCollider(class Collider* _collider);
		DLL static void StopObservingCollider(class Collider* _collider);

		DLL static class Rigidbody* FindBodyFor(b2Fixture* _fixture);
		DLL static class Collider* FindColliderFor(b2Fixture* _fixture);

	};
}