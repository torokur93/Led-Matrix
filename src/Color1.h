#ifndef COLOR1_H
#define COLOR1_H

#define R_Mask 0x04 // B0000 0100
#define G_Mask 0x02 // B0000 0010
#define B_Mask 0x01 // B0000 0001

#define ColorBits 1

class Color1
{
    private:
    public:
        char colorData = 0;
        Color3();
        Color3(char r, char g, char b);
        char GetR();
        char GetG();
        char GetB();
        void SetR(char value);
        void SetG(char value);
        void SetB(char value);
        ~Color3();
};

#endif