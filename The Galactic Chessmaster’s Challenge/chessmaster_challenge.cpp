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

class Quantum_ChessBoard
{
    private:
        std::vector < std::vector < long long > > board;
        std::vector < long long > flattened; 
        long long no_of_inversions = 0;
        int size = 0;
    public:
        void createBoard()
        {
            std::cin >> size;
            board.assign (size, std::vector < long long > (size));
            flattened.resize (size*size, 0);
            for (int i = 0;i < size; i++)
            {
                for(int j = 0;j < size; j++)
                {
                    std::cin >> board[i][j];
                }
            }
        }
        void sortRows(Comparator& comp)
        {
            for(int i = 0; i < size; i++)
            {
                mergeSortRow(i, 0, size - 1, comp);      // iteratively sorting for every row
            }                                    
        }
        // Performs merge sort on a specific row of the matrix board using the given comparator.
        void mergeSortRow(int row, int start, int end, Comparator& comp)
        {
            if(start == end)
            {
                return;
            }
            int mid = (start + end)/2; 
            // Recursively sort the left and right halves
            mergeSortRow(row, start, mid, comp);
            mergeSortRow(row, mid + 1, end, comp);

            std::vector<long long> merged(end-start+1);

            int i = start;        // Pointer for left half
            int j = mid + 1;      // Pointer for right half
            int k = 0;            // Pointer for merged array
            while(i <= mid && j <= end)
            {
                if (comp(board[row][i], board[row][j]))
                {
                    merged[k] = board[row][i];
                    i++;                             // push the board[row][i] into merging array
                }
                else 
                {
                    merged[k] = board[row][j];            // push the board[row][j] into merging array
                    j++;
                }
                k++;
            }
            while(i <= mid)
            {
                merged[k] = board[row][i];
                k++;
                i++;
            }
            while(j <= end)
            {
                merged[k] = board[row][j];
                k++;
                j++;
            }
            for(int t = 0; t < (int)(merged.size()) ; t++)
            {
                board[row][start + t] = merged[t];
            }
        }
        long long countInversions()
        {
            no_of_inversions = 0;
            int index = 0;
            // Flatten 2D matrix board into 1D array flattened
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    flattened[index] = board[i][j];
                    index ++;
                }
            }
            // Count inversions using modified merge sort
            mergeCountInversion (0, flattened.size() - 1);
            return no_of_inversions;                                    
        }
        // Recursive merge sort function that counts inversions in array flattened
        void mergeCountInversion (int start,int end)
        {
            if(start == end)
            {
                return;
            }
            int mid = (start + end)/2; 

            mergeCountInversion (start, mid);
            mergeCountInversion (mid + 1, end);

            std::vector<long long> merged(end - start + 1);
                
            int i = start;        // Pointer for left half
            int j = mid + 1;      // Pointer for right half
            int k = 0;            // Pointer for merged array

            while(i <= mid && j <= end)
            {
                if( flattened[i] > flattened[j])
                {                             
                    no_of_inversions += mid - i + 1;     // inversions +=  All remaining elements in left are greater
                    merged[k] = flattened[j];
                    j++;                                                     
                }
                else 
                {
                    merged[k] = flattened[i];                 // no change in no of inversions
                    i++;                         
                }
                k++;                                 
            }
            while (i <= mid)
            {
                merged[k] = flattened[i];
                k++;
                i++;
            }
            while (j <= end)
            {
                merged[k] = flattened[j];
                k++;
                j++;
            }
            for (int t = 0; t < (int)(merged.size()); t++)
            {
                flattened[start + t] = merged[t];
            }
        }
        void display()
        {
            for (int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    std::cout << board[i][j] << " " ;
                }
                std::cout << std::endl;
            }
        }
};

int main()
{
    std::string command;
    Quantum_ChessBoard Qboard;
    while(true)
    {
        std::cin >> command;
        if(command == "END")
        {
            break;
        }
        else if(command == "CREATE_2D")
        { 
            Qboard.createBoard();
        }
        else if(command == "SORT_2D")
        {
            std::string order;
            std::cin >> order;
            if(order == "ascending")
            {
                Comparator C(true); 
                Qboard.sortRows(C);                        // call sort function
            }
            else if(order == "descending")
            {
                Comparator C(false);
                Qboard.sortRows(C);                          // then reverse the order in each row
            }
        }
        else if (command == "INVERSION_2D")
        {
            long long no_of_inversions = Qboard.countInversions();
            std::cout << no_of_inversions << std::endl;
        }
        else if (command == "DISPLAY_2D")
        {
            Qboard.display();
        }
        else if (command == "CLOSEST_2D")
        {
            long long num_points;
            std::cin >> num_points;
            ClosestPair C(num_points);
            C.readPoints();
            C.findAndPrintClosestPair();
        }  
    }
}