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
typedef unsigned int Boolean32;
#define FALSE 0
#define TRUE 1 

/* 
    Operators
*/
#define OR ||
#define AND &&
#define NOT !

/* 
    Memory
*/
#define Memory_Allocate malloc
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
    CString newCString = Memory_Allocate(sizeof(char) * size);

    va_list arglist;
    va_start(arglist, format );

    vsprintf(newCString, format, arglist);
    
    va_end( arglist );

    return newCString;
}

/*
    Unit Testing
*/
#define TEST_OK "Test OK: "
#define TEST_FAILED "Test FAILED: "

#define TEXT_COLOR_RED   "\x1B[31m"
#define TEXT_COLOR_GREEN   "\x1B[32m"
#define TEXT_COLOR_RESET "\x1B[0m"

void Test_SuccessMessage(CString message) {
    Console_Print_CString_Format_Line(TEXT_COLOR_GREEN "%s" TEXT_COLOR_RESET "%s", TEST_OK, message);
}

void Test_FailureMessage(CString message){
    Console_Print_CString_Format_Line(TEXT_COLOR_RED "%s " TEXT_COLOR_RESET "%s", TEST_FAILED, message);
    exit(EXIT_FAILURE);
}

void Test_CheckCondition(Boolean32 condition, CString description){
    if(condition){
        Test_SuccessMessage(description);
    } else {
        Test_FailureMessage(description);
        exit(EXIT_FAILURE);
    }
}

void Assert_True(CString description, Boolean32 condition){
    Test_CheckCondition(condition, description);
}

void Assert_Compare(CString description, void* actual, void* desired, int size){
    Test_CheckCondition(Memory_Compare(actual, desired, size) == 0, description);
}

/*
    Unit Testing Functionallity
*/

typedef struct _T_UnitTest_TestSuite {
    CString name;
    Boolean32 silentMode;

    int testCount;
    int failedCount;
    int succeededCount;
} T_UnitTest_TestSuite;

typedef enum _E_UnitTest_TestState {
    UNITTEST_TESTSTATE_SUCCESS = 0,
    UNITTEST_TESTSTATE_FAIL = 1
} E_UnitTest_TestState;

#define UnitTest_Assert_True(testResultPointer, condition) Internal_UnitTest_Assert_True(testResultPointer, condition, __FILE__, __FUNCTION__, __LINE__); if(testResult->state == UNITTEST_TESTSTATE_FAIL) return;
#define UnitTest_Assert_False(testResultPointer, condition) Internal_UnitTest_Assert_True(testResultPointer, !(condition), __FILE__, __FUNCTION__, __LINE__); if(testResult->state == UNITTEST_TESTSTATE_FAIL) return;

typedef struct _T_UnitTest_TestResult {
    E_UnitTest_TestState state;
    CString errorMessage;
} T_UnitTest_TestResult;

void Internal_UnitTest_Assert_True(T_UnitTest_TestResult* testResult, Boolean32 condition, CString file, const CString function, int line) {
    testResult->state = UNITTEST_TESTSTATE_SUCCESS;

    if(condition == FALSE) { 
        testResult->errorMessage = CString_Create_Format(255, "Assertion Failed: File: %s, Function: %s, Line: %d", file, function, line);
        testResult->state = UNITTEST_TESTSTATE_FAIL;
    }
}

typedef void (*UnitTestFunctionCallback)(T_UnitTest_TestResult* testResult);

void UnitTest_RunSingle(T_UnitTest_TestSuite* testSuite, UnitTestFunctionCallback callback, CString description) {
    /*
        Note(Norskan): Some people will notice that the memory allocated for testResult.errorMessage
        is never freed. I actually do not care about that because the the os will clean up the memory anyway
        after the program has exited.
    */

    ++testSuite->testCount;
    T_UnitTest_TestResult testResult;
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

void UnitTest_PrintTestSuiteState(T_UnitTest_TestSuite* testSuite) {
    if(!testSuite->silentMode) {
        Console_Print_CString_Line("-----Test Metrics -----");
        Console_Print_CString_Format_Line("Run \"%s\" Test Suite", testSuite->name);
        Console_Print_CString_Format_Line("Tests Run: %d", testSuite->testCount);
        Console_Print_CString_Format_Line("Tests Succeeded: %d", testSuite->succeededCount);
        Console_Print_CString_Format_Line("Tests Failed: %d", testSuite->failedCount);
    }
}

int UnitTest_CreateExitCode(T_UnitTest_TestSuite* testSuite) {
    if(testSuite->failedCount > 0) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}


#endif
