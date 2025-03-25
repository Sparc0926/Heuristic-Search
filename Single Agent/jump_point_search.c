#include <pathfinding.h>
#include <iheap.h>
#include <stdio.h>

static iheap _iheap;
static float _cmp(int i, int j)
    { return m[i].g + m[i].h - m[j].g - m[j].h; }

static int jp_buf = -1;
static char d_map_1[8] = {  2,   8, 8,  2,  8, 128,  32, 32},
            d_map_2[8] = {128, 128, 2, 32, 32,   8, 128,  2};

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
        iheap_push(&_iheap, suc);
    }
    else if (m[suc].s == VISED && w < m[suc].g) {
        m[suc].g = w;
        m[suc].p = cur;
        iheap_update(&_iheap, suc);
    }
}

/// @brief search and push all jump points of m[cur] into iheap
/// @param cur index of current point to be expanded
/// @param d_i index of dx[] and dy[], specifying searching direction
/// @return jump point index if found, -1 otherwise
static int push_jp(int cur, int d_i)
{
    if (d_i == 8)  d_i = 0;
    if (d_i & 1) {  // search diagonally
        jp_buf = -1;
        for (int i = cur + dx[d_i] + dy[d_i]; m[i].s != BLKED; i += dx[d_i] + dy[d_i]) {
            if (push_jp(i, d_i + 1) || push_jp(i, d_i - 1) || i == tar) {
                update_cell(cur, i, ABS(i / col - cur / col) * SQRT_2);
                if (jp_buf != -1)  m[jp_buf].g += m[i].g;
                m[i].d |= (1 << d_i);
                return i;
            } else if (m[i - dx[d_i]].s == BLKED && m[i - dx[d_i] + dy[d_i]].s != BLKED && m[i + dy[d_i]].s != BLKED) {
                update_cell(cur, i, ABS(i / col - cur / col) * SQRT_2);
                m[i].d |= (1 << d_i);
                return m[i].d |= d_map_1[d_i];
            } else if (m[i - dy[d_i]].s == BLKED && m[i + dx[d_i] - dy[d_i]].s != BLKED && m[i + dx[d_i]].s != BLKED) {
                update_cell(cur, i, ABS(i / col - cur / col) * SQRT_2);
                m[i].d |= (1 << d_i);
                return m[i].d |= d_map_2[d_i];
            }
        }
    } else if (!d_i || d_i == 4) {  // search horizontally
        for (int i = cur + dx[d_i]; m[i].s != BLKED; i += dx[d_i]) {
            if (i == tar) {
                jp_buf = i;
                update_cell(cur, i, ABS(i - cur));
                m[i].d |= (1 << d_i);
                return 1;
            } else if (m[i + dx[d_i]].s == BLKED)  return 0;
            else if (m[i - col].s == BLKED && m[i - col + dx[d_i]].s != BLKED) {
                jp_buf = i;
                update_cell(cur, i, ABS(i - cur));
                m[i].d |= (1 << d_i);
                return m[i].d |= d_map_1[d_i];
            } else if (m[i + col].s == BLKED && m[i + col + dx[d_i]].s != BLKED) {
                jp_buf = i;
                update_cell(cur, i, ABS(i - cur));
                m[i].d |= (1 << d_i);
                return m[i].d |= d_map_2[d_i];
            }
        }
    } else {  // search vertically
        for (int i = cur + dy[d_i]; m[i].s != BLKED; i += dy[d_i]) {
            if (i == tar) {
                jp_buf = i;
                update_cell(cur, i, ABS(i - cur) / col);
                m[i].d |= (1 << d_i);
                return 1;
            } else if (m[i + dy[d_i]].s == BLKED)  return 0;
            else if (m[i - dy[d_i]].s == BLKED && m[i - 1 + dy[d_i]].s != BLKED) {
                jp_buf = i;
                update_cell(cur, i, ABS(i - cur) / col);
                m[i].d |= (1 << d_i);
                return m[i].d |= d_map_1[d_i];
            } else if (m[i + 1].s == BLKED && m[i + 1 + dy[d_i]].s != BLKED) {
                jp_buf = i;
                update_cell(cur, i, ABS(i - cur) / col);
                m[i].d |= (1 << d_i);
                return m[i].d |= d_map_2[d_i];
            }
        }
    }
    return 0;
}

float jump_point_search()
{
    create_iheap(&_iheap, row * col, _cmp);
    m[src].g = 0;
    set_h(src, OCTILE);
    for (int i = 0; i < 8; i++)
        push_jp(src, i);
    while (_iheap.cnt) {  // heap not empty
        int cur = iheap_pop(&_iheap);
        if (cur == tar) {
            destroy_iheap(&_iheap);
            return m[tar].g;
        }
        m[cur].s = EXPND;
        for (int i = 0; i < 8; i++) {
            if (m[cur].d >> i & 1)
                push_jp(cur, i);
        }
    }
    destroy_iheap(&_iheap);
    return -1.0f;
}