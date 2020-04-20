#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

void push(int *, int );
void rev_arr(int *, int );
int total_of_arrele(int *, int );
void display(int *, int );
int pop_stack(int *, int );

char* readline();
char** split_string(char*);

/*
 * Complete the equalStacks function below.
 */
int equalStacks(int h1_count, int* h1, int h2_count, int* h2, int h3_count, int* h3) {
    /*
     * Write your code here.
     */
    int i = 0, j = 0, k = 0;
    int tota = 0, totb = 0, totc = 0;
    while (h1_count > 0) {
        push(h1, i);
        i++;
        h1_count--;
    }
    i--;
    while (h2_count > 0) {
        push(h2, j);
        j++;
        h2_count--;
    }
    j--;
    while (h3_count > 0) {
        push(h3, k);
        k++;
        h3_count--;
    }
    k--;

    printf("\nFirst Stack");
    display(h1, i);
    printf("\nSecond Stack");
    display(h2, j);
    printf("\nThird Stack");
    display(h3, k);

    // reversing the array
    rev_arr(h1, i);
    rev_arr(h2, j);
    rev_arr(h3, k);

    //get the total
    tota = total_of_arrele(h1, i);
    totb = total_of_arrele(h2, j);
    totc = total_of_arrele(h3, k);

    //logic for getting max and popping elements
    int c = 0;
    while (c == 0) {
        if (tota == totb) {
            if (totb == totc) {
                c = 1;
            }
            else if (totb > totc) {
                i = pop_stack(h1, i);
                j = pop_stack(h2, j);
            }
            else {
                k = pop_stack(h3, k);
            }
        }
        else if (tota == totc) {
            if (totc > totb) {
                i = pop_stack(h1, i);
                k = pop_stack(h3, k);
            }
            else {
                j = pop_stack(h2, j);
            }
        }
        else if (totb == totc) {
            if (totc > tota) {
                j = pop_stack(h2, j);
                k = pop_stack(h3, k);
            }
            else {
                i = pop_stack(h1, i);
            }
        }
        else if (tota > totb) {
            if (tota > totc) {
                i = pop_stack(h1, i);
            }
            else {
                k = pop_stack(h3, k);
            }
        }
        else {
            if (totb > totc) {
                j = pop_stack(h2, j);
            }
            else {
                k = pop_stack(h3, k);
            }
        }
        tota = total_of_arrele(h1, i);
        totb = total_of_arrele(h2, j);
        totc = total_of_arrele(h3, k);
    }
    return tota;
}

void push(int *h1, int i) {
    if (i != size - 1) {
        scanf("%d", &h1[i]);
    }
}

int total_of_arrele(int *h1, int i) {
    int m = 0, sum = 0;
    while (m <= i) {
        sum += h1[m];
        m++;
    }
    return sum;
}

int pop_stack(int *h1, int i) {
    if (i >= 0) {
        i--;
    }
    return i;
}

void rev_arr(int *h1, int i) {
    int temp, m = 0;
    while (m <= i/2) {
        temp = h1[m];
        h1[m] = h1[i - m];
        h1[i - m] = temp;
        m++;
    }
}

void display(int *h1, int i) {
    int m = 0;
    while (m <= i) {
        printf("\n%d", h1[m]);
        m++;
    }
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** n1N2N3 = split_string(readline());

    char* n1_endptr;
    char* n1_str = n1N2N3[0];
    int n1 = strtol(n1_str, &n1_endptr, 10);

    if (n1_endptr == n1_str || *n1_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n2_endptr;
    char* n2_str = n1N2N3[1];
    int n2 = strtol(n2_str, &n2_endptr, 10);

    if (n2_endptr == n2_str || *n2_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n3_endptr;
    char* n3_str = n1N2N3[2];
    int n3 = strtol(n3_str, &n3_endptr, 10);

    if (n3_endptr == n3_str || *n3_endptr != '\0') { exit(EXIT_FAILURE); }

    char** h1_temp = split_string(readline());

    int h1[n1];

    for (int h1_itr = 0; h1_itr < n1; h1_itr++) {
        char* h1_item_endptr;
        char* h1_item_str = h1_temp[h1_itr];
        int h1_item = strtol(h1_item_str, &h1_item_endptr, 10);

        if (h1_item_endptr == h1_item_str || *h1_item_endptr != '\0') { exit(EXIT_FAILURE); }

        h1[h1_itr] = h1_item;
    }

    char** h2_temp = split_string(readline());

    int h2[n2];

    for (int h2_itr = 0; h2_itr < n2; h2_itr++) {
        char* h2_item_endptr;
        char* h2_item_str = h2_temp[h2_itr];
        int h2_item = strtol(h2_item_str, &h2_item_endptr, 10);

        if (h2_item_endptr == h2_item_str || *h2_item_endptr != '\0') { exit(EXIT_FAILURE); }

        h2[h2_itr] = h2_item;
    }

    char** h3_temp = split_string(readline());

    int h3[n3];

    for (int h3_itr = 0; h3_itr < n3; h3_itr++) {
        char* h3_item_endptr;
        char* h3_item_str = h3_temp[h3_itr];
        int h3_item = strtol(h3_item_str, &h3_item_endptr, 10);

        if (h3_item_endptr == h3_item_str || *h3_item_endptr != '\0') { exit(EXIT_FAILURE); }

        h3[h3_itr] = h3_item;
    }

    //declaration of h1_count, h2_count and h3_count
    int h1_count, h2_count, h3_count;
    scanf("%d", &h1_count);
    scanf("%d", &h2_count);
    scanf("%d", &h3_count);

    int result = equalStacks(h1_count, h1, h2_count, h2, h3_count, h3);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
