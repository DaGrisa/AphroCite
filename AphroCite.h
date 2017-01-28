/*
    Created by Daniel on 14.01.17.
*/

#ifndef APHROCITE_APHROCITE_H
#define APHROCITE_APHROCITE_H

/*
    Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*
    bool
*/
typedef enum {
    FALSE = 0,
    TRUE = 1,
} Boolean;

/* 
    Operators
*/
#define OR ||
#define AND &&
#define NOT !

/* 
    Memory
*/
#define Memory_Allocate_Init malloc
#define Memory_Free free
#define Memory_Compare memcmp

/* 
    Console
*/
#define Console_Print_NextLine() printf("\n")
#define Console_Print_CString(cString) printf(cString)
#define Console_Print_CString_Line(cString) \
    printf(cString); \
    Console_Print_NextLine();
#define Console_Print_CString_Format(format, ...) printf(format, __VA_ARGS__)
#define Console_Print_CString_Format_Line(format, ...) \
    printf(format, __VA_ARGS__); \
    Console_Print_NextLine();
#define Console_Read_Line(cString) scanf(cString)

/*
    CString
*/
#define CString char*

#define CString_Format(formatResult, toFormat, ...) sprintf(formatResult, toFormat, __VA_ARGS__)
#define CString_Copy strcpy
#define CString_Compare strcmp

CString CString_Create_Format(int size, CString format, ...) {
    CString newCString = Memory_Allocate_Init(sizeof(char) * size);

    va_list arglist;
    va_start(arglist, format );

    vsprintf(newCString, format, arglist);
    
    va_end( arglist );

    return newCString;
}

/*
    Unit Testing
*/
#define TEXT_COLOR_RED   "\x1B[31m"
#define TEXT_COLOR_GREEN   "\x1B[32m"
#define TEXT_COLOR_RESET "\x1B[0m"

typedef struct {
    CString name;
    Boolean silentMode;

    int testCount;
    int failedCount;
    int succeededCount;
} UnitTest_TestSuite;

typedef enum {
    UNITTEST_TESTSTATE_SUCCESS = 0,
    UNITTEST_TESTSTATE_FAIL = 1
} UnitTest_TestState;

#define UnitTest_Assert_True(testResultPointer, condition) Internal_UnitTest_Assert_True(testResultPointer, condition, __FILE__, __FUNCTION__, __LINE__); if(testResult->state == UNITTEST_TESTSTATE_FAIL) return;
#define UnitTest_Assert_False(testResultPointer, condition) Internal_UnitTest_Assert_True(testResultPointer, !(condition), __FILE__, __FUNCTION__, __LINE__); if(testResult->state == UNITTEST_TESTSTATE_FAIL) return;
#define UnitTest_Assert_Memory_Same(testResultPointer, pointerA, pointerB, size) Internal_UnitTest_Assert_True(testResultPointer, Memory_Compare(pointerA, pointerB, size) == 0, __FILE__, __FUNCTION__, __LINE__); if(testResult->state == UNITTEST_TESTSTATE_FAIL) return;
#define UnitTest_Assert_Memory_NotSame(testResultPointer, pointerA, pointerB, size) Internal_UnitTest_Assert_True(testResultPointer, Memory_Compare(pointerA, pointerB, size) != 0, __FILE__, __FUNCTION__, __LINE__); if(testResult->state == UNITTEST_TESTSTATE_FAIL) return;


typedef struct {
    UnitTest_TestState state;
    CString errorMessage;
} UnitTest_TestResult;

void Internal_UnitTest_Assert_True(UnitTest_TestResult* testResult, Boolean condition, CString file, const CString function, int line) {
    testResult->state = UNITTEST_TESTSTATE_SUCCESS;

    if(condition == FALSE) { 
        testResult->errorMessage = CString_Create_Format(255, "Assertion Failed: File: %s, Function: %s, Line: %d", file, function, line);
        testResult->state = UNITTEST_TESTSTATE_FAIL;
    }
}

typedef void (*UnitTestFunctionCallback)(UnitTest_TestResult* testResult);

void UnitTest_RunSingle(UnitTest_TestSuite* testSuite, UnitTestFunctionCallback callback, CString description) {
    /*
        Note(Norskan): Some people will notice that the memory allocated for testResult.errorMessage
        is never freed. I actually do not care about that because the the os will clean up the memory anyway
        after the program has exited. If there is ever an memory issue because of running the unit test I will
        change that ;)
    */

    ++testSuite->testCount;
    UnitTest_TestResult testResult;
    callback(&testResult);

    if(testResult.state == UNITTEST_TESTSTATE_SUCCESS) {
        ++testSuite->succeededCount;
        
        if(!testSuite->silentMode) {
            Console_Print_CString_Format_Line(TEXT_COLOR_GREEN "Test OK" TEXT_COLOR_RESET ":\t %s", description);
        }
    } else {
        ++testSuite->failedCount;

        if(!testSuite->silentMode) {
             Console_Print_CString_Format_Line(TEXT_COLOR_RED  "Test FAIL" TEXT_COLOR_RESET ":\t %s -> %s", description, testResult.errorMessage);
        }
    } 
}

void UnitTest_PrintTestSuiteState(UnitTest_TestSuite* testSuite) {
    if(!testSuite->silentMode) {
        Console_Print_CString_Line("-----Test Metrics -----");
        Console_Print_CString_Format_Line("Run \"%s\" Test Suite", testSuite->name);
        Console_Print_CString_Format_Line("Tests Run: %d", testSuite->testCount);
        Console_Print_CString_Format_Line("Tests Succeeded: %d", testSuite->succeededCount);
        Console_Print_CString_Format_Line("Tests Failed: %d", testSuite->failedCount);
    }
}

int UnitTest_CreateExitCode(UnitTest_TestSuite* testSuite) {
    if(testSuite->failedCount > 0) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}


#endif
