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
    assertTrue("and Operator", 0 == FALSE and 1 == TRUE);
    assertTrue("or Operator", 0 == FALSE or 1 == TRUE);
    assertTrue("not Operator", 0 == not TRUE);
}

void testMacros(){
    testStdlib();
    testString();
}

void testStdlib(){
    int* pInteger;
    pInteger = AllocateMemory(sizeof(int));
    *pInteger = 42;

    int* pIntegerCompare;
    pIntegerCompare = AllocateMemory(sizeof(int));
    *pIntegerCompare = 42;

    assertCompare("Allocate Memory Macro", pInteger, pIntegerCompare, sizeof(int));

    assertTrue("Compare Memory Macro", CompareMemory(&pInteger, &pIntegerCompare, sizeof(int)));

    FreeMemory(pInteger);
    FreeMemory(pIntegerCompare);
};

void testString(){
    char formattedString[] = "It's all about the %d\n";
    char copyString[] = "It's all about the 21\n";
    CopyString(copyString, formattedString);

    assertCompare("Copy String Macro", &copyString, &formattedString, sizeof(copyString));
    assertTrue("Compare Sring Macro", CompareString(formattedString, copyString) == 0);
};

// Main
int main() {
    testConstants();
    testOperators();
    testMacros();

    return EXIT_SUCCESS;
}