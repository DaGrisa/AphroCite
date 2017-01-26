//
// Created by Daniel on 15.01.17.
//

#include "AphroCite.h"

// Declaration
void testConstants();

void testOperators();

void testMacros();
void testStdlib();
void testString();

// Definition
void testConstants(){
    Assert_True("FALSE Constant", 0 == FALSE);
    Assert_True("TRUE Constant", 1 == TRUE);
}

void testOperators(){
    Assert_True("and Operator", 0 == FALSE AND 1 == TRUE);
    Assert_True("or Operator", 0 == FALSE OR 1 == TRUE);
    Assert_True("not Operator", 0 == NOT TRUE);
}

void testMacros(){
    testStdlib();
    testString();
}

void testStdlib(){
    int* pInteger;
    pInteger = Memory_Allocate(sizeof(int));
    *pInteger = 42;

    int* pIntegerCompare;
    pIntegerCompare = Memory_Allocate(sizeof(int));
    *pIntegerCompare = 42;

    Assert_Compare("Allocate Memory Macro", pInteger, pIntegerCompare, sizeof(int));

    Assert_True("Compare Memory Macro", Memory_Compare(&pInteger, &pIntegerCompare, sizeof(int)));

    Memory_Free(pInteger);
    Memory_Free(pIntegerCompare);
};

void testString(){
    char formattedString[] = "It's all about the %d\n";
    char copyString[] = "It's all about the 21\n";
    CString_Copy(copyString, formattedString);

    Assert_Compare("Copy String Macro", &copyString, &formattedString, sizeof(copyString));
    Assert_True("Compare Sring Macro", CString_Compare(formattedString, copyString) == 0);
};

void TestUnitTestAssertTrueSuccess(T_UnitTest_TestResult* testResult) {
    UnitTest_Assert_True(testResult, TRUE);

    Console_Print_CString_Line("Should be reached!");
}

void TestUnitTestAssertTrueFail(T_UnitTest_TestResult* testResult) {
    UnitTest_Assert_True(testResult, FALSE);
    Console_Print_CString_Line("Should not be reached!");
}

// Main
int main() {
    testConstants();
    testOperators();
    testMacros();

    Console_Print_NextLine();
    Console_Print_CString_Line(".---------------------.");
    Console_Print_CString_Line("| New Unit Test Style |");
    Console_Print_CString_Line(".---------------------.");
    Console_Print_NextLine();

    T_UnitTest_TestSuite testSuite = {0};
    testSuite.name = "New Unit Test";
    testSuite.silentMode = FALSE;

    UnitTest_RunSingle(&testSuite, &TestUnitTestAssertTrueSuccess, "Test Success TRUE assert Unit Test");
    UnitTest_RunSingle(&testSuite, &TestUnitTestAssertTrueFail, "Test Fail TRUE assert Unit Test");

    UnitTest_PrintTestSuiteState(&testSuite);

    return UnitTest_CreateExitCode(&testSuite);
}
