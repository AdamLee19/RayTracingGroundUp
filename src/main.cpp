#include <iostream>

#include "World.h"

int main(int argc, char *argv[])
{
    World w;
    w.build();

    w.camera_ptr->render_scene(w);
    w.write_image("test.jpg");
    return 0;
}
