#ifndef IMAGE_BUFFER
#define IMAGE_BUFFER

#include "color.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class image_buffer {

protected : int w;
protected : int h;
protected : Color c_color = Color(0,0,0);
protected : std::vector<Color> buffer;

//constructors
public : image_buffer(int width,int height) {
    w = width;
    h = height;
    buffer.resize(w*h);
    for(long int p = 0; p < w*h; p++) {
        buffer[p] = Color(255,255,255,255);
    }
}
public : image_buffer(int width,int height,int red,int green,int blue) {
    w = width;
    h = height;
    buffer.resize(w*h);
    for(long int p = 0; p < w*h; p++) {
        buffer[p] = Color(red,green,blue,255);
    }
}
public : image_buffer(int width,int height,int red,int green,int blue,int alpha) {
    w = width;
    h = height;
    buffer.resize(w*h);
    for(long int p = 0; p < w*h; p++) {
        buffer[p] = Color(red,green,blue,alpha);
    }
}
public : image_buffer(int width,int height,bool alpha) {
    w = width;
    h = height;
    buffer.resize(w*h);
    if(alpha) {
        for(long int p = 0; p < w*h; p++) {
            buffer[p] = Color(0,0,0,0);
        }
    } else {
        for(long int p = 0; p < w*h; p++) {
            buffer[p] = Color(255,255,255,255);
        }
    }
}

//set_color functions
public : void set_color(Color color){
    this->c_color = color;
}
public : void set_color(int red,int green,int blue){
    this->c_color.set(red,green,blue);
}
public : void set_color(int red,int green,int blue,int alpha){
    this->c_color.set(red,green,blue,alpha);
}

//place pixel functions
public : bool pixel(int x, int y) {
        //checks that is trying to place a pixel inside the boundrys of the image
    if((x < 0) | (x >= w) | (y < 0) | (y >= h))
        return false;

    buffer[x + y*w] = c_color;

    return true;
}

public : bool pixel(int x, int y,Color c) {
    //checks that is trying to place a pixel inside the boundrys of the image
    if((x < 0) | (x >= w) | (y < 0) | (y >= h))
        return false;

    buffer[x + y*w] = c;

    return true;
}

public : bool pixel(int x, int y,int red,int green,int blue) {
    //checks that is trying to place a pixel inside the boundrys of the image
    if((x < 0) | (x >= w) | (y < 0) | (y >= h))
        return false;

    buffer[x + y*w] = Color(red,green,blue,255);

    return true;
}

public : bool pixel(int x, int y,int red,int green,int blue,int alpha) {
    //checks that is trying to place a pixel inside the boundrys of the image
    if((x < 0) | (x >= w) | (y < 0) | (y >= h))
        return false;

    buffer[x + y*w] = Color(red,green,blue,alpha);

    return true;
}

//saving to file the image functions
public : bool write_p3(std::string name) {
    FILE * output;
    std::string full_name = name + ".ppm";
    output = fopen(full_name.c_str(),"w");;
    if(output == NULL)
        return false;

    fprintf(output,"P3 %d %d 255\n",w,h);
    Color c = buffer[0];
    int red, green, blue;
    c.get_rgb(&red,&green,&blue);
    for(long int p = 0; p < h*w; p++) {
        if(c != buffer[p]){
            c = buffer[p];
            c.get_rgb(&red,&green,&blue);
        }
        fprintf(output,"%d %d %d\n",red,green,blue);
    }
    fprintf(output,"#snoping around as usual i see");
    return true;
}

public : bool write_p6(std::string name) {
    FILE * output;
    std::string full_name = name + ".ppm";
    output = fopen(full_name.c_str(),"wb");
    if(output == NULL)
        return false;

    fprintf(output,"P6 %d %d 255\n",w,h);
    if(!output)
        return false;

    Color c = buffer[0];
    unsigned char color[3];
    c.get_rgb_byte(&color[0],&color[1],&color[2]);
    for(long int p = 0; p < h*w; p++) {
        if(c != buffer[p]){
            c = buffer[p];
            c.get_rgb_byte(&color[0],&color[1],&color[2]);
        }
        fwrite(color,sizeof(unsigned char),3,output);
    }
    fclose(output);
    //fprintf(output,"#snoping around as usual i see");*/
    return true;
}

public : bool write_pam_rgba(std::string name) {
    FILE * output;
    std::string full_name = name + ".pam";
    output = fopen(full_name.c_str(),"wb");
    if(output == NULL)
        return false;

    fprintf(output,"P7\nWIDTH %d\nHEIGHT %d\nMAXVAL 255\nDEPTH 4\nTUPLTYPE RGB_ALPHA\nENDHDR\n",w,h);
    if(!output)
        return false;

    Color c = buffer[0];
    unsigned char color[4];
    c.get_rgba_byte(&color[0],&color[1],&color[2],&color[3]);
    for(long int p = 0; p < h*w; p++) {
        if(c != buffer[p]){
            c = buffer[p];
            c.get_rgba_byte(&color[0],&color[1],&color[2],&color[3]);
        }
        fwrite(color,sizeof(unsigned char),4,output);
    }
    fclose(output);
    //fprintf(output,"#snoping around as usual i see");*/
    return true;
}

