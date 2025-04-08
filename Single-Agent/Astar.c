// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <graph.h>

static float _cmp(int i, int j)
    { return m[i].g + m[i].h - m[j].g - m[j].h; }

float search()
{
    struct iheap* ih = new_iheap(node_cnt)
    iheap_push(&ih, src);
    while (ih.cnt) {  // heap not empty
        int cur = iheap_pop(&ih);
        if (cur == tar) {
            
            return m[tar].g;
        } for (int i = 0; i < 8; i++) {
            update_cell(cur,
                cur + dx[i] + dy[i],
                m[cur].g + (i & 1 ? SQRT_2 : 1.0f)
            );
        } m[cur].g = -2.0f;
    }
    return -1.0f;
}