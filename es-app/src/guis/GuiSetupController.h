#pragma once

#include "GuiComponent.h"
#include "components/MenuComponent.h"
#include "components/NetworkInfoComponent.h"
#include "components/ComponentGrid.h"
#include <string>
#include <vector>
#include <functional>

class GuiSetupController : public GuiComponent
{
public:
    GuiSetupController(Window* window, const std::function<void()>& doneCallback);

    bool input(InputConfig* config, Input input) override;
    void update(int deltatime) override;
    void onSizeChanged() override;
    std::vector<HelpPrompt> getHelpPrompts() override;

private:
    bool loadFile();
    int getControllerCount();
    void buildControllerGrid();
    void createSampleFile();

    ComponentGrid mGrid;

    MenuComponent mMenu;

    TextComponent mVersion;

    std::function<void()> mDoneCallback;

    std::vector<std::vector<std::string>> vDocData;
    int mControllerCount = 0;
    bool mFileLoaded = false;
};
