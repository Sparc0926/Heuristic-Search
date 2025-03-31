#include <pathfinding.h>

static float cutoff, min = 3.402823466e+38f;

/// @brief deepen from m[cur] towards m[tar]
/// @param cur 
/// @return cost if path found, -1.0f otherwise
static float deepen(int cur)
{
    if (cur == tar)  return m[tar].g;
    for (int i = 0; i < 8; i++) {
        int suc = src + dx[i] + dy[i];
        m[suc].g = m[src].g + (i & 1 ? 1.5f : 1.0f);
        int f = m[suc].g + m[suc].h;
        if (f <= cutoff)  deepen(suc);
        else if (f <= min)  f = min;
    }
    return -1.0f;
}

float search()
{
    cutoff = m[src].h;
    m[src].g = 0;
    float cost;
    while ((cost = deepen(src)) < 0.0f) {
        
    }
    return cost;
}