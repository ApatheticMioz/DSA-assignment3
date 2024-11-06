#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int max (int a, int b) {
    return (a > b) ? a : b;
}

class GamesPlayedNode {
public:
    string gameID;
    float hoursPlayed;
    int achievements;

    GamesPlayedNode* left;
    GamesPlayedNode* right;

    GamesPlayedNode(const string &gameID, const float hoursPlayed, const int achievements) {
        this->gameID = gameID;
        this->hoursPlayed = hoursPlayed;
        this->achievements = achievements;

        left = nullptr;
        right = nullptr;
    }
};

class PlayerNode {
public:
    string playerID;
    string playerName;
    string phoneNumber;
    string email;
    string password;
    GamesPlayedNode* gamesPlayedRoot;

    PlayerNode* left;
    PlayerNode* right;

    PlayerNode(const string &playerID, const string &playerName, const string &phoneNumber, const string &email, const string &password, GamesPlayedNode* gamesPlayedRoot) {
        this->playerID = playerID;
        this->playerName = playerName;
        this->phoneNumber = phoneNumber;
        this->email = email;
        this->password = password;
        this->gamesPlayedRoot = gamesPlayedRoot;

        left = nullptr;
        right = nullptr;
    }
};

class GameNode {
public:
    string gameID;
    string name;
    string developer;
    string publisher;
    float fileSizeGBs;
    int downloads;

    GameNode* left;
    GameNode* right;

    GameNode(const string& gameID, const string& name, const string& developer, const string& publisher, const float fileSizeGBs, int const downloads) {
        this->gameID = gameID;
        this->name = name;
        this->developer = developer;
        this->publisher = publisher;
        this->fileSizeGBs = fileSizeGBs;
        this->downloads = downloads;

        left = nullptr;
        right = nullptr;
    }
};


int main() {
    int seed = 232523;
    srand(seed);

    // readFile();

    return 0;
}