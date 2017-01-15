//
// Created by Daniel on 14.01.17.
//

#ifndef APHROCITE_APHROCITE_H
#define APHROCITE_APHROCITE_H

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// bool
#define FALSE 0
#define TRUE 1 

typedef unsigned int bool32;

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
#define TEST_FAILED "Test FAILED: "

#define COLOR_RED   "\x1B[31m"
#define COLOR_GREEN   "\x1B[32m"
#define COLOR_RESET "\x1B[0m"

void Test_SuccessMessage(char *message){
    Print_Format(COLOR_GREEN "%s" COLOR_RESET  "%s\n", TEST_OK, message);
}

void Test_FailureMessage(char *message){
    Print_Format(COLOR_RED "%s " COLOR_RESET "%s\n", TEST_FAILED, message);
}

void Test_CheckCondition(bool32 condition, char *description){
    if(condition){
        Test_SuccessMessage(description);
    } else {
        Test_FailureMessage(description);
        exit(EXIT_FAILURE);
    }
}

void Assert_True(char* description, bool32 condition){
    Test_CheckCondition(condition, description);
}

void Assert_Compare(char* description, void* actual, void* desired, int size){
    Test_CheckCondition(Memory_Compare(actual, desired, size) == 0, description);
}

#endif //APHROCITE_APHROCITE_H
