// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <stdio.h>
#include <graph.h>
#include <time.h>

int main(void)
{
    printf("1\n");
    int n, m, src, tar;
    FILE* in_file = fopen("test0.txt", "r");
    fscanf(in_file, "%d%d%d%d", &n, &m, &src, &tar);
    float h_list[n];
    for (int i = 0; i < n; i++)
        fscanf(in_file, "%f", h_list + i);
    new_graph(n, m, h_list);
    for (int i = 0; i < m; i++) {
        int a, b;
        float w;
        fscanf(in_file, "%d%d%f", &a, &b, &w);
        add_edge(a, b, w);
    }
    fclose(in_file);
    print_graph();
    return 0;
}