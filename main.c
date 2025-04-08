// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <stdio.h>
#include <graph.h>
#include <time.h>

int main(void)
{
    int n, m;
    FILE* in_file = fopen("testcases/test1.txt", "r");
    fscanf(in_file, "%d%d%d%d", &n, &m, &src, &tar);
    float h_list[n];
    for (int i = 0; i < n; i++)
        fscanf(in_file, "%f", h_list + i);
    new_graph_static(n, m, h_list);
    for (int i = 0; i < m; i++) {
        int a, b;
        float w;
        fscanf(in_file, "%d%d%f", &a, &b, &w);
        add_edge(a, b, w);
    }
    printf("%.2f\n", search(src, tar));
    for (int i = tar; nodes[i].p != -1; i = nodes[i].p) {
        printf("%d ", i);
    }
    printf("%d\n", src);
    fclose(in_file);
    return 0;
}