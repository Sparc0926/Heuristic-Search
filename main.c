#include <stdio.h>
#include <pathfinding.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int row, col, src, tar;
    FILE* map_src = fopen("dao-map/den510d.map", "r");
    fscanf(map_src, "type octile\nheight %d\nwidth %d\nmap\n", &row, &col);
    // read in map as a string
    char str_m[row * col], tmp;
    int cnt = 0;
    while ((tmp = fgetc(map_src)) != EOF) {
        if (tmp == '\n')  continue;
        if (tmp == 's')  src = cnt;
        else if (tmp == 't')  tar = cnt;
        str_m[cnt++] = tmp;
    }
    fclose(map_src);
    // convert string into struct map
    struct map m[row * col];
    str_m[src] = str_m[tar] = '.';
    for (int i = 0; i < row * col; i++) {
        if (str_m[i] == '.')  m[i].s = UNVIS;
        else  m[i].s = BLKED;
    }
    // begin pathfinding
    load_map(m, row, col);
    set_src_tar(src, tar);
    time_t begin = time(NULL);
    int n = 1000;
    float cost;
    while (n--) {
        str_m[src] = str_m[tar] = '.';
        for (int i = 0; i < row * col; i++) {
            if (str_m[i] == '.')  m[i].s = UNVIS;
            else  m[i].s = BLKED;
        }
        load_map(m, row, col);
        cost = dijkstra();
    }
    time_t end = time(NULL);
    printf("%.1f, it runs in %lf s\n", cost, difftime(end, begin));
    write_path(str_m);

    return 0;
}