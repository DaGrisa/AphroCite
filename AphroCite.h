//
// Created by Daniel on 14.01.17.
//

#ifndef APHROCITE_APHROCITE_H
#define APHROCITE_APHROCITE_H

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define FALSE 0
#define TRUE !(FALSE)

// Operators
#define or ||
#define and &&
#define not !

// Function Macros
// stdio
#define FormattedPrint printf
// stdlib
#define AllocateMemory malloc
#define FreeMemory free
// string
#define CopyString strcpy
#define CompareMemory memcmp
#define CompareString strcmp

// Unit Testing
#define TEST_OK "Test OK: "
#define TEST_NOK "Test FAILED: "

#define TEXT_COLOR_RED   "\x1B[31m"
#define TEXT_COLOR_GREEN   "\x1B[32m"
#define TEXT_COLOR_RESET "\x1B[0m"

void testSuccessMessage(char *message){
    FormattedPrint(TEXT_COLOR_GREEN "%s" TEXT_COLOR_RESET  "%s\n", TEST_OK, message);
}

void testFailureMessage(char *message){
    FormattedPrint(TEXT_COLOR_RED "%s " TEXT_COLOR_RESET "%s\n", TEST_NOK, message);
    exit(EXIT_FAILURE);
}

void testCheckCondition(int condition, char *description){
    if(condition){
        testSuccessMessage(description);
    } else {
        testFailureMessage(description);
    }
}

void assertTrue(char* description, int condition){
    testCheckCondition(condition, description);
}

void assertCompare(char* description, void* actual, void* desired, int size){
    testCheckCondition(CompareMemory(actual, desired, size) == 0, description);
}

#endif //APHROCITE_APHROCITE_H
