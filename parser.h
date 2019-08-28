#include<stdio.h>

#define TOKEN_VALUE_MAX 10
#define SYMBOL_MAX 10

typedef enum {ID =1, INT, REAL, PLUS, MINUS, MUL, DIV, ASSIGN, LP, RP } TOKEN;

typedef struct{
    TOKEN token;
    char value[TOKEN_VALUE_MAX+1];
}TOKEN_LIST;

typedef struct{
    char symbol[SYMBOL_MAX+1];
    TOKEN type;
    union{
	int integer_constant;
	double real_constant;
    }value;
    int set_up;
}SYMBOL_TABLE;
 
typedef struct TreeNode{
    int token_type;
    char token_value[TOKEN_VALUE_MAX+1];
    struct TreeNode * left;
    struct TreeNode * right;
}Tree;

extern TOKEN_LIST token_list[];
extern SYMBOL_TABLE symbol_table[];
extern int token_number;
extern int symbol_number;

Tree* A();
Tree* A_(Tree * a_);
Tree* E();
Tree* E_(Tree* e_);
Tree* T();
Tree* T_(Tree* t_);
Tree* F();
Tree* F_();
void match(int look_ahd);
void syntax_error();
extern void do_syntax_analysis();
int find_symbol(char *target);

extern int l;
extern int index_location;
