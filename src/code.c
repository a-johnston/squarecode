#include <stdlib.h>
#include <stdio.h>

#include "code.h"

/*
 * Correctly places an integer into its Z/mZ eqiv class
 */
int mod(int x, int m) {
    return x < 0 ? m + (x % m) : x % m;
}

data_graph* make_graph(int width, int height) {
    data_graph *graph = (data_graph*) malloc(sizeof(data_graph));

    *graph = (data_graph) {
        (data_block*) malloc(sizeof(data_block) * width * height),
        width,
        height
    };

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            put_block(graph, DEFAULT_DATA_BLOCK, x, y);
        }
    }

    return graph;
}

void free_graph(data_graph *graph) {
    free(graph->code);
    free(graph);
}

void put_block(data_graph *graph, data_block block, int x, int y) {
    x = mod(x, graph->width);
    y = mod(y, graph->height);
    graph->code[x + y * graph->width] = block;
}

data_block* get_block(data_graph *graph, int x, int y) {
    x = mod(x, graph->width);
    y = mod(y, graph->height);
    return &graph->code[x + y * graph->width];
}

void make_extra(data_block *a, data_block *b, data_block *ab) {
    ab->extra = a->data ^ b->data;
}

void make_extras(data_graph *graph) {
    for (int x = 0; x < graph->width; x++) {
        for (int y = 0; y < graph->height; y++) {
            make_extra(get_block(graph, x + 1, y),
                       get_block(graph, x, y + 1),
                       get_block(graph, x, y));
        }
    }
}

int try_recover(data_graph *graph, int x, int y) {
    return 0;
}

int main(void) {
    //data_graph *graph = make_graph(10, 10);

    //free_graph(graph);

    printf("%d %d", mod(-5, 4), mod(10, 4));
}
