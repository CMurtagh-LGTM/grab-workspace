#define WLR_USE_UNSTABLE

#include <hyprland/src/helpers/Workspace.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/config/ConfigManager.hpp>

#include "globals.hpp"

#include <hyprland/src/Compositor.hpp>

void grab_workspace(std::string args){
    
    const auto workspace_to_change_to = g_pCompositor->getWorkspaceByString(args);

    if (workspace_to_change_to == nullptr) {
        // Make a new workspace
        HyprlandAPI::invokeHyprctlCommand("dispatch", "workspace " + args);
        return;
    }

    if (g_pConfigManager->getWorkspaceRuleFor(workspace_to_change_to).monitor != ""){
        // We don't want to mess with workspaces with rules
        HyprlandAPI::invokeHyprctlCommand("dispatch", "workspace " + args);
        return;
    }

    const auto old_monitor = g_pCompositor->getMonitorFromID(workspace_to_change_to->m_iMonitorID);
    const auto new_monitor = g_pCompositor->m_pLastMonitor;

    if(
        old_monitor->activeWorkspace == workspace_to_change_to->m_iID && // Moving from a workspace that is active on a screen
        g_pConfigManager->getWorkspaceRuleFor(g_pCompositor->getWorkspaceByID(new_monitor->activeWorkspace)).monitor == "" // We don't want to swap with a workspace that has a monitor rule
    ){
        // Swap the workspaces
        HyprlandAPI::invokeHyprctlCommand("dispatch", "swapactiveworkspaces " + old_monitor->szName + " " + new_monitor->szName);
    } else {
        // Grab the workspace
        HyprlandAPI::invokeHyprctlCommand("dispatch", "moveworkspacetomonitor " + workspace_to_change_to->m_szName + " current");
        HyprlandAPI::invokeHyprctlCommand("dispatch", "workspace " + workspace_to_change_to->m_szName);
    }

}

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    HyprlandAPI::addDispatcher(PHANDLE, "grab-workspace", grab_workspace);

    return {"grab-workspace", "Grabs a workspace", "CMurtagh-LGTM", "0.1"};
}

