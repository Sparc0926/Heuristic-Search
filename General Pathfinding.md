# General Pathfinding

## A* Algorithm ()

Look at the following graphs, what if we let Dijkstra's algorithm don't expand nodes "behind" `src`.

// TODO make two graph illustrating difference between Dijkstra and A*.

Block those nodes? No, since sometimes it has to "go backward", like

// TODO make a graph showing a oathfinding algorithm goes backward before going forward.

Since it expands nodes based on `g` values, what if we change `g` value computation for each node, letting it expands "forward". No, because `g` value is what it's going to return, shouldn't be modified. However, we can add a mask on it but still return the original `g` value. The mask is called the **heuristic value** (i.e. `h` value).

```c
static float _cmp(int i, int j)
    { return m[i].g + m[i].h - m[j].g - m[j].h; }
```

This changes the expansion to base on `g + h` value of each node (i.e. `f` value).

There are multiple ways to compute `h` value for each node, here it's abstracted in `set_h(enum h_type h_t)` where `h_t` specifies in which way we are going to compute it (eg. MANHATON, OCTILE).

To avoid computing `h` value each time upadting a node, we precompute it in load map stage.

```c
void load_map(struct map* m_, int row_, int col_)
{
    m = m_, row = row_, col = col_;
    for (int i = 0; i < 8; i++)
        dy[i] = dy[i] < 0 ? -col : dy[i] ? col : 0;
    set_h(OCTILE);
}
```

It's called A* algorithm, the other part of it is exactly same as for Dijlstra's algorithm. The story does not end here, since variations of A* pop up after then.

### Iterative Deepening A* (IDA*)

IDA* comes from imposing heuristic on [IDDFS](). 
