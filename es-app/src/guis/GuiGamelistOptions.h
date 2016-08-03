#include "GuiComponent.h"
#include "components/MenuComponent.h"
#include "components/OptionListComponent.h"
#include "components/SwitchComponent.h"
#include "FileSorts.h"

class IGameListView;

class GuiGamelistOptions : public GuiComponent
{
public:
	GuiGamelistOptions(Window* window, SystemData* system);
	virtual ~GuiGamelistOptions();

	//void update(int deltatime) override;
	virtual bool input(InputConfig* config, Input input) override;
	virtual std::vector<HelpPrompt> getHelpPrompts() override;

private:
	void openMetaDataEd();
	void jumpToLetter();
	
	MenuComponent mMenu;

	typedef OptionListComponent<char> LetterList;
	std::shared_ptr<LetterList> mJumpToLetterList;

	typedef OptionListComponent<const FileData::SortType*> SortList;
	std::shared_ptr<SortList> mListSort;

	typedef OptionListComponent<std::string> ViewList;
	std::shared_ptr<ViewList> mViewList;

	std::shared_ptr<SwitchComponent> systemEnable_switch;
	
	SystemData* mSystem;
	IGameListView* getGamelist();
};
