#ifndef COLOR1_H
#define COLOR1_H

#define R_Mask 0x01 // B0000 0001
#define G_Mask 0x02 // B0000 0010
#define B_Mask 0x04 // B0000 0100

#define ColorBits 1

class Color1
{
    private:
    public:
        char colorData = 0;
        Color1();
        Color1(char r, char g, char b);
        char GetR();
        char GetG();
        char GetB();
        char GetRGB();
        void SetR(char value);
        void SetG(char value);
        void SetB(char value);
        ~Color1();
};

#endif