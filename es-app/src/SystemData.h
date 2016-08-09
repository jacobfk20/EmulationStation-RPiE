#pragma once

#include <vector>
#include <string>
#include "FileData.h"
#include "Window.h"
#include "MetaData.h"
#include "PlatformId.h"
#include "ThemeData.h"

class SystemData
{
public:
	SystemData(const std::string& name, const std::string& fullName, const std::string& startPath, const std::vector<std::string>& extensions, 
		const std::string& command, const std::vector<PlatformIds::PlatformId>& platformIds, const std::string& themeFolder, std::string& rawTheme,
		bool systemEnabled = true, std::string viewMode = "GRID VIEW", int modSize = 1);
	~SystemData();

	inline FileData* getRootFolder() const { return mRootFolder; };
	inline const std::string& getName() const { return mName; }
	inline const std::string& getFullName() const { return mFullName; }
	void setFullName(std::string nName);
	inline const std::string& getStartPath() const { return mStartPath; }
	inline const std::vector<std::string>& getExtensions() const { return mSearchExtensions; }
	inline const std::string& getThemeFolder() const { return mThemeFolder; }
	inline const bool getSystemEnabled() const { return mSystemEnabled; }
	bool setSystemEnabled(bool bEnabled);
	inline const std::string& getRawTheme() const { return mRawTheme; }
	inline const int getGridModSize() const { return mGridModSize; }
	void setGridModSize(int s);

	// View mode get/set
	std::string getSystemViewMode() const { return mViewMode; };
	void setSystemViewMode(std::string newViewMode);

	inline const std::vector<PlatformIds::PlatformId>& getPlatformIds() const { return mPlatformIds; }
	inline bool hasPlatformId(PlatformIds::PlatformId id) { return std::find(mPlatformIds.begin(), mPlatformIds.end(), id) != mPlatformIds.end(); }

	inline const std::shared_ptr<ThemeData>& getTheme() const { return mTheme; }

	std::string getGamelistPath(bool forWrite) const;
	bool hasGamelist() const;
	std::string getThemePath() const;
	
	unsigned int getGameCount() const;

	void launchGame(Window* window, FileData* game);

	static void deleteSystems();
	static int saveConfig();  // Save system to writeable config file.  returns 0 on success, 1 = reload gamelist; 2=reload systemview; -x=errors
	static bool loadConfig(); // Load the system config file at getConfigPath(). Returns true if no errors were encountered. An example will be written if the file doesn't exist.
	static void writeExampleConfig(const std::string& path);
	static std::string getConfigPath(bool forWrite); // if forWrite, will only return ~/.emulationstation/es_systems.cfg, never /etc/emulationstation/es_systems.cfg

	static std::vector<SystemData*> sSystemVector;

	inline std::vector<SystemData*>::const_iterator getIterator() const { return std::find(sSystemVector.begin(), sSystemVector.end(), this); };
	inline std::vector<SystemData*>::const_reverse_iterator getRevIterator() const { return std::find(sSystemVector.rbegin(), sSystemVector.rend(), this); };
	
	inline SystemData* getNext() const
	{
		auto it = getIterator();
		it++;
		if(it == sSystemVector.end()) it = sSystemVector.begin();
		return *it;
	}

	inline SystemData* getPrev() const
	{
		auto it = getRevIterator();
		it++;
		if(it == sSystemVector.rend()) it = sSystemVector.rbegin();
		return *it;
	}

	// Load or re-load theme.
	void loadTheme();

private:
	std::string mName;
	std::string mFullName;
	std::string mStartPath;
	std::vector<std::string> mSearchExtensions;
	std::string mLaunchCommand;
	std::vector<PlatformIds::PlatformId> mPlatformIds;
	std::string mRawTheme;		// Add this so we can re-save it later.
	std::string mThemeFolder;
	std::shared_ptr<ThemeData> mTheme;
	bool mSystemEnabled;
	std::string mViewMode;		// What view mode this system will render in. 
	int mGridModSize;

	void populateFolder(FileData* folder);

	FileData* mRootFolder;
};
