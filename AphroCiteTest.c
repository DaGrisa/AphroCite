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

void TestUnsignedIntegerTypes(UnitTest_TestResult* testResult) {
    UnsignedInteger8 integer8 = UNSIGNED_INTEGER_8_MAX;
    UnsignedInteger16 integer16 = UNSIGNED_INTEGER_16_MAX;
    UnsignedInteger32 integer32 = UNSIGNED_INTEGER_32_MAX;

    UnitTest_Assert_True(testResult, integer8 == 255);
    UnitTest_Assert_True(testResult, integer16 == 65535);
    UnitTest_Assert_True(testResult, integer32 == 4294967295);
}

void TestSignedIntegerTypes(UnitTest_TestResult* testResult) {
    SignedInteger8 signedInteger8LowerBound = SIGNED_INTEGER_8_MIN;
    SignedInteger8 signedInteger8UpperBound = SIGNED_INTEGER_8_MAX;
    SignedInteger16 signedInteger16LowerBound = SIGNED_INTEGER_16_MIN;
    SignedInteger16 signedInteger16UpperBound = SIGNED_INTEGER_16_MAX;
    SignedInteger32 signedInteger32LowerBound = SIGNED_INTEGER_32_MIN;
    SignedInteger32 signedInteger32UpperBound = SIGNED_INTEGER_32_MAX;

    UnitTest_Assert_True(testResult, signedInteger8LowerBound == -128);
    UnitTest_Assert_True(testResult, signedInteger8UpperBound == 127);
    UnitTest_Assert_True(testResult, signedInteger16LowerBound == -32768);
    UnitTest_Assert_True(testResult, signedInteger16UpperBound == 32767);
    UnitTest_Assert_True(testResult, signedInteger32LowerBound == -2147483648);
    UnitTest_Assert_True(testResult, signedInteger32UpperBound == 2147483647);
}

/* 
    Main
*/
int main() {
    UnitTest_TestSuite testSuite = {0};
    testSuite.name = "New Unit Tests";
    testSuite.silentMode = FALSE;

    TestDefinition testDefinitions[] = {
        { &TestBooleanConstants, "Boolean Constants" },
        { &TestBooleanOperators, "Boolean Operators" },
        { &TestMemoryCompare, "Memory Compare" },
        { &TestMemoryAllocate, "Memory Allocation" },
        { &TestStringSame, "String Same" },
        { &TestStringNotSame, "String not Same" },
        { &TestUnsignedIntegerTypes, "Unsigned Integer Types Boundary Checks" },
        { &TestSignedIntegerTypes, "Signed Integer Types Boundary Checks" }
    };

    testSuite.testDefinitions = testDefinitions;
    testSuite.testDefininitionCount = sizeof(testDefinitions) / sizeof(testDefinitions[0]);

    return UnitTest_RunTestSuite(&testSuite);
}
