#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"
#include "graph.hpp"


typedef struct {
    int *buffer = nullptr;
    int size = 0;
} Array;


void set_fill_and_empty(List *list, Array *fill, Array *empty);


void free_fill_and_empty(Array *fill, Array *empty);


void write_records(List *list, FILE *file, Array *arr);


void write_ranks(FILE *file, size_t count);


void write_edges(List *list, FILE *file, Array *arr);


void write_hidden_edges(List *list, FILE *file);




int generate_file(List *list, FILE *file) {
    Array fill = {}, empty = {};

    set_fill_and_empty(list, &fill, &empty);

    fprintf(file, "digraph G {\n");
    fprintf(file, "rankdir = LR\n");

    write_ranks(file, list -> size);

    write_records(list, file, &fill);

    write_records(list, file, &empty);

    write_hidden_edges(list, file);

    fprintf(file, "edge[color=\"#02e5ca\", fontcolor=\"blue\", fontsize=12];\n");

    for(size_t i = 0; i < list -> size; i++)
        fprintf(file, "{ rank = same; \"%llu\"; \"e%llu\";}\n", i, i);

    write_edges(list, file, &fill);

    write_edges(list, file, &empty);

    fprintf(file, "}\n");

    free_fill_and_empty(&fill, &empty);

    return 0;
}


void set_fill_and_empty(List *list, Array *fill, Array *empty) {
    fill -> buffer = (int *) calloc(list -> size, sizeof(int));

    empty -> buffer = (int *) calloc(list -> size, sizeof(int));

    for(int i = list -> head; i != 0; i = list -> buffer[i].next, fill -> size++)
        fill -> buffer[fill -> size] = i;
    
    for(int i = list -> free; i != list -> size; i = list -> buffer[i].next, empty -> size++)
        empty -> buffer[empty -> size] = i;
}


void free_fill_and_empty(Array *fill, Array *empty) {
    free(fill -> buffer);
    fill -> buffer = nullptr;

    free(empty -> buffer);
    empty -> buffer = nullptr;
}


void write_ranks(FILE *file, size_t count) {
    fprintf(file, "{\n");
    fprintf(file, "    node[shape=plaintext, fontcolor=white];\n");
    fprintf(file, "    edge[color=white]\n");

    fprintf(file, "    ");

    for(size_t i = 0; i < count - 1; i++)
        fprintf(file, "\"%llu\" -> ", i);
    
    fprintf(file, "\"%llu\";\n", count - 1);

    fprintf(file, "}\n");
}


void write_records(List *list, FILE *file, Array *arr) {
    fprintf(file, "{\n");

    fprintf(file, "    node[shape=record, color=\"#355250\", fontsize=14, fontcolor=\"#355250\", style=\"filled\", fillcolor=\"#daf9f4\"];\n");

    for(int i = 0; i < arr -> size; i++) {
        int j = arr -> buffer[i];
        fprintf(file, "    \"e%i\"[label=\"<index> %i | %i |  {<prev> %i | <next> %i}\"];\n", j, j, list -> buffer[j].data, list -> buffer[j].prev, list -> buffer[j].next);
    }

    fprintf(file, "}\n");
}


void write_edges(List *list, FILE *file, Array *arr) {
    for(int i = 0; i < arr -> size; i++) {
        int j = arr -> buffer[i];

        fprintf(file, "\"e%i\":next -> \"e%i\":index;\n", j, list -> buffer[j].next);

        if (list -> buffer[j].prev > -1)
            fprintf(file, "\"e%i\":prev -> \"e%i\":index;\n", j, list -> buffer[j].prev);
    }
}


void write_hidden_edges(List *list, FILE *file) {
    fprintf(file, "{\n");

    fprintf(file, "    edge[color=white, weight = 1000];\n");

    for(size_t i = 0; i < list -> size - 1; i++)
        fprintf(file, "    \"e%llu\" -> \"e%llu\";\n", i, i + 1);
    
    fprintf(file, "}\n");
}


int generate_image() {
    return system("dot graph.txt -Tpng -O");
}
