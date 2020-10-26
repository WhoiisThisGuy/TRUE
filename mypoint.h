#ifndef MYPOINT_H
#define MYPOINT_H

struct Point{

public:
    Point(): x(0),y(0){}
    Point(int x_,int y_):x(x_),y(y_){}
    int x;
    int y;
    bool operator==(const Point& rhs){
        if(this->x == rhs.x && this->y == rhs.y)
            return true;
        return false;
    }
};

#endif // MYPOINT_H
