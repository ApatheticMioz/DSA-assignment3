#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int countFileLines(const string &fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return 0;
    }

    int lines = 0;
    string line;
    while (getline(file, line)) {
        lines++;
    }

    file.close();

    return lines;
}

int countCommas(const string& line) {
    int count = 0;
    stringstream ss(line);
    string entry;

    while (getline(ss, entry, ',')) {
        count++;
    }

    return count/3;
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
        else {
            cout << "Duplicate value entered, not added." << endl;
            return node;
        }

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

    GamesPlayedNode* search(GamesPlayedNode* node, const string& gameID) {
        if (node == nullptr)
            return nullptr;

        if (node->gameID == gameID)
            return node;

        if (strComp(gameID, node->gameID) == -1)
            return search(node->left, gameID);

        return search(node->right, gameID);
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
        else {
            cout << "Duplicate value entered, not added." << endl;
            return node;
        }

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

    PlayerNode* search(PlayerNode* node, const string& playerID) {
        if (node == nullptr)
            return nullptr;

        if (node->playerID == playerID)
            return node;

        if (strComp(playerID, node->playerID) == -1)
            return search(node->left, playerID);

        return search(node->right, playerID);
    }

    PlayerNode * minNode(PlayerNode* node) {
        PlayerNode* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    PlayerNode* deleteNode(PlayerNode* root, string& playerID) {
        if (root == nullptr)
            return root;

        if (strComp(playerID, root->playerID) == -1)
            root->left = deleteNode(root->left, playerID);
        else if (strComp(playerID, root->playerID) == 1)
            root->right = deleteNode(root->right, playerID);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                PlayerNode *temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;

                delete temp;
            } else {
                PlayerNode* temp = minNode(root->right);

                root->playerID = temp->playerID;

                root->right = deleteNode(root->right, temp->playerID);
            }
        }

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        deleteTree(root->gamesPlayedRoot);

        return root;
    }

    void deleteTree(GamesPlayedNode* rootGames) {
        if (rootGames == nullptr) {
            return;
        }

        deleteTree(rootGames->left);
        deleteTree(rootGames->right);

        delete rootGames;
    }

    void saveGamesPlayedInOrder(ofstream& csv, GamesPlayedNode* node) {
        if (node == nullptr)
            return;

        saveGamesPlayedInOrder(csv, node->left);

        csv << node->gameID << ',';
        csv << node->hoursPlayed << ',';
        csv << node->achievements << ',';

        //cout << node->gameID << ' ' << node->hoursPlayed << ' ' << node->achievements;

        saveGamesPlayedInOrder(csv, node->right);
    }

    void saveInOrder(ofstream& csv, PlayerNode* node) {
        if (node == nullptr)
            return;

        saveInOrder(csv, node->left);

        csv << node->playerID << ",";
        csv << node->playerName << ",";
        csv << node->phoneNumber << ",";
        csv << node->email << ",";
        csv << node->password << ",";

        //cout << node->playerID << ' ' << node->playerName << ' ' << node->phoneNumber << ' ' << node->email << ' ' << node->password;

        saveGamesPlayedInOrder(csv, node->gamesPlayedRoot);

        csv << '\n';
        //cout << endl;

        saveInOrder(csv, node->right);
    }

    void saveToCSV(const string& fileName) {
        ofstream csv(fileName);

        if (!csv.is_open()) {
            cout << "Failed to open file for saving." << endl;
        }

        csv << "playerID,Name,PhoneNumber,Email,Password,GamesPlayed" << endl;
        saveInOrder(csv, root);

        csv.close();
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
        else {
            cout << "Duplicate value entered, not added." << endl;
            return node;
        }

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

    GameNode* search(GameNode* node, const string& gameID) {
        if (node == nullptr)
            return node;

        if (node->gameID == gameID)
            return node;

        if (strComp(gameID, node->gameID) == -1)
            return search(node->left, gameID);

        return search(node->right, gameID);
    }

    GameNode * minNode(GameNode* node) {
        GameNode* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    GameNode* deleteNode(GameNode* root, string& gameID) {
        if (root == nullptr)
            return root;

        if (strComp(gameID, root->gameID) == -1)
            root->left = deleteNode(root->left, gameID);
        else if (strComp(gameID, root->gameID) == 1)
            root->right = deleteNode(root->right, gameID);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                GameNode *temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;

                delete temp;
            } else {
                GameNode* temp = minNode(root->right);

                root->gameID = temp->gameID;

                root->right = deleteNode(root->right, temp->gameID);
            }
        }

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void saveInOrder(ofstream& csv, GameNode* node) {
        if (node == nullptr)
            return;

        saveInOrder(csv, node->left);

        csv << node->gameID << ",";
        csv << node->name << ",";
        csv << node->developer << ",";
        csv << node->publisher << ",";
        csv << node->fileSizeGBs << ",";
        csv << node->downloads << "\n";

        //cout << node->gameID << ' ' << node->name << ' ' << node->developer << ' ' << node->publisher << ' ' << node->fileSizeGBs << ' ' << node->downloads <<  endl;

        saveInOrder(csv, node->right);
    }

    void saveToCSV(const string& fileName) {
        ofstream csv(fileName);

        if (!csv.is_open()) {
            cout << "Failed to open file for saving." << endl;
        }

        csv << "gameID,name,developer,publisher,fileSizeGBs,downloads" << endl;
        saveInOrder(csv, root);

        csv.close();
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

        GamesPlayedAVL gamePlayedAVL;

        stringstream ss(line);

        getline(ss, playerID, ',');
        getline(ss, name, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        while (ss.good()) {
            string gameID;
            float hoursPlayed;
            int achievements;

            if (!getline(ss, gameID, ','))
                break;

            if (!(ss >> hoursPlayed))
                break;

            ss.ignore(1, ',');

            if (!(ss >> achievements))
                break;

            gamePlayedAVL.root = gamePlayedAVL.insert(gamePlayedAVL.root, gameID, hoursPlayed, achievements);

            ss.ignore(1, ',');
        }

        playerAVL.root = playerAVL.insert(playerAVL.root, playerID, name, phoneNumber, email, password, gamePlayedAVL.root);
    }

    file.close();
}

GamesPlayedNode* generateGamesPlayedAVL_Array(GamesPlayedNode** gamesArray, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    GamesPlayedNode* root = gamesArray[mid];

    root->left = generateGamesPlayedAVL_Array(gamesArray, start, mid - 1);
    root->right = generateGamesPlayedAVL_Array(gamesArray, mid + 1, end);

    return root;
}

GamesPlayedNode* generateGamesPlayedAVL_CSV(const string& line) {
    stringstream ss(line);
    string temp;

    for (int i = 0; i < 5; i++) {
        getline(ss, temp, ',');
    }



    int gamesCount = countCommas(ss.str()) - 1;
    //cout << gamesCount << endl;
    auto** array = new GamesPlayedNode*[gamesCount];

    int index = 0;

    while (ss.good()) {
        string gameID;
        float hoursPlayed;
        int achievements;

        if (!getline(ss, gameID, ','))
            break;

        if (!(ss >> hoursPlayed))
            break;

        ss.ignore(1, ',');

        if (!(ss >> achievements))
            break;

        //cout << gameID << ' ' << hoursPlayed << ' ' << achievements << endl;

        array[index++] = new GamesPlayedNode(gameID, hoursPlayed, achievements);

        ss.ignore(1, ',');
    }

    //cout << "Games played array" << endl;

    return generateGamesPlayedAVL_Array(array, 0, gamesCount - 1);
}

void generatePlayerArray_CSV(string& fileName, PlayerNode**& playerArray, int& playerCount) {
    playerCount = countFileLines(fileName) - 1;
    playerArray = new PlayerNode*[playerCount];

    ifstream csv(fileName);
    string line;

    getline(csv, line);

    int index = 0;

    while (getline(csv, line) && index < playerCount) {
        stringstream ss(line);

        string playerID, playerName, phoneNumber, email, password;

        getline(ss, playerID, ',');
        getline(ss, playerName, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        GamesPlayedAVL gamesPlayedAVL;

        gamesPlayedAVL.root = generateGamesPlayedAVL_CSV(ss.str());
        //cout << "Returned" << endl;

        playerArray[index++] = new PlayerNode(playerID, playerName, phoneNumber, email, password, gamesPlayedAVL.root);
    }

    //cout << "Array generated" << endl;

    csv.close();
}

PlayerNode* generatePlayerAVL_Array(PlayerNode** gamesArray, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    PlayerNode* root = gamesArray[mid];

    root->left = generatePlayerAVL_Array(gamesArray, start, mid - 1);
    root->right = generatePlayerAVL_Array(gamesArray, mid + 1, end);

    return root;
}

void generatePlayerAVL_CSV(PlayerAVL& gameAVL, string& fileName) {
    int gamesCount;
    PlayerNode** playerArray = nullptr;

    generatePlayerArray_CSV(fileName, playerArray, gamesCount);

    gameAVL.root = generatePlayerAVL_Array(playerArray, 0, gamesCount - 1);

    for (int i = 0; i < gamesCount; ++i) {
        delete playerArray[i];
    }
    delete[] playerArray;
}

void generateGameArray_CSV(string& fileName, GameNode**& gamesArray, int& gamesCount) {
    gamesCount = countFileLines(fileName) - 1;
    gamesArray = new GameNode*[gamesCount];

    ifstream csv(fileName);
    string line;

    getline(csv, line);

    int index = 0;

    while (getline(csv, line) && index < gamesCount) {
        stringstream ss(line);

        string gameID, name, developer, publisher, password;
        float sizeInGBs;
        int downloads;

        getline(ss, gameID, ',');
        getline(ss, name, ',');
        getline(ss, developer, ',');
        getline(ss, publisher, ',');
        ss >> sizeInGBs;
        ss.ignore(1, ',');
        ss >> downloads;

        gamesArray[index++] = new GameNode(gameID, name, developer, publisher, sizeInGBs, downloads);
    }

    csv.close();
}

GameNode* generateGameAVL_Array(GameNode** gamesArray, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    GameNode* root = gamesArray[mid];

    root->left = generateGameAVL_Array(gamesArray, start, mid - 1);
    root->right = generateGameAVL_Array(gamesArray, mid + 1, end);

    return root;
}

void generateGameAVL_CSV(GameAVL& gameAVL, string& fileName) {
    int gamesCount;
    GameNode** gamesArray = nullptr;

    generateGameArray_CSV(fileName, gamesArray, gamesCount);

    gameAVL.root = generateGameAVL_Array(gamesArray, 0, gamesCount - 1);

    for (int i = 0; i < gamesCount; ++i) {
        delete gamesArray[i];
    }
    delete[] gamesArray;
}

void generateGameAVL(GameAVL& gameAVL, string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Failed to open file for loading." << endl;;
        return;
    }

    string line;

    while (getline(file, line)) {
        string gameID, name, developer, publisher;
        float sizeInGBs;
        int downloads;

        stringstream ss(line);

        getline(ss, gameID, ',');
        getline(ss, name, ',');
        getline(ss, developer, ',');
        getline(ss, publisher, ',');
        ss >> sizeInGBs;
        ss.ignore(1, ',');
        ss >> downloads;

        gameAVL.root = gameAVL.insert(gameAVL.root, gameID, name, developer, publisher, sizeInGBs, downloads);
    }

    file.close();
}

void menu() {
    cout << "Welcome to the Gamers Database Manager." << endl;
    cout << endl;
    cout << "1. Insertion." << endl;
    cout << "2. Search and Retrieval." << endl;
    cout << "3. Deletion." << endl;
    cout << "4. Save data." << endl;
    cout << "5. Show N Layers." << endl;
    cout << "6. Show Layer Number." << endl;
    cout << "7. Show path." << endl;
    cout << "9. Edit entry. " << endl;
    cout << "10. Top N players." << endl;
    cout << "11. Show details." << endl;
    cout << "12. Has played. " << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

int main() {
    int seed = 232523;
    srand(seed);

    PlayerAVL playerAVL;
    string playerFile = "Players.txt";

    generatePlayerAVL(playerAVL, playerFile, seed);

    GameAVL gamesAVL;
    string gameFile = "Games.txt";

    generateGameAVL(gamesAVL, gameFile);

    string gameCSV = "Games.csv";
    gamesAVL.saveToCSV(gameCSV);
    cout << "Games saved." << endl;
    //gamesAVL.preOrder(gamesAVL.root);

    string playerCSV = "Players.csv";
    playerAVL.saveToCSV(playerCSV);
    cout << "Players saved." << endl;
    cout << "Reloading from hard disk." << endl;

    generateGameAVL_CSV(gamesAVL, gameCSV);
    //gamesAVL.preOrder(gamesAVL.root);

    PlayerAVL temp;
    generatePlayerAVL_CSV(temp, playerCSV);
    string tempPlayers = "tempPlayers.csv";
    temp.saveToCSV(tempPlayers);


    return 0;
}
