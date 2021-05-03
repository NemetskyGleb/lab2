#ifndef PRINTOPERATORUNIT_H
#define PRINTOPERATORUNIT_H
#include <iostream>
#include <memory>
#include <string>
#include "unit.h"



class PrintOperatorUnit : public Unit
{
public:
    std::string compile(unsigned int level = 0) const = 0;
};

class CPPPrintOperatorUnit : public PrintOperatorUnit {
private:
    std::string m_text;
public:
    explicit CPPPrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf( \"" + m_text + "\");\n";
    }
};

class CSharpPrintOperatorUnit : public PrintOperatorUnit {
private:
    std::string m_text;
public:
    explicit CSharpPrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "Console.WriteLine(\"" + m_text + "\");\n";
    }
};

class JavaPrintOperatorUnit : public PrintOperatorUnit {
private:
    std::string m_text;
public:
    explicit JavaPrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "System.out.println(\"" + m_text + "\");\n";
    }
};

#endif // PRINTOPERATORUNIT_H
