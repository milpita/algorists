#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} NODE;

NODE* create_node(int value) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    if (node) {
        node->data = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void init_tree(NODE** root) {
    if (root != NULL) {
        *root = NULL;
    }
}

void free_tree(NODE* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
        std::cout << "freed node\n";
    }
}

void insert_tree(NODE** root, int value) {
    if (*root == NULL) {
        *root = create_node(value);
        std::cout << "created node: " << value << "\n";
        return;
    }
    if (value < (*root)->data) {
        insert_tree(&((*root)->left), value);
    }
    else {
        insert_tree(&((*root)->right), value);
    }
}

void print_vector(std::vector<int> &a) {
    std::cout << "original:\n";
    for (auto it = a.begin(); it != a.end(); it++) {
        std::cout << *it << ((it != a.end() - 1) ? ", " : "\n");
    }
}

void print_help(char** argv) {
    cout << "Specify input file:\n" <<
        argv[0] << " --file <filename>\n";
    cout << "File must contain one vector per row\n";
}

int main(int argc, char** argv) {
    if (argc != 3) {
        print_help(argv);
        return EXIT_FAILURE;
    }
    if (strncmp("--file", argv[1], 6) !=0) {
        print_help(argv);
        return EXIT_FAILURE;
    }

    string s = argv[2];
    ifstream ifs(s);
    if (!ifs) {
        cout << "Could not open file: " << s << "\n";
        return EXIT_FAILURE;
    }
    while (std::getline(ifs, s)) {
        std::istringstream iss(s);
        std::vector<int> v;
        int i;
        while (iss >> i) {
            v.push_back(i);
        }
        if (v.size() > 0) {
            print_vector(v);
            NODE *root;
            init_tree(&root);
            for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
                insert_tree(&root, *it);
            }
            free_tree(root);
        }
    }
    return EXIT_SUCCESS;
}