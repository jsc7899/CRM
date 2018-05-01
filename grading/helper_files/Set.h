#ifndef __SET_H__
#define __SET_H__
// #include "MemHeap.h"

struct Set
{
    int *elements;
    int len;
    int capacity;
};

#define reassignSet     assignSet

void createSingletonSet(Set* self, int x);
void createEmptySet(Set* self);
void createCopySet(Set* self, const Set* other);
void assignSet(Set* self, const Set* other);
void destroySet(Set* self);

bool isMemberSet(const Set* self, int x);
bool isEmptySet(const Set* self);
bool isEqualToSet(const Set* self, const Set* other);
bool isSubsetOf(const Set* self, const Set* other);
void displaySet(const Set* self);

void insertSet(Set* self, int x);
void removeSet(Set* self, int x);

void unionInSet(Set* self, const Set* other);
void intersectFromSet(Set* self, const Set* other);
void subtractFromSet(Set* self, const Set* other);
#endif