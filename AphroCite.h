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
#define TRUE 1 

// Operators
#define OR ||
#define AND &&
#define NOT !

// Function Macros
// print
#define Print_Format printf

// string
#define CString_Copy strcpy

// memory
#define Memory_Allocate malloc
#define Memory_Free free
#define Memory_Compare memcmp

// Unit Testing
#define TEST_OK "Test OK: "
#define TEST_NOK "Test FAILED: "

// Color
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define RESET "\x1B[0m"

void Test_SuccessMessage(char *message){
    Print_Format(GREEN "%s" RESET  "%s\n", TEST_OK, message);
}

void Test_FailureMessage(char *message){
    Print_Format(RED "%s " RESET "%s\n", TEST_NOK, message);
    exit(EXIT_FAILURE);
}

void testCheckCondition(int condition, char *description){
    if(condition){
        Test_SuccessMessage(description);
    } else {
        Test_FailureMessage(description);
    }
}

void assertTrue(char* description, int condition){
    testCheckCondition(condition, description);
}

void assertCompare(char* description, void* actual, void* desired, int size){
    testCheckCondition(Memory_Compare(actual, desired, size) == 0, description);
}

#endif //APHROCITE_APHROCITE_H
