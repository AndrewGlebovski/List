
typedef struct {
    int data = 0;
    int next = 0;
    int prev = 0;
} Node;


typedef struct {
    Node *buffer = nullptr;
    int head = 0;
    int tail = 0;
    int free = 0;
    size_t size = 0;
} List;


int construct(List *list, size_t size);


int resize(List *list, size_t new_size);


[[nodiscard]] int insert(List *list, int index, int value);


int remove(List *list, int index);


int destruct(List *list);


int dump(List *list);
