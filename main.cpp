#include <iostream>
#include <string>
#include "codegenerator.h"

int main()
{
    ICodeFactory* icd = new CPPCodeFactory();
    CodeGenerator* cd = new CodeGenerator(icd);
    std::cout << cd->generateCXXProgram() << std::endl;
    delete icd;
    delete cd;
    return 0;
}
