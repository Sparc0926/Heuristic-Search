# Single Agent Pathfinding

## Dijkstra

All single agent pathfinding algorithms evolve from Dijkstra's algorithm, which follows the logic below.

1. Push `src` into heap
2. Pop and return `cur`
3. Examine through it's neighbors
    1. Ignore if it's expanded
    2. Update `g` value if it's visited
    3. Push it if it's unvisited
4. If `cur == tar`, return it's `g` value



## Breadth First Search

The container for BFS is a queue. Here we implement it with an array and two pointers to it's head an tail.

```c
int queue[height * width], head = 0, tail = 0;
```

The **push** operation is `queue[++tail] = target;` and **pop** is simply `head++;`.

Lemma
: 

## Jump Point Search (JPS)

### Neighbor Pruing

Definition (Dominated Neighbor)
: $m[suc]$ is **dominated** if exists a cheaper or equal path from $m[cur.p]$ to $m[suc]$ bypassing $m[cur]$.

Denote by $\pi$ such path, this gives a good reason pruning those successors. We observe that

>for strait move, prune $m[suc]$ if $cost(\pi)\leq w_{cur.p,\,cur}+w_{cur,\,suc}$
>for diagonal move, prune $m[suc]$ if $cost(\pi)<w_{cur.p,\,cur}+w_{cur,\,suc}$

Definition (Forced Neighbor)
: $m[suc]$ is **forced** if it would have been dominated, but not due to blocked by obstacles.

Definition (Jump Point)
: $m[suc]$ is a **jump point** of $m[cur]$ if one of the followings holds

1. $suc = tar$
2. $m[suc]$ is forced
3. if it's a diagonal move, then 
