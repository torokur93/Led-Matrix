#include "Color3.h"

Color3::Color3(char r, char g, char b)
{
    colorData = ((r << (ColorBits * 2)) & R_Mask) | ((g << ColorBits) & G_Mask) | (b & B_Mask);
}

Color3::Color3()
{

}

Color3::~Color3()
{
}


char Color3::GetR(){
    return (colorData & R_Mask) >> (ColorBits * 2);
}

char Color3::GetG(){

    return (colorData & G_Mask) >> ColorBits;
}

char Color3::GetB(){

    return (colorData & B_Mask);
}

char Color3::GetR(char pwm){
    return ((colorData & R_Mask) >> (ColorBits * 2)) <= (pwm+1);
}

char Color3::GetG(char pwm){

    return ((colorData & G_Mask) >> ColorBits) <= (pwm+1);
}

char Color3::GetB(char pwm){

    return (colorData & B_Mask) <= (pwm+1);
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
