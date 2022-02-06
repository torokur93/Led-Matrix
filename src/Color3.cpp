#include "Color3.h"

Color3::Color3(char r, char g, char b)
{
    colorData = (r & R_Mask) | (g & G_Mask) | (b & B_Mask);
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

    return colorData & G_Mask;
}

char Color3::GetB(){

    return colorData & B_Mask;
}

void Color3::SetR(char value){
    colorData &= ~R_Mask;
    colorData |= (value & R_Mask);
}

void Color3::SetG(char value){
    colorData &= ~G_Mask;
    colorData |= (value & G_Mask);
}

void Color3::SetB(char value){
    colorData &= ~B_Mask;
    colorData |= (value & B_Mask);
}
