#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

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

    int len1 = num1.length() - idxI;
    int len2 = num2.length() - idxJ;

    if (len1 < len2)
        return -1;

    if (len1 > len2)
        return 1;

    for (int i = 0; i < len1; ++i) {
        if (num1[idxI + i] < num2[idxJ + i])
            return -1;

        if (num1[idxI + i] > num2[idxJ + i])
            return 1;
    }

    return 0;
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
    GamesPlayedNode* root;

public:
    GamesPlayedAVL() {
        root = nullptr;
    }

    int height(GamesPlayedNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    GamesPlayedNode *rightRotate(GamesPlayedNode *root) {
        GamesPlayedNode *node = root->left;

        node->right = root;
        root->left = node->right;;

        root->height = 1 + max(height(root->left), height(root->right));
        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    GamesPlayedNode *leftRotate(GamesPlayedNode *root) {
        GamesPlayedNode *node = root->right;

        node->left = root;
        root->right = node->left;;

        root->height = 1 + max(height(root->left), height(root->right));
        node->height = 1 + max(height(node->left), height(node->right));

        return node;
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
    PlayerNode* root;

public:
    PlayerAVL() {
        root = nullptr;
    }

    int height(PlayerNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    PlayerNode *rightRotate(PlayerNode *root) {
        PlayerNode *node = root->left;

        node->right = root;
        root->left = node->right;;

        root->height = 1 + max(height(root->left), height(root->right));
        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    PlayerNode *leftRotate(PlayerNode *root) {
        PlayerNode *node = root->right;

        node->left = root;
        root->right = node->left;;

        root->height = 1 + max(height(root->left), height(root->right));
        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    int getBalance(PlayerNode *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    PlayerNode* insert(PlayerNode* node, const string &playerID, const string &playerName, const string &phoneNumber, const string &email, const string &password, GamesPlayedNode* gamesPlayedRoot) {

        if (node == nullptr)
            return new PlayerNode(playerID, playerName, phoneNumber, email, password, gamesPlayedRoot);

        if ((strComp(playerID, node->playerID)) == -1)
            node->left = insert(node->left, playerID, playerName, phoneNumber, email, password, gamesPlayedRoot);
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
    GameNode* root;

public:
    GameAVL() {
        root = nullptr;
    }

    int height(GameNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    GameNode *rightRotate(GameNode *root) {
        GameNode *node = root->left;

        node->right = root;
        root->left = node->right;;

        root->height = 1 + max(height(root->left), height(root->right));
        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }

    GameNode *leftRotate(GameNode *root) {
        GameNode *node = root->right;

        node->left = root;
        root->right = node->left;;

        root->height = 1 + max(height(root->left), height(root->right));
        node->height = 1 + max(height(node->left), height(node->right));

        return node;
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

int main() {
    // Construct the AVL tree for GameNode
    AVLTree<GameNode, string> gameTree;

    // Sample data for GameNode entries
    vector<GameNode> games = {
        GameNode("G001", "Chess", "GameDevCo", "PubCo", 0.5, 10000),
        GameNode("G002", "Checkers", "GameStudio", "PubInc", 0.4, 8000),
        GameNode("G003", "TicTacToe", "FunGames", "PubWorld", 0.3, 5000)
    };

    // Insert games into the AVL tree
    for (const auto& game : games) {
        gameTree.insert(game.gameID, game);
    }

    cout << "In-order traversal of GameNode AVL tree:" << endl;
    gameTree.print();

    // Construct the AVL tree for PlayerNode
    AVLTree<PlayerNode, string> playerTree;

    // Sample data for GamesPlayedNode entries
    GamesPlayedNode* gamesPlayedRoot1 = nullptr;
    AVLTree<GamesPlayedNode, string> gamesPlayedTree1;
    gamesPlayedTree1.insert("G001", GamesPlayedNode("G001", 10.5, 3));
    gamesPlayedTree1.insert("G002", GamesPlayedNode("G002", 5.0, 1));
    gamesPlayedTree1.insert("G003", GamesPlayedNode("G003", 8.2, 2));
    gamesPlayedRoot1 = gamesPlayedTree1.getRoot();

    // Create PlayerNodes with nested GamesPlayedNode AVL trees
    vector<PlayerNode> players = {
        PlayerNode("P001", "Alice", "123456789", "alice@example.com", "password1", gamesPlayedRoot1),
        PlayerNode("P002", "Bob", "987654321", "bob@example.com", "password2", nullptr),
        PlayerNode("P003", "Carol", "555555555", "carol@example.com", "password3", nullptr)
    };

    // Insert players into the AVL tree
    for (const auto& player : players) {
        playerTree.insert(player.playerID, player);
    }

    cout << "In-order traversal of PlayerNode AVL tree:" << endl;
    playerTree.print();

    return 0;
}
