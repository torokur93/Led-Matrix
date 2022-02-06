#ifndef COLOR3_H
#define COLOR3_H

#define R_Mask 0x30
#define G_Mask 0x0C
#define B_Mask 0x03

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
        void SetR(char value);
        void SetG(char value);
        void SetB(char value);
        ~Color3();
};

#endif