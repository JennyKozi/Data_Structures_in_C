typedef int ListItem;
typedef struct node *Listptr;

// Requested Functions
void Create(Listptr *, Listptr *, Listptr *);
int Size(Listptr);
int IsEmpty(Listptr);
Listptr GetFirst(Listptr);
Listptr GetLast(Listptr);
Listptr GetPrev(Listptr);
Listptr GetNext(Listptr);
void AddBefore(Listptr *, Listptr *, Listptr *, Listptr *);
void AddAfter(Listptr *, Listptr *, Listptr *);
void AddFirst(Listptr *, Listptr *, Listptr *, Listptr *);
void AddLast(Listptr *, Listptr *, Listptr *, Listptr *);
int Remove(Listptr *, Listptr *, Listptr *, Listptr *, ListItem *);
void Print(Listptr);

// My Functions
void CreateNewNode(Listptr *);
void PrintNode(Listptr);
void PrintReverse(Listptr);
Listptr FindNode(Listptr, int);
Listptr GetNode(Listptr, int);
void FreeList(Listptr *, Listptr *, Listptr *);
