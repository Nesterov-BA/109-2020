/**
    ** 7. Для заданного каталога и его подкаталогов найти все файлы, 
	**    имеющие заданное расширение, и составить их список с полными путями.
	**
    ** Параметры:
    **   int argc: количество аргументов командной строки.
    **   char *argv[]: массив аргументов командной строки.
    **   
    ** Количество аргументов командной стороки может быть равно 2 или 3. 
	** В случае трех аргументов: 
	** 		- в первом указывается имя исполяемого файла;
	**		- во втором - имя директории, в которой будет происходить поиск;
	**		- в третьем - тип файла, который нужно найти.
	** В случае двух аргументов указывается только имя исполяемого файла и  тип файла, 
	**      который нужно найти. Поиск будет происходить в текущей дикертории.
	**
	** Если количество аргументов командной строки не равно 2 или 3, то выводятся правила использования программы.
	**
	** В результате работы программы на стандартный поток вывода будет напечатан список всех файлов,
	**      имеющих заданное расширение с полными путями.
	** Если в результате работы программы на стандартный поток вывода ничего не будет напечатано, 
	**      то это означает, что файлов с заданным расширением в указанном каталоге нет.
	** 
    ** Метод:
    **   для обхода дерева файлов, используется функция ftw из библиотеки <ftw.h>.
*/



#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static const char *type;

/**
	** "callback function" check - функция, вызымаемая для каждого элемента дерева файлов.
	**
	** Параметры:
	**     const char *fpath: полное имя элемента в виде, или пути относительно рабочего каталога вызывающего процесса на момент вызова ftw().
	**     const struct stat *sb: здесь задаётся указатель на структуру stat, возвращаемую вызовом stat(2) для fpath.
	**     int tflag: целое число, которое показывает тип fpath. 
	**
	** Для обычного файла, при условии соответствия его типа заданному, на стандартный поток вывода печатается путь до этого файла.
	**
	** Метод:
	**     для проверки на соответствие типов используется функция strstr из библиотеки <string.h>. 
*/


static int check(const char *fpath, const struct stat *sb, int tflag) {
    if (tflag == FTW_F) {
        if(strstr(fpath, type)) {
            printf("%s\n", fpath);
        }
    }
    return 0;         
}

int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 3) {
        printf("set the directory to processed in the second command line arguments\nand type of files to find in third");
        printf("Or u can set only type of files to find\n");
    } else if (argc == 2) {
        type = argv[1];
        ftw(".", check, 20);
    } else if (argc == 3) {
        type = argv[2];
        ftw(argv[1], check, 20);
    }
    return 0;
}
