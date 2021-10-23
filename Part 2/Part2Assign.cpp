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

class Spot{
    private:
    Piece piece; 
    int column;
    int rank;
    bool occupied;

    public:

    Spot(int column,int rank,Piece piece){
        this.setPiece(piece);
        this.setRank(rank);
        this.setColumn(rank);
        occupySpot();
    }

    bool getOccupation(){
        return this.occupied;
    }

    void occupySpot(){
        occupied = true;
    }

    void unoccupySpot(){
        occupied = false;
    }

    Piece getPiece(){
        return this.piece;
    }

    void setPiece(Piece p){
       this.piece = p;
    }

    int getRank(){
        return this.rank;
    }
    void setRank(int r){
        rank = r;
    }

    int getColumn(){
        return column;
    }
    void setColumn(char c){
        column = c;
    }
};

class Piece{
    
    public:
    string position;
    int rank;
    int column;
    string colour;
    string type;

    string getPosition(){
        return position;
    }
    string getColour(){
        return colour;
    }
    string getType(){
        return type;
    }
    char getRank(){
        return rank;
    }
    int getColumn(){
        return column;
    }
};

class Board{

    public:
    Spot boxes[7][7];

    Board(){
        
        setBoard();
    }

    Spot getBox(int col, int rank){

        return boxes[rank][col];
        
    }

    void setBoard(){
        
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 7; j++){
                boxes[i][j] = new Spot(i,j,NULL);
            }
        }
    }

    
};

void setBoard(string fen){
    
}

bool my_cmp(const Piece& a, const Piece& b){
    
    // smallest comes first
    if(a.position.at(0) == b.position.at(0)){
        return a.position.at(1) < b.position.at(1);
    }

    return (int)a.position.at(0) < (int)b.position.at(0);
    
}

