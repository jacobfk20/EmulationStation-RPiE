#include "views/SetupGamepad.h"
#include "SystemData.h"
#include "Renderer.h"
#include "Log.h"
#include "Window.h"
#include "views/ViewController.h"
#include "animations/LambdaAnimation.h"
#include "SystemData.h"
#include "Settings.h"
#include "Util.h"

#define SELECTED_SCALE 1.5f

SetupGamepad::SetupGamepad(Window* window) : GuiComponent(window),
mSystemInfo(window, "NO CONTROLLER DETECTED.", Font::get(FONT_SIZE_MEDIUM), 0x33333300, ALIGN_CENTER)
{
	mCamOffset = 0;
	mExtrasCamOffset = 0;
	mExtrasFadeOpacity = 0.0f;

	setSize((float)Renderer::getScreenWidth(), (float)Renderer::getScreenHeight());

	mSystemInfo.setSize(1080, 800);
	mSystemInfo.setPosition(0, 80);

	addChild(&mSystemInfo);

	populate();
}

void SetupGamepad::populate()
{

}

bool SetupGamepad::input(InputConfig* config, Input input)
{
	if (input.value != 0)
	{
	}

	return GuiComponent::input(config, input);
}

void SetupGamepad::update(int deltaTime)
{
	//listUpdate(deltaTime);
	GuiComponent::update(deltaTime);
}

//void SetupGamepad::onCursorChanged(const CursorState& state)
//{
//}

void SetupGamepad::render(const Eigen::Affine3f& parentTrans)
{
	Eigen::Affine3f trans = getTransform() * parentTrans;
	
	// Final rendering
	Renderer::setMatrix(trans);
	Renderer::drawRect(mSystemInfo.getPosition().x(), mSystemInfo.getPosition().y() - 1, mSize.x(), mSystemInfo.getSize().y(), 0xDDDDDD00 | (unsigned char)(mSystemInfo.getOpacity() / 255.f * 0xD8));
	mSystemInfo.render(trans);
}

std::vector<HelpPrompt> SetupGamepad::getHelpPrompts()
{
	std::vector<HelpPrompt> prompts;
	//prompts.push_back(HelpPrompt("left/right", "choose"));
	prompts.push_back(HelpPrompt("a", "Continue"));
	return prompts;
}

//HelpStyle SetupGamepad::getHelpStyle()
//{
//	HelpStyle style;
//	style.applyTheme(mEntries.at(mCursor).object->getTheme(), "system");
//	return style;
//}
