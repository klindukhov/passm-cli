#include "Password.h"
#include <string>

using namespace std;

void Password::setName(const string &name) {
    Password::name = name;
}

void Password::setCategory(const string &category) {
    Password::category = category;
}

void Password::setLogin(const string &login) {
    Password::login = login;
}

void Password::setPass(const string &pass) {
    Password::pass = pass;
}

void Password::setPasswords(const vector<Password> &passwords) {
    Password::passwords = passwords;
}

void Password::addCategory(string cat){
    categories.push_back(cat);
}

void Password::rmCategory(string cat){
    remove(categories.begin(), categories.end(), cat);
}

void Password::addPassword(Password p){
    passwords.push_back(p);
}

void Password::rmPassword(Password p){
    remove(passwords.begin(), passwords.end(), p);
}

void Password::editPassword(Password p){
    //TODO figure out how to edit password
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