#include <iostream>
#include <cmath>
#include "include/image_buffer.hpp"


int main() {
    image_buffer test(800,800);
    test.set_color(0,0,0);
	for(int n = 0; n <= 400;n+=3){
		test.draw_circle(400,400,n);
	}
	test.write_p6("circ");
	test.read_p6("circ.ppm");
    return 0;
}