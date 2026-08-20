#include <stdio.h>
#include <stdlib.h>

void backtrack(int* nums, int numsSize, int* path, int depth, int** result, int* returnSize, int* returnColumnSizes) {
   if (depth == numsSize) {
        result[*returnSize] = malloc(sizeof(int) * numsSize);
        for (int i = 0; i < numsSize; i++) {
            result[*returnSize][i] = path[i];
        }
        returnColumnSizes[*returnSize] = numsSize;
        (*returnSize)++;
        return;
    }
    for (int i = 0; i < numsSize; i++) {
        int used = 0;
        for (int j = 0; j < depth; j++) {
            if (path[j] == nums[i]) {
                used = 1;
                break;
            }
        }
        if (!used) {
            path[depth] = nums[i];
            backtrack(nums, numsSize, path, depth + 1, result, returnSize, returnColumnSizes);
        }
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalPermutations = 1;
    for (int i = 1; i <= numsSize; i++) {
        totalPermutations *= i;
    }
    int **result = malloc(sizeof(int*) * totalPermutations);
    int path[numsSize];
    *returnSize = 0;
    *returnColumnSizes = malloc(sizeof(int) * totalPermutations);
    backtrack(nums, numsSize, path, 0, result, returnSize, *returnColumnSizes);
    return result;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* returnColumnSizes;
    int** result = permute(nums, numsSize, &returnSize, &returnColumnSizes);

    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            if (j > 0) {
                printf(",");
            }
            printf("%d", result[i][j]);
        }
        if (i < returnSize - 1) {
            printf("],");
        } else {
            printf("]");
        }
        free(result[i]);
    }
    printf("]");
    free(result);
    free(returnColumnSizes);
}