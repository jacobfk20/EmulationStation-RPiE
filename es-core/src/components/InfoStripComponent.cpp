#include "components/InfoStripComponent.h"
#include "Log.h"

#define TITLE_HEIGHT = 100 //(mTitle->getFont()->getLetterHeight() + TITLE_VERT_PADDING)

using namespace Eigen;

InfoStripComponent::InfoStripComponent(Window* window, const std::shared_ptr<Font>& titleFont) : GuiComponent(window), 
	mBackground(window), mGrid(window, Vector2i(1, 1)), mWifiImg(window), mLanImg(window)
{	
	addChild(&mBackground);
	//addChild(&mGrid);

	mBackground.setImagePath(":/frame.png");

	// set up list which will never change (externally, anyway)
	//mList = std::make_shared<ComponentList>(mWindow);
	//mGrid.setEntry(mList, Vector2i(0, 1), true);

	// setup fake objects
	mWifiImg.setImage("/home/pi/ESbuild/wificon.png");
	mWifiImg.setMaxSize(320, 320);
	mLanImg.setImage("/home/pi/ESbuild/lancon.png");
	mLanImg.setMaxSize(320, 320);
	mWifiImg.setPosition(0, 0);
	mLanImg.setPosition(32, 0);

	//mGrid.setEntry(mWifiImg, Vector2i(0, 0), false, true);
	//mGrid.setEntry(mLanImg, Vector2i(1, 0), false, true);
	addChild(&mWifiImg);
	addChild(&mWifiImg);

	//updateGrid();
	updateSize();

	setPosition(0, 0);

	mGrid.resetCursor();
}


void InfoStripComponent::update(int deltatime) {
	if (mFrameCount > 1000) {
		mFrameCount = 0;

		// update lan and wan
		// See if wifi is a thing with pipes!
		bool bWifi = false;
		FILE *fp;
		char path[1035];
		fp = popen("ifconfig wlan0 | grep \"inet addr:\"", "r");

		while (fgets(path, sizeof(path), fp) != NULL) {
			std::string cline = path;
			if (cline.length() > 15) bWifi = true;
		}

		LOG(LogError) << "Update!";
		LOG(LogError) << "IScomp : " << getPosition() << ".  Size: " << getSize();

		if (bWifi) {
			mWifiImg.setColorShift(0x3355DD);
		}
		else {
			mWifiImg.setColorShift(0xDD5533);
		}
	}

	mFrameCount++;
}



void InfoStripComponent::updateSize()
{
	const float maxHeight = Renderer::getScreenHeight() * 0.9f;
	//float height = TITLE_HEIGHT; + mList->getTotalRowHeight() + getButtonGridHeight() + 2;
	//if(height > maxHeight)
	//{
	//	height = TITLE_HEIGHT + getButtonGridHeight();
	//	int i = 0;
	//	while(i < mList->size())
	//	{
	//		float rowHeight = mList->getRowHeight(i);
	//		if(height + rowHeight < maxHeight)
	//			height += rowHeight;
	//		else
	//			break;
	//		i++;
	//	}
	//}

	//setSize(Renderer::getScreenWidth() * 0.5f, height);
	setSize(Renderer::getScreenWidth() * 0.3f, maxHeight);
}

void InfoStripComponent::onSizeChanged()
{
	//mBackground.fitTo(mSize, Eigen::Vector3f::Zero(), Eigen::Vector2f(-32, -32));

	//// update grid row/col sizes
	//mGrid.setRowHeightPerc(0, TITLE_HEIGHT / mSize.y());
	//mGrid.setRowHeightPerc(2, getButtonGridHeight() / mSize.y());
	//
	//mGrid.setSize(mSize);
}
