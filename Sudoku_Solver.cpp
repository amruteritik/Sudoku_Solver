#include <iostream>
#include <vector>

using namespace std;

void print(int Sudoku[9][9])
{
    cout << " ********************** " << endl;

    for (int i = 0; i < 9; i++)
    {
        cout << "    ";
        for (int j = 0; j < 9; j++)
        {
            cout << Sudoku[i][j] << " ";
        }
        cout << endl;
    }
    cout << " ********************** " << endl;
}

bool Place_Check(int Sudoku[9][9], int row, int col, int num)
{
    if (Sudoku[row][col] != 0)
        return false;

    int Box_x = (col / 3) * 3;
    int Box_y = (row / 3) * 3;

    for (int i = 0; i < 9; i++)
    {
        if (Sudoku[i][col] == num)
            return false;

        if (Sudoku[row][i] == num)
            return false;

        if (Sudoku[Box_y + i / 3][Box_x + i % 3] == num)
            return false;
    }
    return true;
}

void Next_place_available(int Sudoku[9][9], int row, int col, int &Next_row, int &Next_col)
{

    for (int i = row * 9 + col + 1; i < 9 * 9; i++)
    {
        if (Sudoku[i / 9][i % 9] == 0)
        {
            Next_row = i / 9;
            Next_col = i % 9;
            return;
        }
    }
}

vector<int> Are_Available(int Sudoku[9][9], int row, int col)
{

    vector<int> Availble;
    for (int i = 1; i <= 9; i++)
    {
        if (Place_Check(Sudoku, row, col, i))
            Availble.push_back(i);
    }
    return Availble;
}

void Duplicate(int Sudoku[9][9], int Temp_Sudoku[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Temp_Sudoku[i][j] = Sudoku[i][j];
        }
    }
}
bool Solve(int Sudoku[9][9], int row, int col)
{
    if (row > 8)
        return true;

    if (Sudoku[row][col] != 0)
    {
        int Next_row;
        int Next_col;
        Next_place_available(Sudoku, row, col, Next_row, Next_col);
        return Solve(Sudoku, Next_row, Next_col);
    }

    vector<int> Available = Are_Available(Sudoku, row, col);

    if (Available.size() == 0)
        return false;
    bool ans = false;

    for (int i = 0; i < Available.size(); i++)
    {
        int n = Available[i];

        int Temp_Sudoku[9][9];
        Duplicate(Sudoku, Temp_Sudoku);

        Temp_Sudoku[row][col] = n;
        int Next_row = row;
        int Next_col = col;

        Next_place_available(Temp_Sudoku, row, col, Next_row, Next_col);

        if (Solve(Temp_Sudoku, Next_row, Next_col))
        {
            Duplicate(Temp_Sudoku, Sudoku);
            return true;
        }
    }
    return ans;
}

int main()
{
    // input the Sudoku you want to solve
    int Sudoku[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    Solve(Sudoku, 0, 0);
    print(Sudoku);
}
