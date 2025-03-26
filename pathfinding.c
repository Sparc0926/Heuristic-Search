// Copyright (C) 2025 杨锦熠 - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <pathfinding.h>
#include <iheap.h>
#include <stdio.h>

struct map* m = (void*)0;  // map to be searched on
int row, col;              // number of rows and columns of map
int src, tar;              // source and target index
iheap ih;                  // index heap used in search
// directions that a cell can reach
int dx[8] = { 1,  1,  0, -1, -1, -1, 0, 1},
    dy[8] = { 0, -1, -1, -1,  0,  1, 1, 1};

void load_map(struct map* m_, int row_, int col_)
{
    m = m_, row = row_, col = col_;
    for (int i = 0; i < row * col; i++) {
        m[i].d = 0;      // initialize directions bitmask to 0
    }
    for (int i = 0; i < 8; i++)
        dy[i] = dy[i] < 0 ? -col : dy[i] ? col : 0;
    // TODO: benhcmark multiplication over -1 and 1 and ternary opration.
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

// debug functions
void write_path(char* map)
{
    FILE* f = fopen("output.ppm", "w");
    for (int i = 0; i < row * col; i++) {
        if (m[i].s == EXPND)  map[i] = 'e';
        else if (m[i].s == VISED)  map[i] = 'v';
    }
    fprintf(f, "P3\n%d %d\n255\n", col, row);
    for (int i = tar; i != src; i = m[i].p) {
        int dx_ = NORM(m[i].p % col - i % col),
            dy_ = NORM(m[i].p / col - i / col);
        for (int j = i; j != m[i].p; j += dx_ + dy_ * col)
            map[j] = 'p';
    }
    map[src] = 's', map[tar] = 't';
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            switch (map[j + i * col]) {
                case 'T': fprintf(f, "0 255 0 "); break;
                case '@': fprintf(f, "125 125 125 "); break;
                case '.': fprintf(f, "255 255 255 "); break;
                case 'v': fprintf(f, "255 255 0 "); break;
                case 'e': fprintf(f, "255 0 0 "); break;
                case 'p': fprintf(f, "0 0 255 "); break;
                default: fprintf(f, "255 255 255 "); break;
            }
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void write_map()
{
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (m[j + i * col].s == BLKED) {
                printf("%5.1f", -1.0);
                continue;
            }
            printf("%5.1f", m[j + i * col].g);
        }
        printf("\n");
    }
}