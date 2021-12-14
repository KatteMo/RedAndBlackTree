#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Tree.h"
#include "ctime"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(866);



    try {
        std::ifstream fin;
        fin.open("c:\\ClionProjects\\hardtree\\test.txt");
        if (!fin.is_open()) {
            throw FileNotOpen();
        }
        RaBTree tree;
        while (!fin.eof()) {
            std::string str;
            getline(fin, str);
            tree.insert(str);
        }
        tree.print(std::cout);
        fin.close();
    }
    catch (WordError error) {
        std::cout << error.what();
    }
    catch (FoundError error) {
        std::cout << error.what();
    }
    catch (FalseTranlanion error) {
        std::cout << error.what();
    }
    return 0;
}