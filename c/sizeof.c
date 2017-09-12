#include <stdio.h>
#include <stddef.h>

struct PackStruct {
    short a;
    char  b;
    int  *c;
    unsigned int d;
} __attribute__((packed));

typedef struct TestStruct {
    short a;
    int  *c;
    char  b;
    unsigned int d;
} TestStruct_t;

#define OffsetOf(s, d) (size_t)(&(((s*)0)->d))

void PrintSize(size_t s, char *name) {

    printf("Size of %s is %zu\n", name, s);
}

int main() {
    char str[] = "hello";
    int *arr1[8];
    int (*arr2)[8];
    int *(arr3[8]);
    PrintSize(sizeof(str), "str");
    PrintSize(sizeof(arr1), "arr1");
    PrintSize(sizeof(arr2), "arr2");
    PrintSize(sizeof(arr3), "arr3");
    PrintSize(sizeof(char), "char");
    PrintSize(sizeof(short), "short");
    PrintSize(sizeof(int), "int");
    PrintSize(sizeof(int *), "int *");
    PrintSize(sizeof(unsigned int), "unsigned int");
    PrintSize(sizeof(long), "long");
    PrintSize(sizeof(long long), "long long");
    PrintSize(sizeof(struct PackStruct), "PackStruct");
    PrintSize(sizeof(struct TestStruct), "TestStruct");

    printf("offset of c is %zu\n", offsetof(struct PackStruct, c));
    printf("offset of c is %zu\n", OffsetOf(struct PackStruct, c));
    printf("offset of c is %zu\n", offsetof(struct TestStruct, c));
    printf("offset of c is %zu\n", OffsetOf(struct TestStruct, c));

    size_t off = (size_t)(&(((TestStruct_t *)0)->d));
    printf("off is %zu\n", off);

    return 0;
}
