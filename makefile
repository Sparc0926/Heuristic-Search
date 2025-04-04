#-------------------------------------------------------
# Copyright (C) 2025 Jarry Yang - All rights reserved
#
# You may use, distribute and modify this code under the
# terms of the MIT license, for details, see LICENCE.md
#-------------------------------------------------------

# override built macros
CC =@ clang
CFLAGS = -I ./ -Wall -Wno-unused-result -Wno-switch -O2
LINK.c = $(CC) $(CFLAGS)
COMPILE.c = $(LINK.c) -c
OUTPUT_OPTION = -o $(@F)
RM = @ rm -f

all: clean
	@ echo "Please specify an algorithm to compile:"
	@ echo "To compile Dijkstra's algorithm ---- type [make dij]."
	@ echo "To compile Breadth First Search ---- type [make bfs]."
	@ echo "To compile A* algorithm ------------ type [make ast]."
	@ echo "To compile A* algorithm ------------ type [make ida]."
	@ echo "To compile Jump Point Search ------- type [make jps]."
	@ echo "To compile Cooperative Search ------ type [make cps]."
	@ echo "To compile Conflict Based Search --- type [make cbs]."

dij: Single-Agent/Dijkstra clean
bfs: Single-Agent/BFS clean
ast: Single-Agent/Astar clean
ida: Single-Agent/IDAstar clean
jps: Single-Agent/JPS clean

cps: Multi-Agent/CPS Single-Agent/JPS clean
cbs: Multi-Agent/CBS clean

%: %.o iheap.o pathfinding.o main.o
	$(LINK.c) *.o -o a.exe
	
%: %.c

clean:
	$(RM) -f *.o *.ppm