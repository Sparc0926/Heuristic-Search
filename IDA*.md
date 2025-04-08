# IDA* Based Algorithms

## Iterative Deepening A* (IDA*)

With the consistency of heuristic, one can easily figure out that the $f$ value is **non-decreasing** along the final path! This is because
    $$m[i].g+m[i].h\leq m[i].g+minc(i,j)+m[j].h=m[j].g+m[j].h$$
This motivates the idea borrowed from [IDDFS](), can we iteratively increasing the cutoff of $f$ value until $m[tar]$ is reached? Instead of `f_bound++` each time, we can simply set it to the smallest $f$ value exceeds `f_bound` at previous iteration, which makes it a bit faster.

### Binary Search on IDA*
