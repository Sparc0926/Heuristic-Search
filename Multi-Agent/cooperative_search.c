// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <pathfinding.h>

static int agt = 2, s[2] = {55, 70}, t[2] = {49, 31};

static void clear_map()
{
    int i = row * col;
    while (i--) {
        m[i].s &= 4;  // set non-blocked cells unvisited
        m[i].g = 0;   // set g value to 0
    }
    // add walls on former agent's path
    for (int i = tar; i != src; i = m[i].p) {
        int dx_ = NORM(m[i].p % col - i % col),
            dy_ = NORM(m[i].p / col - i / col) * col;
        for (int j = i; j != m[i].p; j += dx_ + dy_)
            m[j].s = BLKED;
    }
}

float cooperative_search()
{
    int i = 1;
    set_src_tar(s[0], t[0]);
    float sum = jump_point_search();
    if (sum < 0.0f)  return -1.0f;
    do { clear_map();
        set_src_tar(s[i], t[i]);
        float cost = jump_point_search();
        if (cost >= 0.0f)  sum += cost;
        else  return -1.0f;
        i++;
    } while (i != agt);
    return sum;
}