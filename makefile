#-------------------------------------------------------
# Copyright (C) March 2025 杨锦熠 - All rights reserved
#
# You may use, distribute and modify this code under the
# terms of the MIT license, for details, see LICENCE.md
#-------------------------------------------------------

# override of built macros
CC = @ gcc
CFLAGS = -I ./ -Wall -Wno-unused-result -Wno-switch -O2 -flto
LINK.c = $(CC) $(CFLAGS)
COMPILE.c = $(LINK.c) -c
OUTPUT_OPTION = -o $(@F)
RM = @ rm -f
# algorithms to file
dij = dijkstra
bfs = breadth_first_search
a* = a_star
jps = jump_point_search
ca* = cooperative_a_star
cbs = conflict_based_search

all:
	@ echo "Please specify an algorithm to run:"
	@ echo "To run Dijkstra's algorithm ---- type [make dij]."
	@ echo "To run Breadth First Search ---- type [make bfs]."
	@ echo "To run A* algorithm ------------ type [make a* ]."
	@ echo "To run Jump Point Search ------- type [make jps]."
	@ echo "To run Cooperative A* ---------- type [make ca*]."
	@ echo "To run Conflict Based Search --- type [make cbs]."
	$(RM) *.o *.exe *.ppm

dij: Single-Agent/$(dij).o
bfs: Single-Agent/$(bfs).o
a*: Single-Agent/$(a*).o
jps: Single-Agent/$(jps).o

ca*: Multi-Agent/$(ca*).o
cbs: Multi-Agent/$(cbs).o

%: iheap.o pathfinding.o
	$(COMPILE.c) -o main.o -D $($@)_D main.c
	$(LINK.c) *.o -o a.exe
	@ echo "Running $($@)"
	@ ./a.exe
	$(RM) *.o *.exe