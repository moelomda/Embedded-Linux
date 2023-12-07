#include <stdio.h>

int Binary_Search(int *ptr, int size, int Key) {
    int L = 0;
    int R = size - 1;
    int mid;

    while (L <= R) {
        mid = (L + R) / 2;
        if (Key > ptr[mid]) {
            L = mid + 1;
        } else if (Key < ptr[mid]) {
            R = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int main() {
    int arr[8] = {23, 12, 43, 11, 55, 32, 67, 99};

    int Index = Binary_Search(arr, 8, 11);

    if (Index != -1) {
        printf("Element is Found at Index: %d\n", Index);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}

