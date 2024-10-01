/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H


#include <libcli3/parsing/int.h>
#include <libtask/task3/task3.h>
#include <libcli3/parsing/params.h>
#include <libtask/utils.h>

#define DEFAULT_EPS 1e-6



/**
 * @brief q arg
 * @details первый параметр (вещественное число) задаёт точность сравнения
 * вещественных чисел (эпсилон), оставшиеся три (вещественные числа) являются
 * коэффициентами квадратного уравнения; необходимо вывести в консоль решения
 * этого уравнения при всевозможных уникальных перестановках значений
 * коэффициентов при степенях переменной;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void q_arg_handler(const int token_count, const char** tokens);

/**
 * @brief m arg
 * @details необходимо задать два ненулевых целых числа, после чего определить,
 * кратно ли первое число второму;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void m_arg_handler(const int token_count, const char** tokens);
/**
 * @brief t arg
 * @details первый параметр (вещественное число) задаёт точность сравнения
 * вещественных чисел (эпсилон); необходимо проверить, могут ли оставшиеся три
 * (вещественные числа) параметра являться длинами сторон прямоугольного
 * треугольника.
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void t_arg_handler(const int token_count, const char** tokens);



#endif //HANDLER_H

