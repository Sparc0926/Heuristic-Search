// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <pathfinding.h>

float breadth_first_search()
{
    int queue[row * col], head = 0, tail = 0;
    queue[0] = src;
    m[src].g = 0;
    do {
        m[queue[head]].s = BLKED;  // mark expanded
        for (int i = 0; i < 4; i++) {
            int cur = queue[head++];
            int suc = cur + dy[i] * col + dx[i];
            int w = m[cur].g + 1;
            if (m[suc].s == UNVIS) {  // unvisited
                queue[++tail] = suc;
                m[suc].g = w;
                m[suc].p = cur;
                m[suc].s = VISED;  // mark visited
            } else if (m[suc].s == VISED && w < m[suc].g) {
                m[suc].g = w;
                m[suc].p = cur;
            } if (m[tar].s == BLKED)  return m[tar].g;
        }
    } while (head != tail);
    return -1.0f;
}