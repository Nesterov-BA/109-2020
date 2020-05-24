/* 
 * Составление списков файлов, содержащихся в каталоге, и вывод различий 
 * на основе полученной информации
 *
 * Параметры:
 * output: файл, куда будут выведены различия;
 * dir1_name, dir2_name: имена сравниваемых директорий.
 *
 * Функция для каждого каталога поочередно находит файлы, содержащиеся в нем, 
 * но отсутствующие в другом каталоге, и выводит два списка в алфавитном порядке в output.
 * Файлы, находящиеся в разных подкаталогах, но имеющие одинаковые имена, будут отождествляться.
 *
 * Возвращаемое значение: в случае успешного завершения работы - 0, 
 * в случае ошибки - некоторое отрицательное значение.
 *
 * Пример:
 * dir1		dir2
 * a.c		a.c
 * b.c		b.c
 * c.c		c.h
 * in.txt	out.txt
 *
 * В output будет выведено
 * dir1: c.c in.txt
 * dir2: c.h out.txt
 *
 * Метод:
 * Для нахождения отличий между папками заполняются два массива, содержащие все 
 * 'встретившиеся' функции ftw в соответствующих каталогах имена файлов (поэтому для больших
 * директорий может потребоваться значительный расход памяти). Затем массивы сортируются 
 * в лексикографическом порядке и, проходя по каждому из отсортированных массивов, программа 
 * выводит в output не найденные в другом массиве имена.
 */

int find_dir_diff(FILE *output, const char *dir1_name, const char *dir2_name);