int counter=0;

bool working(int **sudoku, int x, int y, int number)
{
    //return false if cannot put this number at this position in the sudoku

    //determine if the same row or the same column contains this number
    for (int i=0; i<9; i++)
    {
        if(sudoku[i][x]==number or sudoku[y][i]==number)
        {
            return false;
        }
    }
    
    //determine where the current space is in the 3x3 box

    //x%3=0 --> left column
    //x%3=1 --> middle column
    //x%3=2 --> right column
    int x_pos=x%3;
    //the current box starts at this x
    int x_start=x-x_pos;

    //y%3=0 --> top row
    //y%3=1 --> middle row
    //y%3=2 --> buttom row
    int y_pos=y%3;
    //the current box starts at this y
    int y_start=y-y_pos;

    //determine if the 3x3 square contains this number
    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(sudoku[y_start+j][x_start+i]==number)
            {
                return false;
            }
        }
    }

    //if no conflict, can put this number here
    return true;
}

bool complete(int **sudoku)
{
    //if find an empty spot, return right away
    for(int y=0; y<9; y++)
    {
        for(int x=0; x<9; x++)
        {
            if(sudoku[y][x]==0)
            {
                return false;
            }
        }
    }
    
    //if no empty spot found, game is complete
    return true;
}

bool backtracking_helper(int **sudoku)
{
    //first check if the current board is complete, if so return true
    if(complete(sudoku))
    {
        return true;
    }
    // iterate through all boxes in the board
    for(int y=0; y<9; y++)
    {
        for(int x=0; x<9; x++)
        {
            //if the current box is empty
            if(sudoku[y][x]==0)
            {
                //iterate through each of the 9 numbers
                for(int insertnumber=1; insertnumber<10; insertnumber++)
                {
                    //every time you test a number, increment the counter
                    counter++;
                    //if putting this number on the board would not violate contraints
                    if(working(sudoku,x,y,insertnumber))
                    {
                        //update the board with the new number
                        sudoku[y][x]=insertnumber;
                        //if the new board is correct, meaning that putting this number on the board will eventually lead to the correct complete board
                        if(backtracking_helper(sudoku))
                        {
                            //ancestor of the complete board is also true
                            return true;
                        }
                        //if the new board does eventually lead to correct complete board, reset this box to 0 to allow next number to be inserted
                        sudoku[y][x]=0;
                    }
                }
                //if the board is false after trying all 9 possible numbers, the previous number shouldn't be put--> return false to end searching the parent board so can go back to the grandparent board
                return false;
            }
        }
    }
}

int sudoku_backtracking(int **sudoku)
{
    // PUT YOUR CODE HERE
    // access the sudoku using "sudoku[y][x]"
    // y between 0 and 9
    // x between 0 and 9
    // function must return the number of permutations performed
    
    //reset the counter to 0
    counter=0;
    //if there's a solution to the sudoku, return counter
    if(backtracking_helper(sudoku))
    {
        return counter;
    }
    //if there's no solution to the sudoku, return -1
    else
    {
        return -1;
    }
}

bool forwardtracking_helper(int **sudoku)
{
    //first check if the current board is complete, if so return true
    if(complete(sudoku))
    {
        return true;
    }
    // iterate through all boxes in the board
    for(int y=0; y<9; y++)
    {
        for(int x=0; x<9; x++)
        {
            //if the current box is empty
            if(sudoku[y][x]==0)
            {
                //iterate through each of the 9 numbers
                for(int insertnumber=1; insertnumber<10; insertnumber++)
                {
                    //if putting this number on the board would not violate contraints
                    if(working(sudoku,x,y,insertnumber))
                    {
                        //every time the new board works, increment the counter
                        counter++;
                        //update the board with the new number
                        sudoku[y][x]=insertnumber;
                        //if the new board is correct, meaning that putting this number on the board will eventually lead to the correct complete board
                        if(forwardtracking_helper(sudoku))
                        {
                            //ancestor of the complete board is also true
                            return true;
                        }
                        //if the new board does eventually lead to correct complete board, reset this box to 0 to allow next number to be inserted
                        sudoku[y][x]=0;
                    }
                }
                //if the board is false after trying all 9 possible numbers, the previous number shouldn't be put--> return false to end searching the parent board so can go back to the grandparent board
                return false;
            }
        }
    }
}

int sudoku_forwardchecking(int **sudoku)
{
    // PUT YOUR CODE HERE
    // access the sudoku using "sudoku[y][x]"
    // y between 0 and 9
    // x between 0 and 9
    // function must return the number of permutations performed
    
    //reset the counter to 0
    counter=0;
    //if there's a solution to the sudoku, return counter
    if(forwardtracking_helper(sudoku))
    {
        return counter;
    }
    //if there's no solution to the sudoku, return -1
    else
    {
        return -1;
    }
}

int totalconstraint(int **sudoku, int x, int y)
{
    //constraint is at most 9 if this box cannot be filled with any number
    int constraint=9;
    //check if there is contraint by iterating through each number
    for(int i=1; i<10; i++)
    {
        //check if this number works at this position
        if(working(sudoku,x,y,i))
        {
            //if so, decrement constraint
            constraint--;
        }
    }
    //return the number of constraints at this position
    return constraint;
}

bool mrv_helper(int **sudoku)
{
    //first check if the current board is complete, if so return true
    if(complete(sudoku))
    {
        return true;
    }
    //constraint checking
    int mostconstraint=0;
    int newx=-1;
    int newy=-1;
    //iterate through all 81 boxes to find the one with the most constraints
    for(int y=0; y<9; y++)
    {
        for(int x=0; x<9; x++)
        {
            //only count the ones that are empty
            if(sudoku[y][x]==0)
            {
                //store the number of constraints at this position
                int temp=totalconstraint(sudoku, x, y);
                //if there is a new box with more constaints, update mostconstraint to be this new box
                if(temp>mostconstraint)
                {
                    mostconstraint=temp;
                    newx=x;
                    newy=y;
                }
            }
        }
    }
    //iterating through all 9 numbers to insert at the most constraint spot
    for(int insertnumber=1; insertnumber<10; insertnumber++)
    {
        //if this number works at the most constraint spot
        if(working(sudoku,newx,newy,insertnumber))
        {
            //every time the new board works, increment the counter
            counter++;
            //update the board with the new number
            sudoku[newy][newx]=insertnumber;
            //if the new board is correct, meaning that putting this number on the board will eventually lead to the correct complete board
            if(mrv_helper(sudoku))
            {
                //ancestor of the complete board is also true
                return true;
            }
            //if the new board does eventually lead to correct complete board, reset this box to 0 to allow next number to be inserted
            sudoku[newy][newx]=0;
        }
    }
    //if this spot cannot be filled with any number, then the parent board must be wrong
    return false;
}

int sudoku_mrv(int **sudoku)
{
    // PUT YOUR CODE HERE
    // access the sudoku using "sudoku[y][x]"
    // y between 0 and 9
    // x between 0 and 9
    // function must return the number of permutations performed
    
    //reset the counter to 0
    counter=0;
    //if there's a solution to the sudoku, return counter
    if(mrv_helper(sudoku))
    {
        return counter;
    }
    //if there's no solution to the sudoku, return -1
    else
    {
        return -1;
    }
}
