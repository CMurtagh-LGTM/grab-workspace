# compile with HYPRLAND_HEADERS=<path_to_hl> make all
# make sure that the path above is to the root hl repo directory, NOT src/
# and that you have ran `make protocols` in the hl dir.


PLUGIN_NAME=grab-workspace

all:
	$(CXX) -shared -fPIC --no-gnu-unique main.cpp -o ${PLUGIN_NAME}.so -g `pkg-config --cflags pixman-1 libdrm hyprland` -std=c++2b
clean:
	rm ./${PLUGIN_NAME}.so
