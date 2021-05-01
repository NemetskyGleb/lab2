#include <iostream>
#include <string>
#include "codegenerator.h"

int main()
{
    ICodeFactory* icd = new CSharpCodeFactory();
    CodeGenerator* cd = new CodeGenerator(icd);
    std::cout << cd->generateProgram() << std::endl;
    delete icd;
    delete cd;
    return 0;
}
