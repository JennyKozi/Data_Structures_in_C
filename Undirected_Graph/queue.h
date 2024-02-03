typedef int ItemType;

typedef struct QueueNodeTag {
	ItemType Item;
	struct QueueNodeTag *Link;
} QueueNode;

typedef struct {
	QueueNode *Front;
	QueueNode *Rear;
} Queue;

void InitializeQueue(Queue *);
int Empty(Queue *);
int Full(Queue *);
void Insert(ItemType, Queue *);
void Remove(Queue *, ItemType *);
