// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iheap.h>

#define SQRT_2     1.5f
#define MIN(A, B)  ((A) < (B) ? (A) : (B))
#define MAX(A, B)  ((A) > (B) ? (A) : (B))
#define ABS(A)     ((A) < 0 ? -(A) : (A))
#define NORM(A)    ((A) < 0 ? -1 : (A) ? 1 : 0)

#define SINGLE_AGENT

//------------------------- general attributes -------------------------//

enum status { UNVIS, VISED, EXPND, BLKED = 4 };
enum h_type { MANHATTAN, OCTILE };
struct map {
    float g, h;        // g value and h value
    enum status s;     // status
    int p;             // parent
    unsigned char d;   // bitmask of directions (in index of dx[], dy[]])
};
extern struct map* m;  // map to be searched on
extern int row, col;   // number of rows, columns and agents
extern int src, tar;   // indices of source and target cells
extern iheap ih;       // index heap used in search

#ifdef SINGLE_AGENT
extern char dx[8];
extern int  dy[8];
#endif//SINGLE_AGENT

#ifdef MULTI_AGENT
extern char dx[9];
extern int  dy[9];
#endif//MULTI_AGENT

//-------------------------- general functions ---------------------------//

/// @brief initialize m with a string mask file
/// @param m_name the string mask file name
/// @note this should be called before any related functions
void load_map_static(char* m_name);
void unload_map();
/// @brief precompute and set h value for every cell based on specific h_type
/// @param h_t type of heuristic function
void set_h(int cur, enum h_type h_t);
/// @brief update attributes of m[suc]
/// @param cur index of current cell
/// @param suc index of successor cell
/// @param w new cost from m[src] to m[suc]
void update_cell(int cur, int suc, float w);
/// @brief find the shortest path from src to tar
/// @return minimal cost if path found, -1.0f if not found
float search();

// TODO

//--------------------------- debug functions ----------------------------//
//void write_path(char* map);

#endif//PATHFINDING_H