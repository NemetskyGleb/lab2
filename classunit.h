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



const std::vector<std::string> CPPClassUnit::ACCESS_MODIFIERS = { "public",
            "protected", "private" };


#endif // CLASSUNIT_H
