#ifndef COLOR_CUSTOM_LIBRARY_H
#define COLOR_CUSTOM_LIBRARY_H

#include "vector_custom_library.h"
#include <iostream>

using color =vector3;
void do_color(std::ostream& out, const color& pixel)
{
    auto red=pixel.give_x();
    auto blue=pixel.give_y();
    auto green=pixel.give_z();

    int final_red=int(255.999*red);
    int final_blue=int(255.999*blue);
    int final_green=int(255.999*green);

    out<<final_red <<' '<<final_blue<<' '<<final_green<<'\n';
}
#endif
