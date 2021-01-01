#ifndef POINT_H
#define POINT_H

class Point{
    public:
        Point(){}
        Point(float x, float y, float z);
        void print();
        float x, y, z;
        static Point add(Point a, Point b);
        static Point scale(Point a, float s);
};

#endif // POINT_H
