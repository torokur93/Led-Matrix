#include "Color1.h"

Color1::Color1(char r, char g, char b)
{
    colorData = ((r << (ColorBits * 2)) & R_Mask) | ((g << ColorBits) & G_Mask) | (b & B_Mask);
}

Color1::Color1()
{

}

Color1::~Color1()
{
}


char Color1::GetR(){
    return (colorData & R_Mask) >> (ColorBits * 2);
}

char Color1::GetG(){

    return (colorData & G_Mask) >> ColorBits;
}

char Color1::GetB(){

    return (colorData & B_Mask);
}

void Color1::SetR(char value){
    colorData &= ~R_Mask;
    colorData |= ((value << (ColorBits * 2)) & R_Mask);
}

void Color1::SetG(char value){
    colorData &= ~G_Mask;
    colorData |= ((value << ColorBits) & G_Mask);
}

void Color1::SetB(char value){
    colorData &= ~B_Mask;
    colorData |= (value & B_Mask);
}
