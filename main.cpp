#include <iostream>
#include <fstream>
#include <unistd.h> // buat ms
#include <json/json.h> // buat database

using namespace std;

bool filterUmur(int age) {
    return age >= 18;
}

bool filterKotor(const string& name) {
    vector<string> dirtyWords = {"anjing", "memek", "kontol"};

    
    for (const string& word : filterKotor) {
        if (name.find(word) != string::npos) {
            return true;
        }
    }
    return false;
}

bool filterAngka(const string& str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

void printError(const string& message) {
    cout << "\033[1;31m" << "Error: " << message << "\033[0m" << endl;
}

void typeWriter(const string& text) {
    for (const char& c : text) {
        cout << c << flush;
        usleep(100000); // 100ms 
    }
    cout << endl;
}

int main() {
    ifstream inFile("database.json");
    Json::Value existingDatabase;


    if (inFile.is_open()) {
        inFile >> existingDatabase;
        inFile.close();
    }


    cout << "\033[1;35m" << "Selamat Datang Di Sekai Network :)!" << "\033[0m" << endl;
    cout << "\033[1;35m" << "━━━━━━━━━━━━━━━━━━━━━━" << "\033[0m" << endl;
    cout << endl;


    string name;
    cout << "\033[1;32m" << "Masukkan Namamu: " << "\033[0m";
    getline(cin, name);
    cout << endl;


    cout << "\033[1;33m" << "Hello ";
    typeWriter(name);
    cout << "\033[0m" << endl;


    cout << "\033[1;36m" << "Ciloko Akan Membantu Pendaftaranmu!." << "\033[0m" << endl;
    cout << "\033[1;36m" << "Silahkan Masukkan Umur dan usia mu." << "\033[0m" << endl;
    cout << endl;

    
    int age;
    cout << "\033[1;32m" << "Umur Kamu: " << "\033[0m";
    cin >> age;

    
    if (!filterUmur(age)) {
        printError("Maaf Umur Kamu Harus di atas 18!.");
        return 1; // Exit with error code
    }

    cin.ignore();


    string skills;
    cout << "\033[1;32m" << "Skill Masukkan skill kamu: " << "\033[0m";
    getline(cin, skills);
    cout << endl;


    if (filterKotor(name)) {
        printError("Kamu Ciloko Banned Karena Berkata Kasar!.");
        return 1; 
    }


    if (skills.empty()) {
        printError("Skill nya kok kosong?.");
        return 1; 
    }

    
    if (!filterAngka(to_string(age))) {
        printError("Umur itu angka bukun huruf kak.");
        return 1; 
    }

    
    Json::Value newEntry;
    newEntry["name"] = name;
    newEntry["age"] = age;
    newEntry["skills"] = skills;


    existingDatabase.append(newEntry);

    
    ofstream outFile("database.json");
    outFile << existingDatabase;
    outFile.close();

  
    cout << "\033[1;32m" << "Thank you for joining Sekai Network!" << "\033[0m" << endl;

    return 0;
}
