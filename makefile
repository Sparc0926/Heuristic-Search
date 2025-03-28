#-------------------------------------------------------
# Copyright (C) 2025 杨锦熠 - All rights reserved
#
# You may use, distribute and modify this code under the
# terms of the MIT license, for details, see LICENCE.md
#-------------------------------------------------------

# override built macros
CC = @ gcc
CFLAGS = -I ./ -Wall -Wno-unused-result -Wno-switch -O2 -flto
LINK.c = $(CC) $(CFLAGS)
COMPILE.c = $(LINK.c) -c
OUTPUT_OPTION = -o $(@F)
RM = @ rm -f
# folder name for short
S = Single-Agent
M = Multi-Agent

all:
	$(RM) -f *.o *.exe *.ppm

cps: $(M)/cooperative_search.o
	$(COMPILE.c) -D $($@)_D main.c -o main.o

cbs: $(M)/confilct_based_search.o
	$(COMPILE.c) -D $($@)_D main.c -o main.o

%: $(S)/%.o iheap.o pathfinding.o
	$(CC) -D $@_D $(CFLAGS) -c main.c -o main.o
	$(LINK.c) *.o -o a.exe
	@ echo "Running $@"
	@ ./a.exe
	$(RM) -f *.o *.exe

dij: dijkstra
bfs: breadth_first_search
ast: a_star
jps: jump_point_search