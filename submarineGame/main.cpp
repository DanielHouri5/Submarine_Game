#include <iostream>
using namespace std;
//*****************************************
#define minPosition 0
#define maxPosition 2
#define horizontal 0
#define minCoordinate 0
#define maxCoordinate 10
#define minRow 0
#define maxRow 9
#define minCol 0
#define maxCol 9
#define zero 0
#define one 1
#define two 2
#define three 3
#define four 4
#define five 5
#define six 6
#define size 10
#define win 58
#define out (-1)
#define space ' '
#define hit 'X'
#define miss '~'
//*****************************************
void resetMat(int matPosting [size][size]);
int random(int min, int max);
bool limit(int submarineSize, int check);
void resetUserMat(char userMat[size][size]);
void printUserMat(char userMat[size][size]);
int chooseCoordinate(int matPosting[size][size], char userMat[size][size]);
void game(int matPosting[size][size], char userMat[size][size]);
bool checkCells(int matPosting[size][size], int startRow, int startCol, int endRow, int endCol);
bool emptyCells(int matPosting[size][size], int row, int col, int position, int submarineSize);
void postingSubmarine(int matPosting[size][size], int sign, int submarineSize);
//*****************************************
int main()
{
    srand((unsigned)time(NULL)); // Initialization of random
    char userMat[size][size];//Creating a 10x10 character type matrix - the user game matrix.
    resetUserMat(userMat);//Initialize a matrix with space in each cell.
    printUserMat(userMat);
    cout << endl;
    int matPosting [size][size];//Creating a 10x10 integer type matrix - the submarine placement matrix.
    resetMat(matPosting);//Initialize a matrix with a zero value in each cell.
    postingSubmarine(matPosting, one, two);//Placing the size 2 submarine.
    postingSubmarine(matPosting, two, three);//Placing the first size 3 submarine
    postingSubmarine(matPosting, three, three);//Placing the second size 3 submarine
    postingSubmarine(matPosting, four, four);//Placing the size 4 submarine
    postingSubmarine(matPosting, five, five);//Placing the size 5 submarine
    game(matPosting, userMat);//A call to a function which actually starts the game.
    return 0;
}
//*****************************************
/*This function accepts an array of character type (the board the user sees)
  and initializes its values to be spaces.*/
void resetUserMat(char userMat[size][size])
{
    for (int i = 0; i < size; ++i)//The loop runs from the first row to the last row in the matrix.
        for (int j = 0; j < size; ++j)//The loop runs from the first column to the last column in the matrix.
            userMat[i][j] = ' ';//Place the space character in each cell of the matrix.
}
//*****************************************
/*This function accepts an array of character type (the board the user sees)
  and prints it*/
void printUserMat(char userMat[size][size])
{
    cout << "  ";//Print two spaces.
    for (int j = 0; j < size; ++j)//The loop runs from the first column to the last column in the matrix.
        cout << "   " << j << "  ";//Print two spaces, the column number and a space.
    cout << endl;//A linebreak.
    for (int i = 0; i < size; ++i)//The loop runs from the first row to the last row in the matrix.
    {
        cout << "  ";//Print two spaces.
        for (int j = 0; j < size; ++j)//The loop runs from the first column to the last column in the matrix.
            cout << " -----";//Print a space and three hyphens.
        cout << endl << i << " |";//A linebreak, print the row number, space and a line.
        for (int j = 0; j < size; ++j)//The loop runs from the first column to the last column in the matrix.
            cout << "  " << userMat[i][j] << "  |";//Print a space, print the value of userMat in the row [i] and col [j], space and a line.
        cout << endl;//A linebreak.
    }
    cout << "  ";//Print two spaces.
    for (int j = 0; j < size; ++j)//The loop runs from the first column to the last column in the matrix.
        cout << " -----";//Print a space and three hyphens.
    cout << endl;//A linebreak.
}
//*****************************************
/*This function accepts an integer type array
  (the array where the submarines are placed) and initializes it with zeros.*/
void resetMat(int matPosting [size][size])
{
    for (int i = 0; i < size; ++i)//The loop runs from the first row to the last row in the matrix.
        for (int j = 0; j < size; ++j)//The loop runs from the first column to the last column in the matrix.
            matPosting[i][j] = zero;//Place the zero value in each cell of the matrix.
}
//*****************************************
/*This function accepts two integers
  and triggers a number between them.*/
