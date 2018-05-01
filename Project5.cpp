/*
 * Set ADT
 * Project5.c 
 *
// Set <Project5.cpp>
// EE 312 Project 5 submission by
// Jared Campbell
// jsc3642
// Slip days used: 0
// Spring 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    if(self->len == 0) return false;
    int min = 0;
    int max = self->len-1;
    while(min <= max) {
        int mid = (min + max)/2;
        if(self->elements[mid] == x) {
            return true;
        }
        if(self->elements[mid] < x) {
            min = mid+1;
        }
        else if(self->elements[mid] > x) {
            max = mid-1;
        }
    }
    return false;
    /*
    int mid = (self->len)/2;
    if(x == self->elements[mid]) return true;
    if(x < self->elements[mid]) {
        for(int i = 0; i < mid; i++) {
            if(self->elements[i] == x) return true;
        }
    }
    else {
        for(int i = mid; i < self->len; i++) {
            if(self->elements[i] == x) return true;
        }
    }
    return false;
     */
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if(isMemberSet(self, x)) {
        return;
    }
    if(self->elements == nullptr){
        createSingletonSet(self, x);
        return;
    }
    if(x > self->elements[self->len-1]) {
        self->elements = (int*)realloc(self->elements, sizeof(int)*((self->len)+1));
        self->elements[self->len] = x;
        self->len++;
        return;
    }
    if(x < self->elements[0]){
        self->elements = (int*)realloc(self->elements, sizeof(int)*((self->len)+1));
        for(int i = self->len; i > 0; i--){
            self->elements[i] = self->elements[i-1];
        }
        self->elements[0] = x;
        self->len++;
        return;
    }
    int i = 0;
    self->elements = (int*)realloc(self->elements, sizeof(int)*((self->len)+1));
    int index = 0;
    while(i < self->len-1) {
        if(self->elements[i] < x && self->elements[i+1] > x) {
            index = i+1;
            for(int j = self->len; j > index && j > 0; j--){
                self->elements[j] = self->elements[j-1];
            }
            break;
        }
        i++;
    }
    self->elements[index] = x;
    self->len++;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if(!isMemberSet(self, x)) return;
    int i = 0;
    int j = 0;
    while(i < self->len-1 && j < self->len) {
        if(self->elements[i] == x) {
            j++;
        }
        self->elements[i] = self->elements[j];
        i++;
        j++;
    }
    self->len--;
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len) return false;
    for(int i = 0; i < self->len && i < other->len; i++) {
        if(self->elements[i] != other->elements[i]) {
            return false;
        }
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    for(int i = 0; i < self->len; i++) {
        if(!isMemberSet(other, self->elements[i])) return false;
    }
    return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    for(int i = 0; i < self->len; i++) {
        if(!isMemberSet(other, self->elements[i])) {
            removeSet(self, self->elements[i]);
            i--;
        }
    }
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    for(int i = 0; i < self->len; i++) {
        if(isMemberSet(other, self->elements[i])) {
            removeSet(self, self->elements[i]);
            i--;
        }
    }
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    for(int i = 0; i < other->len; i++) {
        insertSet(self, other->elements[i]);
    }
}
