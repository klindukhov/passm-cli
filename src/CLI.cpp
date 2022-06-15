#include <chrono>
#include <cstring>
#include "../include/passm_cli/CLI.h"
#include "../include/passm_cli/File.h"
#include "../include/passm_cli/Encryption.h"

char getOptionInput(){
    cout << "(1)Search for passwords" << endl;
    cout << "(2)Sort passwords" << endl;
    cout << "(3)Add a password" << endl;
    cout << "(4)Edit a password" << endl;
    cout << "(5)Remove a password" << endl;
    cout << "(6)Add a category" << endl;
    cout << "(7)Remove a category" << endl;
    cout << "(8)Change master password" << endl;
    cout << "(q)Exit" << endl;
    char i;
    cin >> i;
    return i;
}

vector<Password> CLI::searchPass(bool isVoid){
    cout << "Search by:" << endl
         << "(1)name" << endl
         << "(2)category" << endl
         << "(3)login" << endl
         << "(q)cancel" << endl;
    char searchBy;
    cin >> searchBy;
    if(searchBy == 'q') return {};
    string searchQuery;
    vector<Password> passwords;
    switch(searchBy){
        case '1':
            cout<< "Enter partial or full name of the password" << endl;
            cin >> searchQuery;
            passwords = Password::searchPassword(searchBy, searchQuery);
            break;
        case '2':{
            cout << "Pick category" << endl;
            int n = 0;
            for(auto c : Password::getCategories()){
                cout << '(' << n << ')' << c << endl;
                n++;
            }
            cin >> n;
            passwords = Password::searchPassword(searchBy, Password::getCategories().at(n));
            break;
        }
        case '3':
            cout<< "Enter partial or full login of the password" << endl;
            cin >> searchQuery;
            passwords = Password::searchPassword(searchBy, searchQuery);
            break;
    }

    if(!isVoid){return passwords;}

    cout << "/name/category/username/password" << endl;
    if(!passwords.empty()){
        for(auto p: passwords){
            cout << ">" << p;
        }
    }else{
        cout << "No entries match the search query";
    }

    cout << endl;
    cout<< "(q) exit to main menu" << endl << "(s) another search" << endl;
    char s;
    cin>>s;
    if(s == 's'){
        searchPass();
    }else{
        cout << endl;
        return {};
    }
}

vector<Password> sortVector(vector<Password> v, char sortBy, char sortDir){
    switch (sortBy) {
        case '1':
            if(sortDir == '1'){
                sort(v.begin(),v.end(),[](Password p1, Password p2){
                    char name1[p1.getName().length()];
                    char name2[p2.getName().length()];
                    for(int i = 0; i < p1.getName().length(); i++){
                        name1[i] = tolower(p1.getName()[i]);
                    }
                    for(int i = 0; i < p2.getName().length(); i++){
                        name2[i] = tolower(p2.getName()[i]);
                    }
                    return strcmp(name1, name2) < 0;
                });
            }else{
                sort(v.begin(),v.end(),[](Password p1, Password p2){
                    char name1[p1.getName().length()];
                    char name2[p2.getName().length()];
                    for(int i = 0; i < p1.getName().length(); i++){
                        name1[i] = tolower(p1.getName()[i]);
                    }
                    for(int i = 0; i < p2.getName().length(); i++){
                        name2[i] = tolower(p2.getName()[i]);
                    }
                    return strcmp(name1, name2) > 0;
                });
            }
            break;
        case '2':
            if(sortDir == '1'){
                sort(v.begin(),v.end(),[](Password p1, Password p2){
                    char name1[p1.getCategory().length()];
                    char name2[p2.getCategory().length()];
                    for(int i = 0; i < p1.getCategory().length(); i++){
                        name1[i] = tolower(p1.getCategory()[i]);
                    }
                    for(int i = 0; i < p2.getCategory().length(); i++){
                        name2[i] = tolower(p2.getCategory()[i]);
                    }
                    return strcmp(name1, name2) < 0;
                });
            }else{
                sort(v.begin(),v.end(),[](Password p1, Password p2){
                    char name1[p1.getCategory().length()];
                    char name2[p2.getCategory().length()];
                    for(int i = 0; i < p1.getCategory().length(); i++){
                        name1[i] = tolower(p1.getCategory()[i]);
                    }
                    for(int i = 0; i < p2.getCategory().length(); i++){
                        name2[i] = tolower(p2.getCategory()[i]);
                    }
                    return strcmp(name1, name2) > 0;
                });
            }
            break;
        case '3':
            if(sortDir == '1'){
                sort(v.begin(),v.end(),[](Password p1, Password p2){
                    char name1[p1.getLogin().length()];
                    char name2[p2.getLogin().length()];
                    for(int i = 0; i < p1.getLogin().length(); i++){
                        name1[i] = tolower(p1.getLogin()[i]);
                    }
                    for(int i = 0; i < p2.getLogin().length(); i++){
                        name2[i] = tolower(p2.getLogin()[i]);
                    }
                    return strcmp(name1, name2) < 0;
                });
            }else{
                sort(v.begin(),v.end(),[](Password p1, Password p2){
                    char name1[p1.getLogin().length()];
                    char name2[p2.getLogin().length()];
                    for(int i = 0; i < p1.getLogin().length(); i++){
                        name1[i] = tolower(p1.getLogin()[i]);
                    }
                    for(int i = 0; i < p2.getLogin().length(); i++){
                        name2[i] = tolower(p2.getLogin()[i]);
                    }
                    return strcmp(name1, name2) > 0;
                });
            }
            break;
    }
    vector<Password> sorted = v;
    return sorted;
}

