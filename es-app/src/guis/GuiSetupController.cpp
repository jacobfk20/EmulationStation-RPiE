#include "EmulationStation.h"
#include "guis/GuiSetupController.h"
#include "guis/GuiDetectDevice.h"
#include "Window.h"
#include "Sound.h"
#include "Log.h"
#include "Settings.h"
#include "guis/GuiMsgBox.h"

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include "stdlib.h"
#include <vector>

#include "pugixml/pugixml.hpp"
#include "platform.h"
#include <boost/filesystem.hpp>
#include <boost/assign.hpp>

#include "components/ImageComponent.h"
#include "components/ComponentGrid.h"
#include "components/ButtonComponent.h"
#include "components/TextComponent.h"
#include "components/MenuComponent.h"


GuiSetupController::GuiSetupController(Window* window, const std::function<void()>& doneCallback) : GuiComponent(window), mVersion(window),
    mGrid(window, Eigen::Vector2i(getControllerCount(), 3)), mMenu(window, "CONTROLLER")
{
    // SETUP CONTROLLER

    // *Grid size is determined by controllers in es_controllers.cfg

    // [     IMG    ] [     IMG    ] [     IMG    ]
    // [ Controller ] [ Controller ] [ Controller ]
    // [ Instructio ] [ Instructio ] [ Instructio ]

    // [version]

    mDoneCallback = doneCallback;

    mGrid.setPosition(0, Renderer::getScreenHeight() * .2f);
    mGrid.setSize(Renderer::getScreenWidth(), Renderer::getScreenHeight() * .6f);

    // Get controllers from config file
    buildControllerGrid();


    mVersion.setFont(Font::get(FONT_SIZE_MEDIUM));
    mVersion.setColor(0xC6C6C6FF);
    mVersion.setText("NO CONTROLLER DETECTED!");
    mVersion.setAlignment(ALIGN_CENTER);
    mVersion.setPosition(100, 100);
    mVersion.setSize(500, 200);

    addChild(&mVersion);
    addChild(&mGrid);


    setSize(Renderer::getScreenWidth(), Renderer::getScreenHeight());
    setPosition((Renderer::getScreenWidth() - mSize.x()) / 2, Renderer::getScreenHeight() * 0.15f);
}

void GuiSetupController::onSizeChanged()
{
    mVersion.setSize(mSize.x(), 0);
    mVersion.setPosition(0, mSize.y() - mVersion.getSize().y());
}


bool GuiSetupController::input(InputConfig* config, Input input)
{
    if(GuiComponent::input(config, input)) {
        return true;
    }

    if((config->isMappedTo("b", input) || config->isMappedTo("start", input)) && input.value != 0) {
        delete this;
        return true;
    }

    return false;
}

void GuiSetupController::update(int deltatime)
{
    // Run trigger scripts for controllers
    if (mFileLoaded) {

        for (int i = 0; i < vDocData.size(); i++) {
            std::string script = vDocData[i][4];

            // Open pipe and run a command
            FILE *fp;
            char path[1035];
            fp = popen(script.c_str(), "r");
        }

    }

    if (InputManager::getInstance()->getNumJoysticks() > 0) {
        mWindow->pushGui(new GuiDetectDevice(mWindow, true, mDoneCallback));
        //if (mDoneCallback) mDoneCallback();
        delete this;
    }
}

std::vector<HelpPrompt> GuiSetupController::getHelpPrompts()
{
    std::vector<HelpPrompt> prompts;
    prompts.push_back(HelpPrompt("b", "close"));
    return prompts;
}



// ~ PRIVATES ~

