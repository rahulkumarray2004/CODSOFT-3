#include <iostream>
#include <string>

class GAME
{
    typedef enum {
        PLAYER_X,
        PLAYER_O,
        NONE
    } Player;

    Player Players_Board[3][3];
    Player Now_Available;
    Player Winner_Name;
public:
    static Player inputPlayer(std::string prompt)
    {
        std::cout << prompt;
        char ch; std::cin >> ch;
        switch (ch) {
            case 'x': case 'X': return PLAYER_X;
            case 'o': case 'O': return PLAYER_O;
            default:
               std::cout << "Invalid player value: '" << ch << "'\n";
               exit(1);
        }
        return PLAYER_X;
    }

    GAME(Player p1, Player p2) : Winner_Name(NONE)
    {
        if (p1 == p2) {
            std::cout << "Invalid game, both players are same\n";
            exit(1);
        }
        if (p1 == PLAYER_X) Now_Available = p1;
        else Now_Available = p2;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                Players_Board[i][j] = NONE;
            }
        }
    }

    void DISPLAYBOARD_ON_TICTACTOE()
    {
        std::cout << "Current board:\n";
        std::cout << "   - 1 - 2 - 3 -\n";

        for (int i = 0; i < 3; ++i) {
            std::cout << " " << (i+1) << " | ";

            for (int j = 0; j < 3; ++j) {
                char symbol = (Players_Board[i][j] == PLAYER_X) ?
                    'X' : (Players_Board[i][j] == NONE) ?
                        ' ' : 'O';
                std::cout << symbol << " | ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    std::pair<int, int> inputCell()
    {
        int ROW, COLUMN;

        while (true) {
            std::cout << "Enter row (1-3) and column (1-3) for Player " << (Now_Available == PLAYER_X ? 'X' : 'O') << ": ";
            std::cin >> ROW >> COLUMN;
            if ((ROW < 1 || ROW > 3) ||
                (COLUMN < 1 || COLUMN > 3)) {
                    std::cout << "Invalid row or column value\n";
                    continue;
            } else if (Players_Board[ROW-1][COLUMN-1] != NONE) {
                std::cout << "Cell (" << ROW << ", " << COLUMN << ") is already occupied\n";
                continue;
            } else break;
        }
        Players_Board[ROW-1][COLUMN-1] = Now_Available;
        return { ROW-1, COLUMN-1 };
    }

    void CALCULATOR_WINNER(std::pair<int, int> p)
    {
        int i = p.first,
            j = p.second;

        if (checkRow(i, j, Now_Available) || checkColumn(i, j, Now_Available)) {
            Winner_Name = Now_Available;
            Now_Available = NONE;
            return;
        }
        if (checkDiagonals(Now_Available)) {
            Winner_Name = Now_Available;
            Now_Available = NONE;
            return;
        }
        /* count for draw */
        int cnt = 0;

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                cnt += (Players_Board[i][j] != NONE);

        if (cnt == 9)
            Winner_Name = Now_Available = NONE;
    }

    bool HAS_ENDED()
    {
        return Now_Available == NONE;
    }

    void SWITCH_PLAYER()
    {
        Now_Available = (Now_Available == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }

    void DISPLAY_WINNER()
    {
        std::cout << "GAME OVER!\n";

        if (Winner_Name == Now_Available && Now_Available == NONE) {
            std::cout << "It's a draw\n";
            return;
        }
        std::cout << "Player " << (Winner_Name == PLAYER_X ? 'X' : 'O') <<" Won the match "<< std::endl;
    }

private:
    bool checkRow(int row, int col, Player player)
    {
        for (int j = 0; j < 3; ++j) {

            if (Players_Board[row][j] != player) {
                return false;
            }
        }
        return true;
    }

    bool checkColumn(int row, int col, Player player)
    {
        for (int i = 0; i < 3; ++i) {

            if (Players_Board[i][col] != player) {
                return false;
            }
        }
        return true;
    }

    bool checkDiagonals(Player player)
    {
        if ((Players_Board[0][0] == player && Players_Board[1][1] == player && Players_Board[2][2] == player) || (Players_Board[0][2] == player && Players_Board[1][1] == player && Players_Board[2][0] == player)) 
        {
                return true;
        }
        return false;
    }
};

int main()
{
    std::cout << "Welcome to the Tic-Tac-Toe Game! " << std::endl;
    while (true) {
        GAME game(
            GAME::inputPlayer("Enter player 1 (X/O): "),
            GAME::inputPlayer("Enter player 2 (X/O): "));
        game.DISPLAYBOARD_ON_TICTACTOE();

        while (true) {
            auto p = game.inputCell();
            game.DISPLAYBOARD_ON_TICTACTOE();
            game.CALCULATOR_WINNER(p);

            if (game.HAS_ENDED()) break;
            game.SWITCH_PLAYER();
        }
        game.DISPLAY_WINNER();
        std::cout << "\nEnter Y to replay, quit otherwise: ";
        char ch; std::cin >> ch;

        switch (ch) {
            case 'y': case 'Y': continue;
            default: exit(0);
        }
    }
    return 0;
}