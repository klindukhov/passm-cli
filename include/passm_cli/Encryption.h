#ifndef PASSM_CLI_ENCRYPTION_H
#define PASSM_CLI_ENCRYPTION_H

#include <string>

using namespace std;

class Encryption {
private:
    static inline int key = 0;
    static inline string masterPassword;
    static inline string validationString;
public:
    static void setMasterPassword(const string &masterPassword);
    static void setValidationString(const string &validation);

    static string masterPasswordToValidationString(string masterPass);

    static string encodeDate(string rawDate);
    static string decodeDate(string encodedDate);


    static string encrypt(string s);
    static string decrypt(string s);
    static bool isPasswordValid();
    static const string &getValidationString();
};


#endif //PASSM_CLI_ENCRYPTION_H
