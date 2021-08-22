#include <iostream>
#include <vector>
using namespace std;

const int ROW_SIZE = 3;

void printColumn()
{
    string columnDecorator = "";
    for (int i = 0; i < ROW_SIZE; i++)
    {
        columnDecorator += "  - ";
    }
    cout << columnDecorator << "\n";
}

vector<vector<string> > createBoard()
{
    vector<vector<string> > board(ROW_SIZE);
    for (int i = 0; i < ROW_SIZE; i++)
    {
        vector<string> row(ROW_SIZE);
        board[i] = row;
        for (int j = 0; j < ROW_SIZE; j++)
        {
            int point = (i > 0 ? i + 2 : 0) + j;
            point = i > 1 ? point + 2 : point;
            board[i][j] = to_string(point);
        }
    }
    return board;
};

void printBoard(vector<vector<string> > board)
{
    for (int i = 0; i < board.size(); i++)
    {
        printColumn();
        for (int j = 0; j < board.size(); j++)
        {
            const string rightDecorator = j == 2 ? " |" : "";
            const string leftDecorator = j == 0 ? "| " : " | ";
            cout << leftDecorator << board[i][j] << rightDecorator;
        }
        cout << "\n";
    }
    printColumn();
    cout << "\n";
};

void printInstruction(string currentPlayer)
{
    cout << "its: " << currentPlayer << " turn" << endl;
    cout << "please pick a number from the board" << endl;
};

bool validateInput(vector<vector<string> > board, string input)
{
    if (input == "x" || input == "o")
    {
        return false;
    };
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == input)
                return true;
        };
    };
    return false;
};

vector<vector<string> > playTurn(vector<vector<string> > board, string currentPlayer)
{
    printInstruction(currentPlayer);
    printBoard(board);
    string pick;
    bool isInputInConstraints = false;
    cin >> pick;
    isInputInConstraints = validateInput(board, pick);
    while (!isInputInConstraints)
    {
        cout << "invalid input" << endl;
        cin.clear();
        cin >> pick;
        isInputInConstraints = validateInput(board, pick);
    };
    const int rowFromPick = stoi(pick) / 3;
    const int colFromPick = stoi(pick) % 3;
    board[rowFromPick][colFromPick] = currentPlayer;
    return board;
};
string checkWinner(vector<vector<string> > board)
{
    if (board[0][0] == board[0][1] && board[0][0] == board[0][2])
        return board[0][0];
    if (board[1][0] == board[1][1] && board[1][0] == board[1][2])
        return board[1][0];
    if (board[2][0] == board[2][1] && board[2][0] == board[2][2])
        return board[2][0];
    if (board[0][0] == board[1][0] && board[0][0] == board[2][0])
        return board[0][0];
    if (board[0][1] == board[1][1] && board[0][1] == board[2][1])
        return board[0][1];
    if (board[0][2] == board[1][2] && board[0][2] == board[2][2])
        return board[0][2];
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];
    return "";
};
int main()
{
    string currentPlayer = "x";
    string winner;
    vector<vector<string> > board = createBoard();
    while (winner.length() == 0)
    {
        board = playTurn(board, currentPlayer);
        winner = checkWinner(board);
        currentPlayer = currentPlayer == "x" ? "o" : "x";
    }
    cout << "congrats " << winner << " you won 🔥🎉" << endl;
    string rematchAns;
    cout << "rematch? (y/n)" << endl;
    cin >> rematchAns;
    while (rematchAns != "y" && rematchAns != "n")
    {
        cin.clear();
        cout << "invlaid input (y/n)" << endl;
        cin >> rematchAns;
    };
    if (rematchAns == "y")
    {
        main();
    };
};