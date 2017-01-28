/*
    Created by Daniel on 15.01.17.
*/

#include "AphroCite.h"

/*  
    Definition
*/
void TestBooleanConstants(UnitTest_TestResult* testResult){
    UnitTest_Assert_True(testResult, 0 == FALSE);
    UnitTest_Assert_True(testResult, 1 == TRUE);
}

void TestBooleanOperators(UnitTest_TestResult* testResult){
    UnitTest_Assert_True(testResult, 0 == FALSE AND 1 == TRUE);
    UnitTest_Assert_True(testResult, 0 == FALSE OR 1 == TRUE);
    UnitTest_Assert_True(testResult, 0 == NOT TRUE);
}

void TestMemoryCompare(UnitTest_TestResult* testResult) {
    int value = 42;
    int* expected = &value;
    int* actual = &value;

    UnitTest_Assert_Memory_Same(testResult, actual, expected, sizeof(int));
    UnitTest_Assert_True(testResult, Memory_Compare(actual, expected, sizeof(int)) == 0);
}

void TestMemoryAllocate(UnitTest_TestResult* testResult) {
    int* actual = Memory_Allocate_Init(sizeof(int));
    int* expected = Memory_Allocate_Init(sizeof(int));

    UnitTest_Assert_Memory_Same(testResult, actual, expected, sizeof(int));

    *actual = 42;

    UnitTest_Assert_Memory_NotSame(testResult, actual, expected, sizeof(int));
}

void TestStringSame(UnitTest_TestResult* testResult) {
    CString actual = "It's all about the 21";

    UnitTest_Assert_Memory_Same(testResult, &actual, &actual, sizeof(actual));
    UnitTest_Assert_True(testResult, CString_Compare(actual, actual) == 0);
}

void TestStringNotSame(UnitTest_TestResult* testResult) {
    CString actual = "It's all about the 21";
    CString expected = "It's all about the 42";

    UnitTest_Assert_Memory_NotSame(testResult, &actual, &expected, sizeof(expected));
    UnitTest_Assert_True(testResult, CString_Compare(actual, expected));
}


/* 
    Main
*/
int main() {
    UnitTest_TestSuite testSuite = {0};
    testSuite.name = "New Unit Test";
    testSuite.silentMode = FALSE;

    UnitTest_RunSingle(&testSuite, &TestBooleanConstants, "Boolean Constants");
    UnitTest_RunSingle(&testSuite, &TestBooleanOperators, "Boolean Operators");
    UnitTest_RunSingle(&testSuite, &TestMemoryCompare, "Memory Compare");
    UnitTest_RunSingle(&testSuite, &TestMemoryAllocate, "Memory Allocation");
    UnitTest_RunSingle(&testSuite, &TestStringSame, "String Same");
    UnitTest_RunSingle(&testSuite, &TestStringNotSame, "String not Same");

    UnitTest_PrintTestSuiteState(&testSuite);

    return UnitTest_CreateExitCode(&testSuite);
}
