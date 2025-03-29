// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <pathfinding.h>

static float _cmp(int i, int j)
    { return m[i].g + m[i].h - m[j].g - m[j].h; }

/// @brief update attributes of m[suc]
/// @param cur index of current cell
/// @param suc index of successor cell
/// @param w new cost from m[src] to m[suc]
static void update_cell(int cur, int suc, float w)
{
    if (m[suc].s == UNVIS) {
        m[suc].g = w;
        set_h(suc, OCTILE);
        m[suc].s = VISED;
        m[suc].p = cur;
        iheap_push(&ih, suc);
    } else if (m[suc].s == VISED && w < m[suc].g) {
        m[suc].g = w;
        m[suc].p = cur;
        iheap_update(&ih, suc);
    }
}

float a_star()
{
    create_iheap(&ih, row * col, _cmp);
    m[src].g = 0;
    set_h(src, OCTILE);
    iheap_push(&ih, src);
    while (ih.cnt) {  // heap not empty
        int cur = iheap_pop(&ih);
        if (cur == tar) {
            destroy_iheap(&ih);
            return m[tar].g;
        }  m[cur].s = EXPND;
        for (int i = 0; i < 8; i++) {
            update_cell(cur,
                cur + dx[i] + dy[i],
                m[cur].g + (i & 1 ? SQRT_2 : 1.0f)
            );
        }
    } destroy_iheap(&ih);
    return -1.0f;
}