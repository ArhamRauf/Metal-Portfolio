#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

struct Song {
    string title;
    string artist;
    string album;
    string genre;
    int year;
};

vector<Song> musicLibrary;

void pauseForUser() {
    cout << "\nPress Enter to return to the menu...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void addSong() {
    Song newSong;
    cin.ignore();
    cout << "Enter song title: ";
    getline(cin, newSong.title);

    cout << "Enter artist name: ";
    getline(cin, newSong.artist);

    cout << "Enter album name: ";
    getline(cin, newSong.album);

    cout << "Enter genre: ";
    getline(cin, newSong.genre);

    cout << "Enter year: ";
    cin >> newSong.year;

    musicLibrary.push_back(newSong);
    cout << "\n Song added successfully!\n";
}

void displaySongs() {
    if (musicLibrary.empty()) {
        cout << "\n No songs in the library.\n";
        return;
    }

    cout << "\n Music Library:\n";
    for (const auto& song : musicLibrary) {
        cout << "-----------------------------\n";
        cout << "Title : " << song.title << "\n";
        cout << "Artist: " << song.artist << "\n";
        cout << "Album : " << song.album << "\n";
        cout << "Genre : " << song.genre << "\n";
        cout << "Year  : " << song.year << "\n";
    }
    cout << "-----------------------------\n";
}

void searchSongs() {
    if (musicLibrary.empty()) {
        cout << "\n No songs to search.\n";
        return;
    }

    int searchChoice;
    string query;

    cout << "\n===  Search Songs ===\n";
    cout << "1. By Title\n";
    cout << "2. By Artist\n";
    cout << "3. By Genre\n";
    cout << "Choose an option: ";
    cin >> searchChoice;
    cin.ignore();

    cout << "Enter your search term: ";
    getline(cin, query);

    bool found = false;

    for (const auto& song : musicLibrary) {
        bool match = false;
        switch (searchChoice) {
            case 1: match = (song.title.find(query) != string::npos); break;
            case 2: match = (song.artist.find(query) != string::npos); break;
            case 3: match = (song.genre.find(query) != string::npos); break;
            default: cout << " Invalid search option!\n"; return;
        }

        if (match) {
            found = true;
            cout << "-----------------------------\n";
            cout << "Title : " << song.title << "\n";
            cout << "Artist: " << song.artist << "\n";
            cout << "Album : " << song.album << "\n";
            cout << "Genre : " << song.genre << "\n";
            cout << "Year  : " << song.year << "\n";
        }
    }

    if (!found) {
        cout << "\n No matching songs found.\n";
    }
}

void saveToFile() {
    ofstream file("../data/songs.txt");
    if (!file) {
        cout << " Error opening file for writing.\n";
        return;
    }

    for (const auto& song : musicLibrary) {
        file << song.title << ";"
             << song.artist << ";"
             << song.album << ";"
             << song.genre << ";"
             << song.year << "\n";
    }

    file.close();
    cout << "\n Library saved successfully!\n";
}

void loadFromFile() {
    ifstream file("../data/songs.txt");
    if (!file) {
        cout << " No existing song file found. Starting fresh.\n";
        return;
    }

    musicLibrary.clear();
    string line;

    while (getline(file, line)) {
        Song song;
        size_t pos = 0;
        int field = 0;

        while ((pos = line.find(';')) != string::npos) {
            string token = line.substr(0, pos);
            switch (field) {
                case 0: song.title = token; break;
                case 1: song.artist = token; break;
                case 2: song.album = token; break;
                case 3: song.genre = token; break;
            }
            line.erase(0, pos + 1);
            field++;
        }

        try {
            song.year = stoi(line);
        } catch (...) {
            song.year = 0;
        }

        musicLibrary.push_back(song);
    }

    file.close();
    cout << " Library loaded successfully!\n";
}

int main() {
    loadFromFile();
    int choice;

    while (true) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "=== Music Organizer ===\n";
        cout << "1. Add Song\n";
        cout << "2. Display Songs\n";
        cout << "3. Search Songs\n";
        cout << "4. Save & Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addSong(); pauseForUser(); break;
            case 2: displaySongs(); pauseForUser(); break;
            case 4: saveToFile(); cout << "Exiting...\n"; return 0;
            case 3: searchSongs(); pauseForUser(); break;
            default: cout << " Invalid option!\n"; pauseForUser();
        }
    }

    return 0;
}

