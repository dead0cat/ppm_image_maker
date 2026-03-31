#include <iostream>
//#include <cmath>
#include "include/image_buffer.hpp"

std::vector<Color> color_pallet;

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

void build_pallet(std::string pallet_name) {
	FILE* file;
    file = fopen(pallet_name.c_str(),"rb");
    int size;
    fscanf(file,"%d",&size);

	std::vector<unsigned char> c_byte;
	c_byte.resize(size*3);
	color_pallet.resize(size);
    fread(c_byte.data(),sizeof(unsigned char),size*3,file);
	for(int p = 0;p<size;p++) {
		color_pallet[p] = Color(c_byte[3*p],c_byte[3*p+1],c_byte[3*p+2]);
		//printf("%d %d %d\n",c_byte[3*p],c_byte[3*p+1],c_byte[3*p+2]);
	}
    fclose(file);
}

float dist_3d(int x1,int y1,int z1,int x2,int y2,int z2) {
	return std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

Color reduce_pallet(int x,int y,Color c) {
	int size = color_pallet.size()/3;
	int best_p = 0;
	float best_dis = 502;

	int red,green,blue;
	c.get_rgb(&red,&green,&blue);
	int pred,pgreen,pblue;

	for(int p = 0; p < size;p++) {
		color_pallet[p].get_rgb(&pred,&pgreen,&pblue);
		//printf("%f\n",dist_3d(red,green,blue,pred,pgreen,pblue));
		if(best_dis > dist_3d(red,green,blue,pred,pgreen,pblue)) {
			best_dis = dist_3d(red,green,blue,pred,pgreen,pblue);
			best_p = p;
		}
	}
	//printf("%d\n",best_p);
	return color_pallet[best_p];
}

int main() {
    image_buffer test;
    test.read_p6("spectrum");
	std::string pallet;
	std::cin >> pallet;
	build_pallet(pallet + ".hex");
	test.simple_pass(reduce_pallet);
	pallet = "spc_" + pallet;

	for(long unsigned int p = 0;p<color_pallet.size();p++) {
		test.set_color(color_pallet[p]);
		test.draw_line(p*16,10,p*16,800);
	}

	test.write_p3(pallet);
    return 0;
}