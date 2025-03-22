#include <pathfinding.h>
#include <iheap.h>

static iheap _iheap;
static int _cmp(int i, int j)
    { return m[i].g - m[j].g; }

/// @brief update attributes of m[suc]
/// @param cur index of current cell
/// @param suc index of successor cell
/// @param w new cost from m[src] to m[suc]
static void update_cell(int cur, int suc, float w)
{
    if (m[suc].s == UNVIS) {
        m[suc].g = w;
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

float dijkstra()
{
    create_iheap(&_iheap, row * col, _cmp);
    m[src].g = 0;
    iheap_push(&_iheap, src);
    while (_iheap.cnt) {  // heap not empty
        int cur = iheap_pop(&_iheap);
        m[cur].s = EXPND;
        for (int i = 0; i < 8; i++) {
            update_cell(cur,
                cur + dx[i] + dy[i] * col,
                m[cur].g + (i & 1 ? SQRT_2 : 1.0f)
            );
        }
        if (m[tar].s == EXPND) {
            destroy_iheap(&_iheap);
            return m[tar].g;
        }
    }
    destroy_iheap(&_iheap);
    return -1.0f;
}