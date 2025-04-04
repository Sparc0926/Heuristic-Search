#include <pathfinding.h>
#include <stdio.h>

static float cutoff, min;

/// @brief deepen from m[cur] towards m[tar]
/// @param cur index of current node
/// @param g m[cur].g
static void deepen(int cur, float g)
{
    if (cur == tar)  return;
    for (int i = 0; i < 8; i++) {
        int suc = cur + dx[i] + dy[i];
        if (m[suc].g < 0.0f)  continue;
        m[suc].g = g + (i & 1 ? SQRT_2 : 1.0f);
        float f = m[suc].g + m[suc].h;
        //printf("%d-->%d: g = %.1f, h = %.1f, cutoff = %.1f\n", cur, suc, m[suc].g, m[suc].h, cutoff);
        //int a;
        //scanf("%d", &a);
        if (f <= cutoff) {
            m[cur].g = -2.0f;
            m[suc].p = cur;
            deepen(suc, m[suc].g);
            m[cur].g = g;
        } else if (f < min) {
            min = f;
            //printf("min = %.1f\n", min);
            return;
        }
    } return;
}

float search()
{
    cutoff = m[src].h;
    while (m[tar].g == 3.402823466e+38f) {
        //printf("call\n");
        min = 3.402823466e+38f;
        deepen(src, 0);
        cutoff = min;
    } return m[tar].g;
}