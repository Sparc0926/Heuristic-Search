#include <graph.h>

static float f_bound, min;
static char* vis = 0;

/// @brief deepen from m[cur] towards m[tar]
/// @param cur index of current node
/// @param g m[cur].g
static void deepen(int cur, float g)
{
    if (cur == tar)  return;
    for (int i = nodes[cur].first_edge_id; i != -1; i = edges[i].next_edge_id) {
        int suc = edges[i].to_node_id;
        if (nodes[suc].g < 0.0f)  continue;
        nodes[suc].g = g + edges[i].w;
        float f = nodes[suc].g + nodes[suc].h;
        if (f <= f_bound) {
            nodes[cur].g = -1.0f;
            nodes[suc].p = cur;
            deepen(suc, nodes[suc].g);
            nodes[cur].g = g;
        } else if (f < min) {
            min = f;
            return;
        }
    }
}

float search()
{
    nodes[src].g = 0.0f;
    f_bound = nodes[src].h;
    while (nodes[tar].g == 3.402823466e+38f) {
        //printf("call\n");
        min = 3.402823466e+38f;
        deepen(src, 0);
        f_bound = min;
    }
    return nodes[tar].g;
}