//reading files
public : bool read_p6(std::string name) {
    FILE * input;
    input = fopen(name.c_str(),"rb");
    if(!input)
        return false;
    int type,width,height,depth;
    fscanf(input,"%*c %d %d %d %d",&type,&width,&height,&depth);
    printf("%d %d %d %d\n",type,width,height,depth);
    return true;
}

//draw functions and aux draw functions
private : int min(int x1,int x2){
	if(x1 > x2)
		return x2;
	else
		return x1;
}
private : int max(int x1,int x2){
	if(x1 > x2)
		return x1;
	else
		return x2;
}

public : void draw_line(int x1, int y1, int x2, int y2) {
    
    //definindo as primeira variaveis (as que são usada para casos triviais
    int dx = x2 - x1;
    int dy = y2 - y1;
    bool flip_x = false;
    bool flip_y = false;
    bool flip_xy = false;


    //verificações com relação ao eixo x
    if (dx == 0)
        //do menor valor y vai iterando até o maior valor y
        for (int y = min(y1, y2); y <= max(y1, y2); y++) {
            this->pixel(x1, y);
        }
    else if (dx < 0)
        //se o dx < 0 a reta deve ser espelhada isso coloca um triger para realizar isso
        flip_x = true;

    //verificações com relação ao eixo y
    if (dy == 0)
        //do menor valor x vai iterando até o maior valor x
        for (int x = min(x1, x2); x <= max(x1, x2); x++) {
            this->pixel(x, y1);
        }
    else if (dy < 0)
        //se dy < 0 a reta deve ser espelhada com relação ao eixo y isso informa o codigo
        flip_y = true;

    //tira o sinal dos delta agora que isso deixa de ser util
    dx = abs(dx);
    dy = abs(dy);

    //verificação de angulo
    if (dx == dy) {
        //situação da reta trivial diagonal (multiplo de 45 graus)
        for (int x = 0; x <= dx; x++) {
            //itera do menor x até o maior x, e soma ao ponto (x1,y1) com espelhamentos dados pelos flips x e y
            this->pixel((1 - 2 * flip_x) * x + x1, (1 - 2 * flip_y) * x + y1);
        }
    }
    else if (dy > dx) {
        //verifica se o angulo é maior que 45, se sim ativa um triger para o loop
        flip_xy = true;
    }

    //define os valores para a execução do algoritomo do ponto medio
    unsigned int y = 0;
    unsigned int inc_e, inc_ne, inc_u, inc_ue;
    unsigned int range;
    inc_e = 2 * dy;
    inc_ne = 2 * (dy - dx);
    inc_u = 2 * dx;
    inc_ue = 2 * (dx - dy);
    int d = 0;

    //define o intervalo que é iterado sob quando gerando a reta levando em conta o eixo que esta sendo usado
    if (flip_xy)
        range = dy;
    else
        range = dx;

    /*
    * codigo que realiza o algoritimo do ponto medio
    * usa uma implementação muito estranha para escanear sob o eixo x e y
    * se o triger flip_xy esta ativo o codigo usa as constante para o escaneamente sob o eixo y e inverte o x e y dinamicos
    * as cordenadas constantes para o ponto que esta sendo escrito ainda são mantidas
    */
    for (unsigned int x = 0; x <= range; x++) {

        if (flip_xy)
            this->pixel((1 - 2 * flip_x) * y + x1, (1 - 2 * flip_y) * x + y1);
        else 
            this->pixel((1 - 2 * flip_x) * x + x1, (1 - 2 * flip_y) * y + y1);


        if (d <= 0) {
            if (flip_xy)
                d += inc_u;
            else
                d += inc_e;
        }
        else {
            if (flip_xy)
                d += inc_ue;
            else
                d += inc_ne;
            y++;
        }
    }
    //um ponto a mais, provavelmente desnecesario para a situação que eu errei a ordem que acontece as coisa no for
    //que se o for acaba antes ou quando o x e y estao no x2 e y2, isso garante que nao vai ficar faltando o ponto
    this->pixel(x2, y2);
}
private : void CirclePoint(int ix0, int iy0, int ix, int iy) {
    this->pixel( ix0 + ix, iy0 + iy);
    this->pixel( ix0 + ix, iy0 - iy);
    this->pixel( ix0 - ix, iy0 + iy);
    this->pixel( ix0 - ix, iy0 - iy);
    this->pixel( ix0 + iy, iy0 + ix);
    this->pixel( ix0 + iy, iy0 - ix);
    this->pixel( ix0 - iy, iy0 + ix);
    this->pixel( ix0 - iy, iy0 - ix);
}
public : void draw_circle(int x0, int y0, int r) {
    //define as variaveis incias
    int x = 0;
    int y = r;
    int z = 1 - r;
    int dE = 3;
    int dSE = -2 * r + 5;

    //desenha o ponto incial
    CirclePoint(x0, y0, x, y);

    //loop que vai desenhado os pixeis
    while (y > x) {
        if (z < 0) {
            z += dE;
            dE += 2;
            dSE += 2;
        }
        else {
            z += dSE;
            dE += 2;
            dSE += 4;
            y--;
        }

        x++;
        CirclePoint(x0, y0, x, y);
    }
}

};
#endif