vector<string> possibleLionMoves(Board board, Piece piece){

    vector<string> possibleMoves;
    vector<char> c = {'a','b','c','d','e','f','g'};
    
    int col = 0;
    for(int i = 0; i < c.size(); i++){
        if(piece.getColumn() == c[i]){
            col = i;
        }
    }

    string currentPos = piece.getPosition();
    string ourColour = piece.getColour();
    string opponentColour;
    
    if(ourColour == "white"){
        opponentColour = "black";
    }

    else{
        opponentColour = "white";
    }

    int rank = piece.getRank();
    int col = piece.getColumn();

    //can we move up?
    if(rank < 7){

        //directly above:
        //is it occupied?
        if(board.getBox(col, rank+1).getOccupation() == true){

           Piece theAbovePiece = board.getBox(col, rank+1).getPiece();

           //check if the spot is ourColour or opponent's colour:
           if(theAbovePiece.getColour() == opponentColour){
                //vertically:
                string up = c[col] + to_string(rank+1);
                string possibleMove = currentPos + up;
                possibleMoves.push_back(possibleMove);
           }
        }

        //it's not occupied
        else{
            string up = c[col] + to_string(rank+1);
            string possibleMove = currentPos + up;
            possibleMoves.push_back(possibleMove);
        }

        //diagonally right:
        if(col < 7){

            //if it's occupied:
            if(board.getBox(col+1, rank+1).getOccupation() == true){

            Piece theDiagonallyAbovePiece = board.getBox(col+1, rank+1).getPiece();

                //check if the spot is ourColour or opponent's colour:
                if(theDiagonallyAbovePiece.getColour() == opponentColour){
                    string up = c[col+1] + to_string(rank+1);
                    string possibleMove = currentPos + up;
                    possibleMoves.push_back(possibleMove);
                }
            }

            //if it's not occupied
            else{
                string up = c[col+1] + to_string(rank+1);
                string possibleMove = currentPos + up;
                possibleMoves.push_back(possibleMove);
            }
        }
        
        //diagonally left:
        if(col > 0){
            
            //if it's occupied
            if(board.getBox(col-1, rank+1).getOccupation() == true){

                Piece theDiagonallyLeftPiece = board.getBox(col-1, rank+1).getPiece();

                    //check if the spot is ourColour or opponent's colour:
                    if(theDiagonallyLeftPiece.getColour() == opponentColour){
                        string up = c[col-1] + to_string(rank+1);
                        string possibleMove = currentPos + up;
                        possibleMoves.push_back(possibleMove);
                    }
            }

            //it's not occupied
            else{
                string up = c[col-1] + to_string(rank+1);
                string possibleMove = currentPos + up;
                possibleMoves.push_back(possibleMove);
            }
        }
    }

    //can we move down?
    if(rank > 0){

        //directly below:
        
        //check if the below spot is occupied
        if(board.getBox(col, rank-1).getOccupation() == true){

           Piece theBelowPiece = board.getBox(col, rank-1).getPiece();

            //vertically:
            if(theBelowPiece.getColour() == opponentColour){
                string down = c[col] + to_string(rank-1);
                string possibleMove = currentPos + down;
                possibleMoves.push_back(possibleMove);
            }
        }

        //not occupied
        else{
            string down = c[col] + to_string(rank-1);
            string possibleMove = currentPos + down;
            possibleMoves.push_back(possibleMove);
        }
        
        //diagonally left:
        if(col > 0){

            //if occupied
            if(board.getBox(col-1, rank-1).getOccupation() == true){

            Piece theDiagonallyBelowPiece = board.getBox(col-1, rank-1).getPiece();
                //vertically:
                if(theDiagonallyBelowPiece.getColour() == opponentColour){
                    string down = c[col-1] + to_string(rank-1);
                    string possibleMove = currentPos + down;
                    possibleMoves.push_back(possibleMove);
                }
            }

            //else not occupied:
            else{
                string down = c[col-1] + to_string(rank-1);
                string possibleMove = currentPos + down;
                possibleMoves.push_back(possibleMove);
            }
        }

        //diagonally right:
        if(col < 7){

            //if occupied
            if(board.getBox(col+1, rank-1).getOccupation() == true){

            Piece theDiagonallyBelowPiece = board.getBox(col+1, rank-1).getPiece();
                //vertically:
                if(theDiagonallyBelowPiece.getColour() == opponentColour){
                    string down = c[col+1] + to_string(rank-1);
                    string possibleMove = currentPos + down;
                    possibleMoves.push_back(possibleMove);
                }
            }

            //else not occupied
            else{
                string down = c[col+1] + to_string(rank-1);
                string possibleMove = currentPos + down;
                possibleMoves.push_back(possibleMove);
            }   
        }
    }

    //can we move left?
    if(col > 0){
        
        //check if the position is occupied:
        if(board.getBox(col-1, rank).getOccupation() == true){

            Piece theLeftSidePiece = board.getBox(col-1, rank).getPiece();
            
            if(theLeftSidePiece.getColour() == opponentColour){
                string left = c[col-1] + to_string(rank);
                string possibleMove = currentPos + left;
                possibleMoves.push_back(possibleMove);
            }
        }

        // else unoccupied:
        else{
            string left = c[col-1] + to_string(rank);
            string possibleMove = currentPos + left;
            possibleMoves.push_back(possibleMove);
        }
    }

    //can we move right?
    if(col < 7){
        //check if the position is occupied:
        if(board.getBox(col+1, rank).getOccupation() == true){

            Piece theRightSidePiece = board.getBox(col+1, rank).getPiece();
            
            //if it's the opponent colour
            if(theRightSidePiece.getColour() == opponentColour){
                string left = c[col+1] + to_string(rank);
                string possibleMove = currentPos + left;
                possibleMoves.push_back(possibleMove);
            }
        }

        // else unoccupied:
        else{
            string left = c[col+1] + to_string(rank);
            string possibleMove = currentPos + left;
            possibleMoves.push_back(possibleMove);
        }
    }

    //now we need to check if we can chow an opposing lion:

}


vector<string> possibleZebraMoves(Board board, Piece zebra){
    vector<string> possibleMoves;
    vector<char> c = {'a','b','c','d','e','f','g'};
    
   

    string currentPos = zebra.getPosition();
    string ourColour = zebra.getColour();
    string opponentColour;
    
    if(ourColour == "white"){
        opponentColour = "black";
    }

    else{
        opponentColour = "white";
    }

    int rank = zebra.getRank();
    int col = zebra.getColumn();

}

vector<string> getPossibleMoves(Board board, Piece piece){

    //we can abstract a lot away by creating smaller functions
    if(piece.getType() == "lion"){
        possibleLionMoves(board, piece);
    }

    if(piece.getType() == "zebra"){
        possibleZebraMoves(board, piece);
    }
}

