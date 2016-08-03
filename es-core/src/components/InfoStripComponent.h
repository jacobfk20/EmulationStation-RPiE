#pragma once

#include "components/NinePatchComponent.h"
#include "components/ComponentList.h"
#include "components/TextComponent.h"
#include "components/ComponentGrid.h"
#include "Util.h"

class InfoStripComponent;

//std::shared_ptr<ImageComponent> makeArrow(Window* window);

#define TITLE_VERT_PADDING (Renderer::getScreenHeight()*0.0637f)

class InfoStripComponent : public GuiComponent
{
public:
	InfoStripComponent(Window* window, const std::shared_ptr<Font>& sharedFont = Font::get(FONT_SIZE_SMALL));

	void onSizeChanged() override;

	// void addRow(const ComponentListRow& row, bool setCursorHere = false) { mList->addRow(row, setCursorHere); updateSize(); }

	void update(int deltatime) override;


private:
	void updateSize();
	//void updateGrid();
	float getButtonGridHeight() const;

	NinePatchComponent mBackground;
	//ComponentList mList;
	ComponentGrid mGrid;

	std::shared_ptr<ComponentList> mList;

	// temoporarily make some fake objects
	int mFrameCount = 0;
	int mDCount = 0;
	// wifi info obj:
	ImageComponent mWifiImg;
	bool mWifiState;
	// Lan Info obj:
	ImageComponent mLanImg;
	bool mLanState;
};
