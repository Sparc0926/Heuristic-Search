WARN = -Wall
OPTM = -O2 -flto

all: a.exe clean

a.exe: main.o iheap.o pathfinding.o dijkstra.o a_star.o
	@ gcc $(WARN) $(OPTM) $^ -o a.exe

iheap.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c iheap.c -o $@

dijkstra.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c "Single Agent"/dijkstra.c -o $@

a_star.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c "Single Agent"/a_star.c -o $@

pathfinding.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c pathfinding.c -o $@

main.o:
	@ gcc -I ./ $(WARN) $(OPTM) -c main.c -o $@

clean:
	@ rm -f *.o