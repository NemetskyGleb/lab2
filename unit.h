#ifndef UNIT_H
#define UNIT_H
#include <memory>
#include <vector>

class Unit
{
public:
    using Flags = unsigned int;
    /**
     * @brief Виртуальная функция-член, предназначеная для
     * добавления вложенных элементов(через умный указатель)
     * @param uptr 
     * @param f 
     */
    virtual void add(const std::shared_ptr<Unit>& unit, Flags flags) {
        throw std::runtime_error("Not supported");
    }
    /**
     * @brief Функция генерирует код на C++, соответствующий
     * содержимого элемента
     * @param level указывает на уровень вложенности узла дерева. 
     * Это требуется для корректной расстоновки отступов в начала строк
     * генерируемого кода
     * @return std::string 
     */
    virtual std::string compile(unsigned int level = 0) const = 0;
    virtual ~Unit() = default;
protected:
    /**
     * @brief Вспомогательная функция-член всего
     * лишь возвращает строку, состоящую из
     * нужного числа пробелов. Результат зависит от
     * уровня вложенности
     * @param level уровень вложенности
     * @return std::string 
     */
    virtual std::string generateShift(unsigned int level) const {
        static const auto DEFAULT_SHIFT = "  ";
        std::string result;
        for (unsigned int i = 0; i < level; i++) {
            result += DEFAULT_SHIFT;
        }
        return result;
    }
};

class ClassUnit : public Unit
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
    explicit ClassUnit(const std::string& name) : m_name(name)
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

const std::vector<std::string> ClassUnit::ACCESS_MODIFIERS = { "public",
            "protected", "private" };
            
class MethodUnit : public Unit
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
    MethodUnit(const std::string& name, const std::string& returnType, Flags flags) :
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

class PrintOperatorUnit : public Unit {
private:
    std::string m_text;
public:
    explicit PrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf( \"" + m_text + "\");\n";
    }
};
#endif // UNIT_H