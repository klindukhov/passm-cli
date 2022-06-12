#include <iostream>
#include <vector>

#include "Password.h"

using namespace std;

vector<Password>  parseFile(){
    return  {
            Password("a", "johndoe", "aaaaaaaaaaaa"),
            Password("b", "johndoe", "bbbbbbbbbbbbb"),
            Password("c", "johndoe", "ccccccccccccc"),
            Password("d", "johndoe", "dddddddddddd"),
            Password("e", "johndoe", "eeeeeeeeeeeeee"),
            Password("j", "johndoe", "jjjjjjjjjjjjjj")
    };
}

int getOptionInput(){
    cout << "(1)Search for passwords" << endl;
    cout << "(2)Sort passwords" << endl;
    cout << "(3)Add a password" << endl;
    cout << "(4)Edit a password" << endl;
    cout << "(5)Remove a password" << endl;
    cout << "(6)Add a category" << endl;
    cout << "(7)Remove a category" << endl;
    cout << "(0)Exit" << endl;
    int i;
    cin >> i;
    return i;
}

string searchPass(){
    cout<<"searchPass";
    return "searchPass";
}

void sortPass(){cout<<"sortPass";}
void addPass(){cout<<"addPass";}
void editPass(){cout<<"editPass";}
void removePass(){cout<<"removePass";}
void addCategory(){cout<<"addCategory";}
void removeCategory(){cout<<"removeCategory";}

void optionController(vector<Password> passwords){
    bool run = true;
    while(run){
        switch (getOptionInput()) {
            case 1:
                searchPass();
                break;
            case 2:
                sortPass();
                break;
            case 3:
                addPass();
                break;
            case 4:
                editPass();
                break;
            case 5:
                removePass();
                break;
            case 6:
                addCategory();
                break;
            case 7:
                removeCategory();
                break;
            case 0:
                cout << "terminating...";
                run = false;
                break;
            default:
                cout << "Invalid input, try again" << endl;
        }
    }
}

int main() {
    cout << "Enter the path to the password file, leave empty if there is no such file" << std::endl;
    string path;
    cin >> path;
    //TODO validate the path
    //TODO parse the path
    cout << "Enter the master password" << endl;
    //TODO change console input mode
    string masterPass;
    cin >> masterPass;
    //TODO validate password
    cout << "timestamp" << endl; //TODO
    optionController(parseFile());
    return 0;
}



