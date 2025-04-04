// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <stdio.h>
#include <pathfinding.h>
#include <time.h>

int main(void)
{
    //da2-map/ht_0_hightown_a2.map
    load_map_static("dao-map/arena.map");
    // begin pathfinding
    float cost = 0.0f;
    time_t begin = clock();
    cost = search();
    time_t end = clock();
    if (cost >= 0) {
        printf("Path found with %.1f cost and %ld CPU clocks.\nSee details in output.ppm.\n", cost, end - begin);
    } else  printf("Path not found.\n");
    unload_map();
    
    return 0;
}