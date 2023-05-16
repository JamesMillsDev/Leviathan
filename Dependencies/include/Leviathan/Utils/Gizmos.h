#pragma once

#include <Leviathan/Core/Color32.h>
#include <Leviathan/Core/Leviathan.h>

#include <glm/vec2.hpp>

#include <vector>

using glm::vec2;

using std::vector;

class Gizmos
{
public:
	DLL static Color32 color;

public:
	DLL static void DrawRect(Rectangle _rect, vec2 _center, float _rotation);
	DLL static void DrawWireRect(vec2 _position, vec2 _size, float _rotation);
	DLL static void DrawCircle(vec2 _position, float _radius);
	DLL static void DrawWireCircle(vec2 _position, float _radius);
	DLL static void DrawPolyShape(vector<vec2> _verts, vec2 _position);

private:
	friend class Application;

	DLL static class Config* m_config;

	DLL static int m_toggleKey;
	DLL static bool m_shown;

	DLL static float m_lineThickness;
	DLL static int m_circleLineDensity;

private:
	DLL static void Init();
	DLL static void Tick();

	DLL static void OnConfigReload(class Config* _config);

};