/*
    AVL tree implementation in C.
    Copyright (C) 2025  João Manica

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TEST_AUTO

compar(x, y)
void *x, *y;
{
    return *(int*)x-*(int*)y;
}

main()
{
    avl_tree t;
    create_alvtree(t, compar);
    int *key;
    
#ifdef TEST_AUTO
//  #define DEBUG
//  #define PRINT
    #define N 5000
    #define M N
    #define K 200
    #define MAX_LEN K*N
    #define MOD 1000
    
    int end, last;
    int *queue;
    int i,j,m;
    void *value;
    avl_tree removed;
    create_alvtree(removed, compar);

#ifndef DEBUG    
    srand(time(NULL));
#endif
    end = last = 0;
    queue = malloc(sizeof(int)*MAX_LEN);
    // Repeat K times:
    for (i=0; i < K; i++) {
        // Generate N random numbers:
        for (j=last; j < last+N; j++)
            queue[j] = rand()%MOD;
        end = j;
        // Insert in tree:
        for (j=last; j < last+N; j++) {
            key = malloc(sizeof(int));
            *key = queue[j];
            insert_avltree(&t, key, NULL);
#ifdef DEBUG
            printf("Inserted: %d\n", *key);
#endif
            height_avltree(t);
#ifdef PRINT
            prefix_avltree(t);
            putchar('\n');
#endif
        }
        // Sort in ascending order:
        qsort(&queue[last], N, sizeof(int), compar);
        // Remove M in this order (everything needs to be present):
        m = rand()%M+1;
        for (j=last; j < last+m; j++) {
            key = malloc(sizeof(int));
            *key = queue[j];
            if (find_node_avltree(&removed, removed.root, key, NULL)) {
                free(key);
                continue;
            }
            height_avltree(t);
#ifdef PRINT
            prefix_avltree(t);
            putchar('\n');
#endif
            insert_avltree(&removed, key, NULL);
#ifdef DEBUG
            printf("Removing: %d\n", queue[j]);
#endif
            assert(!remove_avltree(&t, &queue[j], &value));
        }
#ifdef PRINT
        prefix_avltree(t);
        putchar('\n');
#endif
        last = j;
    }
    // Remove everything:
    for (; last < end; last++)  {
        key = malloc(sizeof(int));
        *key = queue[last];
        if (find_node_avltree(&removed, removed.root, key, NULL)) {
            free(key);
            continue;
        }
        height_avltree(t);
#ifdef PRINT
        prefix_avltree(t);
        putchar('\n');
#endif
        insert_avltree(&removed, key, NULL);
#ifdef DEBUG
        printf("Removing: %d\n", queue[last]);
#endif
        assert(!remove_avltree(&t, &queue[last], &value));
    }
    // Need to verify if happened any memory error.
    destroy_avltree(removed);
    free(queue);
#else
    char opt;

    do {
        printf("Insert the new key: ");
        key = malloc(sizeof(int));
        scanf("%d", key);
        insert_avltree(&t, key, NULL);
        prefix_avltree(t);
        putchar('\n');
        infix_avltree(t);
        putchar('\n');
        posfix_avltree(t);
        putchar('\n');
        printf("Continue (y)? ");
        getchar();
        opt = getchar();
    } while (opt == 'Y' || opt == 'y');
#endif
    destroy_avltree(t);
}
