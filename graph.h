// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <iheap.h>

extern int node_cnt, edge_cnt;   // number of nodes and edges
extern struct node* nodes;       // array of all nodes
extern struct edge* edges;       // array of all edges
extern int src, tar;             // source and target nodes in search

#define SWAP(A, B) { int tmp = A; A = B, B = tmp; }

struct node {
    float g, h;
    int p;
    int first_edge_id;
};
struct edge {
    float w;
    int next_edge_id;
    int to_node_id;
};

void new_graph_static(int node_cnt_, int edge_cnt_, float* h_list);
void new_graph_dynamic(int node_cnt_, int edge_cnt_);
void delete_graph();
void add_edge(int node_a_id, int node_b_id, float weight);

float search(int src, int tar);

void print_graph();

#endif//GRAPH_H