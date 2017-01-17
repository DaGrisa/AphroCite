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
typedef unsigned int bool32;
#define FALSE 0
#define TRUE 1 

// Operators
#define OR ||
#define AND &&
#define NOT !

// print
#define Console_Print_NextLine() printf("\n")
#define Console_Print(cString) printf(cString)
#define Console_Print_Line(cString) printf(cString "\n")
#define Console_Print_Format(format, ...) printf(format, __VA_ARGS__)
#define Console_Print_Format_Line(format, ...) printf(format "\n", __VA_ARGS__)
#define Console_Read_Line(cString) scanf(cString)

// c-string
#define CString_Copy strcpy
#define CString_Compare strcmp

// memory
#define Memory_Allocate malloc
#define Memory_Free free
#define Memory_Compare memcmp

// Unit Testing
#define TEST_OK "Test OK: "
#define TEST_FAILED "Test FAILED: "

#define TEXT_COLOR_RED   "\x1B[31m"
#define TEXT_COLOR_GREEN   "\x1B[32m"
#define TEXT_COLOR_RESET "\x1B[0m"

void Test_SuccessMessage(char *message) {
    Console_Print_Format_Line(TEXT_COLOR_GREEN "%s" TEXT_COLOR_RESET "%s", TEST_OK, message);
}

void Test_FailureMessage(char *message){
    Console_Print_Format_Line(TEXT_COLOR_RED "%s " TEXT_COLOR_RESET "%s", TEST_FAILED, message);
    exit(EXIT_FAILURE);
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

/*
    Unit Testing Functionality
*/

typedef struct _T_UnitTest_TestSuite {
    int testCount;
    int failedCount;
    int succeededCount;
} T_UnitTest_TestSuite;

typedef enum _E_UnitTest_TestState {
    UNITTEST_TESTSTATE_SUCCESS = 0,
    UNITTEST_TESTSTATE_FAIL = 1
} E_UnitTest_TestState;

#define UNITTEST_SUCCESS return UNITTEST_TESTSTATE_SUCCESS
#define UNITTEST_FAIL return UNITTEST_TESTSTATE_FAIL

#define UnitTest_Assert_True(condition) return Internal_UnitTest_Assert_True(condition, __FILE__, __FUNCTION__, __LINE__)
#define UNITTest_Assert_False(condition) return Internal_UnitTest_Assert_False(condition, __FILE__, __FUCNTION__, __LINE__)

E_UnitTest_TestState Internal_UnitTest_Assert_True(bool32 condition, char* file, char* function, int line) {
    if(condition == FALSE) { 
        Console_Print_Format_Line("Assertion Failed: File: %s, Function: %s, Line: %d", file, function, line);
        return UNITTEST_TESTSTATE_FAIL;
    } else {
        return UNITTEST_TESTSTATE_SUCCESS;
    }
}

E_UnitTest_TestState Internal_UnitTest_Assert_False(bool32 condition, char* file, char* function, int line) {
    if(condition == TRUE) { 
        Console_Print_Format_Line("Assertion Failed: File: %s, Function: %s, Line: %d", file, function, line);
        return UNITTEST_TESTSTATE_FAIL;
    } else {
        return UNITTEST_TESTSTATE_SUCCESS;
    }
}

#define UNITTEST_TEXT_SUCCESS "SUCCESS"
#define UNITTEST_TEXT_FAIL "FAILED"

typedef int (*UnitTestFunctionCallback)();

void UnitTest_RunSingle(T_UnitTest_TestSuite* testSuite, UnitTestFunctionCallback callback, char* description) {
    Console_Print_Format_Line("Start Test: %s ", description);
    ++testSuite->testCount;
    E_UnitTest_TestState unitTestState = callback();

    if(unitTestState == UNITTEST_TESTSTATE_SUCCESS) {
        ++testSuite->succeededCount;
        Console_Print_Format_Line(TEXT_COLOR_GREEN "%s" TEXT_COLOR_RESET, UNITTEST_TEXT_SUCCESS);
    } else if (UNITTEST_TESTSTATE_FAIL) {
        ++testSuite->failedCount;
        Console_Print_Format_Line(TEXT_COLOR_RED "%s" TEXT_COLOR_RESET, UNITTEST_TEXT_FAIL);
    } else {
     //TODO(ans) be explit an crash the application here because of development error  
    }
    
    Console_Print_NextLine();
}

void UnitTest_PrintTestSuiteState(T_UnitTest_TestSuite* testSuite) {
    Console_Print_Format_Line("Tests Run: %d", testSuite->testCount);
    Console_Print_Format_Line("Tests Succeeded: %d", testSuite->succeededCount);
    Console_Print_Format_Line("Tests Failed: %d", testSuite->failedCount);
}


#endif //APHROCITE_APHROCITE_H
