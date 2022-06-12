#ifndef PASSM_CLI_PASSWORD_H
#define PASSM_CLI_PASSWORD_H

#include <iostream>
#include <vector>

using namespace std;


class Password {
private:
    string name, category, login, pass;
    static vector<Password> passwords;
    static vector<string> categories;
public:
    const string getName(){return name;};
    void setName(const string &name);
    const string &getCategory() {return category;};
    void setCategory(const string &category);
    const string &getLogin() {return login;};
    void setLogin(const string &login);
    const string &getPass() {return pass;};
    void setPass(const string &pass);
    static const vector<Password> &getPasswords();
    static const vector<string> &getCategories();
    static void setPasswords(const vector<Password> &passwords);
    static void addCategory(string cat);
    static void rmCategory(string cat);
    static void addPassword(Password p);
    static void rmPassword(Password p);
    static void editPassword(Password p);
    Password(const string &name, const string &category, const string &login, const string &pass);
    Password(const string &name, const string &login, const string &pass);
    bool operator==(Password p);

};


#endif //PASSM_CLI_PASSWORD_H
