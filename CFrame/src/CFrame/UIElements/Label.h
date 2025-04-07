#pragma once
#pragma once
#include <string>
#include "../Renderer/Texture.h"
#include "../Renderer/FontLoader.h"
#include "UIElement.h"

namespace CFrame
{
    class CFRAME_API Label : public UIElement
    {
    public:
        Label(int x, int y, int w, int h, const std::string& text = "Label",
            UIElement* parent = nullptr);

        explicit Label(int w, int h)
            : Label(0, 0, w, h, "Button", nullptr) {
        }

        ~Label();

        void Render(Renderer& renderer) override;
        void CreateTexture(const std::string& text, int width, int height);
        void OnEvent(CFrameEvent& event) override;
        inline Texture* GetTexture() { return sdfTexture; };
        inline ElementType GetElementType() const override { return ElementType::LABEL; };

  

    private:
        //Color color;
        std::string text;
        Texture* sdfTexture = nullptr;
        unsigned char* textTexture;
    };
}