int random(int min, int max)
{
    int value = min + (rand() % (max - min));//Declaring the variable value and enter the number that came out in the lottery into the value.
    return value;//The function returns the number that came out in the lottery.
}
//*****************************************
/*This function receives a submarine length and a row number or a column number
 and checks whether it sees the submarine, it will output the limits of the matrix or not.*/
bool limit(int submarineSize, int check)
{
    return check <= size - submarineSize;//The function returns true if the submarine does not exceed the bounds of the matrix and false if it does.
}
//*****************************************
/*This function receives the matrix in which the submarines are placed and the initial and final coordinates of a new matrix,
  which actually includes the place where the submarine was drawn to be placed and everything that directly surrounds it.
  The function checks whether it can be placed in this place by checking whether all the values of the new matrix are equal to zero,
  if so the function will return true and if at least one element in the new matrix is different from zero then the function will return false.*/
bool checkCells(int matPosting[size][size], int startRow, int startCol, int endRow, int endCol)
{
    if (endRow > size - one)//Checking if the value of the final row variable we got is bigger than the length of the matrix.
        //If the value of the final row variable we got is bigger than the length of the matrix.
        endRow = size - one;//Put the length of the matrix in the final row variable (so that it doesn't try to check if values are outside the matrix).
    if (endCol > size - one)//Checking if the value of the final column variable we got is bigger than the width of the matrix.
        //If the value of the final column variable we got is bigger than the width of the matrix.
        endCol = size - one;//Put the width of the matrix in the final column variable (so that it doesn't try to check if values are outside the matrix).
    for (int i = startRow; i <= endRow ; ++i)//The loop runs from the first row in the new matrix to the last row in the new matrix.
        for (int j = startCol; j <= endCol; ++j)//The loop runs from the first column in the new matrix to the last column in the new matrix.
            if (matPosting[i][j] != zero)//Checking if one of the matrix values is different from zero (because then you can't place a submarine there).
                //If one of the matrix values is different from zero.
                return false;//The function will return false.
    return true;//After the function has run over the entire new matrix and has not found a cell whose value is different from zero, only then will the function return true (because then you can put a submarine there).
}
//*****************************************
/*This function receives the matrix in which the submarines will be placed,
  the number of the drawn row, column and position and the length of the submarine that you want to place.
  The function basically sends the function 'checkCells' a starting and final row and column number according to
  the values that were drawn so that 'checkCells' will check the new matrix that will come out of
  these values and return true or false accordingly.*/
bool emptyCells(int matPosting[size][size], int row, int col, int position, int submarineSize)
{
    if (position == horizontal)//Checking if the drawn position is horizontal.
    {
        //If the drawn position is horizontal.
        if (row == minRow && col == minCol)//Checking if the drawn row is zero and the drawn col is zero.
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row, col, row + one, col + submarineSize);
        else if (row == maxRow && col == minCol)//Checking if the drawn row is nine and the drawn col is zero.
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row, col, row - one, col + submarineSize);
        else if (row == minRow)//Checking if the drawn row is zero(If the drawn point is on the first row except for the edges).
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row, col - one, row + one, col + submarineSize);
        else if (col == minCol)//Checking if the drawn col is zero(If the drawn point is on the first column except for the edges).
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row - one, col, row + one, col + submarineSize);
        else if (row == maxRow)//Checking if the drawn row is nine(If the drawn point is on the last row except for the edges).
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row - one, col - one, row, col + submarineSize);
        else//Checking if the point is in the matrix but not in the first and last rows and columns.
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row - one, col - one, row + one, col + submarineSize);
    }
    else
    {
        //If the drawn position is vertical.
        if (row == minRow && col == minCol)//Checking if the drawn row is zero and the drawn col is zero.
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row, col, row + submarineSize, col + one);
        else if (row == minRow && col == maxCol)//Checking if the drawn row is zero and the drawn col is nine.
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row, col - one, row + submarineSize, col);
        else if (row == minRow)//Checking if the drawn row is zero(If the drawn point is on the first row except for the edges).
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row, col - one, row + submarineSize, col + one);
        else if (col == minCol)//Checking if the drawn col is zero(If the drawn point is on the first column except for the edges).
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row - one, col, row + submarineSize, col + one);
        else if (col == maxCol)//Checking if the drawn col is nine(If the drawn point is on the last column except for the edges).
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row - one, col - one, row + submarineSize, col);
        else//Checking if the point is in the matrix but not in the first and last rows and columns.
            //Passing appropriate values to the function 'checkCells' so that it examines a new matrix defined by these values, and returning true or false accordingly.
            return checkCells(matPosting, row - one, col - one, row + submarineSize, col + one);
    }
}
//*****************************************
/*This function receives the submarine placement matrix,
  the length of the submarine and the sign of the submarine (related to the bonus)
  It extracts the row number, column and position, sends these values to the test,
  extracts again when the test is not passed and places the submarines after the test is passed.*/
