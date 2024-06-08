#ifndef TEXTURECOMPONENT
#define TEXTURECOMPONENT

#include "Component.h"
#include <string>

namespace dae
{
    class Texture2D;

    class TextureComponent : public Component
    {
    public:
        void Render() const;

        void SetTexture(const std::string& filename);
        void SetTexture(const std::shared_ptr<Texture2D>& texture);

        glm::ivec2 GetSize() const { return m_Texture->GetSize(); }

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