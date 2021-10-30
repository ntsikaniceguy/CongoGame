#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include <random>
#include <list>
#include<tuple>
#include <chrono>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include<string.h>
#include<ctype.h>
#include <algorithm>
using std::istringstream;
using namespace std::chrono;
using namespace std;

void printVector(vector<string> v){

    if(v.size() == 0){
        return;
    }

    if(v.size() == 1){
        cout << v[0] << endl;
    }

    if(v.size() == 2){
        cout << v[0] << " " << v[1] << endl;
    }

    else if(v.size() > 2){

        cout << v[0];

        for(int i = 1; i < v.size() - 1; i++){
            cout << " " << v[i];
        }

        cout << " " << v[v.size()-1] << endl;
    }
}

void vectorToFile(vector<string> v){

    fstream myfile;
    myfile.open("log.txt", fstream::app);

    if(v.size() == 1){
        myfile << v[0] << endl;
    }

    if(v.size() == 2){
        myfile << v[0] << " " << v[1] << endl;
    }

    else if(v.size() > 2){

        myfile << v[0];

        for(int i = 1; i < v.size() - 1; i++){
            myfile << " " << v[i];
        }
        
        myfile << " " << v[v.size()-1] << endl;
    }

    myfile.close();
}

vector<string> tokenize(string s, string del = "/"){

    vector<string> row;

    int start = 0;
    int end = s.find(del);

    while(end != -1){
        row.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }

    row.push_back(s.substr(start, end - start));

    return row;

}

vector<string> readline(int lineSize){
    vector<string> vec;

    for(int i = 0; i < lineSize; i++){
        string n;
        cin >> n;
        vec.push_back(n);
    }

    return vec;
}

bool isStringNumber(char c){

    if(c <'0' || c >'9'){
        return false;
    }
    
    return true; 
}

vector<vector<char>> makeBoard(vector<string> boardSetup){

    //we're gonna start from the top and work down
    int row = 6;

    //just believe in Allah!
    vector<vector<char> > board;

    while(row >= 0){

        int column = 0;

        //initialise empty row
        vector<char> temp = {'0', '0', '0', '0', '0', '0', '0'};

        string s = boardSetup.at(6 - row);

        //empty row
        if(s == "7"){
            board.push_back(temp);
        }

        //populate row
        else{

            for(char c : s){

                //these are empty spaces
                if(isStringNumber(c)){
                    int n = c - '0';
                    column += n;
                }

                else{
                    temp.at(column) = (char)c;
                    column = column + 1;
                }
            }

            board.push_back(temp);
        }

        row = row - 1;
    }

    return board;

}

vector<int> getPosition(vector<vector<char> > board, char piece){

    vector<int> position;
    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){
            if(board.at(row).at(col) == piece){
                position.push_back(row);
                position.push_back(col);
                return position; //return the coordinates wrt how we access arrays in c++
            }
        }
    }

    return position;

}

static std::string removeSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}



