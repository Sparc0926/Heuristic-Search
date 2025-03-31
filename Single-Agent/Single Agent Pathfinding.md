# Single Agent Pathfinding

## Some Variations of A*

### Hierarchical A* (HA*)

This approach aims to reduce the time of computing `h` value for each node.

Definition (Valtorta's Barrier)
: The number of nodes expanded when blindly searching in a space.

## Jump Point Search (JPS) - Best for Static Map

As the expanded set of A* algorithm contains multiple shortest paths, are there any ways to prune it so as to speed it up?

### Neighbor Pruing

Let's call those shortest paths **symmetric** as they act the same role consider the simplest case symmetric paths take place, 9-grid map.

#### Straight Move

The following map is represented by `m[0 : 8]` where `m[3]` is just expanded, hence `m[3].g` is minimized, and it's currently evaluating `m[4]`.

| @  |  @ |  @ |
|---|---|---|
|  d |  e |  f |
| g  |  h | i  |

Notice that there are two 

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
