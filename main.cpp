#include <iostream>
#include <string>
#include "unit.h"


//Пояснение ко второй лабораторной (что именно нужно сделать к контрольной точке):
//1. Изучить паттерн.
//2. Собрать код из лекции, посмотреть, как он работает.
//3. Декомпозировать его (разбить продукцию по разным файлам).
//4. Написать фабрику (не пугайтесь, она крохотная.
//Внимательно посмотрите на функцию generateProgram
//и выделите из неё те части, которые ответственны за создание продукции.
//Это и есть методы фабрики.) и переделать generateProgram таким образом,
//чтобы она использовала эту самую фабрику.



std::string generateProgram() {
    ClassUnit myClass("MyClass");
    myClass.add(std::make_shared<MethodUnit>("testFunc1", "void", 0),
              ClassUnit::PUBLIC);
    myClass.add(std::make_shared<MethodUnit>("testFunc2", "void", 
             MethodUnit::STATIC), ClassUnit::PRIVATE);
    myClass.add(std::make_shared<MethodUnit>("testFunc3", "void", 
             MethodUnit::VIRTUAL | MethodUnit::CONST), ClassUnit::PUBLIC);
    auto method = std::make_shared<MethodUnit>("testFunc4", "void", MethodUnit::STATIC);
    method->add(std::make_shared<PrintOperatorUnit>(R"(Hello, world!\n)"));
    myClass.add(method, ClassUnit::PROTECTED);
    return myClass.compile();
}

int main()
{
    std::cout << generateProgram() << std::endl;
    return 0;
}
