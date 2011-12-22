#include "ContextMenuContribution.h"

#include <memory>
#include <sdk.h>
#include <manager.h>
#include <projectmanager.h>
#include <wx/wx.h>

#include "../model/GitStatusCommand.h"
#include "../controller/actions/MenuAction.h"
#include "../Utils.h"
#include "../controller/actions/MenuActionFactory.h"
#include "../controller/actions/MenuActionSet.h"


ContextMenuContribution::ContextMenuContribution()
{
    //ctor
}

void ContextMenuContribution::expandMenu(const ModuleType type, wxMenu* menu,
        const FileTreeData* data)
{
    if (data == NULL)
    {
        cout << "data is null" << endl;
    }

    wxMenu *gitMenu = new wxMenu();

    switch ( type )
    {

    case mtProjectManager:
    {

        expandProjectManagerMenu(type, gitMenu, data);
        break;

    }
    default:
        break;
    }

    if (gitMenu->GetMenuItemCount() > 0)
    {
        menu->AppendSubMenu(gitMenu, _("Git"));
    }
    else
    {
        delete gitMenu;
    }

}

void ContextMenuContribution::expandProjectManagerMenu(
    const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    switch ( data->GetKind() )
    {
    case FileTreeData::ftdkProject:
    {

        cbProject* project = getSelectedProject(data);
        if (project != NULL)
        {
            auto_ptr<MenuActionSet> actions =
                MenuActionFactory::getInstance().getActions((*project));
            addActionsToMenu(menu, *actions);
        }
        break;
    }

    case FileTreeData::ftdkFile:
    {
        ProjectFile* selectedFile = getSelectedProjectFile(data);
        if (selectedFile != NULL)
        {
            auto_ptr<MenuActionSet> actions =
                MenuActionFactory::getInstance().getActions((*selectedFile));
            addActionsToMenu(menu, *actions);
        }

        break;
    }

    default:
        // Do nothing.
        break;
    }
}

void ContextMenuContribution::addActionsToMenu(
    wxMenu* menu, const MenuActionSet& actions)
{

    for (int i = 0; i < actions.size(); i++)
    {
        const MenuAction& currAction = actions[i];
        wxMenuItem* menuItem = menu->Append(currAction.getWxEventID(),
                                            toWxStr(currAction.getText()));
        menuItem->Enable(currAction.isEnabled());
        menu->Connect(currAction.getWxEventID(),
                      wxEVT_COMMAND_MENU_SELECTED,
                      wxCommandEventHandler(MenuActionHandler::onActionFired),
                      NULL,
                      &currAction.getHandler());
    }
}


ContextMenuContribution::~ContextMenuContribution()
{
    //dtor
}