vector<string> possibleLionMoves(vector<vector<char>> board, char piece){

    vector<string> column = {"a", "b", "c", "d", "e", "f,", "g"};
    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<string> possibleMoves;

    vector<int> position = getPosition(board, piece);

    if(position.size() == 0){
        return possibleMoves;
    }

    int row = position[0];
    int col = position[1];
    string ourColour;
    string opponentColour;

    string boardPosition = column.at(col) + to_string(rank.at(row)); //this holds the position wrt how we will display it

    
    //can we move up:
    //we can only (potentially) move up if we're not on the top row already

    //black 
    if(islower(piece)){

        if(row > 0){
            //either straight up
            //then we need to check if there's a piece above us:
            if(board[row-1][col] == '0'){
            // cout << "nope! no piece here. straight above " << endl;
                //if the answer is no, we can make this move
                string up = column.at(col) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + up;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece above us
            else{
                //cout << "oops! looks like someone's already here. straight above" << endl;
                //check if the piece is the same colour or opposite colour:
                char above = board.at(row-1).at(col);

                if( isupper(above) ){
                // cout << "this is an opp!" << endl;
                    string up = column.at(col) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + up;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //left diagonally up
            //can we even move left?
            if(col > 2){
                //check if there's a piece there:
                if(board[row-1][col-1] == '0'){
                    //cout << "nope! no piece here. left diagonally up" << endl;
                    //if the answer is no, we can make this move
                    string upLeft = column[col-1] + to_string(rank[row-1]);
                    string possibleMove = boardPosition + upLeft;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //check if the piece is the same colour or opposite colour:
                // cout << "oops! looks like someone's already here. left diagonally up " << endl;
                    char above = board[row-1][col-1];
                    

                    if( isupper(above) ){
                        //cout << "this is an opp!" << endl;
                        string upLeft = column[col-1] + to_string(rank[row-1]);
                        string possibleMove = boardPosition + upLeft;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //right diagonally up
            //can we even move right?
            if(col < 4){
                //check if there's a piece there:
                if(board[row-1][col+1] == '0'){
                    //if the answer is no, we can make this move
                    //cout << "nope! no piece here. right diagonally up" << endl;
                    string upRight = column[col+1] + to_string(rank[row-1]);

                    string possibleMove = boardPosition + upRight;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //cout << "oops! some piece already right. left diagonally up" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board[row-1][col+1];

                    if( isupper(above) ){
                    // cout << "this is an opp!" << endl;
                        string upRight = column[col+1] + to_string(rank[row-1]);
                        string possibleMove = boardPosition + upRight;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }
        }

        //can we move down:
        if(row < 2){

            //either straight down
            //then we need to check if there's a piece below us:
            if(board[row+1][col] == '0'){

                //cout << "nope! no piece here. straight down" << endl;
                //if the answer is no, we can make this move
                string down = column[col] + to_string(rank[row+1]);
                string possibleMove = boardPosition + down;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece below us
            else{
                //cout << "oops! some piece already here here. straight down" << endl;
                //check if the piece is the same colour or opposite colour:
                char below = board[row+1][col];

                if( isupper(below) ){
                    string down = column[col] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + down;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //left diagonally down
            //can we even move left?
            if(col > 2){
                //check if there's a piece there:
                if(board[row+1][col-1] == '0'){
                // cout << "nope! no piece here. left diagonally down" << endl;
                    //if the answer is no, we can make this move
                    string downLeft = column.at(col-1) + to_string(rank.at((row+1)));
                    string possibleMove = boardPosition + downLeft;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                // cout << "oops! some piece already here. left diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board[row+1][col-1];
                    

                    if( isupper(above)){
                        string downLeft = column.at(col-1) + to_string(rank.at(row+1));
                        string possibleMove = boardPosition + downLeft;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //right diagonally down
            //can we even move right?
            if(col < 4){
                //check if there's a piece there:
                if(board[row+1][col+1] == '0'){
                //  cout << "nope! no piece here. right diagonally down" << endl;
                    //if the answer is no, we can make this move
                    string downRight = column[col+1] + to_string(rank[row+1]);
                    string possibleMove = boardPosition + downRight;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                // cout << "oops! piece here. right diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char below = board[row+1][col+1];
                   
                    if( isupper(below) ){
                        string downRight = column[col+1] + to_string(rank[row+1]);
                        string possibleMove = boardPosition + downRight;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }
        }

        //can we move horizontally left?
        if(col > 2){
            //check if there's a piece there:
            if(board[row][col-1] == '0'){
                //cout << "nope! no piece here. left horizontally" << endl;
                //if the answer is no, we can move w there no problem
                
                string left = column[col-1] + to_string(rank[row]);
                string possibleMove = boardPosition + left;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. left horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char left = board.at(row).at(col-1);
    
                if( isupper(left) ){
                    string left = column.at(col-1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + left;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }

        //can we move horizontally right?
        if(col < 4){
            //check if there's a piece there:
            if(board.at(row).at(col+1) == '0'){
                //cout << "nope! no piece here. horizontally right" << endl;
                //if the answer is no, we can move w there no problem
                string right = column.at(col+1) + to_string(rank.at(row));
                string possibleMove = boardPosition + right;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. right horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char right = board.at(row).at(col+1);
                
                //we know we're black
                if( isupper(right) ){
                    string right = column.at(col+1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + right;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

        }

        //lion to lion:
        vector<int> otherLionPosition = getPosition(board, 'L');

      //  cout << "BEFORE: \n";
        int otherLionRow = otherLionPosition[0];
        int otherLionCol = otherLionPosition[1];
     //   cout << "other lion row: " << otherLionRow <<"\t" << "other lion col: " << otherLionCol << endl;;
        

        string stringOtherLionPosition = column[otherLionCol] + to_string(rank[otherLionRow]);
     //   cout << "Other Lion Position: " << stringOtherLionPosition << endl;
        // if we are in the same column
        if(otherLionCol == col){

            bool canAttack = true;
            //if it's above us
            for(int i = row+1; i < otherLionRow; i++){
                if(board[i][col] != '0'){
                    canAttack = false;
                }
            }

            if(canAttack){
                string possibleMove = boardPosition +  stringOtherLionPosition;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }

        //if it's a diagonal ting going on:
        if(otherLionRow == row+2){
            //to the right
            // cout << "AFTER: \n";
            // cout << "other lion row: " << otherLionRow <<"\t" << "other lion col: " << otherLionCol << endl;
            if(col + 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row+1).at(col+1) == '0'){
                    cout << "This is where it's happening" << endl;
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //to the left
            if(col - 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row+1).at(col-1) == '0'){
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    //else:
    else{
        //going up
        if(row > 4){
            //either straight up
            //then we need to check if there's a piece above us:
            if(board.at(row-1).at(col) == '0'){
            // cout << "nope! no piece here. straight above " << endl;
                //if the answer is no, we can make this move
                string up = column.at(col) + to_string(rank.at(row-1));
                string possibleMove = boardPosition + up;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece above us
            else{
                //cout << "oops! looks like someone's already here. straight above" << endl;
                //check if the piece is the same colour or opposite colour:
                char above = board.at(row-1).at(col);
                
                //we know we're white
                if( islower(above) ){
                // cout << "this is an opp!" << endl;
                    string up = column.at(col) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + up;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //left diagonally up
            //can we even move left?
            if(col > 2){
                //check if there's a piece there:
                if(board.at(row-1).at(col-1) == '0'){
                    //cout << "nope! no piece here. left diagonally up" << endl;
                    //if the answer is no, we can make this move
                    string upLeft = column.at(col-1) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + upLeft;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //check if the piece is the same colour or opposite colour:
                // cout << "oops! looks like someone's already here. left diagonally up " << endl;
                    char above = board.at(row-1).at(col-1);
                    
                    //we know we're white
                    if( islower(above) ){
                        //cout << "this is an opp!" << endl;
                        string upLeft = column.at(col-1) + to_string(rank.at(row-1));
                        string possibleMove = boardPosition + upLeft;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //right diagonally up
            //can we even move right?
            if(col < 4){
                //check if there's a piece there:
                if(board.at(row-1).at(col+1) == '0'){
                    //if the answer is no, we can make this move
                    //cout << "nope! no piece here. right diagonally up" << endl;
                    string upRight = column.at(col+1) + to_string(rank.at(row-1));
                    string possibleMove = boardPosition + upRight;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    //cout << "oops! some piece already right. left diagonally up" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board.at(row-1).at(col+1);
                    
                    //we know we're white
                    if( islower(above) ){
                    // cout << "this is an opp!" << endl;
                        string upRight = column.at(col+1) + to_string(rank.at((row-1)));
                        string possibleMove = boardPosition + upRight;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }
        }

        //can we move down:
        if(row < 6){

            //either straight down
            //then we need to check if there's a piece below us:
            if(board.at(row+1).at(col) == '0'){

                //cout << "nope! no piece here. straight down" << endl;
                //if the answer is no, we can make this move
                string down = column.at(col) + to_string(rank.at(row+1));
                string possibleMove = boardPosition + down;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //else there is a piece below us
            else{
                //cout << "oops! some piece already here here. straight down" << endl;
                //check if the piece is the same colour or opposite colour:
                char below = board.at(row+1).at(col);
                

                if( islower(below) ){
                    string down = column.at(col) + to_string(rank.at(row+1));
                    string possibleMove = boardPosition + down;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //left diagonally down
            //can we even move left?
            if(col > 2){
                //check if there's a piece there:
                if(board.at(row+1).at(col-1) == '0'){
                // cout << "nope! no piece here. left diagonally down" << endl;
                    //if the answer is no, we can make this move
                    string downLeft = column.at(col-1) + to_string(rank.at((row+1)));
                    string possibleMove = boardPosition + downLeft;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                // cout << "oops! some piece already here. left diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char above = board.at(row+1).at(col-1);
                    
                    //we know we are white
                    if( islower(above) ){
                        string downLeft = column.at(col-1) + to_string(rank.at(row+1));
                        string possibleMove = boardPosition + downLeft;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }

            //right diagonally down
            //can we even move right?
            if(col < 4){
                //check if there's a piece there:
                if(board.at(row+1).at(col+1) == '0'){
                //  cout << "nope! no piece here. right diagonally down" << endl;
                    //if the answer is no, we can make this move
                    string downRight = column.at(col+1) + to_string(rank.at(row+1));
                    string possibleMove = boardPosition + downRight;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }

                //there's a piece there
                else{
                    // cout << "oops! piece here. right diagonally down" << endl;
                    //check if the piece is the same colour or opposite colour:
                    char below = board.at(row+1).at(col+1);
                    
                    //we know we're white
                    if( islower(below)){
                        string downRight = column.at(col+1) + to_string(rank.at(row+1));
                        string possibleMove = boardPosition + downRight;
                        removeSpaces(possibleMove);
                        possibleMoves.push_back(possibleMove);
                    }
                }
            }
        }

        //can we move horizontally left?
        if(col > 2){
            //check if there's a piece there:
            if(board.at(row).at(col-1) == '0'){
                //cout << "nope! no piece here. left horizontally" << endl;
                //if the answer is no, we can move w there no problem
                
                string left = column.at(col-1) + to_string(rank.at(row));
                string possibleMove = boardPosition + left;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. left horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char left = board.at(row).at(col-1);
        
                if( islower(left) ){
                    string left = column.at(col-1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + left;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }

        //can we move horizontally right?
        if(col < 4){
            //check if there's a piece there:
            if(board.at(row).at(col+1) == '0'){
                //cout << "nope! no piece here. horizontally right" << endl;
                //if the answer is no, we can move w there no problem
                string right = column.at(col+1) + to_string(rank.at(row));
                string possibleMove = boardPosition + right;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }

            //the position is occupied
            else{
                //cout << "oops! piece here. right horizontally" << endl;
                //check if the piece is the same colour as our piece:
                char right = board.at(row).at(col+1);
                
                if( islower(right) ){
                    string right = column.at(col+1) + to_string(rank.at(row));
                    string possibleMove = boardPosition + right;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

        }

        //lion to lion:
        vector<int> otherLionPosition = getPosition(board, 'l');

        int otherLionRow = otherLionPosition[0];
        int otherLionCol = otherLionPosition[1];

        string stringOtherLionPosition = column.at(otherLionCol) + to_string(rank.at(otherLionRow));
       // cout << "other Lion position: " << stringOtherLionPosition << endl;

        // if we are in the same column
        if(otherLionCol == col){

            bool canAttack = true;
            //if it's above us
            for(int i = row-1; i > otherLionRow; i--){
                if(board[i][col] != '0'){
                    canAttack = false;
                }
            }

            if(canAttack){
                string possibleMove = boardPosition +  stringOtherLionPosition;
                removeSpaces(possibleMove);
                possibleMoves.push_back(possibleMove);
            }
        }


        //if it's a diagonal ting going on:
        if(row - 2 == otherLionRow){
            //to the right
            if(col + 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row-1).at(col+1) == '0'){
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }

            //to the left
            if(col - 2 == otherLionCol){
                //check if anything is in the way
                if(board.at(row-1).at(col-1) == '0'){
                    string possibleMove = boardPosition + stringOtherLionPosition;
                    removeSpaces(possibleMove);
                    possibleMoves.push_back(possibleMove);
                }
            }
        }
    }

    

    sort(possibleMoves.begin(), possibleMoves.end());

    return possibleMoves;

}

vector<string> getPossibleMoves(vector<vector<char> > board, char piece){

    if(piece == 'l' || piece == 'L'){
        return possibleLionMoves(board, piece);
    }
}

void print2DVector(vector<vector<char> > my2DArray, int height, int width){

    vector<int> rank = {7, 6, 5, 4, 3, 2, 1};
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    for (int h = 0; h < height; h++){

        cout << rank[h] << " ";
        for (int w = 0; w < width; w++)
        {  
            char c = (char)my2DArray[h][w];
            cout << c << " ";
        }
        cout << endl;
    }

    cout << "  ";

    for(char c : column){
        cout << c << " ";
    }

    cout << endl;
}
 

int main(){

    int nLines;

    cin >> nLines;

    vector<vector<string> > allPossibleMoves;
    for(int i = 0; i < nLines; i++){
    
        //fenString vector will look something like this:
        //{2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z, w, 4}
        vector<string> fenString = readline(3);

        //the board is setup occording to fenstring[0] of course
        vector<string> boardSetup = tokenize(fenString.at(0), "/");

        //this creates the 2D char vector of the board
        vector<vector<char> > thisBoard = makeBoard(boardSetup);

        // print2DVector(thisBoard, 7, 7);
        // cout << endl;

        //this gets the colour's turn
        char l = fenString.at(1).at(0);

        if(l == 'b'){
            allPossibleMoves.push_back( possibleLionMoves(thisBoard, 'l') );
        }

        if(l == 'w'){
            allPossibleMoves.push_back( possibleLionMoves(thisBoard, 'L') );
        }
    }

    //output all the possible moves for each input
    for(vector<string> v : allPossibleMoves)
    {
        vectorToFile(v);
        printVector(v);
    }

}