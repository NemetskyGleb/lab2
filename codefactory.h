#ifndef CODEFACTORY_H
#define CODEFACTORY_H
#include "classunit.h"
#include "methodunit.h"
#include "printoperatorunit.h"

class ICodeFactory
{
public:
    virtual std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) = 0;
    virtual std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) = 0;
    virtual ~ICodeFactory() {}
};

class CPPCodeFactory : public ICodeFactory
{
public:
    explicit CPPCodeFactory() {}
    ~CPPCodeFactory() {}
    std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
        return std::make_shared<CPPClassUnit>(name);
    }
    std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
        return std::make_shared<CPPMethodUnit>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
        return std::make_shared<CPPPrintOperatorUnit>(text);
    }
};

class CSharpCodeFactory : public ICodeFactory
{
public:
   explicit CSharpCodeFactory() {}
   ~CSharpCodeFactory() {}
   std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
       return std::make_shared<CSharpClassUnit>(name, modifier, access_modifier);
   }
   std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
       return std::make_shared<CSharpMethodUnit>(name, returnType, flags);
   }
   std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
       return std::make_shared<CSharpPrintOperatorUnit>(text);
   }
};

class JavaCodeFactory : public ICodeFactory
{
public:
   explicit JavaCodeFactory() {}
   ~JavaCodeFactory() {}
   std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
       return std::make_shared<JavaClassUnit>(name, modifier, access_modifier);
   }
   std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
       return std::make_shared<JavaMethodUnit>(name, returnType, flags);
   }
   std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
       return std::make_shared<JavaPrintOperatorUnit>(text);
   }
};


#endif // CODEFACTORY_H
