/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H

#include <libtask/task9/task9.h>
#include <libcli3/parsing/params.h>

#define TASK9_STATIC_ARRAY_SIZE 15

/**
 * @brief default handler
 * @details  В текстовом файле, путь к которому подаётся как второй аргумент
 * командной строки, находятся числа, записанные в разных системах счисления
 * (в диапазоне [2..36]), при этом информация о конкретной системе счисления
 * для каждого числа утеряна. В файле числа разделены произвольным количеством
 * разделителей (символов пробела, табуляций и переносов строки). Для каждого
 * числа из входного файла программа должна определить минимальное основание
 * системы счисления (в диапазоне [2..36]), в которой представление этого числа
 * корректно, и в выходной файл, путь к которому подаётся третьим аргументом
 * командной строки, построчно выводит: входное число без ведущих нулей,
 * определенное для него минимальное основание системы счисления и представление
 * этого числав системе счисления с основанием 10. Прописные и строчные символы
 * букв латинского алфавита отождествляются.
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void r_arg_handler(const int token_count, const char** tokens);


#endif //HANDLER_H