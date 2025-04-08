// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <graph.h>

static float _cmp(int i, int j)
    { return nodes[i].g + nodes[i].h - nodes[j].g - nodes[j].h; }

float search(int src, int tar)
{
    struct iheap* ih = new_iheap(node_cnt, _cmp);
    nodes[src].g = 0.0f;
    iheap_push(ih, src);
    while (ih->cnt) {  // iheap not empty
        int cur = iheap_pop(ih);
        printf("%d: %f\n", cur, nodes[cur].g + nodes[cur].h);
        if (cur == tar) {
            delete_iheap(ih);
            return nodes[tar].g;
        }
        for (int i = nodes[cur].first_edge_id; i != -1; i = edges[i].next_edge_id) {
            int suc = edges[i].to_node_id;
            if (nodes[suc].g == 3.40282347e+38f) {
                nodes[suc].g = nodes[cur].g + edges[i].w;
                nodes[suc].p = cur;
                iheap_push(ih, suc);
            } else if (nodes[cur].g + edges[i].w < nodes[suc].g) {
                nodes[suc].g = nodes[cur].g + edges[i].w;
                nodes[suc].p = cur;
                iheap_update(ih, suc);
            }
        }
        nodes[cur].g = -1.0f;
    }
    delete_iheap(ih);
    return -1.0f;
}