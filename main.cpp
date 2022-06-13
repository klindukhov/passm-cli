#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Password.h"

using namespace std;

char getOptionInput(){
    cout << "(1)Search for passwords" << endl;
    cout << "(2)Sort passwords" << endl;
    cout << "(3)Add a password" << endl;
    cout << "(4)Edit a password" << endl;
    cout << "(5)Remove a password" << endl;
    cout << "(6)Add a category" << endl;
    cout << "(7)Remove a category" << endl;
    cout << "(q)Exit" << endl;
    char i;
    cin >> i;
    return i;
}

void searchPass(){
    cout<< "Enter partial or full name of the password" << endl;
    string searchQuery;
    cin >> searchQuery;
    vector<Password> passwords = Password::getPasswordByName(searchQuery);
    cout << "/name/category/username/password" << endl;
    for(auto p: passwords){
        cout << ">" << p;
    }
    cout << endl;
    cout<< "(q) exit to main menu" << endl << "(s) another search" << endl;
    char s;
    cin>>s;
    if(s == 's'){
        searchPass();
    }
    cout << endl;
}

void sortPass(){
    cout<< "Sorting by name:" << endl;
    cout<< "(1)Ascending" << endl;
    cout<< "(2)Descending" << endl;
    int i;
    cin >> i;
    vector<Password> passwords = Password::getPasswords(i);
    for(auto p: passwords){
        cout << p;
    }
    cout<< "Press Enter to exit to main menu" << endl;
    cin.get();
    cin.get();
    cout << endl;
}

void addPass(){
    //TODO add category choice
    cout << "Enter name of the password" << endl;
    string name;
    cin >> name;
    cout << "Enter category of the password, leave empty for 'none'" << endl;
    string category;
    cin >> category;
    cout << "Enter login for the password" << endl;
    string login;
    cin >> login;
    cout << "Enter the password" << endl;
    string password;
    cin >> password;
    Password::addPassword(Password(name,category,login,password));
    cout << "Password added" << endl <<  "(q) exit to the main menu" << endl << "(a) add another password"<< endl;
    char a;
    cin >> a;
    if(a == 'a'){
        addPass();
    }
}

void editPass(){
    //TODO add category choice
    vector<Password> passwords = Password::getPasswords();
    int n = 0;
    for(auto p: passwords){
        cout << ">" << '(' << n << ')' << p;
        n++;
    }
    cout << "Enter the number of the password you want to edit" << endl;
    int i;
    cin >> i;
    cout << "(n)name" << endl << "(c)category" << endl << "(l)login" << endl << "(p)password" << endl;
    cout << "Choose what you want to change" << endl;
    char a;
    cin >> a;
    string s;
    Password p = passwords.at(i);
    switch(a){
        case 'n':
            cout << "Enter new name" << endl;
            cin >> s;
            p.setName(s);
            break;
        case 'c':
            cout << "Enter new category" << endl;
            cin >> s;
            p.setCategory(s);
            break;
        case 'l':
            cout << "Enter new login" << endl;
            cin >> s;
            p.setLogin(s);
            break;
        case 'p':
            cout << "Enter new password" << endl;
            cin >> s;
            p.setPass(s);
            break;
    }
    Password::editPassword(p, i);
    cout << "Password edited" << endl << "(q)exit to the main menu" << endl << "(e)edit another password" << endl;
    char c;
    cin >> c;
    if(c =='e'){editPass();}
}

void removePass(){
    vector<Password> passwords = Password::getPasswords();
    int n = 0;
    for(auto p: passwords){
        cout << ">" << '(' << n << ')' << p;
        n++;
    }
    cout << "Enter the number of the password you want to delete" << endl;
    int index;
    cin >> index;

    char c;
    bool yn = true;
    while(yn){
        cout << "Do you want to delete password " << passwords.at(index) << " ?(Y/N)";
        cin >> c;
        if(c == 'Y' || c == 'y'){
            Password::rmPassword(passwords.at(index));
            cout << "Password deleted" << endl;
            yn = false;
        }else if(c== 'N' || c == 'n'){
            cout<<"Password deletion cancelled" << endl;
            yn = false;
        }
    }
}