void CLI::sortPass(){
    cout << "Sort by:" << endl
         << "(1)name" << endl
         << "(2)category" << endl
         << "(3)login" << endl
         << "(q)cancel" << endl;
    char sortingField;
    cin >> sortingField;
    if(sortingField == 'q') return;
    cout<< "(1)Ascending" << endl;
    cout<< "(2)Descending" << endl;
    char sortingDirection;
    cin >> sortingDirection;
    cout<< "Sorting" << endl;
    vector<Password> sorted = sortVector(Password::getPasswords(), sortingField, sortingDirection);
    for(auto p: sorted){
        cout << p;
    }
    cout<<"(s)sort by additional parameter" << endl;
    cout<< "(q)exit to main menu" << endl;
    char ch;
    cin >> ch;
    if(ch == 's'){
        cout << "Sort by:" << endl
             << "(1)name" << endl
             << "(2)category" << endl
             << "(3)login" << endl
             << "(q)cancel" << endl;
        cin >> sortingField;
        if(sortingField == 'q') return;
        cout<< "(1)Ascending" << endl;
        cout<< "(2)Descending" << endl;
        cin >> sortingDirection;
        cout<< "Sorting" << endl;
        for(auto p: sortVector(sorted, sortingField, sortingDirection)){
            cout << p;
        }
        cout << "Press Enter to exit to main menu" << endl;
        cin.get();
        cin.get();
    }
    cout << endl;
}

void CLI::addPass(){
    cout << "Enter name of the password or (q) to cancel" << endl;
    string name;
    cin >> name;
    if(name == "q") return;
    cout << "Pick category" << endl;
    int n = 0;
    for(auto c : Password::getCategories()){
        cout << '(' << n << ')' << c << endl;
        n++;
    }
    cout << "(c)New category" << endl;
    char c;
    cin >> c;
    string category;
    if(c == 'c'){
        cout << "Enter the new category name" << endl;
        cin >> category;
    }else{
        category = Password::getCategories().at(stoi(string(1,c)));
    }
    cout << "Enter login for the password" << endl;
    string login;
    cin >> login;
    cout << "Enter the password \n(g)generate \n(m)enter manually" << endl;
    char passChoice;
    cin >> passChoice;
    if(passChoice == 'm'){
        bool confirm = false;
        string password;
        while(!confirm){
            cout << "Enter the password:" << endl;
            cin >> password;
            if(password.length() < 6){
                cout << "Password safety: Bad" << endl;
            }else if(password.length() < 12){
                cout << "Password safety: Ok" << endl;
            }else{
                cout << "Password safety: Good" << endl;
            }
            char cont = 'g';
            while (cont != 'y' && cont != 'n' && cont != 'N' && cont != 'Y'){
                cout << "Confirm? Y/N" << endl;
                cin >> cont;
            }
            if(cont == 'y' || cont == 'Y'){confirm = true;}
        }
        Password::addPassword(Password(name,category,login,password));
    }else{
        cout << "Enter length from 15 to 30:" << endl;
        int passLength;
        cin >> passLength;
        if(passLength < 15){ passLength = 15;}
        if(passLength > 30){ passLength = 30;}
        cout << "Both upper and lower case letters? Y/N" << endl;
        char isAllCase;
        cin >> isAllCase;
        cout << "Special characters? Y/N" << endl;
        char specChar;
        cin >> specChar;
        string p = Password::generatePassword(passLength, (isAllCase == 'y' || isAllCase == 'Y'), (specChar == 'y' || specChar == 'Y'));
        Password::addPassword(Password(name,category,login,p));
    }

    cout << "Password added" << endl <<  "(q) exit to the main menu" << endl << "(a) add another password"<< endl;
    char a;
    cin >> a;
    if(a == 'a'){
        addPass();
    }
}

