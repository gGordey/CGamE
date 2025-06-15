#ifndef _C_MATRIX
#define _C_MATRIX

#ifdef __cplusplus 
    #define _restrict
#else
    #define _restrict restrict
#endif

typedef float mat4x4[16];
typedef float mat2x2[4];
typedef struct mat {
    int size_x;
    int size_y;
    float *data;
} mat;

mat _mat_init_matrix(int linear_size_x, int linear_size_y) ;

void _mat_free_matrix(mat *mat);

float* _mat_index_data(mat *mat, int x, int y);
float* _mat4_index_data(mat4x4 *mat, int x, int y);
float* _mat2_index_data(mat2x2 *mat, int x, int y);

void _mat4_mult(mat4x4* _restrict m1, mat4x4* _restrict m2, mat4x4 *buf);
void _mat2_mult(mat2x2* _restrict m1, mat2x2* _restrict m2, mat2x2 *buf);
mat _mat_mult(mat* _restrict m1, mat* _restrict m2);

void _mat4_mult_vec(mat4x4* m,
    float x, float y, float z, float w, 
    float *destX, float *destY, float *destZ, float *destW
);
void _mat2_mult_vec(mat2x2* m,
    float x, float y,
    float *destX, float *destY
);

#endif//_C_MATRIX