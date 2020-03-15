#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
unsigned int ns[] = { 1000, 2000, 3000 };

void fill_increasing(int *t, unsigned int n) {
    for (int i = 0; i<n; i++)
    {
        t[i] = i;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    for (int i= 0; i < n; i++)
    {
        t[i] = n-i;
    }
}

void fill_vshape(int *t, unsigned int n) {
    for (int i = 0; i < n; i++)
    {
        if(i == 0)
            t[i]=n;
        else
        {
            t[n-i] = n-i;
        }
    }
}

void selection_sort(int *t, unsigned int n) {
    int i, x, y;

    for (x = 0; x < n-1; x++)
    {
        i = x;
        for (y = x+1; y < n; y++)
        {
            if (t[y] < t[i])
            i = y;
        }
        swap(t[i], t[x]);
    }
}

void insertion_sort(int *t, unsigned int n) {
    int key, i, j;
    for (i = 1; i<n; i++)
    {
        key = t[i];
        j = i -1;

        while (t[j] > key && j>=0)
        {
            t[j+1] = t[j];
            j = j-1;
        }

        t[j+1] = key;
    }
}

/*void quick_sort(int *t, unsigned int n) {
    // TODO: implement
}

void heap_sort(int *t, unsigned int n) {
    // TODO
}
*/
void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;
    while (*end - *begin > 1)
    {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape }; // , fill_vshape
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };// is vshape
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort }; // heapsort quicksort

char *fill_names[] = { "Random", "Increasing", "Decreasing", "vshape" }; // vshape
char *sort_names[] = { "SelectionSort", "InsertionSort" }; // quicksort heapsort

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = (int*) malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