void output(vector<Piece> all_pieces, Board board){

    
    vector<Piece>w_pawns;
    vector<Piece>b_pawns;
    vector<Piece>w_spawns;
    vector<Piece>b_spawns;
    vector<Piece>w_giraffe;
    vector<Piece>b_giraffe;
    vector<Piece>w_monkey;
    vector<Piece>b_monkey;
    vector<Piece>w_elephant;
    vector<Piece>b_elephant;
    vector<Piece>w_lion;
    vector<Piece>b_lion;
    vector<Piece>w_crocodile;
    vector<Piece>b_crocodile;
    vector<Piece>w_zebra;
    vector<Piece>b_zebra;

    // all_pieces = bubble_sort(all_pieces);
    for(int i = 0; i < all_pieces.size(); i++){


        if(all_pieces.at(i).getType() == "pawn"){
            if((all_pieces.at(i).getCol()) == "white"){

                w_pawns.push_back(all_pieces.at(i));    

            }
            else{

                b_pawns.push_back(all_pieces.at(i));

            }
        }
        else if(all_pieces.at(i).getType() == "superpawn"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_spawns.push_back(all_pieces.at(i));

            }
            else{

                b_spawns.push_back(all_pieces.at(i));

            }

        }
        else if(all_pieces.at(i).getType() == "monkey"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_monkey.push_back(all_pieces.at(i));

            }
            else{

                b_monkey.push_back(all_pieces.at(i));

            }

        }
        else if(all_pieces.at(i).getType() == "giraffe"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_giraffe.push_back(all_pieces.at(i));

            }
            else{

                b_giraffe.push_back(all_pieces.at(i));

            }

        }
        else if(all_pieces.at(i).getType() == "elephant"){

            if((all_pieces.at(i).getCol()) == "white"){

                w_elephant.push_back(all_pieces.at(i));
            }
            else{

                b_elephant.push_back(all_pieces.at(i));

            }
            
        }
        else if(all_pieces.at(i).getType() == "lion" ){

            if((all_pieces.at(i).getCol()) == "white"){

                w_lion.push_back(all_pieces.at(i));

            }
            else{

                b_lion.push_back(all_pieces.at(i));

            }
            
        }
        else if(all_pieces.at(i).getType() == "crocodile" ){

            if((all_pieces.at(i).getCol()) == "white"){

                w_crocodile.push_back(all_pieces.at(i));

            }
            else{

                b_crocodile.push_back(all_pieces.at(i));

            }
            
        }
        else if(all_pieces.at(i).getType() == "zebra" ){

            if((all_pieces.at(i).getCol()) == "white"){
                
                w_zebra.push_back(all_pieces.at(i));

            }
            else{

                b_zebra.push_back(all_pieces.at(i));

            }
            
        }

    }


    cout << "white pawn:";

    sort(w_pawns.begin(), w_pawns.end(), my_cmp);
    for(int i = 0; i < w_pawns.size(); i++){
        cout << " " << w_pawns.at(i).getPos();
    }

    cout << endl;
    cout << "black pawn:";

    sort(b_pawns.begin(), b_pawns.end(), my_cmp);
    for(int i = 0; i < b_pawns.size(); i++){
        cout << " " << b_pawns.at(i).getPos();
    }

    cout << endl;
    cout << "white superpawn:";

    sort(w_spawns.begin(), w_spawns.end(), my_cmp);
    for(int i = 0; i < w_spawns.size(); i++){
        cout << " " << w_spawns.at(i).getPos();
    }

    cout << endl;
    cout << "black superpawn:";

    sort(b_spawns.begin(), b_spawns.end(), my_cmp);
    for(int i = 0; i < b_spawns.size(); i++){
        cout << " " << b_spawns.at(i).getPos();
    }

    cout << endl;
    cout << "white giraffe:";

    sort(w_giraffe.begin(), w_giraffe.end(), my_cmp);
    for(int i = 0; i < w_giraffe.size(); i++){
        cout << " " << w_giraffe.at(i).getPos();
    }

    cout << endl;
    cout << "black giraffe:";

    sort(b_giraffe.begin(), b_giraffe.end(), my_cmp);
    for(int i = 0; i < b_giraffe.size(); i++){
        cout << " " << b_giraffe.at(i).getPos();
    }

    cout << endl;
    cout << "white monkey:";

    sort(w_monkey.begin(), w_monkey.end(), my_cmp);
    for(int i = 0; i < w_monkey.size(); i++){
        cout << " " << w_monkey.at(i).getPos();
    }

    cout << endl;
    cout << "black monkey:";

    sort(b_monkey.begin(), b_monkey.end(), my_cmp);
    for(int i = 0; i < b_monkey.size(); i++){
        cout << " " << b_monkey.at(i).getPos();
    }

    cout << endl;
    cout << "white elephant:";
    
    sort(w_elephant.begin(), w_elephant.end(), my_cmp);
    for(int i = 0; i < w_elephant.size(); i++){
        cout << " " << w_elephant.at(i).getPos();
    }

    cout << endl;
    cout << "black elephant:";

    sort(b_elephant.begin(), b_elephant.end(), my_cmp);
    for(int i = 0; i < b_elephant.size(); i++){
        cout << " " << b_elephant.at(i).getPos();
    }

    cout << endl;
    cout << "white lion:";

    sort(w_lion.begin(), w_lion.end(), my_cmp);
    for(int i = 0; i < w_lion.size(); i++){
        cout << " " << w_lion.at(i).getPos();
    }

    cout << endl;
    cout << "black lion:";

    sort(b_lion.begin(), b_lion.end(), my_cmp);
    for(int i = 0; i < b_lion.size(); i++){
        cout << " " << b_lion.at(i).getPos();
    }

    cout << endl;
    cout << "white crocodile:";

    sort(w_crocodile.begin(), w_crocodile.end(), my_cmp);
    for(int i = 0; i < w_crocodile.size(); i++){
        cout << " " << w_crocodile.at(i).getPos();
    }

    cout << endl;
    cout << "black crocodile:";

    sort(b_crocodile.begin(), b_crocodile.end(), my_cmp);
    for(int i = 0; i < b_crocodile.size(); i++){
        cout << " " << b_crocodile.at(i).getPos();
    }

    cout << endl;
    cout << "white zebra:";

    for(int i = 0; i < w_zebra.size(); i++){
        cout << " " << w_zebra.at(i).getPos();
    }

    cout << endl;
    cout << "black zebra:";

    for(int i = 0; i < b_zebra.size(); i++){
        cout << " " << b_zebra.at(i).getPos();
    }

} 

