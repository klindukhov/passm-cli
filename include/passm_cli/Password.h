#ifndef PASSM_CLI_PASSWORD_H
#define PASSM_CLI_PASSWORD_H

#include <iostream>
#include <vector>

using namespace std;


class Password {
private:
    string name, category, login, pass;
    inline static vector<Password> passwords = {};
    inline static vector<string> categories = {};
public:
    string getName(){return name;};
    void setName(const string &name);

    const string &getCategory() {return category;};
    void setCategory(const string &category);

    const string &getLogin() {return login;};
    void setLogin(const string &login);

    const string &getPass() {return pass;};
    void setPass(const string &pass);

    static const vector<Password> getPasswords();
    static const vector<string> getCategories() {return categories;};

    static vector<Password> searchPassword(char searchBy, string searchQuery);

    static void addCategory(string cat);
    static void rmCategory(string cat);

    static void addPassword(Password p);
    static void rmPassword(Password p);
    static void editPassword(Password p, int index);

    static string generatePassword(int passLength, bool allCase, bool specChar);

    Password(const string &name, const string &category, const string &login, const string &pass);
    Password(const string &name, const string &login, const string &pass);

    bool operator==(Password p);
    friend ostream& operator<<(ostream& o, Password& p);
};


#endif //PASSM_CLI_PASSWORD_H
