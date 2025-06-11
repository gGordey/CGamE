#include "matrix.h"

#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

mat _mat_init_matrix(int linear_size) {
    mat m;
    m.linear_size = linear_size;
    m.data = (float*)malloc(sizeof(float)*linear_size*linear_size);
    return m;
}
void _mat_free_matrix(mat *mat) {
    free(mat->data);
}

float* _mat_index_data(mat *mat, int x, int y) {
    return mat->data+(y*mat->linear_size)+x;
}
float* _mat4_index_data(mat4x4 *mat, int x, int y) {
    return (*mat)+(y*4)+x;
}
float* _mat2_index_data(mat2x2 *mat, int x, int y) {
    return (*mat)+(y*2)+x;
}

void _mat4_mult_mat(mat4x4* _restrict m1, mat4x4* _restrict m2, mat4x4 *buf) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += (*_mat4_index_data(m1, i, k)) * (*_mat4_index_data(m2, k, j));
            }
            *_mat4_index_data(buf, i, j) = sum;
        }
    }
}
void _mat2_mult_mat(mat2x2* _restrict m1, mat2x2* _restrict m2, mat2x2 *buf) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < 2; ++k) {
                sum += (*_mat2_index_data(m1, i, k)) * (*_mat2_index_data(m2, k, j));
            }
            *_mat2_index_data(buf, i, j) = sum;
        }
    }
}