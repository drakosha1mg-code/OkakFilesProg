#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

int com(std::string command, std::string a, int file_is_open){
    std::fstream file (a, std::ios::in | std::ios::out);
    if (!file.is_open()) {
        if (file_is_open == 0) {return 0;}
        return 2;
    }

    if (command == "w" && file_is_open == 1) {
        int s;
        std::vector<std::string> vec;
        std::string in;
        std::string r;
        std::cout << "Ok, Line: \n";
        std::cin >> s;
        std::cin >> in;
        std::string okak;

        while (std::getline(file, okak)) {
            vec.push_back(okak);
        }
        file.close();

        std::ofstream file("a.txt", std::ios::trunc);
        file.close();

        std::fstream fileok (a, std::ios::in | std::ios::out);

        vec[s - 1] = in;
        for (int i = 0; i < vec.size(); i++) {
            fileok << vec[i] << "\n";
        }
        fileok.close();
    }
    else if (command == "r" && file_is_open == 1) {
        std::string str;
        int b = 1;
        while (std::getline(file, str)) {
        std::cout << b << ". " << str << "\n";
        b = b + 1;
        }
    }

    else if (command == "clone" && file_is_open == 1) {
        std::string clone;
        std::cout << "New file name: \n>";
        std::cin >> clone;
        int s;
        std::vector<std::string> vec;
        std::string r;
        std::string okak;

        while (std::getline(file, okak)) {
            vec.push_back(okak);
        }
        file.close();

        std::ofstream outfile(clone);
        outfile.close();

        std::fstream fileok (clone, std::ios::in | std::ios::out);

        for (int i = 0; i < vec.size(); i++) {
            fileok << vec[i] << "\n";
        }
        fileok.close();
    }

    else if (command == "help") {
        std::cout << "[w] - write line to file \n[clone] - clone file \n[close] - Close file \n[N] - Create new file \n[o] - open file \n[r] - read file\n[^C] - exit\n";
    }

    else if(command == "N") {
        std::string Okak;
        std::cout << "File name:\n";
        std::cin >> Okak;
        std::ofstream outfile(Okak);
        outfile.close();
        std::cout << "File Created!\n";
    }

    else if (command == "open") {
        file.close();
        std::cout << "Select file: \n";
        std::cin >> a;
        std::fstream file (a, std::ios::in | std::ios::out);
        if (!file.is_open()) {
            std::cout << "Error opening file, no changes \n " << std::endl;
            return 0;
        }
        std::cout << "File opened!\n";
        file_is_open = 1;
        file.close();
        return 4;
    }

    else if (command == "close") {
        a = "";
        std::cout << "File closed!\n";
        file.close();
        return 3;
    }

    else if (file_is_open == 0) {return 0;}
    else {std::cout << "Error: ivalid command\n";}
    return 1;
}

int okak(std::string a, int file_is_open) {
    std::fstream file (a, std::ios::in | std::ios::out);
    if (!file.is_open()) {
        return 2;
    }
    std::string str;
    std::cout << "OkakFileProg> ";
    std::cin >> str;
    if (str == "^C") {return -1;}
    int rescom = com(str, a, file_is_open);
    if (rescom == 0) {return 0;}
    if (rescom == 4) {file_is_open = 1; return 1;}
    else if(rescom == 2) {return 2;}
    else if(rescom == 3) {file.close(); a = ""; return 3;}
    return 1;
}

int main(void) {
    int file_is_open = 1;
    std::string a;
    int b = 0;
    std::cout << "file: " << "\n";
    std::cin >> a;
    std::ifstream file (a);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }
    else {std::cout << "File opening: OK\n";}

    std::string str;

    while (std::getline(file, str)) {b = b + 1;}

    std::cout << "File: " << a << "\n" << "Lines: " << b << "\n";
    b = 1;
    std::cout << "\n";

    str = " ";

    file.clear();
    file.seekg(0, std::ios::beg);

    while (std::getline(file, str)) {
        std::cout << b << ". " << str << "\n";
        b = b + 1;
    }

    std::cout << "\nWelcome to OkakFileProg v1.0 by drakosha1mg! Type help to show commands \n";
    int error = 0;
    while (error != -1) {
        error = okak(a, file_is_open);
        if(error == 0) {std::cout << "Error: File not selected \n"; file_is_open = 0;}
        else if(error == 2) {std::cout << "Error opening file \n" << std::endl;}
        else if (error == 3) {file.close(); file_is_open = 0;}
    }

    file.close();
}
