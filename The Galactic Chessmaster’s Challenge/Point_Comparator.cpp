#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Comparator
{
    private:
        bool isascending;
    public:
        Comparator (bool flag)
        {
            isascending = flag;
        }
        bool operator () (long long a, long long b)                
        {                                                        
            if(isascending)
            {
                return a <= b;
            }
            else return a > b;
        }
};

struct Point 
{
    long long x, y;
    int ind;
};

bool compareX (Point p1, Point p2) 
{             
    return p1.x < p2.x;                   // Compare points by X-coordinate
}

bool compareY (Point p1, Point p2) 
{
    return p1.y < p2.y;                      // Compare points by Y-coordinate
}

long long distance (Point p1, Point p2)
{
    return ((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}