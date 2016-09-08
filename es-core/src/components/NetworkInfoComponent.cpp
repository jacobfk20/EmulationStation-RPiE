#include "components/NetworkInfoComponent.h"
#include "Settings.h"
#include "Log.h"



NetworkInfoComponent::NetworkInfoComponent(Window* window, std::string wanInterface, std::string lanInterface) : 
	GuiComponent(window), mWifiIcon(window), mLanIcon(window) {

	// Get user settings
	mEnable = Settings::getInstance()->getBool("ShowNetwork");

	mWifiDevice = wanInterface;
	mLanDevice = lanInterface;

	setupIcons();

	mWifiIcon.setPosition(30, 34, 1);
	mWifiIcon.setMaxSize(64, 64);
	mLanIcon.setPosition(128, 32, 1);
	mLanIcon.setMaxSize(64, 64);
	addChild(&mWifiIcon);
	addChild(&mLanIcon);
}



void NetworkInfoComponent::setupIcons() {
	if (mEnable) {
		mWifiIcon.setImage("/home/pi/ESbuild/wificon.png");
		mLanIcon.setImage("/home/pi/ESbuild/lancon.png");
	}
}

void NetworkInfoComponent::hideIcons() {
	// lol, dirty.  (This just hides them.  After the user reopens, they will not load.)
	mWifiIcon.setOpacity(0x00);
	mLanIcon.setOpacity(0x00);
}

void NetworkInfoComponent::updateIcons() {
	// Update Wifi Icon 
	if (mWifiState) {
		mWifiIcon.setOpacity(0xFF);
		mWifiIcon.setColorShift(0x3344DDAA);
	} else {
		mWifiIcon.setOpacity(0x44);
		mWifiIcon.setColorShift(0x55555544);
	}

	// Update Lan Icon
	if (mLanState) {
		mLanIcon.setOpacity(0xFF);
		mLanIcon.setColorShift(0x33DD44AA);
	} else {
		mLanIcon.setOpacity(0x44);
		mLanIcon.setColorShift(0x55555544);
	}
}



// ~ Overrides ~
void NetworkInfoComponent::update(int deltatime) {
	// If this is disabled, just return.
	if (!mEnable) {
		if (mFrameCount > 0) {
			hideIcons();
			mFrameCount = 0;
		}
		return;
	}

	if (mFrameCount == 1) {
		// make sure icons are loaded:
		if (mWifiIcon.hasImage() == false) setupIcons();

		// update lan and wan
		// See if wifi is a thing with pipes!
		FILE *fp;
		char path[1035];
		std::string cmd = "ifconfig " + mWifiDevice + " | grep \"inet addr:\"";
		fp = popen(cmd.c_str(), "r");

		bool bWifi = false;

		while (fgets(path, sizeof(path), fp) != NULL) {
			std::string cline = path;
			if (cline.length() > 15) bWifi = true;
		}

		// Get eth as well
		cmd = "ifconfig " + mLanDevice + " | grep \"inet addr:\"";
		fp = popen(cmd.c_str(), "r");
		bool bLan = false;

		while (fgets(path, sizeof(path), fp) != NULL) {
			std::string cline = path;
			if (cline.length() > 15) bLan = true;
		}

		mLanState = bLan;
		mWifiState = bWifi;

		updateIcons();
	}

	// Get user settings
	mEnable = Settings::getInstance()->getBool("ShowNetwork");

	mFrameCount++;
	if (mFrameCount > mUpdateFrame) mFrameCount = 0;
}

void NetworkInfoComponent::render(const Eigen::Affine3f& parentTrans) {
	mWifiIcon.render(parentTrans);
	mLanIcon.render(parentTrans);
}