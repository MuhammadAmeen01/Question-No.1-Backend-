
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ADD, SUB, MUL, DIV, CONST, VAR //typtag enumeration, used for arithmetic operators
} TypeTag;

typedef struct Node { //structure in c, which includes value, type and left and right node type pointers
    TypeTag type;
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Memo { //structure in C, used to store values and key which is precalculated.
    int key;
    int value;
} Memo;

Memo memo[1000]; //defines the structure array.
int memo_len = 0;

int fibonacci_using_Memoization(int n) {  //fibonacci function which used Memoization method of dynamic programming.
    printf("n: %d \n",n);
    if (n <= 1) {
        return n;
    }
    for (int i = 0; i < memo_len; i++) {
        if (memo[i].key == n) {
            return memo[i].value;
        }
    }
    int result = fibonacci_using_Memoization(n - 1) + fibonacci_using_Memoization(n - 2);
    memo[memo_len].key = n;
    memo[memo_len].value = result;
    memo_len++;
    return result;
}


int fibonacci_using_bottomUp_Approach(int n) { //Bottom up approach of Dynamic programming, which solves the smaller problem first and use it compute further problems.
    if (n <= 1) {
        return n;
    }
    int prev2 = 0;
    int prev1 = 1;
    int fib = 0;

    for (int i = 2; i <= n; i++) {
        fib = prev2 + prev1;
        prev2 = prev1;
        prev1 = fib;
    }

    return fib;
}

int fibonacci_Iterative_Approach(int n) { //Iterative Approach of Dynamic Programming, which uses loop to iterate through fix size of iteration, and compute the result.
    if (n <= 1) {
        return n;
    }
    int a = 1, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}


Node *makeConst(int value) {
    Node *node = malloc(sizeof(Node));
    node->type = CONST;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *makeVar() {
    Node *node = malloc(sizeof(Node));
    node->type = VAR;
    node->value = 0; // initialize value to 0
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *makeFunc(TypeTag type) {
    Node *node = malloc(sizeof(Node)); //this function assign the operator that is sent as paramter to the node.
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int calc(Node *node) { //recursive function to call calc method, which compute the result based on node type and return back the value.
    switch (node->type) {
        case ADD:
            return calc(node->left) + calc(node->right);
        case SUB:
            return calc(node->left) - calc(node->right);
        case MUL:
            return calc(node->left) * calc(node->right);
        case DIV:
            return calc(node->left) / calc(node->right);
        case CONST:
            return node->value;
        case VAR:
            return (node->value-2);
    }
    return 0;
}

int main() {
    //main method to call other defined functions.
    Node *add = makeFunc(ADD);
    add->left = makeConst(10);
    add->right = makeConst(6);
    int addResult = calc(add);

    Node *mul = makeFunc(MUL);
    mul->left = makeConst(5);
    mul->right = makeConst(4);
    int mulResult = calc(mul);

    Node *sub = makeFunc(SUB);
    sub->left = add;
    sub->right = mul;
    int subResult = calc(sub);

    Node *fibo = makeFunc(SUB);
    fibo->left = sub;
    fibo->right =makeVar();
    int var1 = calc(fibo);
    int fiboResult1=fibonacci_using_bottomUp_Approach(var1);
    int fiboResult2=fibonacci_Iterative_Approach(var1);
    int fiboResult3=fibonacci_using_Memoization(var1);

    printf("add : %d\n", addResult);
    printf("mul : %d\n", mulResult);
    printf("sub : %d\n", subResult);
    printf("fibonacci using bottomUp Approach : %d\n", -fiboResult1);
    printf("fibonacci Iterative Approach : %d\n", -fiboResult2);
    printf("fibonacci using Memoization : %d\n", -fiboResult3);

    return 0;
}