void addCategory(){
    cout<<"Enter the name of the category"<<endl;
    string name;
    cin >> name;
    Password::addCategory(name);
    cout << "Category added" << endl <<  "(q) exit to the main menu" << endl << "(a) add another category"<< endl;
    char a;
    cin >> a;
    if(a == 'a'){
        addCategory();
    }
}

void removeCategory(){
    vector<string> cats = Password::getCategories();
    int n = 0;
    cout << "Enter the number of category you want to delete" << endl;
    for(auto c: cats){
        cout << '(' << n << ')' << c << endl;
        n++;
    }
    int i;
    cin >> i;
    Password::rmCategory(cats.at(i));
    cout << "Category deleted" << endl <<  "(q) exit to the main menu" << endl << "(a) delete another category"<< endl;
    char a;
    cin >> a;
    if(a == 'a'){
        removeCategory();
    }
    //TODO fix a bug with empty numbered line
}

void optionController(){
    bool run = true;
    while(run){
        switch (getOptionInput()) {
            case '1':
                searchPass();
                break;
            case '2':
                sortPass();
                break;
            case '3':
                addPass();
                break;
            case '4':
                editPass();
                break;
            case '5':
                removePass();
                break;
            case '6':
                addCategory();
                break;
            case '7':
                removeCategory();
                break;
            case 'q':
                cout << "terminating...";
                run = false;
                break;
            default:
                cout << "Invalid input, try again" << endl;
                break;
        }
    }
}

string encrypt(string s){
    return s;
}

string decrypt(string s){
    return s;
}

void writeToFile(){
    ofstream o("cats.txt");
    o << "validation" << '|' ; //TODO
    for(auto c : Password::getCategories()){
        o << encrypt(c) << ' ';
    }
    o << '|';
    for(auto p : Password::getPasswords()){
        o << p.getName() << '/' << p.getCategory()<< '/' << p.getLogin() << '/' << p.getPass()<< ' ';
    }
    o << endl;
    o.close();
}

void readFromFile(){
    ifstream i("cats.txt");
    string s;
    vector<string> raws;
    vector<string> cats;
    vector<string> passes;
    vector<Password> passwords;
    while (getline(i, s, '|')) {
        raws.push_back(decrypt(s));
    }
    for(auto r : raws){
    }
    stringstream rawsOne(raws.at(1));
    while (rawsOne >> s){
        cats.push_back(s);
    }

    stringstream rawsTwo(raws.at(2));
    while (rawsTwo >> s){
        passes.push_back(s);
    }

    for(auto p : passes){
        vector<string> pFields;
        stringstream ss(p);
        while (getline(ss, s, '/')){
            pFields.push_back(s);
        }
        passwords.push_back(Password(pFields.at(0), pFields.at(1), pFields.at(2), pFields.at(3)));
    }

    for(auto c : cats){
        cout<< c << endl;
    }
    for(auto c : passwords){
        cout<< c;
    }
}

int main() {
//    cout << "Enter the path to the password file, leave empty if there is no such file" << std::endl;
//    string path;
//    cin >> path;
//    //TODO validate the path
//    //TODO parse the path
//    cout << "Enter the master password" << endl;
//    //TODO change console input mode
//    string masterPass;
//    cin >> masterPass;
//    //TODO validate password
//    cout << "timestamp" << endl; //TODO
    Password::setPasswords({
                                   Password("a", "johndoe", "aaaaaaaaaaaa"),
                                   Password("b", "johndoe", "bbbbbbbbbbbbb"),
                                   Password("c", "johndoe", "ccccccccccccc"),
                                   Password("d", "johndoe", "dddddddddddd"),
                                   Password("e", "johndoe", "eeeeeeeeeeeeee"),
                                   Password("j", "johndoe", "jjjjjjjjjjjjjj"),
                                   Password("jasd", "johndoe", "jjjjjjjsjjjjjjj")
                           });
    Password::addCategory("emails");
    Password::addCategory("something");
    Password::addCategory("business");
    Password::addCategory("shopping");
    Password::addCategory("edu");
//    optionController();
    writeToFile();
    readFromFile();

    return 0;
}



