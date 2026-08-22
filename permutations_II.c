#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int* nums, int numsSize, int* path, int depth, int** result, int* returnSize, int* returnColumnSizes, int* used) {
    if (depth == numsSize) {
        result[*returnSize] = (int*)malloc(numsSize * sizeof(int));
        memcpy(result[*returnSize], path, numsSize * sizeof(int));
        returnColumnSizes[*returnSize] = numsSize;
        (*returnSize)++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i]) continue;
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
        used[i] = 1;
        path[depth] = nums[i];
        backtrack(nums, numsSize, path, depth + 1, result, returnSize, returnColumnSizes, used);
        used[i] = 0;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), compare);
    int totalPermutations = 1;
    for (int i = 2; i <= numsSize; i++) {
        totalPermutations *= i;
    }
    int **result = (int**)malloc(totalPermutations * sizeof(int*));
    int path[numsSize];
    *returnColumnSizes = (int*)malloc(totalPermutations * sizeof(int));
    *returnSize = 0;
    int used[numsSize];
    memset(used, 0, sizeof(used));
    backtrack(nums, numsSize, path, 0, result, returnSize, *returnColumnSizes, used);
    return result;
}

int main() {
    int nums[] = {1, 1, 2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* returnColumnSizes;
    int** ans = permuteUnique(nums, numsSize, &returnSize, &returnColumnSizes);
    
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            if (j > 0) printf(",");
            printf("%d", ans[i][j]);
        }
        if (i < returnSize - 1) printf("],");
        else printf("]");
        free(ans[i]);
    }
    printf("]");

    free(returnColumnSizes);
    free(ans);
    return 0;
}