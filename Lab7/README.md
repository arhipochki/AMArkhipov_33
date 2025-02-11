Седьмая лабораторная работа.
===============================

## Вариант 4

В рамках задачи требуется написать программу, которая будет анализировать текст произведений.

Библиотека:
- Библиотека содержит набор книг.
- Каталог содержит не более 30 книг.


Книга:
- Каждая книга имеет наименование, объем, возрастные ограничения, оценки от читателей.
- Книги разделяются на жанры, например: Детектив, Любовный роман, Фентези, Фантастика. 
- Книга может быть прочитана посетителем и оценена. Оценка сохраняется в список оценок.
- Книга содержит автора.

Посетитель:
- Посетитель имеет определенный возраст, что не дает ему брать книги не подходящие под ограничения.
- Посетитель может иметь предпочтения по объему книги (большая > 500, маленькая < 100, средняя) и по жанру.
- Предпочтения по объему и жанру могут меняться от запроса к запросу.
- Посетители читают с не одинаковой скоростью.
- Посетители не читают одну и ту же книгу дважды.


1) Реализовать класс Библиотека, Книга, Посетитель.
2) Реализовать метод генерации каталога книг разного объема, авторов, жанров и ограничений.
3) Реализовать метод поиска нужной книги по критериям отбора: возраст посетителя, предпочтительный объем, жанр, при этом должна браться первая книга.
4) Реализовать метод чтения книги посетителем. Длительность чтения зависит от объема книги и скорости чтения отдельного посетителя.
5) Реализовать метод запроса посетителем книги из библиотеки и ее прочтения.
6) (Усложненный вариант) Реализовать процесс работы библиотеки на протяжении 30 дней. 
   * Каждый день в библиотеку должны приходить от 1 до 5 посетителей, из набора посетителей, в процессе работы посетители могут появляться.
   * Каждый посетитель обязательно берет одну книгу в момент посещения. Книга выбирается методом подбора нужной книги из 2 пункта.
   * Посетитель не появляется в библиотеки если он занят чтением книги, после чтения книги он ставит ей оценку и возвращает ее до своего следующего посещения.
   * Если время моделирование закончилось, а посетитель не вернул книгу, то процесс чтения завершается и книге ставится оценка.
7) По результатам моделирования требуется вывести статистику:
   1) Количество взятия каждой из книг каталога.
   2) Среднюю арифметическую оценку книги на основании отзывов посетителей.
   3) Среднее арифметическое время чтения книги посетителями.
   4) Количество взятия книг на каждого автора.
