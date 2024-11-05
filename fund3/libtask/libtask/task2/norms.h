/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#ifndef NORMS_H
#define NORMS_H

#include <libtask/task2/vectors.h>

//! Type for norm function
typedef long double (*norm_func_t)(mvector_handle_t v, void* args);

/**
 * Compute max norm defined by formula \f$ max_j |x_j| \f$
 * @param v vector
 * @param args matrix
 * @return norm or NAN
 */
long double max_norm(mvector_handle_t v, void* args);
/**
 * Compute p-norm defined by formula \f$ (\sum_{j=1}^n |x_j|^p)^{\frac{1}{p}} \f$
 * @param v vector
 * @param args matrix
 * @return norm or NAN
 */
long double p_norm(mvector_handle_t v, void* args);
/**
 * Compute energy norm defined by formula \f$ \sqrt{(Ax, x)} \f$
 * @param v vector
 * @param args matrix
 * @return norm or NAN
 */
long double energy_norm(mvector_handle_t v, void* args);

#endif  //NORMS_H
