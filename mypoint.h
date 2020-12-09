#ifndef MYPOINT_H
#define MYPOINT_H

struct Point{

public:
    Point(): row(0),col(0){}
    Point(int x,int y):row(x),col(y){}
    int row;
    int col;
    bool operator==(const Point& rhs){
        if(this->row == rhs.row && this->col == rhs.col)
            return true;
        return false;
    }
};

#endif // MYPOINT_H
