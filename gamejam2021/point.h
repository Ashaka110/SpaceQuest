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
		static Point getCenter(Point a, Point b);
        static float sqrDistance(Point a, Point b);

        static void Scale(Point p[], int arraySize, float s);
		static void Translate(Point p[], int arraySize, Point translate);
		static void RotateZ(Point p[], int arraySize, float angle);
		static Point RotateAroundZ(Point p, Point center, float angle);

};

#endif // POINT_H
