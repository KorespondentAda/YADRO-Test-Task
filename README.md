# English
## Task
Have CSV-file with header and every string numbered with positive integer.
Table cells can hold integer number or expressions like:
```
=ARG1#ARG2
```
, where `#` — one of ariphmetic operator `[+-*/]`; `ARG1` and `ARG2` — integer arguments or addresses formed like `NAME###`, where `NAME` --- column name, `###` — row number.

Program must read given CSV file, calculate found expressions and print resulting table.

## Assumptions
As original task does not give full and unambiguous desription, various assumptions will be standed:
- Invalid input data processing must end with error message without partially processed table;
- Program cancel with exception is not acceptable;
- Input CSV file must not be empty - empty file is invalid;
- Field (column) number in every row must be constant - field number less or more than expected is input error;
- Columns and rows order must be saved;
- Encodings not checked, must work for ASCII;
- As input cells must be integer values or expressions, expression results then must be also integers, so using integer ariphmetics;
- Big numbers does not used, `int` type must be enough - overflow checks used for that type;
- Column headers can't contain numbers and operation symbols - expression must be unambiguous

## Build
Solution can be built by CMake in standart way:
1. Create configure and build directory and `cd` to it;
2. Configure project with `cmake` and root `CMakeLists.txt` file;
3. Build configured project by `cmake` or `make`.

Example of commands to execute:
1. `mkdir build && cd build`
2. `cmake ..`
3. `cmake --build .`

As a result in build directory shows up ready to use executable file `csvreader`.

## Launch
Compiled executable can be then executed with input CSV file name as command-line argument:
```sh
$ csvreader file.csv
```
Program will print file processing result in standart output, and print occured runtime errors to standart error.


# Русский
## Задание
Задан CSV-файл с заголовком и строками, пронумерованными целыми положительными числами.
В ячейках файла могут храниться целые числа либо выражения вида:
```
=ARG1#ARG2
```
`#` — один из арифметических операторов `[+-*/]`; `ARG1` и `ARG2` — целые числа или адреса вида `NAME###`, где `NAME` — имя колонки, `###` — номер строки.

Необходимо вывести аналогичную таблицу, в которой выражения будут заменены на результаты их вычисления.

## Предположения
Так как исходная постановка задачи и представленный пример не предполагают однозначного и конкретного понимания всех аспектов требуемого решения, был выставлен ряд предположений, исходя из которых и составлялось решение:
- Неверные входные данные должны вести к завершению программы с выводом ошибки - пытаться обработать данные частично не нужно;
- Падение программы из-за исключения не является приемлемым поведением - нужно вывести сообщение об ошибке, корректно завершиться и вернуть неуспешный код завершения;
- Входной CSV-файл не должен быть пустым - такие входные данные считаются ошибочными;
- Число полей в каждой строке должно быть постоянным - лишние или недостающие поля означают ошибочность входных данных;
- Порядок столбцов и строк должен остаться прежним;
- Решение не обязано учитывать кодировки - проверяется только для ASCII;
- Так как во входных данный ячейки могут содержать лишь целые числа, то и результат выполнения выражений, включая деление, должен быть целым числом - так что деление используется целочисленное;
- Не используются слишком большие числа, типа `int` должно быть достаточно - проверки на переполнение выполняются именно для размерности типа `int`;
- Заголовки столбцов не должны содержать используемых операторов и чисел - иначе выражение может быть неоднозначным;

## Сборка
Решение предполагает сборку посредством CMake стандартным образом:
1. Создать директорию для конфигурации и сборки, и перейти в неё;
2. Сконфигурировать проект с помощью `cmake` и корневого файла `CMakeLists.txt`;
3. Собрать сконфигурированный проект при помощи `cmake` или `make`.

Пример необходимых команд, выполняемых из корня проекта:
1. `mkdir build && cd build`
2. `cmake ..`
3. `cmake --build .`

В результате в директории сборки появится исполняемый файл `csvreader`, готовый к использованию.

## Запуск
Собранный исполняемый файл может быть запущен с передачей ему в качестве единственного и обязательного аргумента имени CSV-файла:
```sh
$ csvreader file.csv
```
В результате программа выведет в стандартный вывод результат обработки файла, а в стандартный вывод ошибок выведет информацию о возникших ошибках работы, при их наличии.

