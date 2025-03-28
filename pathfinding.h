// Copyright (C) 2025 杨锦熠 - All rights reserved
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

//------------------------- general attributes -------------------------//
enum status { UNVIS, VISED, EXPND, BLKED = 4 };
enum h_type { MANHATTAN, OCTILE };
struct map {
    float g, h;       // g value and h value
    enum status s;    // status
    int p;            // parent
    unsigned char d;  // bitmask of directions (in index of dx[], dy[]])
};
extern struct map* m;      // map to be searched on
extern int row, col;       // number of rows, columns and agents
extern int src, tar;       // indices of source and target cells
extern iheap ih;           // index heap used in search
extern int dx[9], dy[9];   // 8 directions an agend will go

//-------------------------- general functions ---------------------------//
/// @brief initialize m, row, col with a specific map
/// @param m_ pointer to map array
/// @param row_ number of rows of the map
/// @param col_ number of columns of the map
/// @note this should be called before any related functions
void load_map(struct map* m_, int row_, int col_);
/// @brief set indices of source and target cell
/// @param src_ index of source cell
/// @param tar_ index of target cell
/// @note this should be called right after load_map
/// @note and before any pathfinding functions
void set_src_tar(int src_, int tar_);
/// @brief compute and set m[cur].h based on specific h_type
/// @param cur index of current cell
/// @param h_t type of heuristic function
void set_h(int cur, enum h_type h_t);

//------------------ single agent pathfinding algorithms -----------------//
/// @brief find the shortest path from src to tar
/// @return minimal cost if path found, -1.0f if not found
float dijkstra();
/// @brief find the shortest path from src to tar
/// @return minimal cost if path found, -1.0f if not found
float breadth_first_search();
/// @brief find the shortest path from src to tar
/// @return minimal cost if path found, -1.0f if not found
float depth_first_search();
/// @brief find the shortest path from src to tar
/// @return minimal cost if path found, -1.0f if not found
float a_star();
/// @brief find the shortest path from src to tar
/// @return minimal cost if path found, -1.0f if not found
float jump_point_search();

//------------------ multi agent pathfinding algorithms ------------------//
float cooperative_based_search();
float conflict_based_search();

//--------------------------- debug functions ----------------------------//
void write_path(char* map);

#endif//PATHFINDING_H