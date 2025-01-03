#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class fichier {
    char* name;
    char* mode;
    FILE* file;
    int size_len;

public:
    fichier(){
        name = nullptr;
        mode = nullptr;
        file = nullptr;
        size_len = 0;
    }

    fichier(char* _name, char* _mode, int _size_len) {
        name = new char[strlen(_name) + 1];
        mode = new char[strlen(_mode) + 1];

        strcpy(name, _name);
        strcpy(mode, _mode);
        size_len = _size_len;

        file = fopen(name, mode);

        if (!file) {
            perror("Error opening file");
            return;
        }
    }

    ~fichier(){
        delete[] name;
        delete[] mode;
        fclose(file);
    }

    // Getter for name
    char* getName() const {
        return name;
    }

    // Getter for mode
    char* getMode() const {
        return mode;
    }

    // Getter for size_len
    int getSizeLen() const {
        return size_len;
    }

    // Setter for name
    void setName(const char* _name) {
        delete[] name;
        name = new char[strlen(_name) + 1];
        strcpy(name, _name);

        if (file) {
            fclose(file);
        }

        file = fopen(name, mode);
        if (!file) {
            perror("Error opening file");
        }
    }

    // Setter for mode
    void setMode(const char* _mode) {
        delete[] name;
        name = new char[strlen(_mode) + 1];
        strcpy(mode, _mode);

        if (file) {
            fclose(file);
        }

        file = fopen(name, mode);
        if (!file) {
            perror("Error opening file");
        }
    }

    // Setter for size_len
    void setSizeLen(int _size_len) {
        size_len = _size_len;
    }

    void writeFile(char* str) {
        // Check mode validity
        if (strcmp(mode, "w") != 0 && strcmp(mode, "w+") != 0) {
            perror("The mode must be 'w' or 'w+'");
            return;
        }

        // Ensure file is open
        if (!file) {
            perror("File is not open");
            return;
        }

        // Write to file
        if (fprintf(file, "%-*.*s", size_len, size_len, str) < 0) {
            perror("Error writing to file");
        }
        fprintf(file,"%-*.*s",size_len,size_len,str);
    }

    void readFile(char* buffer, int bufferSize) {
        // Check mode validity
        if (strcmp(mode, "r") != 0 && strcmp(mode, "r+") != 0 && strcmp(mode, "w+") != 0) {
            perror("The mode must allow reading (r, r+, or w+)");
            return;
        }

        // Ensure file is open
        if (!file) {
            perror("File is not open for reading");
            return;
        }

        // Read from file
        if (fscanf(file, "%s", buffer) == EOF) {
            if (ferror(file)) {
                perror("Error reading from file");
            } else {
                cout << "End of file reached." << endl;
            }
        }
    }

    
};

int main() {
    fichier f("Taki", "Here", 6);
    cout << "Hello World!" << endl;
    cout << strlen(f.getName()) << endl;  // Use the getter
    return 0;
}
