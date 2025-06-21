#include "Point_Comparator.cpp"

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