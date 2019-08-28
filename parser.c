#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"parser.h"

Tree* A();
Tree* A_(Tree * a_);
Tree* E();
Tree* E_(Tree * e_);
Tree* T();
Tree* T_(Tree * t_);
Tree* F();
Tree* F_();

Tree* mkTree(TOKEN type,char*vl);

int not_defined(TOKEN_LIST t[]);
void match(int a);
void syntax_error();
void do_syntax_analysis();
double cal(Tree* rtnode);
void Free_tree(Tree* node);

int s_error;
int l;
int index_location;

void do_syntax_analysis()
{
    s_error = 0;
    index_location = 0;
    l = token_list[index_location].token;
    Tree* root = A();
    if(s_error == 1||index_location+1!=token_number)
    {
	printf("syntax error\n");
	Free_tree(root);
	return;
    }
    if(not_defined(token_list) == 1)
    {
	Free_tree(root);
	return;
    }
    double result = cal(root);
    if(result-(int)(result)==0)
    {
	printf("%d\n",(int)(result));
    }
    else
    {
	printf("%f\n",result);
    }
    Free_tree(root);
    return;
}

Tree* A()
{
    if(l==1)
    {
//	printf("A->idA'\n");
	Tree* temp1 = mkTree(token_list[index_location].token,token_list[index_location].value);
	match(1);
	return A_(temp1);
    }
    else if(l==9|l==2|l==3|l==5)
    {
//	printf("A->F'T'E'\n");
	Tree* temp2;
	temp2 = F_();
	temp2 = T_(temp2);
	return E_(temp2);
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* A_(Tree* a_)
{
    if(l==4|l==5|l==6|l==7|l==0)
    {
//	printf("A'->T'E'\n");
	a_ = T_(a_);
	a_ = E_(a_);
	return a_;
    }
    else if(l==8)
    {
//	printf("A'->=A\n");
	Tree* temp3 = mkTree(token_list[index_location].token,token_list[index_location].value);
	match(8);
	temp3->left = a_;
	temp3->right = A();
	return temp3;
    }

    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* E()
{
    if(l==1|l==9|l==2|l==3|l==5)
    {
//	printf("E->TE'\n");
	Tree* temp15;
	temp15 = T();
	temp15 = E_(temp15);
	return temp15;
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* E_(Tree* e_)
{
    if(l==10|l==0)
    {
//	printf("E'->e\n");
	match(0);
	return e_;
    }
    else if(l==4)
    {
//	printf("E'->+TE'\n");
	Tree* temp4 = mkTree(token_list[index_location].token,"+");
	match(4);
	temp4->left = e_;
	temp4->right = T();
	return E_(temp4);
    }
    else if(l==5)
    {
//	printf("E'->-TE'\n");
	Tree *temp5 = mkTree(token_list[index_location].token,"-");
	match(5);
	temp5->left = e_;
	temp5->right = T();
	return E_(temp5);
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* T()
{
    if(l==1|l==9|l==2|l==3|l==5)
    {
//	printf("T->FT'\n");
	Tree* temp14;
	temp14 = F();
	temp14 = T_(temp14);
	return temp14;
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* T_(Tree *t_)
{
    if(l==10|l==5|l==4|l==0)
    {
//	printf("T'->e\n");
	match(0);
	return t_;
    }
    else if(l==6)
    {
//	printf("T'->*FT'\n");
	Tree *temp6 = mkTree(token_list[index_location].token,"*");
	match(6);
	temp6 -> left = t_;
	temp6 -> right = F();
	return T_(temp6);
    }
    else if(l==7)
    {
//	printf("T'->/FT'\n");
	Tree * temp7 = mkTree(token_list[index_location].token,"/");
	match(7);
	temp7 -> left = t_;
	temp7 -> right = F();
	return T_(temp7);
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* F()
{
    if(l==1)
    {
//	printf("F->id\n");
	Tree * temp8 = mkTree(token_list[index_location].token,token_list[index_location].value);
	match(1);
	return temp8;
    }
    else if(l==9|l==2|l==3|l==5)
    {
//	printf("F->F'\n");
	return F_();
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree* F_()
{
    if(l==9)
    {
//	printf("F'->(E)\n");
	Tree* temp12;
	match(9);
	temp12 = E();
	match(10);
	return temp12;
    }
    else if(l==2)
    {
//	printf("F'->int\n");
	Tree* temp11 = mkTree(token_list[index_location].token,token_list[index_location].value);
	match(2);
	return temp11;
    }
    else if(l==3)
    {
//	printf("F'->Double\n");
	Tree* temp13 = mkTree(token_list[index_location].token, token_list[index_location].value);
	match(3);
	return temp13;
    }
    else if(l==5)
    {
//	printf("F'->-F\n");
	Tree* temp9 = mkTree(token_list[index_location].token,"-");
	match(5);
	temp9->left = F();
	return temp9;
    }
    else
    {
	syntax_error();
	return NULL;
    }
}

Tree * mkTree(TOKEN type,char*vl)
{
    Tree * temp1 = (Tree*)malloc(sizeof(Tree));
    temp1->left = NULL;
    temp1->right = NULL;
    temp1->token_type = type;
    strcpy(temp1->token_value,vl);
    return temp1;
}
void Free_tree(Tree * node)
{
    if(node!=NULL)
    {
	Free_tree(node->left);
	Free_tree(node->right);
	free(node);
    }
}

void match(int look_ahd)
{
    if(look_ahd!=0)
    {
	if(look_ahd==token_list[index_location].token)
	{
	    index_location = index_location+1;
	    l = token_list[index_location].token;
	}
	else
	{
	    syntax_error();
	    return;
	}
    }
}
int not_defined(TOKEN_LIST t[])
{
    for(int i=0;i<token_number;i++)
    {
	if(t[i].token==1)
	{
	    if(t[i+1].token!=8&&symbol_table[find_symbol(t[i].value)].set_up==0)
	    {
		printf("%s is not defined\n",t[i].value);
		return 1;
	    }
	}
    }
    return 0;
}

void syntax_error()
{
    s_error = 1;
}

double cal(Tree* rtnode)
{
    double temp_1,temp_2;
    while(rtnode!=NULL)
    {
	if(rtnode->token_type == 1)
	{
	    return symbol_table[find_symbol(rtnode->token_value)].value.real_constant;
	}
	if(rtnode->token_type == 2)
	{
	    return atof(rtnode->token_value);
	}
	if(rtnode->token_type == 3)
	{
	    return atof(rtnode->token_value);
	}
	if(rtnode->token_type == 4)
	{
	    temp_1 = cal(rtnode->left);
	    temp_2 = cal(rtnode->right);
	    return temp_1+temp_2;
	}
	if(rtnode->token_type == 5)
	{
	    if(rtnode->left == NULL && rtnode->right == NULL)
		break;
	    if(rtnode->right == NULL)
		return -cal(rtnode->left);
	    else
	    {
		temp_1 = cal(rtnode->left);
		temp_2 = cal(rtnode->right);
		return temp_1 - temp_2;
	    }
	}
	if(rtnode->token_type == 6)
	{
	    temp_1 = cal(rtnode->left);
	    temp_2 = cal(rtnode->right);
	    return temp_1*temp_2;
	}
	if(rtnode->token_type == 7)
	{
	    temp_1 = cal(rtnode->left);
	    temp_2 = cal(rtnode->right);
	    return temp_1 / temp_2;
	}
	if(rtnode->token_type == 8)
	{
    	    symbol_table[find_symbol(rtnode->left->token_value)].value.real_constant = cal(rtnode->right);
	    symbol_table[find_symbol(rtnode->left->token_value)].set_up=1;
	    return symbol_table[find_symbol(rtnode->left->token_value)].value.real_constant;
	}
    }
}
