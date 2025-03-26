// Copyright (C) 2025 杨锦熠 - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <pathfinding.h>

#define H_U (m[i - col].s == BLKED && m[i - col + dx[d_i]].s != BLKED)
#define H_D (m[i + col].s == BLKED && m[i + col + dx[d_i]].s != BLKED)
#define V_L (m[i - 1].s == BLKED && m[i - 1 + dy[d_i]].s != BLKED)
#define V_R (m[i + 1].s == BLKED && m[i + 1 + dy[d_i]].s != BLKED)
#define D_A (m[i - dx[d_i]].s == BLKED && m[i - dx[d_i] + dy[d_i]].s != BLKED && m[i + dy[d_i]].s != BLKED)
#define D_C (m[i - dy[d_i]].s == BLKED && m[i + dx[d_i] - dy[d_i]].s != BLKED && m[i + dx[d_i]].s != BLKED)

static float _cmp(int i, int j)
    { return m[i].g + m[i].h - m[j].g - m[j].h; }

static int jp_buf;
// new directions nased on forced nerghbors
static char new_d_1[8] = {  2,   8, 8,  2,  8, 128,  32, 32},
            new_d_2[8] = {128, 128, 2, 32, 32,   8, 128,  2};

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

/// @brief search and push all jump points of m[cur] into iheap
/// @param cur index of current point to be expanded
/// @param d_i index of dx[] and dy[], specifying searching direction
/// @return 1 if found a jump point, 0 otherwise
static int push_jp(int cur, int d_i)
{
    d_i &= 7;  // d_i %= 8
    if (d_i & 1) {  // search diagonally
        for (int i = cur + dx[d_i] + dy[d_i]; m[i].s != BLKED; i += dx[d_i] + dy[d_i]) {
            if (i == tar || push_jp(i, d_i + 1) || push_jp(i, d_i - 1));
            else if (D_A)  m[i].d |= new_d_1[d_i];
            else if (D_C)  m[i].d |= new_d_2[d_i];
            else  continue;
            m[i].d |= (1 << d_i);
            update_cell(cur, i, m[cur].g + ABS(i / col - cur / col) * SQRT_2);
            return 1;
        }
    } else if (!d_i || d_i == 4) {  // search horizontally
        for (int i = cur + dx[d_i]; m[i].s != BLKED; i += dx[d_i]) {
            if (i == tar);
            else if (m[i + dx[d_i]].s == BLKED)  return 0;
            else if (H_U)  m[i].d |= new_d_1[d_i];
            else if (H_D)  m[i].d |= new_d_2[d_i];
            else  continue;
            m[i].d |= (1 << d_i);
            update_cell(cur, i, m[jp_buf].g + ABS(cur / col - jp_buf / col) * SQRT_2 + ABS(i - cur));
            return 1;
        }
    } else {  // search vertically
        for (int i = cur + dy[d_i]; m[i].s != BLKED; i += dy[d_i]) {
            if (i == tar);
            else if (m[i + dy[d_i]].s == BLKED)  return 0;
            else if (V_L)  m[i].d |= new_d_1[d_i];
            else if (V_R)  m[i].d |= new_d_2[d_i];
            else  continue;
            m[i].d |= (1 << d_i);
            update_cell(cur, i, m[jp_buf].g + ABS(cur / col - jp_buf / col) * SQRT_2 + ABS(i - cur) / col);
            return 1;
        }
    }
    return 0;
}

float jump_point_search()
{
    create_iheap(&ih, row * col, _cmp);
    m[src].g = 0;
    set_h(src, OCTILE);
    for (int i = 0; i < 8; i++)
        push_jp(jp_buf = src, i);
    while (ih.cnt) {  // heap not empty
        int cur = iheap_pop(&ih);
        if (cur == tar) {
            destroy_iheap(&ih);
            return m[tar].g;
        }
        m[cur].s = EXPND;
        for (int i = 0; i < 8; i++) {
            if (m[cur].d >> i & 1)
                push_jp(jp_buf = cur, i);
        }
    }
    destroy_iheap(&ih);
    return -1.0f;
}