#define DEFAULT_DATA_BLOCK (data_block) { -1, -1 }

typedef struct {
    int data;
    int extra;
} data_block;

typedef struct {
    data_block *code;
    int width;
    int height;
} data_graph;

int mod(int, int);

data_graph* make_graph(int, int);

void free_graph(data_graph*);

void put_block(data_graph*, data_block, int, int);

data_block* get_block(data_graph*, int, int);

void make_extra(data_block*, data_block*, data_block*);

void make_extras(data_graph*);

int try_recover(data_graph*, int, int);
