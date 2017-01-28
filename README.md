# AphroCite
C Standard Library Wrapper and Unit Test Tool

Currently only supports Ansi C http://www.csse.uwa.edu.au/programming/ansic-library.html

# Table of Contents
* [Syntax Beautify](#syntax-beautify)
  * [Constants](#constants)
  * [Operators](#operators)
  * [Macros](#macros)
    * [Memory](#memory)
    * [Console](#console)
    * [CString](#cstring)
* [Unit Testing Suite](#unit-testing-suite)
  * [Asserts](#asserts)

# Syntax Beautify

## Constants
* TRUE
* FALSE

## Operators
* OR
* AND
* NOT

## Macros

### Memory
* Memory_Allocate
* Memory_Free
* Memory_Compare

### Console
* Console_Print_NextLine()
* Console_Print_CString(cString)
* Console_Print_CString_Line(cString)
* Console_Print_CString_Format(format, ...)
* Console_Print_CString_Format_Line(format, ...)
* Console_Read_Line(cString)

### CString
* CString
* CString_Format(formatResult, toFormat, ...)
* CString_Copy
* CString_Compare
* CString_Create_Format(int size, CString format, ...)

# Unit Testing Suite

## Asserts
* Assert_True(CString description, Boolean32 condition)
* Assert_Compare(CString description, void* actual, void* desired, int size)
