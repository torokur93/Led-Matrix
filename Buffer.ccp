class Buffer
{
private:
    byte data[][];
    byte Rows;
    byte Cols;


public:

    Buffer(byte rows, byte cols)
    {
        Rows = rows;
        Cols = cols;
        data[rows][cols];
        ClearData();
    }

    void ClearData(){
        SetData(0);
    }

    void SetData(byte value){
        
        for (byte row = 0; row < Rows; row++)
        {
            for (byte col = 0; col < Cols; col++)
            {
                data[row][col] = value;
            }
        }
    }

    void SetData(byte x, byte y, byte value){
        if(x<=Rows && y<=Cols){
            data[x][y]=value;
        }

    }

    byte GetData(byte x, byte y){
        if(x<=Rows && y<=Cols){
            return data[x][y];
        }

        return 0;

    }

    ~Buffer();




};

Buffer::Buffer(/* args */)
{
}

Buffer::~Buffer()
{
}
