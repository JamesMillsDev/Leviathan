#include <Leviathan/Utils/Gizmos.h>

#include <Leviathan/Core/Application.h>

#include <Leviathan/Utils/Config.h>
#include <Leviathan/Utils/ConfigValue.h>

#include <glm/gtx/rotate_vector.hpp>

Color32 Gizmos::color = { 0, 245, 0, 255 };

Gizmos* Gizmos::m_instance = nullptr;

void Gizmos::DrawRect(const Rectangle _rect, const vec2 _center, const float _rotation)
{
    DrawRectanglePro(_rect, { _center.x, _center.y }, _rotation, color);
}

void Gizmos::DrawWireRect(const vec2 _position, const vec2 _size, const float _rotation)
{
    const vec2 up = glm::rotate(vec2 { 0, 1 }, _rotation * DEG2RAD);
    const vec2 right = glm::rotate(vec2 { 1, 0 }, _rotation * DEG2RAD);

    const vec2 tl = (up * _size.y - right * _size.x) + _position;
    const vec2 tr = (up * _size.y + right * _size.x) + _position;
    const vec2 bl = (-up * _size.y - right * _size.x) + _position;
    const vec2 br = (-up * _size.y + right * _size.x) + _position;

    DrawLineEx({ tl.x, tl.y }, { tr.x, tr.y }, m_instance->m_lineThickness, color);
    DrawLineEx({ tr.x, tr.y }, { br.x, br.y }, m_instance->m_lineThickness, color);
    DrawLineEx({ br.x, br.y }, { bl.x, bl.y }, m_instance->m_lineThickness, color);
    DrawLineEx({ bl.x, bl.y }, { tl.x, tl.y }, m_instance->m_lineThickness, color);
}

void Gizmos::DrawCircle(const vec2 _position, const float _radius)
{
    DrawCircleV({ _position.x, _position.y }, _radius, color);
}

void Gizmos::DrawWireCircle(const vec2 _position, const float _radius)
{
    DrawPolyLinesEx({ _position.x, _position.y }, m_instance->m_circleLineDensity, _radius, 0.f, m_instance->m_lineThickness, color);
}

void Gizmos::DrawPolyShape(const vector<vec2> _verts, const vec2 _position)
{
    vec2 start = _verts[0] + _position;
    vec2 end = _verts[_verts.size() - 1] + _position;

    DrawLineEx({ start.x, start.y }, { end.x, end.y }, m_instance->m_lineThickness, color);

    for(int i = 0; i < _verts.size() - 1; i++)
    {
        start = _verts[i] + _position;
        end = _verts[i + 1] + _position;

        DrawLineEx({ start.x, start.y }, { end.x, end.y }, m_instance->m_lineThickness, color);
    }
}

void Gizmos::Init()
{
    m_config = Application::GetConfig(ConfigType::Debug);
    m_config->ListenForReload(&Gizmos::OnConfigReload, this);

    m_toggleKey = m_config->GetValue("Gizmos", "showGizmosKey")->Get<int>();
    m_lineThickness = m_config->GetValue("Gizmos", "gizmoLineThickness")->Get<float>();
    m_circleLineDensity = m_config->GetValue("Gizmos", "circleLineDensity")->Get<int>();
}

void Gizmos::Tick()
{
    if(IsKeyPressed(m_toggleKey))
    {
        m_shown = !m_shown;
    }
}

void Gizmos::OnConfigReload(Config* _config)
{
    m_toggleKey = m_config->GetValue("Gizmos", "showGizmosKey")->Get<int>();
    m_lineThickness = m_config->GetValue("Gizmos", "gizmoLineThickness")->Get<float>();
    m_circleLineDensity = m_config->GetValue("Gizmos", "circleLineDensity")->Get<int>();
}
