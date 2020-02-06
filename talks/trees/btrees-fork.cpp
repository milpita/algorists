#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} NODE;

NODE* node_create(int value) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    if (node) {
        node->data = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void tree_init(NODE** root) {
    if (root != NULL) {
        *root = NULL;
    }
}

void tree_free(NODE* root) {
    if (root != NULL) {
        tree_free(root->left);
        tree_free(root->right);
        cout << setw(2) << root->data << " ";
        free(root);
    }
}

void tree_insert(NODE** root, int value) {
    if (*root == NULL) {
        *root = node_create(value);
        return;
    }
    if (value < (*root)->data) {
        tree_insert(&((*root)->left), value);
    }
    else {
        tree_insert(&((*root)->right), value);
    }
}

void print_vector(std::vector<int> &a, const char* header) {
    std::cout << header << ":\n";
    for (auto it = a.begin(); it != a.end(); it++) {
        std::cout << setw(2) << *it << " ";
    }
    std::cout << "\n";
}

void print_help(char** argv) {
    cout << "Specify input file:\n" <<
        argv[0] << " --file <filename>\n";
    cout << "File must contain one vector per row\n";
}

void validate_args(int argc, char** argv) {
    if (argc != 3) {
        print_help(argv);
        exit(EXIT_FAILURE);
    }
    if (strncmp("--file", argv[1], 6) !=0) {
        print_help(argv);
        exit(EXIT_FAILURE);
    }
}

void open_file(ifstream &ifs, const char* s) {
    ifs.open(s);
    if (!ifs.is_open()) {
        cout << "Could not open file: " << s << "\n";
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv) {
    validate_args(argc, argv);

    int i;
    string s;
    ifstream ifs;
    open_file(ifs, argv[2]);

    while (std::getline(ifs, s)) {
        std::istringstream iss(s);
        std::vector<int> v;
        std::vector<int>::const_iterator it;
        while (iss >> i)
            v.push_back(i);
        if (!v.size())
            continue;
        print_vector(v, "ORIGINAL");

        NODE *root;
        tree_init(&root);
        for (it = v.begin(); it != v.end(); it++) {
            tree_insert(&root, *it);
        }
        cout << "FREE (POST-ORDER):\n";
        tree_free(root);
    }
    return EXIT_SUCCESS;
}