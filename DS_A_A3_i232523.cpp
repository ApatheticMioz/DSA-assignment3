#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

#include <direct.h>

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int strComp(const string& num1, const string& num2) {
    int idxI = 0, idxJ = 0;

    while (idxI < num1.length() && num1[idxI] == '0')
        idxI++;

    while (idxJ < num2.length() && num2[idxJ] == '0')
        idxJ++;

    while (idxI < num1.length() && idxJ < num2.length()) {
        if (num1[idxI] < num2[idxJ])
            return -1;

        if (num1[idxI] > num2[idxJ])
            return 1;

        idxI++;
        idxJ++;
    }

    if (idxI == num1.length() && idxJ == num2.length())
        return 0;

    return (idxI < num1.length()) ? 1 : -1;
}

class GamesPlayedNode {
public:
    string gameID;
    float hoursPlayed;
    int achievements;

    int height;
    GamesPlayedNode* left;
    GamesPlayedNode* right;

    GamesPlayedNode(const string &gameID, const float hoursPlayed, const int achievements) {
        this->gameID = gameID;
        this->hoursPlayed = hoursPlayed;
        this->achievements = achievements;

        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

class GamesPlayedAVL {
public:
    GamesPlayedNode* root;

    GamesPlayedAVL() {
        root = nullptr;
    }

    int height(GamesPlayedNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    GamesPlayedNode* rightRotate(GamesPlayedNode* root) {
        GamesPlayedNode* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    GamesPlayedNode* leftRotate(GamesPlayedNode* root) {
        GamesPlayedNode* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    int getBalance(GamesPlayedNode *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    GamesPlayedNode* insert(GamesPlayedNode* node, const string &gameID, const float hoursPlayed, const int achievements) {

        if (node == nullptr)
            return new GamesPlayedNode(gameID, hoursPlayed, achievements);

        if ((strComp(gameID, node->gameID)) == -1)
            node->left = insert(node->left, gameID, hoursPlayed, achievements);
        else if ((strComp(gameID, node->gameID)) == 1)
            node->right = insert(node->right, gameID, hoursPlayed, achievements);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && strComp(gameID, node->left->gameID) == -1)
            return rightRotate(node);

        if (balance < -1 && strComp(gameID, node->right->gameID) == 1)
            return leftRotate(node);

        if (balance > 1 && strComp(gameID, node->left->gameID) == 1) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && strComp(gameID, node->right->gameID) == -1) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void preOrder(GamesPlayedNode *root) {
        if (root != nullptr) {
            cout << root->gameID << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
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

    int height;
    PlayerNode* left;
    PlayerNode* right;

    PlayerNode(const string &playerID, const string &playerName, const string &phoneNumber, const string &email, const string &password, GamesPlayedNode* gamesPlayedRoot) {
        this->playerID = playerID;
        this->playerName = playerName;
        this->phoneNumber = phoneNumber;
        this->email = email;
        this->password = password;
        this->gamesPlayedRoot = gamesPlayedRoot;

        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

class PlayerAVL {
public:
    PlayerNode* root;

    PlayerAVL() {
        root = nullptr;
    }

    int height(PlayerNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    PlayerNode* rightRotate(PlayerNode* root) {
        PlayerNode* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    PlayerNode* leftRotate(PlayerNode* root) {
        PlayerNode* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    int getBalance(PlayerNode *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    PlayerNode* insert(PlayerNode* node, const string &playerID, const string &playerName, const string &phoneNumber, const string &email, const string &password, GamesPlayedNode* gamesPlayedRoot) {

        if (node == nullptr)
            return new PlayerNode(playerID, playerName, phoneNumber, email, password, gamesPlayedRoot);

        if ((strComp(playerID, node->playerID)) == -1) {
            //cout << "Inserting playerID: " << playerID << " into node with playerID: " << node->playerID << endl;

            node->left = insert(node->left, playerID, playerName, phoneNumber, email, password, gamesPlayedRoot);
        }
        else if ((strComp(playerID, node->playerID)) == 1)
            node->right = insert(node->right, playerID, playerName, phoneNumber, email, password, gamesPlayedRoot);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && strComp(playerID, node->left->playerID) == -1)
            return rightRotate(node);

        if (balance < -1 && strComp(playerID, node->right->playerID) == 1)
            return leftRotate(node);

        if (balance > 1 && strComp(playerID, node->left->playerID) == 1) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && strComp(playerID, node->right->playerID) == -1) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void preOrder(PlayerNode *root) {
        if (root != nullptr) {
            cout << root->playerID << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
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

    int height;
    GameNode* left;
    GameNode* right;

    GameNode(const string& gameID, const string& name, const string& developer, const string& publisher, const float fileSizeGBs, int const downloads) {
        this->gameID = gameID;
        this->name = name;
        this->developer = developer;
        this->publisher = publisher;
        this->fileSizeGBs = fileSizeGBs;
        this->downloads = downloads;

        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

class GameAVL {
public:
    GameNode* root;

    GameAVL() {
        root = nullptr;
    }

    int height(GameNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    GameNode* rightRotate(GameNode* root) {
        GameNode* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    GameNode* leftRotate(GameNode* root) {
        GameNode* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    int getBalance(GameNode *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    GameNode* insert(GameNode* node, const string& gameID, const string& name, const string& developer, const string& publisher, const float fileSizeGBs, int const downloads) {

        if (node == nullptr)
            return new GameNode(gameID, name, developer, publisher, fileSizeGBs, downloads);

        if ((strComp(gameID, node->gameID)) == -1)
            node->left = insert(node->left, gameID, name, developer, publisher, fileSizeGBs, downloads);
        else if ((strComp(gameID, node->gameID)) == 1)
            node->right = insert(node->right, gameID, name, developer, publisher, fileSizeGBs, downloads);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && strComp(gameID, node->left->gameID) == -1)
            return rightRotate(node);

        if (balance < -1 && strComp(gameID, node->right->gameID) == 1)
            return leftRotate(node);

        if (balance > 1 && strComp(gameID, node->left->gameID) == 1) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && strComp(gameID, node->right->gameID) == -1) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void preOrder(GameNode *root) {
        if (root != nullptr) {
            cout << root->gameID << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
};

void generatePlayerAVL(PlayerAVL& playerAVL, string& fileName, int seed) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Failed to open file for loading." << endl;;
        return;
    }

    string line;

    while (getline(file, line)) {
        int random = rand() % 1001;

        if (random < ((seed % 100) * 10 + 100))
            continue;

        string playerID, name, phoneNumber, email, password;

        string gameID;
        float hoursPlayed;
        int achievements;
        GamesPlayedAVL gamePlayedAVL;

        stringstream ss(line);

        getline(ss, playerID, ',');
        getline(ss, name, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        while (getline(ss, gameID, ',')) {
            ss >> hoursPlayed;
            ss.ignore(1, ',');
            ss >> achievements;

            gamePlayedAVL.root = gamePlayedAVL.insert(gamePlayedAVL.root, gameID, hoursPlayed, achievements);
        }

        playerAVL.root = playerAVL.insert(playerAVL.root, playerID, name, phoneNumber, email, password, gamePlayedAVL.root);
    }

    file.close();
}

int main() {
    int seed = 232523;
    srand(seed);

    PlayerAVL playerAVL;
    string playerFile = "Players.txt";

    generatePlayerAVL(playerAVL, playerFile, seed);

    return 0;
}
