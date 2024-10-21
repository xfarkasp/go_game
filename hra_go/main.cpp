#include "matrix.h"
#include "game.h"

int main(int argc, char* argv[]) 
{
    try {
        if (argc != 3)
        {
            throw std::runtime_error("Too few arguments.");
        }

        const size_t boardSize = std::atoi(argv[1]);
        if (boardSize < 1)
        {
            throw std::runtime_error("Wrong board size.");
        }

        const std::string argSwitch = argv[2];
        if (   argSwitch != "--board"
            && argSwitch != "--score")
        {
            throw std::runtime_error("Wrong program switch argument.");
        }

        Game gameInstacne{ Matrix{ boardSize, boardSize } };

        argSwitch == "--board" ? gameInstacne.printBoard() : gameInstacne.printScore();
    }
    catch (const std::exception& e) {

        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}