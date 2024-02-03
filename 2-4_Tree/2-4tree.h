#define NULLITEM -1
#define SIZE 4

typedef int Item;
typedef struct STnode *link;

// Requested Functions
void STinit(void);
int STcount(void);
void STinsert(Item);
int STsearch(Item);
void STdelete(Item);
Item STselect(int);
void STsort(void);
void STdelete_Tree(void);

// Other Functions
link Create(void);
void Count_Items(link);
int Search_Item(link, Item);
void Select_Item(link, int);
void Print_Sorted(link);
link Insert_Tree(link, Item);
link Insert_Key(link, Item);
link Rearrange(link, int);
int Node_Overflow(link);
link Check_Overflow(link);
link Root_Overflow(link);
void Delete(link);