#pragma once

#include "components/ImageComponent.h"
#include "Util.h"
#include <string>



class NetworkInfoComponent : public GuiComponent
{
public:
    NetworkInfoComponent(Window* window, std::string wanInterface = "wlan0", std::string lanInterface = "eth0");

    void update(int deltatime);
    void render(const Eigen::Affine3f& parentTrans) override;

    void setWanInterface(std::string wanInterface)
    {
        mWifiDevice = wanInterface;
    }
    void setLanInterface(std::string lanInterface)
    {
        mLanDevice = lanInterface;
    }
    std::string getWanInterface()
    {
        return mWifiDevice;
    }
    std::string getLanInterface()
    {
        return mLanDevice;
    }

    bool getWanState()
    {
        return mWifiState;
    }
    bool getLanState()
    {
        return mLanState;
    }

    void setUpdateFrame(int updateframe)
    {
        mFrameCount = 0;
        mUpdateFrame = updateframe;
    }


private:
    // Updates the icon images
    void updateIcons();
    void setupIcons();
    void hideIcons();

    bool mEnable = true;		// Controled from UI SETTINGS (Show Network)

    // Keep a frame count to update on specific key frames
    int mFrameCount = 0;
    int mUpdateFrame = 300;		// Which frame to update on.

    // wifi info:
    bool mWifiState = false;
    ImageComponent mWifiIcon;
    std::string mWifiDevice;


    // Lan Info:
    bool mLanState = false;
    ImageComponent mLanIcon;
    std::string mLanDevice;

};
