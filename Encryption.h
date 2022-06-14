#ifndef PASSM_CLI_ENCRYPTION_H
#define PASSM_CLI_ENCRYPTION_H

#include <string>

using namespace std;

class Encryption {
private:
    static inline int key = 0;
    static inline bool valid = false;
public:
    static int getKey();
    static void setKey(int key);
    static bool isValid();
    static void setValid(bool valid);
    static void calcKey(string masterPassword);
    static string encrypt(string s);
    static string decrypt(string s);
    static bool  validate(string s);
};


#endif //PASSM_CLI_ENCRYPTION_H
