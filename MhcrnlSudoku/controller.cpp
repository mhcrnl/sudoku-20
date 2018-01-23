/**
	@Author:	Mihai Cornel	Romania			mhcrnl@gmail.com
	@System:	Ubuntu 16.04	Code::Blocks 13.12	gcc 5.4.0
                Fedora 25	    Code::Blocks 16.01	gcc 5.3.1
                Windows Vista 	Code::Blocks 16.01
	@Copyright:	2018
	@file:
*/
#include "controller.h"

void controller(sudoku &sudo){
    char comanda = ' ';

    cout<<"Salut! Din linia de comanda a jocului Sudoku!"<<endl;

    while(comanda != 'X'){
        comanda = meniu();
        switch(comanda){
            case 'D':
                cout<<"Acesta este Sudoku:"<<endl;
                sudo.draw();
                break;

        }
    }
}
/**
    Return char comanda and print meniu
*/
char meniu(){
    char comanda = ' ';

    cout<<"\t\t1.[D]raw"<<endl;
    cout<<"\t\t5.E[X]it"<<endl;

    while((comanda == toupper(comanda))&&(comanda == tolower(comanda))){
        cin.get(comanda);
    }
    return comanda;
}