void postingSubmarine(int matPosting[size][size], int sign, int submarineSize)
{
    int row, col, position;//Declaring the variables row, col and position.
    do
    {
        position = random(minPosition, maxPosition);//Drawing the position where the submarine was placed and entering a drawn value into position(0 - horizontal, 1 - vertical).
        row = random(minCoordinate, maxCoordinate);//Drawing the number of the row from which to start placing the submarine and entering the drawn value into row(0 - 9).
        col = random(minCoordinate, maxCoordinate);//Drawing the number of the col from which to start placing the submarine and entering the drawn value into col(0 - 9).
    }
        //The loop will continue to run and draw a point and position as long as the drawn values do not meet the requirements of the game
    while (!limit(submarineSize, row) || !limit(submarineSize, col) || !emptyCells(matPosting, row, col, position, submarineSize));
    //After the program has exited the loop and normal values have been drawn, the program checks in which position the submarine should be placed.
    if (position == horizontal)//Checking if position is horizontal.
        //If position is horizontal.
        for (int i = col; i < submarineSize + col; ++i)//The loop runs from the drawn col to the drawn col plus the size of the received submarine in the matrix.
            matPosting[row][i] = sign;//Place the value of sign in the relevant positions on row.
    else//If position is vertical.
        for (int i = row; i < submarineSize + row; ++i)//The loop runs from the drawn row to the drawn row plus the size of the received submarine in the matrix.
            matPosting[i][col] = sign;//Place the value of sign in the relevant positions on col.
}
//*****************************************
/*This function receives the submarine placement matrix and the user game matrix,
  She asks the user to enter coordinates that he wants to try to hit and if he entered
  incorrect values (outside the matrix) she will ask him to enter values again.

  After entering correct values, the function will check in the submarine placement
  matrix whether there is a submarine at the point you selected,
  if so it will be checked if he has already chosen this place and if so it will be print
  to the screen the word 'miss' and the value zero will be returned.

  And if not it will be print to the screen the word 'hit' and enter the character 'X' in the user game matrix at
  the point he selected and the value at this position in the matrix will be returned.

  And if there is a zero there it will print to the screen the word 'miss' and
  enter the character '~' in the user game matrix at the point he chose and the value zero will be returned.

  And if the user entered both the row number and the column number the value -1 at the same time,
  he will exit the game and return -1.*/
int chooseCoordinate(int matPosting[size][size], char userMat[size][size])
{
    int row, col;//Declaring the variables row and col.
    cout << "Choose the row:" << endl;//Printing a message to the user to enter a row number.
    cin >> row;//Inserting the entered value into row.
    cout << "Choose the col:" << endl;//Printing a message to the user to enter a col number.
    cin >> col;//Inserting the entered value into col.
    while (row > maxRow || row < minRow || col > maxCol || col < minCol)//The loop will continue to run as long as the user enters invalid values.
    {
        if (row == out && col == out)//Checking if the row is -1 and the col is -1.
        {
            //If the row is -1 and the col is -1.
            cout << "See you next time!" << endl;//A corresponding message is printed.
            return out;//And if there is a zero there.
        }
        cout << "Illegal values, please try again." << endl;//A corresponding message is printed.
        cout << "Choose the row:" << endl;//Printing a message to the user to enter a row number.
        cin >> row;//Inserting the entered value into row.
        cout << "Choose the col:" << endl;//Printing a message to the user to enter a col number.
        cin >> col;//Inserting the entered value into col.
    }
    if (matPosting[row][col] != zero)//Checking if at the point the user selected in the submarine placement matrix the value is different from zero.
    {
        //If at the point the user selected in the submarine placement matrix the value is different from zero.
        if (userMat[row][col] == space)//Checking if a point in the user's game matrix has the space character (checking if he has not yet selected this point).
        {
            //if a point in the user's game matrix has the space character (if he has not yet selected this point).
            cout << "Hit" << endl;//A corresponding message is printed.
            userMat[row][col] = hit;//Inserting the character 'X' into the cell in the user's game matrix at the point the user has chosen.
            return matPosting[row][col];//The cell value in the submarine placement matrix at the point the user selected will be returned.
        }
        else//if a point in the user's game matrix has not the space character (if he has yet selected this point).
        {
            cout << "You already hit this point, please enter another point:" << endl;//A corresponding message is printed.
            return zero;//The value zero will be returned.
        }
    }
    else//If at the point the user selected in the submarine placement matrix the value is zero.
    {
        cout << "Miss" << endl;//A corresponding message is printed.
        userMat[row][col] = miss;//Inserting the character '~' into the cell in the user's game matrix at the point the user has chosen.
        return zero;//The value zero will be returned.
    }
}
//*****************************************
/*This function receives the submarine placement matrix and the user game matrix.
  It prints to the screen the user's game matrix every turn, checks whether a
  certain submarine has been sunk (the bonus), checks whether the user has finished
  the game or chosen to exit it and prints messages accordingly. */
