#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000001

typedef struct Node {
    int count;
    struct Node *edges[26];
} Node;

Node *new_node();

void insert(Node *root, char *word);

void print_trie_rec(Node *root, unsigned char *fix, int length);

void print_trie(Node *root);

void free_node(Node *node);

int main(void) {
    Node *root = (Node *) calloc(sizeof(Node), 1);
    static char word[MAX_LENGTH];
    int ch;
    int i = 0;

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            insert(root, word);
            memset(word, 0, MAX_LENGTH);
            i = 0;
        } else {
            word[i] = ch;
            i++;
        }
    }

    print_trie(root);
    free_node(root);
    return 0;
}

Node *new_node() {
    Node *node = calloc(sizeof(Node), 1);
    node->count = 0;
    return node;
}

void insert(Node *root, char *word) {
    Node *temp = root;

    for (int i = 0; i < strlen(word); i++) {
        if (word[i] < 'a' || word[i] > 'z') return;

        int index = word[i] - 'a';

        if (temp->edges[index] == NULL) temp->edges[index] = new_node();

        temp = temp->edges[index];
    }

    temp->count++;
}

void print_trie_rec(Node *root, unsigned char *fix, int length) {
    if (root == NULL) return;

    fix[length] = '\0';

    for (int i = 0; i < root->count; i++) printf("%s\n", fix);

    for (int i = 0; i < 26; i++) {
        if (root->edges[i] != NULL) {
            fix[length] = i + 'a';
            print_trie_rec(root->edges[i], fix, length + 1);
        }
    }
}

void print_trie(Node *root) {
    static unsigned char fix[MAX_LENGTH];
    print_trie_rec(root, fix, 0);
}

void free_node(Node *node) {
    for (int i = 0; i < 26; i++)
        if (node->edges[i] != NULL) free_node(node->edges[i]);

    free(node);
}
