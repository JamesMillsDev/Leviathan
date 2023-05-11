#include <Leviathan/Gizmos.h>

#include <glm/gtx/rotate_vector.hpp>

#include <Leviathan/Application.h>
#include <Leviathan/Config.h>

Config* Gizmos::m_config = nullptr;
Color32 Gizmos::color = { 0, 245, 0, 255 };
int Gizmos::m_toggleKey = 0;
float Gizmos::m_lineThickness = 0;
bool Gizmos::m_shown = false;
int Gizmos::m_circleLineDensity = 45;

void Gizmos::DrawRect(Rectangle _rect, vec2 _center, float _rotation)
{
	DrawRectanglePro(_rect, { _center.x, _center.y }, _rotation, color);
}

void Gizmos::DrawWireRect(vec2 _position, vec2 _size, float _rotation)
{
	vec2 up = glm::rotate(vec2{ 0, 1 }, _rotation * DEG2RAD);
	vec2 right = glm::rotate(vec2{ 1, 0 }, _rotation * DEG2RAD);

	vec2 tl = (up * _size.y - right * _size.x) + _position;
	vec2 tr = (up * _size.y + right * _size.x) + _position;
	vec2 bl = (-up * _size.y - right * _size.x) + _position;
	vec2 br = (-up * _size.y + right * _size.x) + _position;

	DrawLineEx({ tl.x, tl.y }, { tr.x, tr.y }, m_lineThickness, color);
	DrawLineEx({ tr.x, tr.y }, { br.x, br.y }, m_lineThickness, color);
	DrawLineEx({ br.x, br.y }, { bl.x, bl.y }, m_lineThickness, color);
	DrawLineEx({ bl.x, bl.y }, { tl.x, tl.y }, m_lineThickness, color);
}

void Gizmos::DrawCircle(vec2 _position, float _radius)
{
	DrawCircleV({ _position.x, _position.y }, _radius, color);
}

void Gizmos::DrawWireCircle(vec2 _position, float _radius)
{
	DrawPolyLinesEx({ _position.x, _position.y }, m_circleLineDensity, _radius, 0.f, m_lineThickness, color);
}

void Gizmos::DrawPolyShape(vector<vec2> _verts, vec2 _position)
{
	vec2 start = _verts[0] + _position;
	vec2 end = _verts[_verts.size() - 1] + _position;

	DrawLineEx({ start.x, start.y }, { end.x, end.y }, m_lineThickness, color);

	for (int i = 0; i < _verts.size() - 1; i++)
	{
		vec2 start = _verts[i] + _position;
		vec2 end = _verts[i + 1] + _position;

		DrawLineEx({ start.x, start.y }, { end.x, end.y }, m_lineThickness, color);
	}
}

void Gizmos::Init()
{
	m_config = Application::GetConfig(ConfigType::DEBUG);
	m_config->ListenForReload(&Gizmos::OnConfigReload);

	m_toggleKey = *m_config->GetValue<int>("Gizmos", "showGizmosKey");
	m_lineThickness = *m_config->GetValue<float>("Gizmos", "gizmoLineThickness");
	m_circleLineDensity = *m_config->GetValue<int>("Gizmos", "circleLineDensity");
}

void Gizmos::Tick()
{
	if (IsKeyPressed(m_toggleKey))
	{
		m_shown = !m_shown;
	}
}

void Gizmos::OnConfigReload(Config* _config)
{
	m_toggleKey = *m_config->GetValue<int>("Gizmos", "showGizmosKey");
	m_lineThickness = *m_config->GetValue<float>("Gizmos", "gizmoLineThickness");
	m_circleLineDensity = *m_config->GetValue<int>("Gizmos", "circleLineDensity");
}
