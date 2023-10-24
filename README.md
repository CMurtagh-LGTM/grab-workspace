# grab-workspace
A plugin to grab a workspace and display it on the current monitor.
If the workspace is already displayed on another monitor it will instead swap the workspaces.

## Installation
Check the [wiki](https://wiki.hyprland.org/Plugins/Using-Plugins/).
1. Compile `make`
2. Add to config `plugin = /path/to/grab-workspace/grab-workspace.so`

## Usage
Have binds in the form
```
# Switch workspaces with mainMod + [0-9]
bind = $mainMod, 1, grab-workspace, 1
bind = $mainMod, 2, grab-workspace, 2
bind = $mainMod, 3, grab-workspace, 3
bind = $mainMod, 4, grab-workspace, 4
bind = $mainMod, 5, grab-workspace, 5
bind = $mainMod, 6, grab-workspace, 6
bind = $mainMod, 7, grab-workspace, 7
bind = $mainMod, 8, grab-workspace, 8
bind = $mainMod, 9, grab-workspace, 9
bind = $mainMod, 0, grab-workspace, 10
```
