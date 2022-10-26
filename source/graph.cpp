#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"
#include "graph.hpp"


void write_records(List *list, FILE *file, int from, int to);


void write_ranks(FILE *file, size_t count);


void write_edges(List *list, FILE *file, int from, int to);


void write_hidden_edges(List *list, FILE *file);




int generate_file(List *list, FILE *file) {
    fprintf(file, "digraph G {\n");
    fprintf(file, "rankdir = LR\n");

    write_ranks(file, list -> size);

    write_records(list, file, list -> head, 0);

    write_records(list, file, list -> free, (int) list -> size);

    write_hidden_edges(list, file);

    fprintf(file, "edge[color=\"#02e5ca\", fontcolor=\"blue\", fontsize=12];\n");

    for(size_t i = 0; i < list -> size; i++)
        fprintf(file, "{ rank = same; \"%llu\"; \"e%llu\";}\n", i, i);

    write_edges(list, file, list -> head, 0);

    write_edges(list, file, list -> free, (int) list -> size);

    fprintf(file, "}\n");

    return 0;
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


void write_records(List *list, FILE *file, int from, int to) {
    fprintf(file, "{\n");

    fprintf(file, "    node[shape=record, color=\"#355250\", fontsize=14, fontcolor=\"#355250\", style=\"filled\", fillcolor=\"#daf9f4\"];\n");

    for(int j = from; j != to; j = list -> buffer[j].next)
        fprintf(file, "    \"e%i\"[label=\"<index> %i | %i |  {<prev> %i | <next> %i}\"];\n", j, j, list -> buffer[j].data, list -> buffer[j].prev, list -> buffer[j].next);

    fprintf(file, "}\n");
}


void write_edges(List *list, FILE *file, int from, int to) {
    for(int j = from; j != to; j = list -> buffer[j].next) {
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
