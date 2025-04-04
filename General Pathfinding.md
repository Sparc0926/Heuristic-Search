# General Pathfinding

## A* Algorithm

Look at the following graphs, what if we let Dijkstra's algorithm don't expand nodes "behind" $src$.

// TODO make two graph illustrating difference between Dijkstra and A*.

Block those nodes? No, since sometimes it has to "go backward", like

// TODO make a graph showing a oathfinding algorithm goes backward before going forward.

Since it expands nodes based on $g$ values, what if we change $g$ value computation for each node, letting it expands "forward". No, because $g$ value is what it's going to return, shouldn't be modified. However, we can add a mask on it but still return the original $g$ value. The mask is called the **heuristic value** (i.e. $h$ value).

```c
static float _cmp(int i, int j)
    { return m[i].g + m[i].h - m[j].g - m[j].h; }
```

This changes the expansion to base on $g+h$ value of each node (i.e. $f$ value).

There are multiple ways to compute $h$ value for each node, here it's abstracted in `set_h(enum h_type h_t)` where `h_t` specifies in which way we are going to compute it (eg. MANHATON, OCTILE).

To avoid computing $h$ value each time upadting a node, we precompute it in load map stage.

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

### Correctness of A*

However, overestimation of heuristic may lead to suboptimal path found. To avoid this, some rules must be followed to calculate $m[i].h$ for each node.

Theorem (Amissible Heuristic)
: Let $m[i].h^{*}$ be the optimal cost from $m[i]$ to $m[tar]$, then $h$ is **amissible** if and only if
    $$m[tar].h=0 \textup{ and } \forall i,\ m[i].h\leq m[i].h^{*}$$

//TODO draw the graph on lecture notes Levi P27

proof
: Suppose $m[i]\rightarrow m[j]\dashrightarrow m[tar]$ is the shortest path, thus take any less or equally short path $m[i]\dashrightarrow m[tar]$, it must satisfy
    $$w_{i,j}+m[j].h^{*}\leq cost(i,tar)$$
To achieve the path, $m[j]$ must be expanded before $m[tar]$, that is $m[j].g+m[j].h\leq m[tar].g+m[tar].h$, it follows that
    $$w_{i,j}+m[j].h\leq cost(i,tar)$$
This happens if and only if $m[j].h\leq m[j].h^{*}$, same for other nodes. $m[tar].h=0$ follows from $m[tar].h^{*}=0$.

As is shown above, an amissible heuristic guarantees a shortest path, while it's not enough. Consider this search instance

// TODO draw a graph showing problem brought by inconsistency

Notice that $m[j]$ is popped then pushed again. This is because $h$ is not consistent.

Theorem (Consistent Heuristic)
: Suppose $m[i]$ must exist in final path before $m[j]$ and let $minc(i,j)$ be the cheapest cost between $m[i]$ and $m[j]$, then $h$ is **consistent** if and only if
    $$m[i].h-m[j].h\leq minc(i,j)$$

proof
: Suppose the consistency and $m[k]$ must be expanded before $m[j]$ (note that *must* means there are no equal paths), thus
    $$cost(i,k)+m[k].h<w_{i,j}+m[j].h$$
Connect it with the consistency condition $m[j].h-m[k].h\leq minc(j,k)$, we get
    $$cost(i,k)<w_{i,j}+minc(j,k)$$
which contradicts to the assumption that $m[i]\rightarrow m[j]\dashrightarrow m[k]$ is cheaper.

### Iterative Deepening A* (IDA*)

With the consistency of heuristic, one can easily figure out that the $f$ value is **non-decreasing** along the final path! This is because
    $$m[i].g+m[i].h\leq m[i].g+minc(i,j)+m[j].h=m[j].g+m[j].h$$
This motivates the idea borrowed from [IDDFS](), can we iteratively increasing the cutoff of $f$ value until $m[tar]$ is reached? Instead of `cutoff++` each time, we can simly set it to be the smallest $f$ value exceeds `cutoff` at previous iteration, which makes it a bit faster.

#### Binary Search on IDA*
