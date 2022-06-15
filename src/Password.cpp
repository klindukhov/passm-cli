#include "../include/passm_cli/Password.h"
#include <string>

using namespace std;

void Password::setName(const string &name) {this->name = name;}
void Password::setCategory(const string &category) {this->category = category;}
void Password::setLogin(const string &login) {this->login = login;}
void Password::setPass(const string &pass) {this->pass = pass;}

void Password::addCategory(string cat){Password::categories.push_back(cat);}

void Password::rmCategory(string cat){
    categories.erase(find(categories.begin(), categories.end(), cat));
    for(auto &p : Password::passwords){
        if(p.getCategory() == cat){
            p.setCategory("none");
        }
    }
}

void Password::addPassword(Password p){
    passwords.push_back(p);
    if(none_of(Password::categories.begin(), Password::categories.end(), [&p](string s){ return s == p.getCategory();})){
        addCategory(p.getCategory());
    }
}

void Password::rmPassword(Password p){passwords.erase(find(passwords.begin(), passwords.end(), p));}

void Password::editPassword(Password p, int index){
    passwords.at(index) = p;
    if(none_of(Password::categories.begin(), Password::categories.end(), [&p](string s){ return s == p.getCategory();})){
        addCategory(p.getCategory());
    }
}

const vector<Password> Password::getPasswords(){
    return Password::passwords;
}

string Password::generatePassword(int passLength, bool allCase, bool specChar){
    string s;
    s.resize(passLength);
    if(allCase && specChar){
        for(int i = 0; i < passLength; i ++ ){
            s[i] = char(rand()%128);
        }
    }else if(specChar){
        for(int i = 0; i < passLength; i ++ ){
            int ascii = 91;
            while(ascii < 65 || ascii > 122 || (ascii < 97 && ascii >90)){
                ascii = rand()%58+65;
            }
            s[i] = char(ascii);
        }
    }else if(allCase){
        for(int i = 0; i < passLength; i ++ ){
            int ascii = 91;
            while(ascii > 90 && ascii < 97){
                ascii = rand()%58+65;
            }
            s[i] = char(ascii);
        }
    }else{
        for(int i = 0; i < passLength; i ++ ){
            int ascii = 91;
            while(ascii > 90 && ascii < 97){
                ascii = rand()%58+65;
            }
            s[i] = char(ascii);
        }
    }
    return s;
}

vector<Password> Password::searchPassword(char searchBy, string searchQuery){
    vector<Password> res= {};
    switch(searchBy){
        case '1':
            for_each(passwords.begin(), passwords.end(), [searchQuery, &res](Password p)-> void
            {
                if(p.name.find(searchQuery) != string::npos){res.push_back(p);}
            });
            break;
        case '2':
            for_each(passwords.begin(), passwords.end(), [searchQuery, &res](Password p)-> void
            {
                if(p.category == searchQuery){res.push_back(p);}
            });
            break;
        case '3':
            for_each(passwords.begin(), passwords.end(), [searchQuery, &res](Password p)-> void
            {
                if(p.login.find(searchQuery) != string::npos){res.push_back(p);}
            });
            break;
    }

    return res;
}



Password::Password(const string &name, const string &category, const string &login, const string &pass) : name(name),
                                                                                                category(category),
                                                                                                login(login),
                                                                                                pass(pass) {}

Password::Password(const string &name, const string &login, const string &pass) : name(name),
                                                                        login(login),
                                                                        pass(pass),
                                                                        category("none") {}

bool Password::operator==(Password p) {
    return name == p.getName() && login == p.getLogin() && category == p.getCategory() && pass == p.getPass();
}

ostream& operator<<(ostream& o, Password& p){
    o << p.getName() << " " << p.getCategory() << " " << p.getLogin()<< " " << p.getPass() << endl;
    return o;
}