#include "ClosestPair.cpp"

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