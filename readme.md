## Пояснение к тестам производительности

При реализации простого скользящего среднего использовалось рекурентное соотношение. 
Количество операций в нем никак не зависит от размера скользящего окна. 

Это и подтверждается тестами.

## Сборка

В проекте используется система сборки Cmake. Есть две цели:
* moving_average -- запуск теста производительности
* simple_moving_average_unittests -- запуск юниттестов

## Пример вывода программы

Moving window size: 4
Average executing time: 0.06s.

Moving window size: 8
Average executing time: 0.059s.

Moving window size: 16
Average executing time: 0.059s.

Moving window size: 32
Average executing time: 0.059s.

Moving window size: 64
Average executing time: 0.057s.

Moving window size: 128
Average executing time: 0.056s.