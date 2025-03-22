#include <pathfinding.h>
#include <iheap.h>

static iheap _iheap;
static int _cmp(int i, int j)
    { return m[i].g + m[i].h < m[j].g + m[j].h; }

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
/// @param dx_ -1 move left, 1 move right
/// @param dy_ -col move down, col move up
/// @return 1 if found a jump point, 0 otherwise
static int push_jp(int cur, int dx_, int dy_)
{
    if (!dy_) {  // search horizontally
        for (int i = cur + dx_; m[i].s < BLKED; i += dx_) {
            if (m[i - col].s == BLKED || m[i + col].s == BLKED
                && m[i + dx_].s < BLKED
                || i == tar
            ) {
                update(cur, i, ABS(i - cur));
                return 1;
            }
        }
    }
    else if (!dx_) {  // search vertically
        for (int i = cur + dy_; m[i].s < BLKED; i += dy_) {
            if (m[i - 1].s == BLKED || m[i + 1].s == BLKED
                && m[i + dy_].s < BLKED
                || i == tar
            ) {
                update(cur, i, ABS(i - cur < 0) / col);
                return 1;
            }
        }
    }
    else {  // search diagonally
        for (int i = cur + dx_ + dy_; m[i].s < BLKED; i += dx_ + dy_) {
            if (m[i - dx_].s == BLKED || m[i - dy_].s == BLKED
                || push_jp(cur, dx_, 0)  // search horizontally
                || push_jp(cur, 0, dy_)  // search vertically
                || i == tar
            ) {
                update(cur, i, ABS(i - cur) * SQRT_2);
                return 1;
            }
        }
    }
    return 0;
}

void test()
{
    push()
}

float jump_point_search()
{
    create_iheap(&_iheap, row * col, _cmp);
    m[src].g = 0;
    m[src].h = heur(src);
    for (int i = 0; i < 8; i++) {
        if (m[src + dx[i]].s < EXPND && m[src + dy[i] * col].s < EXPND)
            push_jp(src, dx[i], dy[i] * col);
    }
    while (_iheap.cnt) {  // heap not empty
        int cur = iheap_pop(&_iheap);
        m[cur].s = EXPND;
        for (int i = 0; i < 8; i++) {
            int dx_ = cur - m[cur].p > 0 ? cur - m[cur].p ? 1 : 0 : -1,
                dy_ = cur - m[cur].p > 0 ? cur - m[cur].p ? 1 : 0 : -1,
            push_jp(cur, dx_, dy_);
        }
        if (m[tar].s == EXPND) {
            destroy_iheap(&_iheap);
            return m[tar].g;
        }
    }
    destroy_iheap(&_iheap);
    return -1.0f;
}