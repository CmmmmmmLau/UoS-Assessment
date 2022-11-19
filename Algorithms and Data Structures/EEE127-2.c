#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
The expression tree of y=(3 + x) * (2 / x) is:
         y
         ↑
         *
      /    \
     +      /
   /  \   /  \
  3    x x    2
*/

typedef struct BTNodes{
    char data;
    struct BTNodes *LeftChild;
    struct BTNodes *RightChild;
}BTNode;
// Using struct to define a basic struct type for binary tree node

BTNode  *newNode(char data){
    BTNode *node = malloc(sizeof(BTNode));//allocate memory to the node
    node->data = data;
    node->LeftChild = node->RightChild = NULL;
    return node;
}
//a template function for define a new node

void destoryBTree(BTNode *tree){
    if(tree->RightChild != NULL){
        destoryBTree(tree->RightChild);
    }
    if(tree->LeftChild != NULL){
        destoryBTree(tree->LeftChild);
    }
    free(tree);
}
/*
 * traverse the tree and release the memory of each node.
 */

BTNode *buildBTree(char data[], int *index){
    int status = 0;
    /*  status 0:
     *  looking for a '(' or an integer number for left child node.
     *  If the character is '(', than using recursion into a new state machine.
     *  If the character is an integer number, than assign the value to current node->data
     *
     *  status 1:
     *  looking for an arithmetic operations character{ +, −, ×, ÷}.
     *  then assign the operation to  current node->data.
     *
     *  status 2:
     *  looking for an integer number for right child node.
     *  then assign the value to  current node->data.
     */
    int length = strlen(data); //evaluate the length of the string
    BTNode *node = NULL;
    node = malloc(sizeof(BTNode));

    while (*index < length){
        char ch = data[*index];

        if(ch == ')'){
            ++*index;
            ch = data[*index];
        }//skip the ')'

        switch (status) {
            case 0:
                if(ch == '('){
                    ++*index;//swap to next char
                    node->LeftChild = buildBTree(data, index);
                    // if the char is '(', than recursion into a sub-expression
                    if(data[*index] != ')'){
                        printf("ERROR, invalid sub-expression");
                        exit(1);
                    }//the sub-expression must be ended as ')', if not, it mean the algebraic expression is invalid.
                } else if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')){
                    ++*index;
                    node->LeftChild = newNode(ch);
                    //assign the number to current node->data
                } else{
                    printf("ERROR, invalid operand");
                    exit(1);
                }

                status = 1;
                //swap the status
                break;
            case 1:
                if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
                    ++*index;
                    node->data = ch;
                    //assign the operation to current node->data.
                } else{
                    printf("ERROR, invalid operand");
                    exit(1);
                }

                status = 2;
                break;
            case 2:
                if(ch == '('){
                    ++*index;
                    node->RightChild = buildBTree(data, index);
                    if(data[*index] != ')') {
                        printf("ERROR, invalid sub-expression");
                        exit(1);
                    }
                } else if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')){
                    ++*index;
                    node->RightChild = newNode(ch);
                } else {
                    printf("ERROR, invalid operand");
                    exit(1);
                }//same idea for status 0.
                return node;
        }
    }
    return node;
}
/*
 * This snippet of code used as a state machine to build an expression tree.
 * It will base on the input character to change to different stage.
 * Each stage have different event and action.
 * The whole algebraic expression can be break down into different sub-expression base on the round bracket
 * And each sub-expression must be contained 3 elements: an LHS number, an arithmetic operation and RHS is number.
 * such as (4*1) * (4-1) can be break down as two sub-expression 4*1 and 4-1.
 * Then evaluate and return it.
 *
 * So the important part is how the code detect where is a sub-expression
 * than go into a sub state machine
 * until it reach a number
 */

void traverseBTree(BTNode *root){
    if(root){
        if(root->LeftChild){
            printf("(");
        }
        traverseBTree(root->LeftChild);
        printf("%c ", root->data);
        traverseBTree(root->RightChild);
        if(root->RightChild){
            printf(")");
        }
    }
}
/*
 * using recursion to print the tree.
 * This function will print the node
 * from left to right in horizontal position according to each node
 */

float calculateBTree(BTNode *node, char variable, int valueOfX){
    if (node->data == '+'){
        return (calculateBTree(node->LeftChild, variable, valueOfX) + calculateBTree(node->RightChild, variable, valueOfX));
    } else if (node->data == '-'){
        return (calculateBTree(node->LeftChild, variable, valueOfX) - calculateBTree(node->RightChild, variable, valueOfX));
    } else if (node->data == '*'){
        return (calculateBTree(node->LeftChild, variable, valueOfX) * calculateBTree(node->RightChild, variable, valueOfX));
    } else if (node->data == '/'){
        return (calculateBTree(node->LeftChild, variable, valueOfX) / calculateBTree(node->RightChild, variable, valueOfX));
    } else if (node->data >= '0' && node->data <= '9'){
        return (node->data - '0');
    } else if((node->data >= 'a' && node->data <= 'z') || (node->data >= 'A' && node->data <= 'Z')){
        if(node->data == variable){
            return valueOfX;
        }
    } else{
        printf("\nOops, something went wrong with the expression tree!\n");
    }
}
/*
 * to evaluate the whole is recursion of the tree.
 * if the data is an arithmetic operations{ +, −, ×, ÷}
 * then recursion into the same function again
 * if the data is an integer number or variable then return the number or value of variable
 */

int main (void){
    int x = 0, index = 0;
    char equation[] = "(3+x)*(2/x)";
    float result;

    BTNode *root = NULL;

    printf("The algebraic expression is : %s\n", equation);

    do {
        printf("Please enter the value of X:\n");
        scanf("%d", &x);
        if(x == 0){
            printf("Please enter a non-zero value!\n");
        }
    } while (x == 0);

    root = buildBTree(equation, &index);
    printf("\nNow printing the algebraic expression from binary tree!\n");
    traverseBTree(root);

    result = calculateBTree(root, 'x', x);
    printf("\nThe calculated result from the expression tree is : %.1f", result);
    destoryBTree(root);
    return 0;
}