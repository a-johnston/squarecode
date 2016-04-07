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

/*
 * Performs a 1-step recovery of the data symbols of a block. Requires that the
 * other contributing block to one of this block's direct neighbors has known
 * data. If so, data is recovered and placed into the graph, else the node is
 * left alone.
 *
 * Iteratively finding lost nodes that have these preconditions satisfied
 * should result in data recovery, but more advanced relationships can be used
 * to better exploit the graph structure.
 */
int try_recover(data_graph *graph, int x, int y) {
    data_block *r = get_block(graph, x, y);

    if (r->data != -1) {
        return 0;
    }

    data_block *a, *b, *c, *d;

    a = get_block(graph, x - 1, y);
    b = get_block(graph, x, y - 1);

    c = get_block(graph, x - 1, y + 1); // other dep for a->extra
    d = get_block(graph, x + 1, y - 1); // other dep for b->extra

    if (a->extra != -1 && c->data != -1) {
        r->data = a->extra ^ c->data;
        return 1;
    }

    if (b->extra != -1 && d->data != -1) {
        r->data = b->extra ^ d->data;
    }

    return 0;
}

int iterative_recover(data_graph *graph) {
    int broken  = 0;
    int changed = 1;

    for (int i = 0; i < graph->width * graph->height; i++) {
        if (graph->code[i].data == -1) {
            broken++;
        }
    }

    while (broken > 0) {
        if (!changed) {
            return 0;
        }
        changed = 0;

        for (int x = 0; x < graph->width; x++) {
            for (int y = 0; y < graph->height; y++) {
                if (try_recover(graph, x, y)) {
                    broken--;
                    changed = 1;
                }
            }
        }
    }

    return 1;
}
