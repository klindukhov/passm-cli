#ifndef PASSM_CLI_FILE_H
#define PASSM_CLI_FILE_H

using namespace std;

class File {
private:
    static inline time_t decryptionTimestamp;
    static inline string filePath = " ";
public:
    static bool isValid();
    static void setFilePath(const string &filePath);

    static void setDecryptionTimestamp(time_t decryptionTimestamp);

    static void writeToFile();
    static void readFromFile();

};


#endif //PASSM_CLI_FILE_H
