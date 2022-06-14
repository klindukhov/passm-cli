#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

#include "Password.h"
#include "Encryption.h"

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
    cout << "Enter category of the password" << endl;
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
    //TODO add cancel and confirm;
    //TODO fix deletion
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

void writeToFile(string filename, time_t timeOfDecryption){
    ofstream o(filename);

    o << ctime(&timeOfDecryption);
    o << "validation" << endl << '|' << endl ; //TODO
    for(auto c : Password::getCategories()){
        o << Encryption::encrypt(c) << ' ';
    }
    o << endl << '|' << endl;
    for(auto p : Password::getPasswords()){
        o << Encryption::encrypt(p.getName()) << endl
        << Encryption::encrypt(p.getCategory())<< endl
        << Encryption::encrypt(p.getLogin()) << endl
        << Encryption::encrypt(p.getPass())<< endl << '/' << endl;
    }
    o.close();
}

time_t readFromFile(string filename){
    ifstream i(filename);
    string s;
    vector<string> raws;
    vector<string> passes;
    while (getline(i, s)) {
        raws.push_back(s);
    }

    cout << "Timestamp of last decryption:" << raws.at(0) << endl;

    stringstream rawCategories(raws.at(3));
    while (rawCategories >> s){
        Password::addCategory(Encryption::decrypt(s));
    }

    for(int in = 5; in < raws.size(); in+=5 ){
        Password::addPassword(
                Password(
                        Encryption::decrypt(raws.at(in)),
                        Encryption::decrypt(raws.at(in+1)),
                        Encryption::decrypt(raws.at(in+2)),
                        Encryption::decrypt(raws.at(in +3))
                        )
                );
    }
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
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
//    Password::setPasswords({
//                                   Password("a", "johndoe", "aaaaaaaaaaaa"),
//                                   Password("b", "johndoe", "bbbbbbbbbbbbb"),
//                                   Password("c", "johndoe", "ccccccccccccc"),
//                                   Password("d", "johndoe", "dddddddddddd"),
//                                   Password("e", "johndoe", "eeeeeeeeeeeeee"),
//                                   Password("j", "johndoe", "jjjjjjjjjjjjjj"),
//                                   Password("jasd", "johndoe", "jjjjjjjsjjjjjjj")
//                           });
//    Password::addCategory("emails");
//    Password::addCategory("something");
//    Password::addCategory("business");
//    Password::addCategory("shopping");
//    Password::addCategory("edu");
    string masterPassword = "hbou43fbo283u4bo8bf08o3491094r@$#!@fjoqyb";
    Encryption::calcKey(masterPassword);

    time_t timeOfDecryption = readFromFile("cats.txt");
    optionController();

    writeToFile("cats.txt", timeOfDecryption);
    return 0;
}



