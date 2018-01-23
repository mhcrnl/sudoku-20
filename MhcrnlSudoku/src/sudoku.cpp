/**
	@Author:	Mihai Cornel	Romania			mhcrnl@gmail.com
	@System:	Ubuntu 16.04	Code::Blocks 13.12	gcc 5.4.0
                Fedora 25	    Code::Blocks 16.01	gcc 5.3.1
                Windows Vista 	Code::Blocks 16.01
	@Copyright:	2018
	@file:
*/
#include "sudoku.h"

void fancy_line(){
    for(int j=0; j<=9; j++){
        if(j%3 == 0){
            cout<<"+";
        }
        if(j != 9) cout<<"-";
    }
    cout<<"\n";
}

sudoku::sudoku()
{
    //ctor
    cout<<"Sudoku class initialize grid array!"<<endl;
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            grid[i][j]=0;
}

sudoku::~sudoku()
{
    //dtor
}

void sudoku::draw(){
    cout<<"\n";
    for(int i=0; i<9; i++){
        cout<<"|";
        for(int j=0; j<9; j++){
            if(grid[i][j] == 0){
                cout<<" ";
            } else {
                cout<<grid[i][j];
            }
            if(j%3 == 2) cout << "|";
        }//for
        if(check_row(i)){
            cout<<" V\n";
        } else {
            cout<<" X\n";
        }
        if(i%3 == 2){
            fancy_line();
        }
    }//for
    cout<<" ";
    for(int j=0; j<9; j++){
        if(check_col(j)){
            cout<<"V";
        } else {
            cout<<"X";
        }
        if(j%3 == 2){
            cout<<" ";
        }
    }
    return;
}

bool sudoku::check_row(int row){
    int sum = 0;
    int check[9] = {0,0,0,0,0,0,0,0,0};

    for(int j=0; j<9; j++){
        if(grid[row][j] != 0)
            check[grid[row][j]-1] = 1;
    }//for
    for (int j =0; j<9; j++){
        sum = check[j]+ sum;
    }
    if(sum == 9){
        return true;
    }
    return false;
}

bool sudoku::check_col(int col){
    int sum = 0;
    int check[9] = {0,0,0,0,0,0,0,0,0};

    for(int i=0; i<9; i++){
        if(grid[i][col] != 0)
            check[grid[i][col]-1] = 1;
    }//for
    for (int i =0; i<9; i++){
        sum = check[i]+ sum;
    }
    if(sum == 9){
        return true;
    }
    return false;
}
