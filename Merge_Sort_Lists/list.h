#define LIST_SIZE 10

typedef int ListItem;
typedef struct node *Listptr;

void Create(Listptr *);
int IsEmpty(Listptr);
void InsertAtStart(Listptr *);
void PrintList(Listptr);
void FreeList(Listptr *);
void SortList(Listptr *);
void InsertSort(Listptr *, Listptr);
Listptr Sort2Lists(Listptr *, Listptr *);