bool GuiSetupController::loadFile()
{
    // pretty much a copy/paste of Settings.cpp
    const std::string path = getHomePath() + "/.emulationstation/es_controllers.cfg";

    if (!boost::filesystem::exists(path)) {
        createSampleFile();
    }

    // Open controllers.cfg file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result) {
        LOG(LogError) << "Could not parse Controllers file!\n   " << result.description();
        return false;
    }

    // dump needed data into vector
    int x = 0;
    if (!doc.child("ControllerSetup")) {
        return false;
    }
    for (pugi::xml_node node = doc.child("ControllerSetup").first_child(); node; node = node.next_sibling()) {
        std::vector<std::string> vec;
        vec.push_back(node.child_value("name"));
        vec.push_back(node.child_value("title"));
        vec.push_back(node.child_value("img"));
        vec.push_back(node.child_value("instructions"));
        vec.push_back(node.child_value("trigger"));

        vDocData.push_back(vec);

        x++;
    }

    mControllerCount = x;

    mFileLoaded = true;
    return true;
}

// This needs to load itself and not use private members so it can be called safely anywhere.
int GuiSetupController::getControllerCount()
{
    // Load controllers file
    const std::string path = getHomePath() + "/.emulationstation/es_controllers.cfg";

    if (!boost::filesystem::exists(path)) {
        createSampleFile();
    }

    // Open controllers.cfg file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result) {
        LOG(LogError) << "Could not parse Controllers file!\n   " << result.description();
        return false;
    }

    // Figure out how many controllers are in Setup.
    int x = 0;
    for (pugi::xml_node node = doc.child("ControllerSetup").first_child(); node; node = node.next_sibling()) {
        x++;
    }

    mControllerCount = x;

    return mControllerCount;
}

void GuiSetupController::buildControllerGrid()
{
    // See if cfg file is loaded, if not, load it!
    if (!mFileLoaded) {
        loadFile();
    }

    for (int i = 0; i < mControllerCount; i++) {
        // Get Vector data from loaded cfg
        std::string conName = vDocData[i][1];
        std::string conImgPath = vDocData[i][2];
        std::string conIns = vDocData[i][3];


        // === Create controller objects and add to grid ===
        auto con_img = std::make_shared<ImageComponent>(mWindow);
        con_img->setImage(conImgPath);
        mGrid.setEntry(con_img, Eigen::Vector2i(i, 0), true, false);

        auto con_head = std::make_shared<TextComponent>(mWindow, conName, Font::get(FONT_SIZE_MEDIUM), 0xFFFFFFFF);
        con_head->setAlignment(ALIGN_CENTER);
        mGrid.setEntry(con_head, Eigen::Vector2i(i, 1), true);

        auto con_text = std::make_shared<TextComponent>(mWindow, conIns, Font::get(FONT_SIZE_SMALL), 0xFFFFFFFF);
        con_text->setAlignment(ALIGN_CENTER);
        mGrid.setEntry(con_text, Eigen::Vector2i(i, 2), true);

    }


}

void GuiSetupController::createSampleFile()
{
    const std::string path = getHomePath() + "/.emulationstation/es_controllers.cfg";
    std::ofstream ofs;
    ofs.open(path, std::ofstream::out);
    ofs << "<?xml version=\"1.0\"?>\n"
        "<ControllerSetup>\n"
        "	<Controller>\n"
        "		<name>ps3 - 4</name>\n"
        "		<title>PS3 & PS4 Controller</title>\n"
        "		<instructions>Connect ps3 or ps4 controller through USB</instructions>\n"
        "		<img>/home/pi/ESbuild/playstation.png</img>\n"
        "		<trigger>/home/pi/ESbuild/./psSense</trigger>\n"
        "	</Controller>\n"
        "	<Controller>\n"
        "		<name>example</name>\n"
        "		<title>ADD ANOTHER CONTROLLER</title>\n"
        "		<instructions>You can add more controllers here by editing the es_controllers.cfg file at ~/.emulationstation/</instructions>\n"
        "		<img></img>\n"
        "		<trigger></trigger>\n"
        "	</Controller>\n"
        "</ControllerSetup>\n";

    ofs.close();
}