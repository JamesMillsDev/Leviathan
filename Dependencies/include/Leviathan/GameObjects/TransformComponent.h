#pragma once

#include <Leviathan/Leviathan.h>

#include <Leviathan/Math/Mat3.h>
#include <Leviathan/Math/Vec2.h>

#include <functional>
#include <vector>

using std::function;
using std::vector;

typedef function<void()> UpdateAction;

class TransformComponent
{
public:
	DLL TransformComponent*& Parent();
	DLL void SetParent(TransformComponent* _parent);

	DLL float Rotation();
	DLL float LocalRotation();

	DLL void SetRotation(const float& _newRot);

	DLL void UpdateRotation(const float& _amount);

	DLL void Position(float& _x, float& _y);
	DLL Vec2 Position();

	DLL void LocalPosition(float& _x, float& _y);
	DLL Vec2 LocalPosition();

	DLL void SetPosition(const Vec2& _newPosition);
	DLL void SetPosition(const float& _newX, const float& _newY);

	DLL void UpdatePosition(const Vec2& _amount);
	DLL void UpdatePosition(const float& _x, const float& _y);

	DLL void Scale(float& _x, float& _y);
	DLL Vec2 Scale();

	DLL void LocalScale(float& _x, float& _y);
	DLL Vec2 LocalScale();

	DLL void SetScale(const Vec2& _newScale);
	DLL void SetScale(const float& _newX, const float& _newY);

	DLL void UpdateScale(const Vec2& _amount);
	DLL void UpdateScale(const float& _x, const float& _y);

private:
	friend class IGameObject;

	Mat3 m_transform;
	TransformComponent* m_parent;
	vector<TransformComponent*> m_children;
	vector<UpdateAction> m_listUpdates;

	TransformComponent() : m_transform(Mat3::Identity()), m_parent(nullptr) {}

	DLL Mat3 GlobalTransform();

	DLL void AddChild(TransformComponent* _child);
	DLL void RemoveChild(TransformComponent* _child);
	DLL void Tick();

};

