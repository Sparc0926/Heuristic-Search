#include <pathfinding.h>
#include <iheap.h>
#include <stdio.h>

struct map* m = (void*)0;  // map to be searched on
int row, col;              // number of rows and columns of map
int src, tar;              // source and target index

char dx[8] = { 1,  1,  0, -1, -1, -1, 0, 1},
     dy[8] = { 0, -1, -1, -1,  0,  1, 1, 1};

void load_map(struct map* m_, int row_, int col_)
{
    m = m_, row = row_, col = col_;
}

void set_src_tar(int src_, int tar_)
{
    src = src_, tar = tar_;
}

void set_h(int cur, enum h_type h_t)
{
    int delta_x = tar % col - cur % col,
        delta_y = ABS(tar - col) / col;
    delta_x = ABS(delta_x);
    switch (h_t) {
        case MANHATTAN: {
            m[cur].h = delta_x + delta_y;
            return;
        }
        case OCTILE: {
            m[cur].h = SQRT_2 * MIN(delta_x, delta_y) + ABS(delta_x - delta_y);
            return;
        }
    }
}

void get_path(int* path)
{
    //int cnt = 0;
    printf("%d ", tar);
    for (int i = m[tar].p; i != src; i = m[i].p) {
        printf("%d ", i);
    }
    printf("%d\n", src);
}

void write_path(char* map)
{
    map[src] = 's', map[tar] = 't';
    for (int i = m[tar].p; i != src; i = m[i].p) {
        map[i] = 'p';
    }
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", map[j + i * col]);
        }
        printf("\n");
    }
}