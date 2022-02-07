#ifndef COLOR3_H
#define COLOR3_H

#define R_Mask 0x30 // B0011 0000   >>4 48
#define G_Mask 0x0C // B0000 1100   >>2 12
#define B_Mask 0x03 // B0000 0011   >>0 3

#define ColorBits 2

class Color3
{
    private:
    public:
        char colorData = 0;
        Color3();
        Color3(char r, char g, char b);
        char GetR();
        char GetG();
        char GetB();
        char GetR(char pwm);
        char GetG(char pwm);
        char GetB(char pwm);
        void SetR(char value);
        void SetG(char value);
        void SetB(char value);
        ~Color3();
};

#endif