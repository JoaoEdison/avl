/*
    AVL tree implementation in C.
    Copyright (C) 2025  João Manica

    This program is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details.
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
void print_key(fp, k, v)
FILE *fp;
void *k, *v;
{
    fprintf(fp, "%d", *(int*)k);
}

main()
{
    avltree_tree t;
    avltree_create(t, 1, compar, print_key);
    int *key;
    
#ifdef TEST_AUTO
/*  #define DEBUG */
/*  #define PRINT */
    #define N 5000
    #define M N
    #define K 200
    #define MAX_LEN K*N
    #define MOD 1000
    
    int end, last;
    int *queue;
    int i,j,m;
    void *value;
    avltree_tree removed;
    avltree_create(removed, 1, compar, NULL);

#ifndef DEBUG    
    srand(time(NULL));
#endif
    end = last = 0;
    queue = malloc(sizeof(int)*MAX_LEN);
    /* Repeat K times: */
    for (i=0; i < K; i++) {
        /* Generate N random numbers: */
        for (j=last; j < last+N; j++)
            queue[j] = rand()%MOD;
        end = j;
        /* Insert in tree: */
        for (j=last; j < last+N; j++) {
            key = malloc(sizeof(int));
            *key = queue[j];
            avltree_insert_key(t, key);
#ifdef DEBUG
            printf("Inserted: %d\n", *key);
#endif
            avltree_height(t);
#ifdef PRINT
            avltree_prefix(t);
            putchar('\n');
#endif
        }
        /* Sort in ascending order: */
        qsort(&queue[last], N, sizeof(int), compar);
        /* Remove M in this order (everything needs to be present): */
        m = rand()%M+1;
        for (j=last; j < last+m; j++) {
            key = malloc(sizeof(int));
            *key = queue[j];
            if (avltree_find_node(removed, key)) {
                free(key);
                continue;
            }
            avltree_height(t);
#ifdef PRINT
            avltree_prefix(t);
            putchar('\n');
#endif
            avltree_insert_key(removed, key);
#ifdef DEBUG
            printf("Removing: %d\n", queue[j]);
#endif
            assert(!avltree_remove_node(t, &queue[j]));
        }
#ifdef PRINT
        avltree_prefix(t);
        putchar('\n');
#endif
        last = j;
    }
    /* Remove everything: */
    for (; last < end; last++)  {
        key = malloc(sizeof(int));
        *key = queue[last];
        if (avltree_find_node(removed, key)) {
            free(key);
            continue;
        }
        avltree_height(t);
#ifdef PRINT
        avltree_prefix(t);
        putchar('\n');
#endif
        avltree_insert_key(removed, key);
#ifdef DEBUG
        printf("Removing: %d\n", queue[last]);
#endif
        assert(!avltree_remove_node(t, &queue[last]));
    }
    /* Need to verify if happened any memory error. */
    avltree_destroy(removed);
    free(queue);
#else
    char opt;

    do {
        printf("Insert the new key: ");
        key = malloc(sizeof(int));
        scanf("%d", key);
        avltree_insert_key(t, key);
        avltree_prefix(t);
        putchar('\n');
        avltree_infix(t);
        putchar('\n');
        avltree_posfix(t);
        putchar('\n');
        printf("Continue (y)? ");
        getchar();
        opt = getchar();
    } while (opt == 'Y' || opt == 'y');
#endif
    avltree_destroy(t);
}
