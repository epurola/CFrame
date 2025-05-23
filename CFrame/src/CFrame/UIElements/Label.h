#pragma once
#include <string>
#include "../Renderer/Texture.h"
#include "../Renderer/FontLoader.h"
#include "UIElement.h"
#include "../Renderer/Renderer1.h"


namespace CFrame
{

    class CFRAME_API Label : public UIElement
    {
    public:
        Label(int x, int y, int w, int h, const std::string& text = "Label",
            UIElement* parent = nullptr);

        explicit Label(int w, int h)
            : Label(0, 0, w, h, "Label", nullptr) {
        }

        ~Label();

        void Render(Renderer1& renderer) override;
        void Render(float timestep) override;
        void RegisterAnimator(std::shared_ptr<ApplicationManager> manager);
        void UpdateChildSizes() override;
        void OnEvent(CFrameEvent& event) override;
        inline Texture* GetTexture() { return atlasTexture.get(); };
        inline ElementType GetElementType() const override { return ElementType::LABEL; };

        void SetText(std::string text);

  

    private:
        std::string text;
        std::shared_ptr<Texture> atlasTexture;
        std::optional<int> icon = std::nullopt;
        TextProperties textProps;
        std::map<char, fontInfo> glyphs;
    private:
        void InitFontAtlas();
        void SetOverFlowProperties();
    };
}