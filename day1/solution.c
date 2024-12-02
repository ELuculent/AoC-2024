#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file_into_arrays(char *file_path, int nums1[1000], int nums2[1000]) {
    FILE *f;
    f = fopen(file_path, "r");
    
    char line[15];
    size_t len = 0;

    if (f == NULL) {
        printf("error opening file");
        return 0;
    }

    int i = 0;
    while(fgets(line, 15, f)) {
        char *token = strtok(line, "   ");
        char *list = "left";
        while (token != NULL) {
            if (strcmp(list, "left") == 0) {
                nums1[i] = strtol(token, NULL, 10);
                list = "right";
            } else {
                nums2[i] = strtol(token, NULL, 10);
                list = "left";
            }
            token = strtok(NULL, "   ");
        }
        ++i;
    }
    return 1;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int get_solution1(int nums1[], int nums2[], int nums_length) {
    qsort(nums1, nums_length, sizeof(int), compare);
    qsort(nums2, nums_length, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < nums_length; ++i) {
        int a = abs(nums1[i] - nums2[i]);
        sum += a;
    }

    return sum;
}

int get_idx_in_dict(int needle, int haystack[], int count) {
    for (int i = 0; i < count; ++i) {
        if (needle == haystack[i]) {
            return i;
        }
    }

    return -1;
}

int get_solution2(int nums_1[], int nums_2[], int nums_length) {
    int count_of_nums2_keys[nums_length];
    int count_of_nums2_values[nums_length];
    for (int i = 0; i < nums_length; ++i) {
        int idx = get_idx_in_dict(nums_2[i], count_of_nums2_keys, 1000);
        if (idx != -1) {
            ++count_of_nums2_values[idx];
        } else {
            count_of_nums2_keys[i] = nums_2[i];
            count_of_nums2_values[i] = 1;
        }
    }

    int sum = 0;
    for (int i = 0; i < nums_length; ++i) {
        int idx = get_idx_in_dict(nums_1[i], count_of_nums2_keys, 1000);
        if (idx != -1) {
            sum += nums_1[i] * count_of_nums2_values[idx];
        }
    }

    return sum;
}

int main(int argc, char *argv[]) {

    int nums_1[1000],
        nums_2[1000];
    
    int succeeded = read_file_into_arrays("./input", nums_1, nums_2);
    if (succeeded != 1) {
        printf("Failed to write to arrays from file");
        exit(1);
    }

    int s1 = get_solution1(nums_1, nums_2, 1000);
    int s2 = get_solution2(nums_1, nums_2, 1000);

    printf("Solution 1: %d\n\0", s1);
    printf("Solution 2: %d\n\0", s2);

    return 0;
}
