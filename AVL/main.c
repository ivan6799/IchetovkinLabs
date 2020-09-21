#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    int height;
    struct Node* left;
    struct Node* right;
}Node;


int height(Node* head)
{
	return head?head->height:0;
}

int bfactor(Node* head)
{
	return height(head->right)-height(head->left);
}

void fixheight(Node* head)
{
	head->height = (height(head->left)>height(head->right)?height(head->left):height(head->right))+1;
}

Node* rotateright(Node* head) // правый поворот
{
	Node* tmp = head->left;
	head->left = tmp->right;
	tmp->right = head;
	fixheight(head);
	fixheight(tmp);
	return tmp;
}

Node* rotateleft(Node* head) // левый поворот
{
	Node* tmp = head->right;
	head->right = tmp->left;
	tmp->left = head;
	fixheight(head);
	fixheight(tmp);
	return tmp;
}

Node* balance(Node* head) // балансировка
{
	fixheight(head);
	if( bfactor(head)==2 )
	{
		if( bfactor(head->right) < 0 )
			head->right = rotateright(head->right);
		return rotateleft(head);
	}
	if( bfactor(head)==-2 )
	{
		if( bfactor(head->left) > 0  )
			head->left = rotateleft(head->left);
		return rotateright(head);
	}
	return head;
}

Node* push(Node* head, int k)
{
	if( head==NULL )
    {
        Node *tmp = (Node*)malloc(sizeof(Node));
        if(!tmp)
        {
            printf("Allocation error.");
            return 0;
        }
        tmp->data = k;
        tmp->height = 1;
        tmp->left = NULL;
        tmp->right = NULL;
        return tmp;
    }
	if( k<head->data )
		head->left = push(head->left,k);
	else
		head->right = push(head->right,k);
	return balance(head);
}

int main()
{
    int a,b;
    Node* head = NULL;
    scanf("%d", &a);
    if( a == 0) {printf("%d", a); return 0;}
    while(a)
    {
        scanf("%d", &b);
        head = push(head, b);
        a--;
    }

    printf("%d", head->height);
    return 0;
}
