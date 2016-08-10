#pragma once

#include "GuiComponent.h"
#include "Renderer.h"
#include "components/ImageComponent.h"
#include "components/TextComponent.h"
#include "components/ScrollableContainer.h"
#include "components/IList.h"
#include "resources/TextureResource.h"
#include "components/InfoStripComponent.h"

class GuiComponent;
class SetupGamepad : public GuiComponent
{
public:
    SetupGamepad(Window* window);

    bool input(InputConfig* config, Input input) override;
    void update(int deltaTime) override;
    void render(const Eigen::Affine3f& parentTrans) override;

    std::vector<HelpPrompt> getHelpPrompts() override;
    //virtual HelpStyle getHelpStyle() override;

//protected:
    //void onCursorChanged(const CursorState& state) override;

private:
    void populate();

    TextComponent mSystemInfo;

    // unit is list index
    float mCamOffset;
    float mExtrasCamOffset;
    float mExtrasFadeOpacity;
};
