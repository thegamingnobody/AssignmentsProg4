#ifndef TEXTURECOMPONENT
#define TEXTURECOMPONENT

#include "Component.h"
#include <string>
#include "Transform.h"

namespace dae
{
    class Texture2D;

    class TextureComponent : public Component
    {
    public:
        void Render(float const parentX, float const parentY) const;
        void Render(Transform const& transform) const;

        void SetTexture(const std::string& filename);
        void SetTexture(const std::shared_ptr<Texture2D>& texture);

        TextureComponent(dae::GameObject* object);
        TextureComponent(dae::GameObject* object, const std::string& filename);
        virtual ~TextureComponent() override = default;
        TextureComponent(const TextureComponent& other) = delete;
        TextureComponent(TextureComponent&& other) = delete;
        TextureComponent& operator= (const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) = delete;

    private:
        std::shared_ptr<Texture2D> m_Texture{};
    };
}

#endif