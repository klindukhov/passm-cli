#include <vector>
#include "../include/passm_cli/Encryption.h"

string Encryption::encrypt(string s) {
    for(int i = 0; i < s.length(); i++){
        int ascii = int(s[i])+key+i;
        if(ascii > 127) ascii -= 127;
        s[i] = char(ascii);
    }
    return s;
}

string Encryption::decrypt(string s) {
    for(int i = 0; i < s.length(); i++){
        int ascii =int(s[i])-key-i;
        if(ascii < 0) ascii+= 127;
        s[i] = char(ascii);
    }
    return s;
}


bool Encryption::isPasswordValid() {
    return Encryption::masterPasswordToValidationString(masterPassword) == validationString;
}

void Encryption::setMasterPassword(const string &masterPassword) {
    Encryption::masterPassword = masterPassword;
    vector<char> v(masterPassword.begin(),masterPassword.end());
    int k = 0;
    for(auto c : v){
        k += int(c);
    }
    key = k%128;
}

string Encryption::encodeDate(string rawDate){
    for(int i = 0; i < rawDate.length(); i++){
        rawDate[i] = char(int(rawDate[i]) + i);
    }
    return rawDate;
}
string Encryption::decodeDate(string encodedDate){
    for(int i = 0; i < encodedDate.length(); i ++){
        encodedDate[i] = char(int(encodedDate[i])-i);
    }
    return encodedDate;
}

void Encryption::setValidationString(const string &validation) {
    Encryption::validationString = validation;
}

const string &Encryption::getValidationString() {
    return validationString;
}

string Encryption::masterPasswordToValidationString(string masterPass){
    return encrypt(masterPass);
}