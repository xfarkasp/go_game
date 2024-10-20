#include "matrix.h"
#include "game.h"

int main(int argc, char* argv[]) 
{
	Matrix board{ 9, 9 };
	std::cout << board;
	
    try {
        Game gameInstacne{ std::move(board) };
    }
    catch (const std::exception& e) {

        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

}