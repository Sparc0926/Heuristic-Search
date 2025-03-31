#include <pathfinding.h>

static float _cmp(int i, int j)
    { return m[i].g - m[j].g; }

float search()
{
    create_iheap(&ih, row * col, _cmp);
    int cur = src;
    m[src].g = 0;
    iheap_push(&ih, src);
    for (int i = 1; ;i++) {
        for (int j = 0; j < 8; j++) {
            update_cell()
        }
    }
    while (cur != tar) {
        cur = iheap_pop(&ih);
        iheap_push(&ih, m[iheap_pop(&ih)].g + );
    }
    destroy_iheap(&ih);
}