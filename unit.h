#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <vector>
#include <memory>


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
#endif // UNIT_H
