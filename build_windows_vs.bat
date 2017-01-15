call vcvarsall x64

call clean.bat
cl AphroCiteTest.c -o AphroCiteTest /Zi
AphroCiteTest.exe