#include <iostream>
#include <cmath>
#include "include/image_buffer.hpp"


Color test_filter(int x,int y,Color c){
	int red,green,blue;
	c.get_rgb(&red,&green,&blue);
	if(x%3==0) {
		return Color(red,0,0);
	} else if(x%3==1) {
		return Color(0,green,0);
	}
	return Color(0,0,blue);
}

int main() {
    image_buffer test;
    test.read_p6("auggie.ppm");
	test.simple_pass(test_filter);
	test.write_p3("new_auggie");
    return 0;
}