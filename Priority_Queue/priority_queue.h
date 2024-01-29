#define MAXCOUNT 20

typedef int PQItem;
typedef struct PQueue PriorityQueue;
typedef struct PQNodeTag PQListNode;
typedef PQItem SortingArray[MAXCOUNT];

void Initialize(PriorityQueue *);
int Empty(PriorityQueue *);
int Full(PriorityQueue *);
void PriorityQueueSort(SortingArray);
void Insert(PQItem, PriorityQueue *);
PQListNode *SortedInsert(PQItem, PQListNode *);
PQItem Remove(PriorityQueue *);
