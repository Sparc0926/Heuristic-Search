// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <graph.h>

int node_cnt, edge_cnt = 0;  // number of nodes and edges
struct node* nodes = 0;      // array of all nodes
struct edge* edges = 0;      // array of all edges

void new_graph(int node_cnt_, int edge_cnt_, float* h_list) {
    node_cnt = node_cnt_;
    nodes = malloc(node_cnt_ * sizeof(struct node));
    edges = malloc(edge_cnt_ * sizeof(struct edge));
    for (int i = 0; i < node_cnt; i++) {
        nodes[i].g = 3.40282347e+38f;
        nodes[i].h = h_list[i];
        nodes[i].first_edge_id = -1;
    }
}

void delete_graph() {
    if (nodes) { free(nodes); nodes = 0; }
    if (edges) { free(edges); edges = 0; }
}

void add_edge(int node_a_id, int node_b_id, float weight) {
    edges[edge_cnt].to_node_id = node_b_id;
    edges[edge_cnt].next_edge_id = nodes[node_a_id].first_edge_id;
    edges[edge_cnt].w = weight;
    nodes[node_a_id].first_edge_id = edge_cnt++;
}

void print_graph() {
    for (int i = 0; i < node_cnt; i++) {
        printf("node: %d: h: %4.2f\n", i, nodes[i].h);
        struct node* tmp_node = nodes + i;
        for (int j = tmp_node->first_edge_id; j != -1; j = edges[j].next_edge_id)
            printf("\tw: %.2f to: %d\n", edges[j].w, edges[j].to_node_id);
    }
}