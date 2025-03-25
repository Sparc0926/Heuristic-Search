#include <stdio.h>
#include <stdlib.h>
#include <pathfinding.h>
#include <time.h>

int main()
{
    //da2-map/w_sundermount.map
    int row, col, src, tar;
    FILE* map_src = fopen("da2-map/ht_0_hightown_a2.map", "r");
    fscanf(map_src, "type octile\nheight %d\nwidth %d\nmap\n", &row, &col);
    // read in map as a string
    char* str_m = (char*)malloc(row * col * sizeof(char)), tmp;
    int cnt = 0;  // iteration counter through the the file
    while ((tmp = fgetc(map_src)) != EOF) {
        if (tmp == '\n')  continue;
        if (tmp == 's')  src = cnt;
        else if (tmp == 't')  tar = cnt;
        str_m[cnt++] = tmp;
    }
    fclose(map_src);
    // convert string into struct map
    struct map* m = (struct map*)malloc(row * col * sizeof(struct map));
    str_m[src] = str_m[tar] = '.';
    for (int i = 0; i < row * col; i++) {
        if (str_m[i] == '.')  m[i].s = UNVIS;
        else  m[i].s = BLKED;
    }
    // begin pathfinding
    load_map(m, row, col);
    set_src_tar(src, tar);
    float cost;
    time_t begin = time(NULL);
    cost = jump_point_search();
    time_t end = time(NULL);
    printf("%.1f, it runs in %lf s\n", cost, difftime(end, begin));
    write_path(str_m);
    free(str_m);
    free(m);

    return 0;
}