// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <stdio.h>
#include <stdlib.h>
#include <pathfinding.h>
#include <time.h>

int main()
{
    //da2-map/ht_0_hightown_a2.map
    int row, col, src, tar;
    FILE* map_src = fopen("da2-map/ht_0_hightown_a2.map", "r");
    fscanf(map_src, "type octile\nheight %d\nwidth %d\nmap\n", &row, &col);
    // read in map from file as a string
    char* str_m = (char*)malloc(row * col * sizeof(char)), tmp;
    int cnt = 0;  // iteration counter through the file
    while ((tmp = fgetc(map_src)) != EOF) {
        if (tmp == '\n')  continue;
        if (tmp == 's')  src = cnt;
        else if (tmp == 't')  tar = cnt;
        str_m[cnt++] = tmp;
    }
    fclose(map_src);
    // convert string into struct map
    struct map* m = (struct map*)malloc(row * col * sizeof(struct map));
    str_m[src] = str_m[tar] = '.';
    for (int i = 0; i < row * col; i++) {
        if (str_m[i] == '.')  m[i].s = UNVIS;
        else  m[i].s = BLKED;
    }
    // begin pathfinding
    load_map(m, row, col);
    set_src_tar(src, tar);
    float cost = 0.0f;
    time_t begin = clock();
    #ifdef dijkstra_D
    cost = dijkstra();
    #endif
    #ifdef a_star_D
    cost = a_star();
    #endif
    #ifdef jump_point_search_D
    cost = jump_point_search();
    #endif
    time_t end = clock();
    if (cost >= 0) {
        printf("Path found with %.1f cost and %ld CPU clocks.\nSee details in output.ppm.\n", cost, end - begin);
        write_path(str_m);
    } else  printf("Path not found.\n");
    free(str_m);
    free(m);

    return 0;
}