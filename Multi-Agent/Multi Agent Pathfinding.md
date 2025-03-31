# Multi Agent Pathfinding

multi agent pathfinding problems require agents

Like single agent searches, each algorithm returns `shortest distance` if path found or `-1` otherwise.

## Cooperative Search

Cooperative search (CPS) is as simple as running single agent search one by one on each agent. To avoid collision, it generates fake walls to block following agent to pass. This is the fastest approach since pathfinding of each agent is fully optimized, while it's correctness is not guaranteed.

### Cooperative Jump Point Search

Since jump point search (JPS) is the fastest single agent search so far and it gets speeded up after each time adding walls, we will use JPS as the underlying algorithm for cooperative search.

```c
static void clear_map()
{
    int i = row * col;
    while (i--) {
        m[i].s &= 4;  // set non-blocked cells unvisited
        m[i].g = 0;   // set g value to 0
    }
    // add walls on former agent's path
    for (int i = tar; i != src; i = m[i].p) {
        int dx_ = NORM(m[i].p % col - i % col),
            dy_ = NORM(m[i].p / col - i / col) * col;
        for (int j = i; j != m[i].p; j += dx_ + dy_)
            m[j].s = BLKED;
    }
}
```