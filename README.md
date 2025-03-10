# Spell Checker Program in C++

## Описание

Это простая программа на C++, которая выполняет проверку орфографии текста. Она считывает текст из файла, проверяет каждое слово на наличие в словаре, и если слово не найдено, предлагает пользователю несколько вариантов действий: игнорировать слово, добавить его в словарь или заменить на похожее слово из словаря.

Программа демонстрирует базовые принципы работы с текстом, словарями и пользовательским вводом в C++.

## Как работает программа

1. **Чтение словаря**:
   - Программа считывает словарь из файла `src/words.txt`. Каждое слово в словаре должно быть разделено символом новой строки (`\n`).
   - Словарь хранится в виде `unordered_set<string>`, что позволяет быстро проверять наличие слов.

2. **Обработка текста**:
   - Программа считывает текст из файла `src/text.txt` и записывает обработанный текст в файл `src/out.txt`.
   - Текст обрабатывается посимвольно. Если символ является буквой, он добавляется к текущему слову. Если символ не является буквой (например, пробел, знак препинания), текущее слово обрабатывается.

3. **Проверка слова**:
   - Для каждого слова программа проверяет, есть ли оно в словаре.
   - Если слово найдено в словаре, оно просто записывается в выходной файл.
   - Если слово не найдено в словаре, программа предлагает пользователю несколько вариантов действий:
     1. **Игнорировать** слово (оставить его как есть).
     2. **Добавить** слово в словарь.
     3. **Заменить** слово на одно из предложенных похожих слов (если такие найдены).

4. **Поиск похожих слов**:
   - Если слово не найдено в словаре, программа пытается найти похожие слова, выполняя следующие операции:
     - **Удаление** одной буквы из слова.
     - **Добавление** одной буквы в слово.
     - **Замена** одной буквы в слове на другую.
   - Все найденные похожие слова, которые есть в словаре, предлагаются пользователю для замены.

5. **Запись результата**:
   - После обработки каждого слова и выбора пользователя, программа записывает результат в выходной файл `src/out.txt`.

## Пример работы программы

- **Входной файл (`src/text.txt`)**:
  ```
  Hello, this is a testt.
  ```

- **Словарь (`src/words.txt`)**:
  ```
  hello
  this
  is
  a
  test
  ```

- **Выходной файл (`src/out.txt`)**:
  ```
  Hello, this is a test.
  ```

  В этом примере программа обнаружит, что слово "testt" отсутствует в словаре, и предложит пользователю заменить его на "test".
