#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "codefactory.h"
#include <string>

class CodeGenerator
{
private:
    ICodeFactory* p;
public:
    CodeGenerator(ICodeFactory* factory) : p(factory) {}
    std::string generateCXXProgram() {
        auto myclass = p->createClassUnit("MyClass");

        auto methodUnit1 = p->createMethodUnit("testFunc1", "void", 0);
        myclass->add(methodUnit1, CPPClassUnit::PUBLIC);

        auto methodUnit2 = p->createMethodUnit("testFunc2", "void", CPPMethodUnit::STATIC);
        myclass->add(methodUnit2, CPPClassUnit::PRIVATE);

        auto methodUnit3 = p->createMethodUnit("testFunc3", "void", CPPMethodUnit::VIRTUAL | CPPMethodUnit::CONST);
        myclass->add(methodUnit3, CPPClassUnit::PUBLIC);

        auto methodUnit4 = p->createMethodUnit("testFunc4", "void", CPPMethodUnit::STATIC);
        auto printUnit = p->createPrintOperatorUnit(R"(Hello, World!\n)");

        methodUnit4->add(printUnit);

        myclass->add(methodUnit4, CPPClassUnit::PROTECTED);

        return myclass->compile();
    }
    std::string generateCSharpProgram() {
        auto myclass = p->createClassUnit("MyClass", CSharpClassUnit::ABSTRACT, CSharpClassUnit::PUBLIC);

        auto methodUnit1 = p->createMethodUnit("testFunc1", "void", 0);
        myclass->add(methodUnit1, CSharpClassUnit::PUBLIC);

        auto methodUnit2 = p->createMethodUnit("testFunc2", "void", CSharpMethodUnit::STATIC);
        myclass->add(methodUnit2, CSharpClassUnit::PRIVATE);

        auto methodUnit3 = p->createMethodUnit("testFunc3", "void", CSharpMethodUnit::VIRTUAL);
        myclass->add(methodUnit3, CSharpClassUnit::PUBLIC);

        auto methodUnit4 = p->createMethodUnit("testFunc4", "void", CSharpMethodUnit::STATIC);
        auto printUnit = p->createPrintOperatorUnit(R"(Hello, World!\n)");

        methodUnit4->add(printUnit);

        myclass->add(methodUnit4, CSharpClassUnit::PROTECTED);

        return myclass->compile();
    }
    std::string generateJavaProgram() {
        auto myclass = p->createClassUnit("MyClass", JavaClassUnit::ABSTRACT, JavaClassUnit::PUBLIC);

        auto methodUnit1 = p->createMethodUnit("testFunc1", "void", 0);
        myclass->add(methodUnit1, JavaClassUnit::PUBLIC);

        auto methodUnit2 = p->createMethodUnit("testFunc2", "void", JavaMethodUnit::STATIC | JavaMethodUnit::ABSTRACT);
        myclass->add(methodUnit2, JavaClassUnit::PRIVATE);

        auto methodUnit3 = p->createMethodUnit("testFunc3", "void", JavaMethodUnit::ABSTRACT);
        myclass->add(methodUnit3, JavaClassUnit::PUBLIC);

        auto methodUnit4 = p->createMethodUnit("testFunc4", "void", JavaMethodUnit::STATIC);
        auto printUnit = p->createPrintOperatorUnit(R"(Hello, World!\n)");

        methodUnit4->add(printUnit);

        myclass->add(methodUnit4, JavaClassUnit::PROTECTED);

        return myclass->compile();
    }
};
#endif // CODEGENERATOR_H
