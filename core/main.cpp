#include <iostream>
#include "engine.h"
//#include "window/window.hpp"

int main() {
    EngineWindow window;

    int width = 500;
    int height = 500;
    int tets = 0;

    //window.add(new Circle(width/2, height/2, 100, 100, 1.0f, 0.0f, 0.0f));
    //window.add(new Rect(width/2-50, height/2-50, 100, 100, 1.0f, 0.5f, 0.0f));

    window.Init("Engine window 500x500", width, height, false);

    return 0;   
}
