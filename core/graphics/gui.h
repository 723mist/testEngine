#include "render/object.h"
#include "../input/mouse.h"
#include <vector>

struct object_gui {
    const std::string& text;
    float pos[2];
    float scale[2];
    float color[3];
};

class Gui {
    private:
        std::vector<object_gui> objects;

    public:
        void createWindow(const std::string& name, float pos[2], float scale[2]) {}
};