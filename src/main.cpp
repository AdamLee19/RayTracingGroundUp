#include <iostream>

#include "World.h"

int main(int argc, char *argv[])
{
    World w;
    w.build();
    w.render_scene(); 

    return 0;
}
