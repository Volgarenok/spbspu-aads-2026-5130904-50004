**Техническое задание курсовой работы**  
ФИО: Иванов Тимур Андреевич

Тема: **"Локальная поисковая система по текстовым документам"**  
Краткое описание темы:  
Разработка системы для индексации и полнотекстового поиска по содержимому загруженных текстовых файлов.
Программа строит внутренний индекс слов,
обрабатывает поисковые запросы и возвращает список файлов,
отсортированный по степени соответствия запросу
***
**Описание**  
* Загрузка текстовых файлов в систему с автоматическим разбором на слова и построением инвертированного индекса
* Приведение предложений к нормальной форме, называемой дальше индексом
* Хранение индекса в Красно-Чёрном дереве, где ключ - обработанное слово, значение - упорядоченный список позиций слова в исходном тексте (т.е. порядоквые номера слова)
* Поиск по запросу: запрос разбивается на слова, для каждого слова извлекается список файлов, результат ранжируется по ```TF-IDF```
* Выводится упорядоченный список файлов с указанием оценки релевантности
* Возможность удаления файла из индекса и просмотра списка загруженных файлов
***
**Список команд**  
1. ```read <index_name> <input_file>```
2. ```write <output_file> <index_name>```
3. ```search <word> <index_name>```
4. ```right_merge <new_index> <index1> <index2>```
5. ```down_merge <new_index> <index1> <index2>```
6. ```intersect <new_index> <index1> <index2>```
7. ```subtract <new_index> <index1> <index2>```
8. ```add <new_index> <index1> <index2> <add_pos>```
9. ```list```
10. ```delete <index_name>```
***
**Описание команд**  
1) ```read <index_name> <input_file>```  
**read** - создаёт новый индекс с именем **index_name** из текстового файла **input_file**. Если индекс с таким именем уже существует, операция перезаписывается.  
**Пример ввода**  
```read doc1_index doc1.txt```  
**Ожидаемый вывод**  
```Index 'doc1_index' created from doc1.txt (345 words)```
2) ```write <output_file> <index_name>```  
**write** - восстанавливает текст по индексу **index_name** и записывает его в **output_file**. Если индекс не существует, выводится ошибка.  
**Пример ввода**  
```write restored_doc.txt doc1_index```  
**Ожидаемый вывод**  
```Text restored from 'doc1_index' and written to restored_doc.txt```
3) ```search <word> <index_name>```  
**search** - находит все позиции указанного слова в индексе **index_name**  
**Пример ввода**  
```search algorithm doc1_index```  
**Ожидаемый вывод**  
```Word 'algorithm' found at positions: 12, 47, 103```  
**Если слово не найдено** -> ```Word 'algorithm' not found in 'doc1_index'```
4) ```right_merge <new_index> <index1> <index2>```  
**right_merge** - создаёт новый индекс **new_index** как результат присоединения **index1** к **index2** через **правую грань**  
**Пример ввода**  
```right_merge merged_index doc1_index doc2_index```  
**Ожидаемый вывод**  
```Index 'merged_index' created from 'dc1_index' and 'doc2_index' (total 800 words)```
5) ```down_merge <new_index> <index1> <index2>```  
**down_merge** - создаёт новый индекс **new_index** как результат присоединения **index1** к **index2** через **нижнюю грань**  
**Пример ввода**  
```down_merge merged_index doc1_index doc2_index```  
**Ожидаемый вывод**  
```Index 'merged_index' created from 'dc1_index' and 'doc2_index' (total 800 words)```
6) ```intersect <new_index> <index1> <index2>```  
**intersect** - создаёт новый индекс **new_index**, содержащий только слова, присутствующие одновременно в **index1** и **index2**. Для каждого такого слова сохраняются позиции из обоих исходных индексов. Такой индекс не предназначен для полной реконструкции текста.  
**Пример ввода**  
```intersect common_index doc1_index doc2_index```  
**Ожидаемый вывод**  
```Index 'common_index' created with 52 common words```
7) ```subtract <new_index> <index1> <index2>```  
**subtract** - создаёт новый индекс **new_index** , включающий слова, которые есть в **index1**, но отсутствуют в **index2**. Позиции берутся только из **index2**  
**Пример ввода**  
```subtract unique_index doc1_index doc2_index```  
**Ожидаемый вывод**  
```Index 'unique_index' created with 120 unique words from 'doc1_index'```
8) ```add <new_index> <index1> <index2> <add_pos>```  
**add** - создаёт новый индекс **new_index**, представляющий из себя **index1** с **index2** вставленным в позицию **add_pos**. Такой индекс не подразумевается к переводу в текст.  
**Пример ввода**  
```add united_index doc1_index doc2_index 48```  
**Ожидаемый вывод**  
```Index 'united_index' created with doc2_index merged into 48 position of doc1_index```
9) ```list```  
**list** - выводит список всех активных индексов с краткой статистикой (количество слов, уникальные слова)  
**Пример ввода**  
```list```  
**Ожидаемый вывод**  
```
Active indexes:
- doc1_index (345 words, 210 unique)
- merged_index (800 words, 450 unique) 
```
10) ```delete <index_name>```  
**delete** - удаляет индекс с указанным именем  
**Пример ввода**  
```delete doc1_index```  
**Ожидаемый вывод**  
```Index 'doc1_index' deleted```