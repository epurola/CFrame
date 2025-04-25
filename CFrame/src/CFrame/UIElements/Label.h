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
        void RegisterAnimator(std::shared_ptr<AnimationManager> manager);
        void CreateTexture(const std::string& text, int width, int height);
        void UpdateChildSizes() override;
        void OnEvent(CFrameEvent& event) override;
        inline Texture* GetTexture() { return labelTexture.get(); };
        inline ElementType GetElementType() const override { return ElementType::LABEL; };

  

    private:
        Color color;
        std::string text;
        unsigned char* textTexture;
        std::unique_ptr<Texture> labelTexture;
        TextProperties textProps;
        std::map<char, fontInfo> glyphs;
        std::unique_ptr<FontLoader> fontLoader;
    };
}