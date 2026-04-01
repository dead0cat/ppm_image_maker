#include <iostream>
#include <cmath>
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
    file = fopen(pallet_name.c_str(),"r");
    int size;
    fscanf(file,"%d",&size);
	color_pallet.resize(size);
	unsigned long int color;
	for(int p = 0;p<size;p++) {
		fscanf(file,"%lx",&color);
		color_pallet[p].set(color);
		//printf("%lx\n",color);
	}
    fclose(file);
}

double dist_c(int x1,int y1,int z1,int x2,int y2,int z2) {
	int dx,dy,dz;
	dx =(double) (x1-x2)*(x1-x2);
	dy =(double) (y1-y2)*(y1-y2);
	dz =(double) (z1-z2)*(z1-z2);
	return std::sqrt(dx+dy+dz);
}

Color reduce_pallet(int x,int y,Color c) {
	int size = color_pallet.size();
	int best_p = 0;
	float best_dis = 260;

	int red,green,blue;
	c.get_rgb(&red,&green,&blue);
	int pred,pgreen,pblue;

	for(int p = 0; p < size;p++) {
		color_pallet[p].get_rgb(&pred,&pgreen,&pblue);
		if(best_dis > dist_c(red,green,blue,pred,pgreen,pblue)) {
			best_dis = dist_c(red,green,blue,pred,pgreen,pblue);
			best_p = p;
		}
	}
	//printf("%d\n",best_p);
	return color_pallet[best_p];
}

int main() {
    image_buffer test(800,800,255,255,255);
    test.read_p6("auggie");
	std::string pallet;
	std::cin >> pallet;
	build_pallet(pallet + ".hex");
	test.simple_pass(reduce_pallet);
	pallet = "au_" + pallet;

	for(long unsigned int p = 0;p<color_pallet.size();p++) {
		test.set_color(color_pallet[p]);
		for(int off = 0;off < 8;off++)
			test.draw_line(p*10 + off,10,p*10 + off,40);
	}
	test.write_p6(pallet);

    return 0;
}