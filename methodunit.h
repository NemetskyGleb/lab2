#ifndef METHODUNIT_H
#define METHODUNIT_H
#include <memory>
#include <string>
#include <vector>
#include "unit.h"

class MethodUnit : public Unit
{
public:
    using Flags = unsigned int;
    virtual void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) = 0;
    virtual std::string compile(unsigned int level = 0) const = 0;
    virtual ~MethodUnit() = default;
};

class CPPMethodUnit : public MethodUnit
{
private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector<std::shared_ptr<Unit> > m_body;
public:
    enum Modifier {
        STATIC  = 1,
        CONST   = 1 << 1,
        VIRTUAL = 1 << 2
    };
public:
    /**
     * @brief Конструктор класса MethodUnit принимает
     * имя функции, тип возвращаемого значения и флаги
     * @param name
     * @param returnType
     * @param flags
     */
    CPPMethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
            m_name(name), m_returnType(returnType), m_flags(flags) { }
    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result = generateShift(level);
        if (m_flags & STATIC) {
            result += "static ";
        } else if (m_flags & VIRTUAL) {
            result += "virtual ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        if (m_flags & CONST) {
            result += " const";
        }
        result += " {\n";
        for (const auto& b : m_body) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};

class CSharpMethodUnit : public MethodUnit
{
private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector<std::shared_ptr<Unit> > m_body;
public:
    enum Modifier {
        STATIC   = 1,
        VIRTUAL  = 1 << 1,
        OVERRIDE = 1 << 2,
        SEALED   = 1 << 3,
        ABSTRACT = 1 << 4
    };
public:
    /**
     * @brief Конструктор класса MethodUnit принимает
     * имя функции, тип возвращаемого значения и флаги
     * @param name
     * @param returnType
     * @param flags
     */
    CSharpMethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
            m_name(name), m_returnType(returnType), m_flags(flags) { }
    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result;
        if (m_flags & STATIC) {
            result += "static ";
        } 
        else if (m_flags & VIRTUAL) {
            result += "virtual ";
        }
        else if (m_flags & ABSTRACT) {
            result += "abstract ";
        }
        if (m_flags & OVERRIDE) {
            result += "override ";
        }
        else if (m_flags & SEALED) {
            result += "sealed ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        result += " {\n";
        for (const auto& b : m_body) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};


class JavaMethodUnit : public MethodUnit
{
private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector<std::shared_ptr<Unit> > m_body;
public:
    enum Modifier {
        STATIC   = 1,
        ABSTRACT = 1 << 1,
        FINAL    = 1 << 2
    };
public:
    /**
     * @brief Конструктор класса MethodUnit принимает
     * имя функции, тип возвращаемого значения и флаги
     * @param name
     * @param returnType
     * @param flags
     */
    JavaMethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
            m_name(name), m_returnType(returnType), m_flags(flags) { }
    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) {
        m_body.push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result;
        if (m_flags & STATIC) {
            result += "static ";
        }
        if (m_flags & ABSTRACT) {
            result += "abstract ";
        }
        if (m_flags & FINAL) {
            result += "final ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        result += " {\n";
        for (const auto& b : m_body) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};

#endif // METHODUNIT_H
