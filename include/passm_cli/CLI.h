#ifndef PASSM_CLI_CLI_H
#define PASSM_CLI_CLI_H


#include "Password.h"

/**
 * contains methods related to user interaction with command line
 */
class CLI {
private:
    static void optionController();

    static vector<Password> searchPass(bool isVoid = true);
    static void sortPass();
    static void addPass();
    static void editPass();
    static void removePass();
    static void addCategory();
    static void removeCategory();

    static void changeMasterPassword();

public:
    /**
     * main method of the program
     */
    static void start();
    static void devStart();

};


#endif //PASSM_CLI_CLI_H
