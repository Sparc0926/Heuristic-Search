#ifndef PATHFINDING_H
#define PATHFINDING_H

#define SQRT_2     1.5f
#define MIN(A, B)  ((A) < (B) ? (A) : (B))
#define MAX(A, B)  ((A) < (B) ? (B) : (A))
#define ABS(A)     ((A) < 0 ? -(A) : (A))
#define NORM(A)    ((A) < 0 ? -1 : (A) ? 1 : 0)

enum status { UNVIS, VISED, EXPND, BLKED };
enum h_type { MANHATTAN, OCTILE };

struct map {
    float g, h;       // g value and h value
    enum status s;    // status
    int p;            // parent
    unsigned char d;  // bitmask of directions (in index of dx[], dy[]])
};

extern struct map* m;      // map to be searched on
extern int row, col;       // number of rows and columns of m
extern int src, tar;       // indices of source and target cells
extern int dx[8], dy[8];  // 8 directions an agend will go

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

/// @brief find the shortest path from s to t
/// @return minimal cost if path found, -1.0f if not found
float dijkstra();
/// @brief find the shortest path from s to t
/// @return minimal cost if path found, -1.0f if not found
float breadth_first_search();
/// @brief find the shortest path from s to t
/// @return minimal cost if path found, -1.0f if not found
float depth_first_search();
/// @brief find the shortest path from s to t
/// @return minimal cost if path found, -1.0f if not found
float a_star();
/// @brief find the shortest path from s to t
/// @return minimal cost if path found, -1.0f if not found
float jump_point_search();

/// @brief build founded path and store it in path[]
/// @param path array to store path
void get_path(int* path);

// debug functions
void write_path(char* map);
void write_map();

#endif//PATHFINDING_H

/*
static void set_primary_jp_attrib()
{
    for (int i = col + 1; i < (row - 1) * (col - 1); i++) {
        if (m[i - 1].s == BLKED) [
            m[i].jp_attrib[2] = 1;
            m[i].jp_attrib[3] = 1;
            
        ]
        // approaching horizontally
        if (m[i - col].s == BLKED || m[i + col].s == BLKED) {
            if (m[i - 1].s != BLKED)  m[i].jp_attrib[0] = 1;
            if (m[i + 1].s != BLKED)  m[i].jp_attrib[4] = 1;
        }
        // approaching vertically
        if (m[i - 1].s == BLKED || m[i + 1].s == BLKED) {
            if (m[i - col].s != BLKED)  m[i].jp_attrib[2] = 0;
            if (m[i + col].s != BLKED)  m[i].jp_attrib[6] = 0;
        }
    }
}
*/