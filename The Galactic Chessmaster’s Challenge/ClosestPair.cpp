#include "Quantum_ChessBoard.cpp"

class ClosestPair
{
    private:
        int num_points;
        std::vector<Point> points, sortedByX;       // m set of points , sortedByX for sorted order of points in x
    public:
        ClosestPair(int n)
        {
            num_points = n;
            points.resize(num_points);
            sortedByX.resize(num_points);
        }
        void readPoints() 
        {
            for (int i = 0; i < num_points; i++) 
            {
                std::cin >> points[i].x >> points[i].y;
                points[i].ind = i;
                sortedByX[i] = points[i];
            }
            std::sort(sortedByX.begin(), sortedByX.end(), compareX);
        }
        void findAndPrintClosestPair() 
        {
            Point closestA, closestB;
            findClosestPairRecursive(0, num_points - 1, closestA, closestB);
            std::cout << closestA.x << " " << closestA.y << " " << closestB.x << " " << closestB.y << std::endl;
        }
        long long findClosestPairRecursive(int start, int end, Point &closestA, Point &closestB)
        {
            if (end - start <= 2) 
            { 
                return bruteForce(start, end, closestA, closestB);
            }
            int mid = (end + start)/2;                                             //divide and conquer
            Point midPoint = sortedByX[mid];

            Point pl1, pl2, pr1, pr2;

            long long leftDist = findClosestPairRecursive(start, mid, pl1, pl2);
            long long rightDist = findClosestPairRecursive(mid+1, end, pr1, pr2);

            long long minDist = leftDist;
            closestA = pl1;
            closestB = pl2;
            if(rightDist < minDist)
            {
                minDist = rightDist;
                closestA = pr1;
                closestB = pr2;
            }
            else if (rightDist == minDist)
            {
                if(isLexSmaller(pr1, pr2, closestA, closestB))
                {
                    closestA = pr1;
                    closestB = pr2;   
                }
            }

            if (closestA.ind > closestB.ind) std::swap(closestA, closestB);

            std::vector < Point > verticalStrip;
            for (int i = start; i <= end; i++)
            {
                if((sortedByX[i].x - midPoint.x) * (sortedByX[i].x - midPoint.x) <= minDist)
                    verticalStrip.push_back(sortedByX[i]);
            }                                                   //squares of d
            std::sort(verticalStrip.begin(), verticalStrip.end(), compareY);

            for (int i = 0; i < verticalStrip.size(); i++) 
            {
                for (int j = i + 1; j < verticalStrip.size() ; j++) 
                {
                    if((verticalStrip[j].y - verticalStrip[i].y) *(verticalStrip[j].y - verticalStrip[i].y) <= minDist)
                    {
                        long long dist = distance(verticalStrip[i], verticalStrip[j]);
                        if (dist < minDist) 
                        {
                            minDist = dist;
                            closestA = verticalStrip[i];
                            closestB = verticalStrip[j];
                        }
                        else if (dist == minDist)
                        {
                            Point P1 = verticalStrip[i];
                            Point P2 = verticalStrip[j];
                            
                            if(isLexSmaller(P1, P2, closestA, closestB))
                            {
                                closestA = P1;
                                closestB = P2;
                            }
                        }
                    }
                    if (closestA.ind > closestB.ind) std::swap(closestA, closestB);
                }
            }
            return minDist;
        }
        long long bruteForce(int start, int end, Point& closestA, Point& closestB) 
        {
            long long minDist = 1e18;
            for (int i = start; i < end; i++) 
            {
                for (int j = i + 1; j <= end; j++) 
                {
                    long long d = distance(sortedByX[i], sortedByX[j]);
                    if (d < minDist) 
                    {
                        minDist = d;
                        closestA = sortedByX[i];
                        closestB = sortedByX[j];
                    }
                    else if (d == minDist) 
                    {
                        Point temp1 = sortedByX[i];
                        Point temp2 = sortedByX[j];
                        if (isLexSmaller(temp1, temp2, closestA, closestB)) 
                        {
                            closestA = temp1;
                            closestB = temp2;
                        }
                    }
                }
            }
            if (closestA.ind > closestB.ind) std::swap(closestA, closestB);
            return minDist;
        }
        bool isLexSmaller(Point a1, Point a2, Point b1, Point b2) 
        {
            // Lexicographically compare two pairs of points (a1, a2) and (b1, b2)
            if (a1.x != b1.x) return a1.x < b1.x;
            if (a1.y != b1.y) return a1.y < b1.y;
            if (a2.x != b2.x) return a2.x < b2.x;
            return a2.y < b2.y;
        }
};