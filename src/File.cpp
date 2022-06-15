#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include "../include/passm_cli/File.h"
#include "../include/passm_cli/Encryption.h"
#include "../include/passm_cli/Password.h"

using namespace std;

bool File::isValid(){
    ifstream i(filePath);
    string s;
    getline(i, s);
    i.close();
    return s == "<passm_cli_document>";
}

void File::writeToFile(){
    if(!Encryption::isPasswordValid()){
        ifstream i(filePath);
        string s;
        vector<string> ss;
        while(getline(i, s)){
            ss.push_back(s);
        }
        i.close();
        ofstream o(filePath);
        o << "<passm_cli_document>" << endl;
        o << Encryption::encodeDate(string(ctime(&decryptionTimestamp))) << endl;
        for(int in = 2; in < ss.size(); in++){
            o << ss.at(in) << endl;
        }
        o.close();
        return;
    }
    ofstream o(filePath);
    o << "<passm_cli_document>" << endl;
    o << Encryption::encodeDate(string(ctime(&decryptionTimestamp))) << endl;
    o << Encryption::getValidationString() << endl; //TODO
    for(auto c : Password::getCategories()){
        o << Encryption::encrypt(c) << ' ';
    }
    o << endl;
    for(auto p : Password::getPasswords()){
        o << Encryption::encrypt(p.getName()) << endl
          << Encryption::encrypt(p.getCategory())<< endl
          << Encryption::encrypt(p.getLogin()) << endl
          << Encryption::encrypt(p.getPass())<< endl;
    }
    o.close();
}

void File::readFromFile(){
    ifstream i(filePath);
    string s;
    vector<string> raws;
    vector<string> passes;
    while (getline(i, s)) {
        raws.push_back(s);
    }

    cout << "Timestamp of last decryption:" << Encryption::decodeDate(raws.at(1)) << endl;
    Encryption::setValidationString(raws.at(2));

    stringstream rawCategories(raws.at(3));
    while (rawCategories >> s){
        Password::addCategory(Encryption::decrypt(s));
    }

    for(int in = 4; in < raws.size(); in+=4){
        Password::addPassword(
                Password(
                        Encryption::decrypt(raws.at(in)),
                        Encryption::decrypt(raws.at(in+1)),
                        Encryption::decrypt(raws.at(in+2)),
                        Encryption::decrypt(raws.at(in +3))
                )
        );
    }
    decryptionTimestamp = chrono::system_clock::to_time_t(chrono::system_clock::now());
    i.close();
}

void File::setFilePath(const string &filePath) {
    File::filePath = filePath;
}

void File::setDecryptionTimestamp(time_t decryptionTimestamp) {
    File::decryptionTimestamp = decryptionTimestamp;
}
