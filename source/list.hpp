
typedef struct {
    int data = 0;
    int next = 0;
    int prev = 0;
} Node;


typedef struct {
    Node *buffer = nullptr;
    int head = 0;
    int tail = 0;
    size_t size = 0;
} List;
