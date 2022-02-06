#include "Color3.h"

Color3::Color3(char r, char g, char b)
{
    colorData = (r & R_Mask) | ((g << ColorBits) & G_Mask) | ((b << (ColorBits * 2)) & B_Mask);
}

Color3::Color3()
{

}

Color3::~Color3()
{
}


char Color3::GetR(){
    return colorData & R_Mask;
}

char Color3::GetG(){

    return (colorData & G_Mask) >> ColorBits;
}

char Color3::GetB(){

    return (colorData & B_Mask) >> (ColorBits * 2);
}

void Color3::SetR(char value){
    colorData &= ~R_Mask;
    colorData |= (value & R_Mask);
}

void Color3::SetG(char value){
    colorData &= ~G_Mask;
    colorData |= ((value << ColorBits) & G_Mask);
}

void Color3::SetB(char value){
    colorData &= ~B_Mask;
    colorData |= ((value << (ColorBits * 2)) & B_Mask);
}
