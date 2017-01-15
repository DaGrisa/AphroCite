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
    assertTrue("FALSE Constant", 0 == FALSE);
    assertTrue("TRUE Constant", 1 == TRUE);
}

void testOperators(){
    assertTrue("and Operator", 0 == FALSE AND 1 == TRUE);
    assertTrue("or Operator", 0 == FALSE OR 1 == TRUE);
    assertTrue("not Operator", 0 == NOT TRUE);
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

    assertCompare("Allocate Memory Macro", pInteger, pIntegerCompare, sizeof(int));

    assertTrue("Compare Memory Macro", Memory_Compare(&pInteger, &pIntegerCompare, sizeof(int)));

    Memory_Free(pInteger);
    Memory_Free(pIntegerCompare);
};

void testString(){
    char formattedString[] = "It's all about the %d\n";
    char copyString[] = "It's all about the 21\n";
    CString_Copy(copyString, formattedString);

    assertCompare("Copy String Macro", &copyString, &formattedString, sizeof(copyString));
};

// Main
int main() {
    testConstants();
    testOperators();
    testMacros();

    return EXIT_SUCCESS;
}