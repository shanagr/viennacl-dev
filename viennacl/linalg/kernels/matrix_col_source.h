#ifndef VIENNACL_LINALG_KERNELS_MATRIX_COL_SOURCE_HPP_
#define VIENNACL_LINALG_KERNELS_MATRIX_COL_SOURCE_HPP_
//Automatically generated file from auxiliary-directory, do not edit manually!
namespace viennacl
{
 namespace linalg
 {
  namespace kernels
  {
const char * const matrix_col_align1_trans_lower_triangular_substitute_inplace = 
"__kernel void trans_lower_triangular_substitute_inplace(\n"
"          __global const float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector)\n"
"{\n"
"  float temp;\n"
"  for (int row = 0; row < matrix_rows; ++row)\n"
"  {\n"
"    barrier(CLK_GLOBAL_MEM_FENCE);\n"
"    if (get_global_id(0) == 0)\n"
"      vector[row] /= matrix[row+row*matrix_internal_rows];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE);\n"
"    temp = vector[row];\n"
"    for  (int elim = row + get_global_id(0) + 1; elim < matrix_rows; elim += get_global_size(0))\n"
"      vector[elim] -= temp * matrix[elim * matrix_internal_rows + row];\n"
"  }\n"
"}\n"
; //matrix_col_align1_trans_lower_triangular_substitute_inplace

const char * const matrix_col_align1_add = 
"__kernel void add(  // C = A + B\n"
"          __global const float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * B,\n"
"          unsigned int B_row_start,\n"
"          unsigned int B_col_start,\n"
"          unsigned int B_row_inc,\n"
"          unsigned int B_col_inc,\n"
"          unsigned int B_row_size,\n"
"          unsigned int B_col_size,\n"
"          unsigned int B_internal_rows,\n"
"          unsigned int B_internal_cols,\n"
"          __global float * C,\n"
"          unsigned int C_row_start,\n"
"          unsigned int C_col_start,\n"
"          unsigned int C_row_inc,\n"
"          unsigned int C_col_inc,\n"
"          unsigned int C_row_size,\n"
"          unsigned int C_col_size,\n"
"          unsigned int C_internal_rows,\n"
"          unsigned int C_internal_cols) \n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      C[i * C_row_inc + C_row_start + (j* C_col_inc + C_col_start) * C_internal_rows] =\n"
"        A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows]\n"
"        + B[i * B_row_inc + B_row_start + (j * B_col_inc + B_col_start) * B_internal_rows];\n"
"}\n"
; //matrix_col_align1_add

const char * const matrix_col_align1_inplace_sub = 
"__kernel void inplace_sub( // A -= B\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * B,  \n"
"          unsigned int B_row_start,\n"
"          unsigned int B_col_start,\n"
"          unsigned int B_row_inc,\n"
"          unsigned int B_col_inc,\n"
"          unsigned int B_row_size,\n"
"          unsigned int B_col_size,\n"
"          unsigned int B_internal_rows,\n"
"          unsigned int B_internal_cols)\n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] -=\n"
"        B[i * B_row_inc + B_row_start + (j * B_col_inc + B_col_start) * B_internal_rows];\n"
"}\n"
; //matrix_col_align1_inplace_sub

const char * const matrix_col_align1_trans_unit_lower_triangular_substitute_inplace = 
"\n"
"__kernel void trans_unit_lower_triangular_substitute_inplace(\n"
"          __global const float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector)\n"
"{\n"
"  float temp;\n"
"  for (int row = 0; row < matrix_rows; ++row)\n"
"  {\n"
"    barrier(CLK_GLOBAL_MEM_FENCE);\n"
"\n"
"    temp = vector[row];\n"
"\n"
"    for  (int elim = row + get_global_id(0) + 1; elim < matrix_rows; elim += get_global_size(0))\n"
"      vector[elim] -= temp * matrix[elim * matrix_internal_rows + row];\n"
"  }\n"
"}\n"
"\n"
"\n"
; //matrix_col_align1_trans_unit_lower_triangular_substitute_inplace

const char * const matrix_col_align1_vec_mul = 
"__kernel void vec_mul(\n"
"          __global const float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * v,\n"
"          unsigned int v_start,\n"
"          unsigned int v_inc,\n"
"          unsigned int v_size,\n"
"          __global float * result,\n"
"          unsigned int result_start,\n"
"          unsigned int result_inc,\n"
"          unsigned int result_size) \n"
"{ \n"
"  for (unsigned int row = get_global_id(0); row < A_row_size; row += get_global_size(0))\n"
"  {\n"
"    float dot_prod = 0;\n"
"    for (unsigned int col = 0; col < A_col_size; ++col)\n"
"      dot_prod += A[(row * A_row_inc + A_row_start) + (col * A_col_inc + A_col_start) * A_internal_rows] * v[v_start + v_inc * col];\n"
"    result[row * result_inc + result_start] = dot_prod;\n"
"  }\n"
"}\n"
; //matrix_col_align1_vec_mul

const char * const matrix_col_align1_trans_upper_triangular_substitute_inplace = 
"//transposed lower triangular matrix\n"
"__kernel void trans_upper_triangular_substitute_inplace(\n"
"          __global const float * matrix, \n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector) \n"
"{ \n"
"  float temp; \n"
"  for (int row = matrix_rows-1; row > -1; --row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_global_id(0) == 0) \n"
"      vector[row] /= matrix[row + row*matrix_internal_rows]; \n"
" \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = vector[row]; \n"
"    //eliminate column with index 'row' in parallel: \n"
"    for  (int elim = get_global_id(0); elim < row; elim += get_global_size(0)) \n"
"      vector[elim] -= temp * matrix[row + elim * matrix_internal_rows]; \n"
"  } \n"
"   \n"
"}\n"
; //matrix_col_align1_trans_upper_triangular_substitute_inplace

const char * const matrix_col_align1_lower_triangular_substitute_inplace = 
"__kernel void lower_triangular_substitute_inplace(\n"
"          __global const float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector)\n"
"{\n"
"  float temp;\n"
"  for (int row = 0; row < matrix_rows; ++row)\n"
"  {\n"
"    barrier(CLK_GLOBAL_MEM_FENCE);\n"
"    if (get_global_id(0) == 0)\n"
"      vector[row] /= matrix[row+row*matrix_internal_rows];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE);\n"
"    temp = vector[row];\n"
"    for  (int elim = row + get_global_id(0) + 1; elim < matrix_rows; elim += get_global_size(0))\n"
"      vector[elim] -= temp * matrix[row * matrix_internal_rows + elim];\n"
"  }\n"
"}\n"
; //matrix_col_align1_lower_triangular_substitute_inplace

const char * const matrix_col_align1_fft_radix2 = 
"__kernel void fft_radix2(__global float2* input,\n"
"                         unsigned int s,\n"
"                         unsigned int bit_size,\n"
"                         unsigned int size,\n"
"                         unsigned int stride,\n"
"                         unsigned int batch_num,\n"
"                         float sign) {\n"
"    unsigned int ss = 1 << s;\n"
"    unsigned int half_size = size >> 1;\n"
"    float cs, sn;\n"
"    const float NUM_PI = 3.14159265358979323846;\n"
"    unsigned int glb_id = get_global_id(0);\n"
"    unsigned int glb_sz = get_global_size(0);\n"
"	\n"
"    for(unsigned int batch_id = 0; batch_id < batch_num; batch_id++) {\n"
"        for(unsigned int tid = glb_id; tid < half_size; tid += glb_sz) {\n"
"            unsigned int group = (tid & (ss - 1));\n"
"            unsigned int pos = ((tid >> s) << (s + 1)) + group;\n"
"            unsigned int offset = pos * stride + batch_id;\n"
"            float2 in1 = input[offset];//index\n"
"            float2 in2 = input[offset + ss * stride];//index\n"
"            float arg = group * sign * NUM_PI / ss;\n"
"            sn = sincos(arg, &cs);\n"
"            float2 ex = (float2)(cs, sn);\n"
"            float2 tmp = (float2)(in2.x * ex.x - in2.y * ex.y, in2.x * ex.y + in2.y * ex.x);\n"
"            input[offset + ss * stride] = in1 - tmp;//index\n"
"            input[offset] = in1 + tmp;//index\n"
"        }\n"
"    }\n"
"}\n"
; //matrix_col_align1_fft_radix2

const char * const matrix_col_align1_inplace_divide = 
"__kernel void inplace_divide( // A /= const\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * fac) //note: CPU variant is mapped to prod_scalar\n"
"{ \n"
"  float factor = *fac;\n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] /= factor;\n"
"}\n"
; //matrix_col_align1_inplace_divide

const char * const matrix_col_align1_fft_reorder = 
"/*\n"
"* Performs reordering of input data in bit-reversal order\n"
"* Probably it's better to do in host side,\n"
"*/\n"
"unsigned int get_reorder_num_2(unsigned int v, unsigned int bit_size) {\n"
"    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);\n"
"    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);\n"
"    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);\n"
"    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);\n"
"    v = (v >> 16) | (v << 16);\n"
"    v = v >> (32 - bit_size);\n"
"    return v;\n"
"}\n"
"__kernel void fft_reorder(__global float2* input,\n"
"                          unsigned int bit_size,\n"
"                          unsigned int size,\n"
"                          unsigned int stride,\n"
"                          int batch_num) {\n"
"    unsigned int glb_id = get_global_id(0);\n"
"    unsigned int glb_sz = get_global_size(0);\n"
"	\n"
"    for(unsigned int batch_id = 0; batch_id < batch_num; batch_id++) {\n"
"        for(unsigned int i = glb_id; i < size; i += glb_sz) {\n"
"            unsigned int v = get_reorder_num_2(i, bit_size);\n"
"            if(i < v) {\n"
"                float2 tmp = input[i * stride + batch_id]; // index\n"
"                input[i * stride + batch_id] = input[v * stride + batch_id]; //index\n"
"                input[v * stride + batch_id] = tmp; //index\n"
"            }\n"
"        }\n"
"    }\n"
"}\n"
; //matrix_col_align1_fft_reorder

const char * const matrix_col_align1_lu_factorize = 
"__kernel void lu_factorize(\n"
"          __global float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols) \n"
"{ \n"
"  float temp;\n"
"  for (unsigned int i=1; i<matrix_rows; ++i)\n"
"  {\n"
"    for (unsigned int k=0; k<i; ++k)\n"
"    {\n"
"      if (get_global_id(0) == 0)\n"
"        matrix[i + k*matrix_internal_rows] /= matrix[k + k*matrix_internal_rows];\n"
"      barrier(CLK_GLOBAL_MEM_FENCE);\n"
"      temp = matrix[i + k*matrix_internal_rows];\n"
"      \n"
"      //parallel subtraction:\n"
"      for (unsigned int j=k+1 + get_global_id(0); j<matrix_cols; j += get_global_size(0))\n"
"        matrix[i + j*matrix_internal_rows] -= temp * matrix[k + j*matrix_internal_rows];\n"
"    }\n"
"  }\n"
"} \n"
; //matrix_col_align1_lu_factorize

const char * const matrix_col_align1_clear = 
"__kernel void clear( // A <- 0\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols) \n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] = 0;\n"
"}\n"
; //matrix_col_align1_clear

const char * const matrix_col_align1_fft_direct = 
"// Direct FFT computation (quadratic complexity - use for reference only)\n"
"__kernel void fft_direct(__global float2* input,\n"
"                         __global float2* output,\n"
"                         unsigned int size,\n"
"                         unsigned int stride,\n"
"                         unsigned int batch_num,\n"
"                         float sign) {\n"
"                         \n"
"    const float NUM_PI = 3.14159265358979323846;\n"
"    \n"
"    for(unsigned int batch_id = 0; batch_id < batch_num; batch_id++) {\n"
"        for(unsigned int k = get_global_id(0); k < size; k += get_global_size(0)) {\n"
"            float2 f = 0.0f;\n"
"            for(unsigned int n = 0; n < size; n++) {\n"
"                float2 in = input[n * stride + batch_id]; //input index here\n"
"                float sn, cs;\n"
"                float arg = sign * 2 * NUM_PI * k / size * n;\n"
"                sn = sincos(arg, &cs);\n"
"                float2 ex = (float2)(cs, sn);\n"
"                f = f + (float2)(in.x * ex.x - in.y * ex.y, in.x * ex.y + in.y * ex.x);\n"
"            }\n"
"            output[k * stride + batch_id] = f;// output index here\n"
"        }\n"
"    }\n"
"}\n"
; //matrix_col_align1_fft_direct

const char * const matrix_col_align1_upper_triangular_substitute_inplace = 
"__kernel void upper_triangular_substitute_inplace( \n"
"          __global const float * matrix, \n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector) \n"
"{ \n"
"  float temp; \n"
"  for (int row = matrix_rows-1; row > -1; --row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_global_id(0) == 0) \n"
"      vector[row] /= matrix[row + row*matrix_internal_rows]; \n"
" \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = vector[row]; \n"
"    //eliminate column with index 'row' in parallel: \n"
"    for  (int elim = get_global_id(0); elim < row; elim += get_global_size(0)) \n"
"      vector[elim] -= temp * matrix[elim + row  * matrix_internal_rows]; \n"
"  } \n"
"   \n"
"}\n"
; //matrix_col_align1_upper_triangular_substitute_inplace

const char * const matrix_col_align1_unit_lower_triangular_substitute_inplace = 
"__kernel void unit_lower_triangular_substitute_inplace(\n"
"          __global const float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector)\n"
"{\n"
"  float temp;\n"
"  for (int row = 0; row < matrix_rows; ++row)\n"
"  {\n"
"    barrier(CLK_GLOBAL_MEM_FENCE);\n"
"    temp = vector[row];\n"
"    for  (int elim = row + get_global_id(0) + 1; elim < matrix_rows; elim += get_global_size(0))\n"
"      vector[elim] -= temp * matrix[row * matrix_internal_rows + elim];\n"
"  }\n"
"}\n"
; //matrix_col_align1_unit_lower_triangular_substitute_inplace

const char * const matrix_col_align1_rank1_update = 
"//perform a rank-1 update of the matrix, i.e. A += x * x^T\n"
"__kernel void rank1_update(\n"
"          __global float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global const float * vector1,  \n"
"          __global const float * vector2) \n"
"{ \n"
"  float tmp;\n"
"  for (unsigned int row= get_global_id(0); row < matrix_rows; row += get_global_size(0))\n"
"  {\n"
"    tmp = vector1[row];\n"
"    for (unsigned int col = 0; col < matrix_cols; ++col)\n"
"      matrix[row + col * matrix_internal_rows] += tmp * vector2[col];\n"
"  }\n"
"}\n"
; //matrix_col_align1_rank1_update

const char * const matrix_col_align1_unit_upper_triangular_substitute_inplace = 
"__kernel void unit_upper_triangular_substitute_inplace( \n"
"          __global const float * matrix, \n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector) \n"
"{ \n"
"  float temp; \n"
"  for (int row = matrix_rows-1; row > -1; --row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    \n"
"    temp = vector[row]; \n"
"    //eliminate column with index 'row' in parallel: \n"
"    for  (int elim = get_global_id(0); elim < row; elim += get_global_size(0)) \n"
"      vector[elim] -= temp * matrix[elim + row  * matrix_internal_rows]; \n"
"  } \n"
"   \n"
"}\n"
; //matrix_col_align1_unit_upper_triangular_substitute_inplace

const char * const matrix_col_align1_cpu_inplace_mult = 
"__kernel void cpu_inplace_mult( // A *= const\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          float factor) \n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] *= factor;\n"
"}\n"
; //matrix_col_align1_cpu_inplace_mult

const char * const matrix_col_align1_sub = 
"__kernel void sub(  // C = A - B\n"
"          __global const float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * B,\n"
"          unsigned int B_row_start,\n"
"          unsigned int B_col_start,\n"
"          unsigned int B_row_inc,\n"
"          unsigned int B_col_inc,\n"
"          unsigned int B_row_size,\n"
"          unsigned int B_col_size,\n"
"          unsigned int B_internal_rows,\n"
"          unsigned int B_internal_cols,\n"
"          __global float * C,\n"
"          unsigned int C_row_start,\n"
"          unsigned int C_col_start,\n"
"          unsigned int C_row_inc,\n"
"          unsigned int C_col_inc,\n"
"          unsigned int C_row_size,\n"
"          unsigned int C_col_size,\n"
"          unsigned int C_internal_rows,\n"
"          unsigned int C_internal_cols) \n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      C[i * C_row_inc + C_row_start + (j * C_col_inc + C_col_start) * C_internal_rows] =\n"
"        A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows]\n"
"         - B[i * B_row_inc + B_row_start + (j * B_col_inc + B_col_start) * B_internal_rows];\n"
"}\n"
; //matrix_col_align1_sub

const char * const matrix_col_align1_trans_unit_upper_triangular_substitute_inplace = 
"//transposed lower triangular matrix\n"
"__kernel void trans_unit_upper_triangular_substitute_inplace(\n"
"          __global const float * matrix, \n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          __global float * vector) \n"
"{ \n"
"  float temp; \n"
"  for (int row = matrix_rows-1; row > -1; --row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    \n"
"    temp = vector[row]; \n"
"    //eliminate column with index 'row' in parallel: \n"
"    for  (int elim = get_global_id(0); elim < row; elim += get_global_size(0)) \n"
"      vector[elim] -= temp * matrix[row + elim  * matrix_internal_rows]; \n"
"  } \n"
"   \n"
"}\n"
; //matrix_col_align1_trans_unit_upper_triangular_substitute_inplace

const char * const matrix_col_align1_inplace_mult = 
"__kernel void inplace_mult( // A *= const\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * fac) \n"
"{ \n"
"  float factor = *fac;\n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] *= factor;\n"
"}\n"
; //matrix_col_align1_inplace_mult

const char * const matrix_col_align1_scaled_rank1_update = 
"__kernel void scaled_rank1_update(\n"
"          __global float * matrix,\n"
"          unsigned int matrix_rows,\n"
"          unsigned int matrix_cols,\n"
"          unsigned int matrix_internal_rows,\n"
"          unsigned int matrix_internal_cols,\n"
"          float val,\n"
"          __global const float * vector1,  \n"
"          __global const float * vector2) \n"
"{ \n"
"  float tmp;\n"
"  for (unsigned int row = get_global_id(0); row < matrix_rows; row += get_global_size(0))\n"
"  {\n"
"    tmp = val * vector1[row];\n"
"    for (unsigned int col = 0; col < matrix_cols; ++col)\n"
"      matrix[row + col*matrix_internal_rows] += tmp * vector2[col];\n"
"  }\n"
"}\n"
; //matrix_col_align1_scaled_rank1_update

const char * const matrix_col_align1_trans_vec_mul = 
"__kernel void trans_vec_mul(\n"
"          __global const float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * v,\n"
"          unsigned int v_start,\n"
"          unsigned int v_inc,\n"
"          unsigned int v_size,\n"
"          __global float * result,\n"
"          unsigned int result_start,\n"
"          unsigned int result_inc,\n"
"          unsigned int result_size) \n"
"{ \n"
"  for (unsigned int row = get_global_id(0); row < A_col_size; row += get_global_size(0))\n"
"  {\n"
"    float dot_prod = 0;\n"
"    for (unsigned int col = 0; col < A_row_size; ++col)\n"
"      dot_prod += A[(row * A_col_inc + A_col_start) * A_internal_rows + col * A_row_inc + A_row_start] * v[v_start + col * v_inc];\n"
"    result[row * result_inc + result_start] = dot_prod;\n"
"  }\n"
"}\n"
; //matrix_col_align1_trans_vec_mul

const char * const matrix_col_align1_inplace_add = 
"__kernel void inplace_add( // A += B\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * B,  \n"
"          unsigned int B_row_start,\n"
"          unsigned int B_col_start,\n"
"          unsigned int B_row_inc,\n"
"          unsigned int B_col_inc,\n"
"          unsigned int B_row_size,\n"
"          unsigned int B_col_size,\n"
"          unsigned int B_internal_rows,\n"
"          unsigned int B_internal_cols)\n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] +=\n"
"        B[i * B_row_inc + B_row_start + (j * B_col_inc + B_col_start) * B_internal_rows];\n"
"}\n"
; //matrix_col_align1_inplace_add

const char * const matrix_col_align1_assign = 
"__kernel void assign( // A <- B\n"
"          __global float * A,\n"
"          unsigned int A_row_start,\n"
"          unsigned int A_col_start,\n"
"          unsigned int A_row_inc,\n"
"          unsigned int A_col_inc,\n"
"          unsigned int A_row_size,\n"
"          unsigned int A_col_size,\n"
"          unsigned int A_internal_rows,\n"
"          unsigned int A_internal_cols,\n"
"          __global const float * B,  \n"
"          unsigned int B_row_start,\n"
"          unsigned int B_col_start,\n"
"          unsigned int B_row_inc,\n"
"          unsigned int B_col_inc,\n"
"          unsigned int B_row_size,\n"
"          unsigned int B_col_size,\n"
"          unsigned int B_internal_rows,\n"
"          unsigned int B_internal_cols)\n"
"{ \n"
"  for (unsigned int i = get_global_id(0); i < A_row_size; i += get_global_size(0))\n"
"    for (unsigned int j = get_global_id(1); j < A_col_size; j += get_global_size(1))\n"
"      A[i * A_row_inc + A_row_start + (j * A_col_inc + A_col_start) * A_internal_rows] = \n"
"        B[i * B_row_inc + B_row_start + (j * B_col_inc + B_col_start) * B_internal_rows];\n"
"}\n"
; //matrix_col_align1_assign

const char * const matrix_col_align1_fft_radix2_local = 
"unsigned int get_reorder_num(unsigned int v, unsigned int bit_size) {\n"
"    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);\n"
"    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);\n"
"    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);\n"
"    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);\n"
"    v = (v >> 16) | (v << 16);\n"
"    v = v >> (32 - bit_size);\n"
"    return v;\n"
"}\n"
"__kernel void fft_radix2_local(__global float2* input,\n"
"                                __local float2* lcl_input,\n"
"                                unsigned int bit_size,\n"
"                                unsigned int size,\n"
"                                unsigned int stride,\n"
"                                unsigned int batch_num,\n"
"                                float sign) {\n"
"    unsigned int grp_id = get_group_id(0);\n"
"    unsigned int grp_num = get_num_groups(0);\n"
"    unsigned int lcl_sz = get_local_size(0);\n"
"    unsigned int lcl_id = get_local_id(0);\n"
"    const float NUM_PI = 3.14159265358979323846;\n"
"    for(unsigned int batch_id = grp_id; batch_id < batch_num; batch_id += grp_num) {\n"
"        //unsigned int base_offset = stride * batch_id;\n"
"        //copy chunk of global memory to local\n"
"        for(unsigned int p = lcl_id; p < size; p += lcl_sz) {\n"
"            unsigned int v = get_reorder_num(p, bit_size);\n"
"            lcl_input[v] = input[p * stride + batch_id];//index\n"
"        }\n"
"        barrier(CLK_LOCAL_MEM_FENCE);\n"
"        //performs Cooley-Tukey FFT on local array\n"
"        for(unsigned int s = 0; s < bit_size; s++) {\n"
"            unsigned int ss = 1 << s;\n"
"            float cs, sn;\n"
"            for(unsigned int tid = lcl_id; tid < size; tid += lcl_sz) {\n"
"                unsigned int group = (tid & (ss - 1));\n"
"                unsigned int pos = ((tid >> s) << (s + 1)) + group;\n"
"                float2 in1 = lcl_input[pos];\n"
"                float2 in2 = lcl_input[pos + ss];\n"
"                float arg = group * sign * NUM_PI / ss;\n"
"                sn = sincos(arg, &cs);\n"
"                float2 ex = (float2)(cs, sn);\n"
"                float2 tmp = (float2)(in2.x * ex.x - in2.y * ex.y, in2.x * ex.y + in2.y * ex.x);\n"
"                lcl_input[pos + ss] = in1 - tmp;\n"
"                lcl_input[pos] = in1 + tmp;\n"
"            }\n"
"            barrier(CLK_LOCAL_MEM_FENCE);\n"
"        }\n"
"        //copy local array back to global memory\n"
"        for(unsigned int p = lcl_id; p < size; p += lcl_sz) {\n"
"            input[p * stride + batch_id] = lcl_input[p];//index\n"
"        }\n"
"    }\n"
"}\n"
; //matrix_col_align1_fft_radix2_local

  }  //namespace kernels
 }  //namespace linalg
}  //namespace viennacl
#endif
