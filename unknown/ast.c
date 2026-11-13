#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node *left, *right;
};

char s[100];
int pos = 0, reg = 0;

struct Node* create(char ch) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = ch;
    n->left = n->right = NULL;
    return n;
}

struct Node* expression();

struct Node* factor() {
    if (s[pos] == '(') {
        pos++;
        struct Node *n = expression();
        pos++;
        return n;
    }
    return create(s[pos++]);
}

struct Node* term() {
    struct Node *x = factor();
    while (s[pos] == '*' || s[pos] == '/') {
        char op = s[pos++];
        struct Node *n = create(op);
        n->left = x;
        n->right = factor();
        x = n;
    }
    return x;
}

struct Node* expression() {
    struct Node *x = term();
    while (s[pos] == '+' || s[pos] == '-') {
        char op = s[pos++];
        struct Node *n = create(op);
        n->left = x;
        n->right = term();
        x = n;
    }
    return x;
}

int generate(struct Node *n) {
    if (!n->left && !n->right) {
        int r = reg++;
        printf("MOV R%d, %c\n", r, n->data);
        return r;
    }

    int r1 = generate(n->left);
    int r2 = generate(n->right);

    char *op;
    switch (n->data) {
        case '+': op = "ADD"; break;
        case '-': op = "SUB"; break;
        case '*': op = "MUL"; break;
        case '/': op = "DIV"; break;
    }

    printf("%s R%d, R%d\n", op, r1, r2);
    return r1;
}

int main() {
    char lhs[20];
    printf("Enter expression: ");
    scanf("%19[^=]=%99s", lhs, s);

    struct Node *root = expression();

    printf("\nMachine Code:\n");
    int r = generate(root);
    printf("MOV %s, R%d\n", lhs, r);

    return 0;
}