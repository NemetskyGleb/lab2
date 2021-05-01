#ifndef CLASSUNIT_H
#define CLASSUNIT_H
#include <memory>
#include <vector>
#include <string>
#include "unit.h"


class ClassUnit : public Unit
{
public:
    using Flags = unsigned int;
    virtual void add(const std::shared_ptr<Unit>& unit, Flags flags) = 0;
    virtual std::string compile(unsigned int level = 0) const = 0;
    virtual ~ClassUnit() = default;
};


class CPPClassUnit : public ClassUnit
{
private:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit> >;
    std::vector<Fields> m_fields;
public:
    enum AccessModifier {
        DEFAULT,
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    static const std::vector<std::string> ACCESS_MODIFIERS;
public:
    explicit CPPClassUnit(const std::string name) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }
    void add(const std::shared_ptr<Unit>& unit, Flags flags)
    {
        int accessModifier = PRIVATE;
        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level) + "class " + m_name + " {\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++) {
            if (m_fields[i].empty())
                continue;
            result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto& f : m_fields[i])
                result += f->compile(level + 1);
            result += '\n';
        }
        result += generateShift(level) + "};\n";
        return result;
    }
};

class CSharpClassUnit : public ClassUnit
{
private:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit> >;
    std::vector<Fields> m_fields;
    Flags access_flags;
    Flags m_flags;
    static const std::vector<std::string> ACCESS_MODIFIERS;
public:
    enum AccessModifier {
        DEFAULT,
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAL,
        PROTECTED_PRIVATE,
        PROTECTED_INTERNAL
    };
    enum Modifier {
        STATIC   = 1,
        ABSTRACT = 1 << 1,
        SEALED    = 1 << 2
    };
public:
    explicit CSharpClassUnit(const std::string name, ClassUnit::Flags modifier, ClassUnit::Flags access_modifier) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
        access_flags = access_modifier;
        m_flags = modifier;
    }
    void add(const std::shared_ptr<Unit>& unit, Flags flags)
    {
        int accessModifier = DEFAULT;
        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level);
        switch (access_flags)
        {
            case PUBLIC:
                result += "public ";
                break;
            case PRIVATE:
                result += "private  ";
                break;
            case PROTECTED:
                result += "protected  ";
                break;
            case INTERNAL:
                result += "internal  ";
                break;
        }
        if (m_flags & STATIC)
            result += "static ";
        if (m_flags & ABSTRACT)
            result += "abstract ";
        if (m_flags & SEALED)
            result += "sealed ";
        result += "class " + m_name + " {\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++) {
            if (m_fields[i].empty())
                continue;
            for (const auto& f : m_fields[i]) {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(level + 1);
            }
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};


class JavaClassUnit : public ClassUnit
{
private:
    std::string m_name;
    using Fields = std::vector<std::shared_ptr<Unit> >;
    std::vector<Fields> m_fields;
    Flags access_flags;
    Flags m_flags;
    static const std::vector<std::string> ACCESS_MODIFIERS;
public:
    enum AccessModifier {
        DEFAULT,
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    enum Modifier {
        STATIC   = 1,
        ABSTRACT = 1 << 1,
        FINAL    = 1 << 3
    };
public:
    explicit JavaClassUnit(const std::string name, ClassUnit::Flags modifier, ClassUnit::Flags access_modifier) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
        access_flags = access_modifier;
        m_flags = modifier;
    }
    void add(const std::shared_ptr<Unit>& unit, Flags flags)
    {
        int accessModifier = DEFAULT;
        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const
    {
        std::string result = generateShift(level);
        switch (access_flags)
        {
            case PUBLIC:
                result += "public ";
                break;
            case PRIVATE:
                result += "private ";
                break;
            case PROTECTED:
                result += "protected ";
                break;
        }
        if (m_flags & STATIC)
            result += "static ";
        if (m_flags & ABSTRACT)
            result += "abstract ";
        if (m_flags & FINAL)
            result += "final ";
        result += "class " + m_name + " {\n"; 
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); i++) {
            if (m_fields[i].empty())
                continue;
            for (const auto& f : m_fields[i]) {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(level + 1);
            }
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};


const std::vector<std::string> CPPClassUnit::ACCESS_MODIFIERS = { "", "public",
            "protected", "private" };
            
const std::vector<std::string> CSharpClassUnit::ACCESS_MODIFIERS = { "", "public",
            "protected", "private", "internal", "protected private", "protected internal" };
const std::vector<std::string> JavaClassUnit::ACCESS_MODIFIERS = { "", "public",
            "protected", "private" };


#endif // CLASSUNIT_H