void CLI::editPass(){
    cout << "Editing password:" << endl;
    char ch = '0';
    vector<Password> passwords;
    while(ch == '0'){
        passwords = searchPass(false);
        if(passwords.empty()){
            cout << "No matching entries \n (0)try again \n (q)quit to main menu" << endl;
            cin >> ch;
            if(ch == 'q'){return;}
        }else{
            ch = '1';
        }
    }

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
        case 'c':{
            cout << "Pick new category" << endl;
            n = 0;
            for(auto c : Password::getCategories()){
                cout << '(' << n << ')' << c << endl;
                n++;
            }
            cout << "(c)New category" << endl;
            char c;
            cin >> c;
            string category;
            if(c == 'c'){
                cout << "Enter the new category name" << endl;
                cin >> category;
            }else{
                category = Password::getCategories().at(stoi(string(1,c)));
            }
            p.setCategory(category);
            break;
        }
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
    char confirmation = 'q';
    while(confirmation != 'Y' && confirmation != 'y' && confirmation != 'N' && confirmation != 'n'){
        cout << "Modify password? Y/N" << endl;
        cin >> confirmation;
    }
    if(confirmation == 'n' || confirmation == 'N'){return;}
    Password::editPassword(p, i);
    cout << "Password edited" << endl << "(q)exit to the main menu" << endl << "(e)edit another password" << endl;
    char c;
    cin >> c;
    if(c =='e'){editPass();}
}

void CLI::removePass(){
    cout << "Remove password:" << endl;
    char ch = '0';
    vector<Password> passwords;
    while(ch == '0'){
        passwords = searchPass(false);
        if(passwords.empty()){
            cout << "No matching entries \n (0)try again \n (q)quit to main menu" << endl;
            cin >> ch;
            if(ch == 'q'){return;}
        }else{
            ch = '1';
        }
    }

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

void CLI::addCategory(){
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

void CLI::removeCategory(){
    vector<string> cats ={};
    cats = Password::getCategories();
    int n = 0;
    cout << "Enter the number of category you want to delete" << endl;
    for(auto c: cats){
        cout << '(' << n << ')' << c << endl;
        n++;
    }
    int i;
    cin >> i;
    char confirmation = 'q';
    while(confirmation != 'Y' && confirmation != 'y' && confirmation != 'N' && confirmation != 'n'){
        cout << "Remove category? Y/N" << endl;
        cin >> confirmation;
    }
    if(confirmation == 'n' || confirmation == 'N'){return;}
    Password::rmCategory(cats.at(i));
    cout << "Category deleted \n (q) exit to the main menu \n (a) delete another category"<< endl;
    char a;
    cin >> a;
    if(a == 'a'){
        removeCategory();
    }
}

void CLI::changeMasterPassword() {
    string masterPassword = "r";
    string repeatPassword;
    while (masterPassword != repeatPassword) {
        cout << "Enter new master password" << endl;
        //TODO change console input mode
        cin >> masterPassword;
        cout << "Repeat the master password" << endl;
        //TODO change console input mode
        cin >> repeatPassword;
        if (masterPassword != repeatPassword) { cout << "Passwords don`t match" << endl; }
    }

    if(Encryption::isPasswordValid()){
        Encryption::setMasterPassword(masterPassword);
        Encryption::setValidationString(Encryption::masterPasswordToValidationString(masterPassword));
    }
}

void CLI::optionController(){
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
            case '8':
                changeMasterPassword();
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

void CLI::start(){
    char fileChoice = 0;
    while (fileChoice != '1' && fileChoice != '2' && fileChoice != 'q') {
        cout << "(1)Enter the path of existing password file" << endl
             << "(2)Create a new password file" << endl
             << "(q)quit" << endl;
        cin >> fileChoice;
    }

    string filePath;

    switch (fileChoice) {
        case '1' :{
            bool invalid = true;
            while (invalid){
                cout << "Enter the path to the password file" << endl;
                cin >> filePath;
                File::setFilePath(filePath);
                if(File::isValid()){
                    invalid = false;
                }else{
                    cout << "Path is invalid" << endl;
                }
            }
            cout << "Enter the master password" << endl;     //TODO change console input mode
            string masterPassword;
            cin >> masterPassword;

            Encryption::setMasterPassword(masterPassword);
            File::readFromFile();
            CLI::optionController();

            File::writeToFile();
            break;
        }
        case '2' : {
            cout << "Enter the name of the password file to be created" << endl;
            cin >> filePath;

            File::setFilePath(filePath);
            changeMasterPassword();
            File::setDecryptionTimestamp(chrono::system_clock::to_time_t(chrono::system_clock::now()));
            CLI::optionController();

            File::writeToFile();
            break;
        }
        case 'q':
            break;
    }
}

void CLI::devStart(){
    File::setFilePath("../passwordFiles/dogs.txt");
    Encryption::setMasterPassword("dogs");
    File::readFromFile();
    CLI::optionController();
    File::writeToFile();
}