#pragma once

#include <Leviathan/Math/Mat3.h>
#include <Leviathan/Math/Vec2.h>

#include <functional>
#include <vector>

using std::function;
using std::vector;

typedef function<void()> UpdateAction;

class Transform
{
public:
	Transform*& Parent();
	void SetParent(Transform* _parent);

	float Rotation();
	float LocalRotation();

	void SetRotation(const float& _newRot);

	void UpdateRotation(const float& _amount);

	void Position(float& _x, float& _y);
	Vec2 Position();

	void LocalPosition(float& _x, float& _y);
	Vec2 LocalPosition();

	void SetPosition(const Vec2& _newPosition);
	void SetPosition(const float& _newX, const float& _newY);

	void UpdatePosition(const Vec2& _amount);
	void UpdatePosition(const float& _x, const float& _y);

	void Scale(float& _x, float& _y);
	Vec2 Scale();

	void LocalScale(float& _x, float& _y);
	Vec2 LocalScale();

	void SetScale(const Vec2& _newScale);
	void SetScale(const float& _newX, const float& _newY);

	void UpdateScale(const Vec2& _amount);
	void UpdateScale(const float& _x, const float& _y);

private:
	friend class IGameObject;

	Mat3 m_transform;
	Transform* m_parent;
	vector<Transform*> m_children;
	vector<UpdateAction> m_listUpdates;

	Transform() : m_transform(Mat3::Identity()), m_parent(nullptr) {}

	Mat3 GlobalTransform();

	void AddChild(Transform* _child);
	void RemoveChild(Transform* _child);
	void Tick();

};

