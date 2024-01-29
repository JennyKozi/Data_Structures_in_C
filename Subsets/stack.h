#define STACK_SIZE 100

typedef int StackItem;

typedef struct stack {
	int count;
	StackItem items[STACK_SIZE];
} Stack;

void Initialize(Stack *);
int Empty(Stack *);
int Full(Stack *);
void Push(Stack *, StackItem);
void Pop(Stack *, StackItem *);
int Size(Stack *);
int Search(Stack *, StackItem);
StackItem Find(Stack *, int);
