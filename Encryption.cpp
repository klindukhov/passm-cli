#include <vector>
#include "Encryption.h"

void Encryption::calcKey(string masterPassword){
    vector<char> v(masterPassword.begin(),masterPassword.end());
    int k = 0;
    for(auto c : v){
        k += int(c);
    }
    key = k%128;
}

string Encryption::encrypt(string s) {
    vector<char> v(s.begin(), s.end());
    for(auto &c : v){
        c = char(int(c) + key);
    }
    return string(v);
}

string Encryption::decrypt(string s) {
    vector<char> v(s.begin(), s.end());
    for(auto &c : v){
        c = char(int(c) - key);
    }
    return string(v);
}

int Encryption::getKey() {
    return key;
}

void Encryption::setKey(int key) {
    Encryption::key = key;
}

bool Encryption::isValid() {
    return valid;
}

void Encryption::setValid(bool valid) {
    Encryption::valid = valid;
}
