// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <pathfinding.h>
#include <stdio.h>

struct map* m = (void*)0;  // map to be searched on
int row, col;              // number of rows and columns of map
int src, tar;              // source and target index

#ifdef SINGLE_AGENT
iheap ih;                  // index heap used in search
char dx[8] = { 1,  1,  0, -1, -1, -1, 0, 1};
int  dy[8] = { 0, -1, -1, -1,  0,  1, 1, 1};
#endif//SINGLE_AGENT

#ifdef MULTI_AGENT
int a_c;  // number of agent
char dx[9] = { 1,  1,  0, -1, -1, -1, 0, 1, 0};
int  dy[9] = { 0, -1, -1, -1,  0,  1, 1, 1, 0};
#endif//MULTI_AGENT

void load_map_static(char* m_name)
{
    FILE* m_file = fopen(m_name, "r");
    fscanf(m_file, "type octile\nheight %d\nwidth %d\nmap\n", &row, &col);
    m = (struct map*)malloc(row * col * sizeof(struct map));
    // read in and convert map from file
    for (int i = 0; i < row * col; ) {
        switch (fgetc(m_file)) {
            case '.': m[i++].g = 3.402823466e+38f; break;
            case 's': m[src = i++].g = 0.0f; break;
            case 't': m[tar = i++].g = 3.402823466e+38f; break;
            case '\n': continue;
            default: m[i++].g = -1.0f; break;
        }
    } fclose(m_file);
    // precompute h value for entire map
    for (int i = 0; i < row * col; i++)
        if (m[i].g >= 0.0f)  set_h(i, OCTILE);
    for (int i = 0; i < 8; i++)
        dy[i] = dy[i] < 0 ? -col : dy[i] ? col : 0;
    // TODO: benhcmark multiplication over -1 and 1 and ternary opration.
}

void unload_map()
{
    if (m)  free(m);
    m = (void*)0;
}

void set_h(int cur, enum h_type h_t)
{
    int delta_x = tar % col - cur % col,
        delta_y = tar / col - cur / col;
    delta_x = ABS(delta_x);
    delta_y = ABS(delta_y);
    switch (h_t) {
        case MANHATTAN:
            m[cur].h = delta_x + delta_y;
            break;
        case OCTILE:
            m[cur].h = SQRT_2 * MIN(delta_x, delta_y) + ABS(delta_x - delta_y);
            break;
    }
}

void update_cell(int cur, int suc, float w)
{
    if (m[suc].g == 3.402823466e+38f) {
        m[suc].g = w;
        m[suc].p = cur;
        iheap_push(&ih, suc);
    } else if (m[suc].g < 3.402823466e+38f && w < m[suc].g) {
        m[suc].g = w;
        m[suc].p = cur;
        iheap_update(&ih, suc);
    }
}

// debug functions
//void write_path(char* map)
//{
//    FILE* f = fopen("output.ppm", "w");
//    fprintf(f, "P3\n%d %d\n255\n", col, row);
//    for (int i = 0; i < row * col; i++) {
//        switch (m[i].s) {
//            case VISED: map[i] = 'v'; break;
//            case EXPND: map[i] = 'e'; break;
//        }
//    } for (int i = tar; i != src; i = m[i].p) {
//        int dx_ = NORM(m[i].p % col - i % col),
//            dy_ = NORM(m[i].p / col - i / col);
//        for (int j = i; j != m[i].p; j += dx_ + dy_ * col)
//            map[j] = 'p';
//    } map[src] = 's', map[tar] = 't';
//    for(int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            switch (map[j + i * col]) {
//                case 'T': fprintf(f, "100 255 100 "); break;
//                case '@': fprintf(f, "125 125 125 "); break;
//                case '.': fprintf(f, "255 255 255 "); break;
//                case 'v': fprintf(f, "255 200 0 "); break;
//                case 'e': fprintf(f, "255 75 75 "); break;
//                case 'p': fprintf(f, "0 0 0 "); break;
//                default: fprintf(f, "255 255 255 "); break;
//            }
//        } fprintf(f, "\n");
//    } fclose(f);
//}