void game(int matPosting[size][size], char userMat[size][size])
{
    int counters[six] = {0};//Creating an array with a length of 6 and initializing all its cell values with zero, which actually stores in each cell a counter of a certain submarine (checks when he sinks each one) and in the zero cell is the counter of all the submarines together (checks when he sinks them all).
    int i, state = 0;//Declaring the variables i and state(state with the value zero).
    while (counters[zero] != win && state != out)//The loop will run as long as the counter that is in the zero place has not counted all the submarines (which means that the user has not yet sunk all the submarines) and also that the value returned from the function 'chooseCoordinate' into state is different from -1 (which means that the user has not chosen to exit the game).
    {
        if (state != zero)//Checking if the value returned from the function 'chooseCoordinate' into state is different from zero.
            //If the value returned from the function 'chooseCoordinate' into state is different from zero.
            ++counters[state];//One of the array's counters is incremented by one depending on the value of state.
        if (state < three)//Checking if the value returned from the function 'chooseCoordinate' into state is smaller than three.
        {
            //If the value returned from the function 'chooseCoordinate' into state is smaller than three.
            for (i = 1; i < three; ++i)//The loop will run on the array from the counter in place one to the counter in place two (inclusive)
                if (counters[i] == i + one)//Checking if the value of the counter of the submarine with length 2 is 2 or the value of the counter of the submarine with length 3(the first one) is 3.
                {
                    //If the value of the counter of the submarine with length 2(the counter that in place one) is 2,
                    //or the value of the counter of the submarine with length 3(the first one)(the counter that in place two) is 3.
                    cout << "Congratulation you just sink a submarine with " << state + one << " cells." << endl;//A corresponding message is printed.
                    counters[i] = zero;//Resetting the counter so that it does not print the message again on the next turn.
                }
        }
        else//If the value returned from the function 'chooseCoordinate' into state is bigger or equal to three.
        {
            for (i = 3; i < six; ++i)//The loop will run on the array from the counter in place three to the counter in place five (inclusive)
                if (counters[i] == i)//Checking if the value of the counter of the submarine with length 3(the second one) is 3 or the value of the counter of the submarine with length 4 is 4 or the value of the counter of the submarine with length 5 is 5.
                {
                    //If the value of the counter of the submarine with length 3(the second one) is 3,
                    // or if the value of the counter of the submarine with length 4 is 4,
                    // or if the value of the counter of the submarine with length 5 is 5.
                    cout << "Congratulation you just sink a submarine with " << state << " cells." << endl;//A corresponding message is printed.
                    counters[i] = zero;//Resetting the counter so that it does not print the message again on the next turn.
                }
        }
        state = chooseCoordinate(matPosting, userMat);//Put the value returned from the function 'chooseCoordinate' in state every turn.
        counters[zero] += state;//Adding the value of the variable into the counter instead of the zero in the array.
        if (state != out)//Checking if the value of state is not -1.
            //If the value of state is not -1.
            printUserMat(userMat);//the user game matrix will be printed.
    }
    if (state != out)//Checking if the value of state is not -1.
    {
        //If the value of state is not -1.
        if (state < three)//Checking if the value of state is smaller than 3.
            //If the value of state is smaller than three.
            cout << "Congratulation you just sink a submarine with " << state + one << " cells." << endl;//A corresponding message is printed.
        else//If the value of state is bigger or equal to three.
            cout << "Congratulation you just sink a submarine with " << state << " cells." << endl;//A corresponding message is printed.
        cout << "Congratulation you win!" << endl;//A corresponding message is printed.
    }

}
