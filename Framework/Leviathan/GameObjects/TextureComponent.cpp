#include <Leviathan/GameObjects/TextureComponent.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <Leviathan/Resources/Resources.h>
#include <Leviathan/Resources/TextureResource.h>

#include <exception>
#include <iostream>

using std::exception;

namespace Leviathan
{
    TextureComponent::TextureComponent(GameObject* _owner)
        : Component(_owner), m_texture(nullptr), m_id(nullptr)
    {
    }

    TextureComponent::~TextureComponent()
    {
        if (m_texture != nullptr)
        {
            m_texture->Dispose();
            m_texture = nullptr;
        }
    }

    void TextureComponent::Load()
    {
        if (m_id != nullptr)
        {
            try
            {
                m_texture = Resources::Find<Texture2D, TextureResource>(m_id);
            }
            catch (exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
    }

    void TextureComponent::Render()
    {
        if (m_texture != nullptr)
        {
            TransformComponent* transform = m_owner->Transform();
            if (transform != nullptr)
            {
                const Rectangle src
                {
                    0,
                    0,
                    (float)m_texture->Get().width,
                    (float)m_texture->Get().height,
                };

                const Rectangle dst
                {
                    transform->AnchoredPosition().x,
                    transform->AnchoredPosition().y,
                    transform->Scale().x,
                    transform->Scale().y
                };

                const vec2 center =
                {
                    transform->Scale().x / 2,
                    transform->Scale().y / 2
                };

                DrawTexturePro(*m_texture, src, dst, { center.x, center.y }, transform->Rotation(), WHITE);
            }
        }
    }
}
