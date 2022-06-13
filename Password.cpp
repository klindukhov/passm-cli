#include "Password.h"
#include <string>

using namespace std;

void Password::setName(const string &name) {
    this->name = name;
}

void Password::setCategory(const string &category) {
    this->category = category;
}

void Password::setLogin(const string &login) {
    this->login = login;
}

void Password::setPass(const string &pass) {
    this->pass = pass;
}

void Password::setPasswords(const vector<Password> &passwords) {
    Password::passwords = passwords;
}

void Password::addCategory(string cat){
    Password::categories.push_back(cat);
}

void Password::rmCategory(string cat){
    remove(categories.begin(), categories.end(), cat);
    //TODO change category of passwords to none
}

void Password::addPassword(Password p){
    passwords.push_back(p);
    //TODO check if category exists and if no - add it
}

void Password::rmPassword(Password p){
    remove(passwords.begin(), passwords.end(), p);
}

void Password::editPassword(Password p, int index){
    passwords.at(index) = p;
    //TODO check if category exists and if no - add it

}

const vector<Password> Password::getPasswords(int sort){
    //TODO implement sorting
    return Password::passwords;
}

vector<Password> Password::getPasswordByName(string searchQuery){
    //TODO implement search by other fields
    vector<Password> res= {};
    for_each(passwords.begin(), passwords.end(), [searchQuery, &res](Password p)-> void
    {
        if(p.name.find(searchQuery) != string::npos){
            res.push_back(p);
        }
    });
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