WARN = -Wall
OPTM = -O2 -flto

all:
	@ rm -f *.o

dij: main.o iheap.o pathfinding.o
	@ gcc -I ./ $(WARN) $(OPTM) -c "Single Agent"/dijkstra.c -o dijkstra.o
	@ gcc $(WARN) $(OPTM) $^ dijkstra.o -o a.exe
	@ rm -f *.o

a*: main.o iheap.o pathfinding.o
	@ gcc -I ./ $(WARN) $(OPTM) -c "Single Agent"/a_star.c -o a_star.o
	@ gcc $(WARN) $(OPTM) $^ a_star.o -o a.exe
	@ rm -f *.o

jps: main.o iheap.o pathfinding.o
	@ gcc -I ./ $(WARN) $(OPTM) -c "Single Agent"/jump_point_search.c -o jump_point_search.o
	@ gcc $(WARN) $(OPTM) $^ jump_point_search.o -o a.exe
	@ rm -f *.o

pathfinding.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c pathfinding.c -o $@

iheap.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c iheap.c -o $@

main.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c main.c -o $@