string whatsThePiece(char piece){

    if(piece == 'l' || piece == 'L'){
        return "lion";
    }
    else if(piece == 'p' || piece == 'P'){
        return "pawn";
    }
    else if(piece == 'm' || piece == 'M'){
        return "monkey";
    }
    else if(piece == 'e' || piece == 'E'){
        return "elephant";
    }

    else if (piece == 'c' || piece == 'C'){
        return "crocodile";
    }
    else if (piece == 'z' || piece == 'Z'){
        return "zebra";
    }
    else if(piece == 'g' || piece == 'G'){
        return "giraffe";
    }
    else if(piece == 's' || piece == 'S'){
        return "superpawn";
    }
}

vector<Piece> postionPiece(string locationPiece, Board &board){

    board.setBoard();
    int rank = 6;
    int num = 0;
    char col[] = {'a','b','c','d','e','f','g'};
    vector<Piece> pieces;

    for(int i = 0; i < locationPiece.size(); i++){

        if(locationPiece[i] == '/'){

            rank=rank-1;
            num = 0;
        }

        else if (isdigit(loc_pie[i]) == true){

            string c = {loc_pie[i]};
            istringstream input(c);
            int value;
            input >> value;
            num = num + value;
        }

        else{
            
            Piece p1;
            if(isupper(loc_pie[i])){
                
                // Piece Initialisation
                p1.colour = "white";
                p1.type = whatsThePiece(loc_pie[i]);
                string pos = {col[num]};
                p1.column = col[num];
                p1.rank = rank+1;
                pos.append(to_string(rank+1));
                p1.position = pos;

                // Spot Initialisation
                Spot piece_block;
                piece_block.setColumn(colum);
                piece_block.setRank(rank);
                piece_block.setPiece(p1);

                board[num][rank+1]= piece_block; 

                num = num +1;

            }
            else{
                // Piece Initialisation
                p1.colour = "black";
                p1.type = whatsThePiece(loc_pie[i]);
                string pos = {col[num]};
                p1.column = col[num];
                p1.rank = rank+1;
                pos.append(to_string(rank+1));
                p1.position = pos;


                // Spot Initialisation
                Spot piece_block;
                piece_block.setColumn(column);
                piece_block.setRank(rank);
                piece_block.setPiece(p1);
                board.getBox(column,rank) = piece_block; 

                num = num +1;


            }
            pieces.push_back(p1);
        }
        
    }

    return(pieces);


}

int main(){

    int no_lines;
    cin >> no_lines;
    string fen_string,fen;
    vector<string> list_fen;

    for(int i = 0; i <= no_lines; i++){
        getline(cin,fen_string);
        fen = " " + fen_string;
        istringstream input(fen);
        string value;

        while(input >> value){
            list_fen.push_back(value);
        }
    }

    for(int i = 0; i < list_fen.size(); i = i +3){
        Board board;
        vector<Piece>ieces = posi_piece(list_fen.at(i),board);
        output(ieces, board);

        cout << endl;
        if(list_fen.at(i+1) == "w"){
            cout << "side to play: " << "white" << endl;
        }
        else if(list_fen.at(i+1) == "b"){
            cout << "side to play: " << "black" << endl;

        }
        cout << endl;
        ieces.clear();
        
    }
}