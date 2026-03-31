#ifndef COLOR
#define COLOR
class Color {
protected : unsigned long int c;
public : Color() {
    c = 0;
}
public : Color(unsigned long int c) {
    this->c = c;
}

//constructors with int (0-255)
public : Color(int red,int green,int blue) {
    c = (red<<16) | (green<<8) | blue;
}
public : Color(int red,int green,int blue,int alpha) {
    c = (alpha << 24) | (red<<16) | (green<<8) | blue;
}
//constructors with float (0-1)
public : Color(float red,float green,float blue) {
    unsigned short ired = red*255;
    unsigned short igreen = green*255;
    unsigned short iblue = blue*255;
    c = (ired<<16) | (igreen<<8) | iblue;
}
public : Color(float red,float green,float blue,float alpha) {
    unsigned short ired = red*255;
    unsigned short igreen = green*255;
    unsigned short iblue = blue*255;
    unsigned short ialpha = alpha*255;
    c = (ialpha << 24) | (ired<<16) | (igreen<<8) | iblue;
}
//getters
public: void get_rgb(int *red,int *green,int *blue){
    *red = (c >> 16);
    *green = (c >> 8) & 255;
    *blue = c & 255;
}
public: void get_rgb(float *red,float *green,float *blue){
    *red = ((c >> 16) & 255)/255.0f;
    *green = ((c >> 8) & 255)/255.0f;
    *blue = (c & 255)/255.0f;
}
public: void get_rgba(int *red,int *green,int *blue,int *alpha){
    *alpha = (c >>24) & 255;
    *red = (c >> 16) & 255;
    *green = (c >> 8) & 255;
    *blue = c & 255;
}
public: void get_rgba(float *red,float *green,float *blue,float *alpha){
    *alpha = ((c >>24) & 255)/255.0f;
    *red = ((c >> 16) & 255)/255.0f;
    *green = ((c >> 8) & 255)/255.0f;
    *blue = (c & 255)/255.0f;
}

public : void get_rgb_byte(unsigned char *red,unsigned char *green,unsigned char *blue) {
    *red = (unsigned char) ((c>>16) & 0xff);
    *green = (unsigned char) ((c>>8) & 0xff);
    *blue = (unsigned char) (c & 0xff);
}
public : void get_rgba_byte(unsigned char *red,unsigned char *green,unsigned char *blue,unsigned char *alpha) {
    *alpha = (unsigned char) ((c>>24) & 0xff);
    *red = (unsigned char) ((c>>16) & 0xff);
    *green = (unsigned char) ((c>>8) & 0xff);
    *blue = (unsigned char) (c & 0xff);
}
//setters
public : void set(int red,int green,int blue) {
    c = (red<<16) | (green<<8) | blue;
}
public : void set(int red,int green,int blue,int alpha) {
    c = (alpha << 24) | (red<<16) | (green<<8) | blue;
}
public : void set(float red,float green,float blue) {
    unsigned short ired = red*255;
    unsigned short igreen = green*255;
    unsigned short iblue = blue*255;
    c = (ired<<16) | (igreen<<8) | iblue;
}
public : void set(float red,float green,float blue,float alpha) {
    unsigned short ired = red*255;
    unsigned short igreen = green*255;
    unsigned short iblue = blue*255;
    unsigned short ialpha = alpha*255;
    c = (ialpha << 24) | (ired<<16) | (igreen<<8) | iblue;
}

public : long int get_c() {
    return c;
}

public : bool operator==(Color c) {
    if (this->c == c.c)
        return true;
    else
        return false;
}

public : bool operator!=(Color c) {
    if (this->c != c.c)
        return true;
    else
        return false;
}

public : Color operator+(Color c) {
    unsigned long int out;
    out = this->c;
    out += c.c;
    return Color(out);
}

public : Color operator-(Color c) {
    unsigned long int out;
    out = this->c;
    out -= c.c;
    return Color(out);
}
};

#endif