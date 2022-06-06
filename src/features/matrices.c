#ifndef MATRICES_C
#define MATRICES_C

// Note(julie)2020-07-30:
// Matrix are 1D array of 16 elements. I did not used 2D arrays because I
// did not want to use double pointer to refer to the element inside array.
// I also suspect that it might be slower to access.

// A = [ 0  1  2  3  ]
//     [ 4  5  6  7  ]
//     [ 8  9  10 11 ]
//     [ 12 13 14 15 ]

#include <stdio.h>
#include "raytracer.h" // for the comparison is_equal


void display_matrix4x4(double m[4][4])
{
    printf("Your matrix is:\n");
    for(int row = 0; row < 4; row++)
    {
        printf("| ");
        for(int column = 0; column < 4; column++)
        {
            printf("%f ", m[row][column]);
        }
        printf(" |\n");
    }
}

boolean is_equal_matrices(double *A, double *B)
{
    return is_equal(A[0], B[0])   && is_equal(A[1], B[1])   && is_equal(A[2], B[2])   && is_equal(A[3], B[3])   &&
           is_equal(A[4], B[4])   && is_equal(A[5], B[5])   && is_equal(A[6], B[6])   && is_equal(A[7], B[7])   &&
           is_equal(A[8], B[8])   && is_equal(A[9], B[9])   && is_equal(A[10], B[10]) && is_equal(A[11], B[11]) &&
           is_equal(A[12], B[12]) && is_equal(A[13], B[13]) && is_equal(A[14], B[14]) && is_equal(A[15], B[15]);
}

void display_matrix(double *m)
{
    printf("Your matrix is: | %f, %f, %f, %f |\n", m[0], m[1], m[2], m[3]);
    printf("                | %f, %f, %f, %f |\n", m[4], m[5], m[6], m[7]);
    printf("                | %f, %f, %f, %f |\n", m[8], m[9], m[10], m[11]);
    printf("                | %f, %f, %f, %f |\n", m[12], m[13], m[14], m[15]);
}

void transpose_matrix(double *matrix, double *input)
{
    matrix[0] = input[0];
    matrix[1] = input[4];
    matrix[2] = input[8];
    matrix[3] = input[12];

    matrix[4] = input[1];
    matrix[5] = input[5];
    matrix[6] = input[9];
    matrix[7] = input[13];

    matrix[8] = input[2];
    matrix[9] = input[6];
    matrix[10] = input[10];
    matrix[11] = input[14];

    matrix[12] = input[3];
    matrix[13] = input[7];
    matrix[14] = input[11];
    matrix[15] = input[15];
}

void multiply_matrices(double *output, double *A, double *B)
{
    output[0] =  (A[0] * B[0])  + (A[1] * B[4])  + (A[2] * B[8])  + (A[3] * B[12]);
    output[1] =  (A[0] * B[1])  + (A[1] * B[5])  + (A[2] * B[9])  + (A[3] * B[13]);
    output[2] =  (A[0] * B[2])  + (A[1] * B[6])  + (A[2] * B[10]) + (A[3] * B[14]);
    output[3] =  (A[0] * B[3])  + (A[1] * B[7])  + (A[2] * B[11]) + (A[3] * B[15]);

    output[4] =  (A[4] * B[0])  + (A[5] * B[4])  + (A[6] * B[8])  + (A[7] * B[12]);
    output[5] =  (A[4] * B[1])  + (A[5] * B[5])  + (A[6] * B[9])  + (A[7] * B[13]);
    output[6] =  (A[4] * B[2])  + (A[5] * B[6])  + (A[6] * B[10]) + (A[7] * B[14]);
    output[7] =  (A[4] * B[3])  + (A[5] * B[7])  + (A[6] * B[11]) + (A[7] * B[15]);

    output[8] =  (A[8] * B[0])  + (A[9] * B[4])  + (A[10] * B[8])  + (A[11] * B[12]);
    output[9] =  (A[8] * B[1])  + (A[9] * B[5])  + (A[10] * B[9])  + (A[11] * B[13]);
    output[10] = (A[8] * B[2])  + (A[9] * B[6])  + (A[10] * B[10]) + (A[11] * B[14]);
    output[11] = (A[8] * B[3])  + (A[9] * B[7])  + (A[10] * B[11]) + (A[11] * B[15]);

    output[12] = (A[12] * B[0]) + (A[13] * B[4]) + (A[14] * B[8])  + (A[15] * B[12]);
    output[13] = (A[12] * B[1]) + (A[13] * B[5]) + (A[14] * B[9])  + (A[15] * B[13]);
    output[14] = (A[12] * B[2]) + (A[13] * B[6]) + (A[14] * B[10]) + (A[15] * B[14]);
    output[15] = (A[12] * B[3]) + (A[13] * B[7]) + (A[14] * B[11]) + (A[15] * B[15]);
}

void transform4d(double *output, double *matrix, double x, double y, double z, double w)
{
    // output = Matrix * b
    output[0] = (matrix[0] * x)  + (matrix[1] * y)  + (matrix[2] * z)  + (matrix[3] * w);
    output[1] = (matrix[4] * x)  + (matrix[5] * y)  + (matrix[6] * z)  + (matrix[7] * w);
    output[2] = (matrix[8] * x)  + (matrix[9] * y)  + (matrix[10] * z) + (matrix[11] * w);
    output[3] = (matrix[12] * x) + (matrix[13] * y) + (matrix[14] * z) + (matrix[15] * w);
}

Tuple transform_tuple(double *matrix, Tuple *b)
{
    // output = Matrix * b
    static Tuple output;
    output.x = (matrix[0]  * b->x) + (matrix[1]  * b->y) + (matrix[2]  * b->z) + (matrix[3]  * b->w);
    output.y = (matrix[4]  * b->x) + (matrix[5]  * b->y) + (matrix[6]  * b->z) + (matrix[7]  * b->w);
    output.z = (matrix[8]  * b->x) + (matrix[9]  * b->y) + (matrix[10] * b->z) + (matrix[11] * b->w);
    output.w = (matrix[12] * b->x) + (matrix[13] * b->y) + (matrix[14] * b->z) + (matrix[15] * b->w);
    return output;
}

void identity4d(double *matrix)
{
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = 0;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 1;
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

// double determinant2d(double * m)
// {
//     return (m[0] * m[3]) + (m[1] * m[2]);
// }
// double determinant2d(double * m)
// {
//     return (m[0] * m[3]) + (m[1] * m[2]);
// }
// double * submatrix4d(double * m, int row, int column)
// {
//     double sub[3];
// }
// double cofactor3d(double matrix[], int index)
// {
//     return 0;
// }
// double determinant4d(double matrix[])
// {
//     double det = 0;
//     display_matrix(matrix);



//     det = (matrix[0] * cofactor3d(matrix, 0)) +
//             (matrix[1] * cofactor3d(matrix, 1)) +
//             (matrix[2] * cofactor3d(matrix, 2)) +
//             (matrix[3] * cofactor3d(matrix, 3));
//     return det;
// }



double getCofactor(double m0, double m1, double m2,
                double m3, double m4, double m5,
                double m6, double m7, double m8)
{
	return m0 * (m4 * m8 - m5 * m7) -
		   m1 * (m3 * m8 - m5 * m6) +
		   m2 * (m3 * m7 - m4 * m6);
}
void invert_matrix_4x4(double * output, double * m)
{
	// double output[16];

    // get cofactors of minor matrices
	double cofactor0 = getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
	double cofactor1 = getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
	double cofactor2 = getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
	double cofactor3 = getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);

	// get determinant
	double determinant = m[0] * cofactor0 - m[1] * cofactor1 + m[2] * cofactor2 - m[3] * cofactor3;
	if(fabs(determinant) <= EPSILON)
	{
		// returns identity
        identity4d(output);
	}

	// get rest of cofactors for adj(M)
	double cofactor4 = getCofactor(m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]);
	double cofactor5 = getCofactor(m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]);
	double cofactor6 = getCofactor(m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]);
	double cofactor7 = getCofactor(m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]);

	double cofactor8 = getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]);
	double cofactor9 = getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]);
	double cofactor10 = getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]);
	double cofactor11 = getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]);

	double cofactor12 = getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]);
	double cofactor13 = getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]);
	double cofactor14 = getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]);
	double cofactor15 = getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);

	// build inverse matrix = adj(M) / det(M)
	// adjugate of M is the transpose of the cofactor matrix of M
	double invDeterminant = 1.0f / determinant;
	output[0] = invDeterminant * cofactor0;
	output[1] = -invDeterminant * cofactor4;
	output[2] = invDeterminant * cofactor8;
	output[3] = -invDeterminant * cofactor12;

	output[4] = -invDeterminant * cofactor1;
	output[5] = invDeterminant * cofactor5;
	output[6] = -invDeterminant * cofactor9;
	output[7] = invDeterminant * cofactor13;

	output[8] = invDeterminant * cofactor2;
	output[9] = -invDeterminant * cofactor6;
	output[10] = invDeterminant * cofactor10;
	output[11] = -invDeterminant * cofactor14;

	output[12] = -invDeterminant * cofactor3;
	output[13] = invDeterminant * cofactor7;
	output[14] = -invDeterminant * cofactor11;
	output[15] = invDeterminant * cofactor15;

}



/*
void invert_matrix_4x4(double * inverse1d, double * input)
{
    boolean DEBUG = TRUE;

    // convert [16] to [4][4]
    double m[4][4];
    for(int i = 0; i < 16; i++)
    {
        int column = i % 4;
        int row = floor(i / 4);
        m[row][column] =  input[i];
    }
    if(DEBUG)
    {
        printf("input as 4x4:\n");
        display_matrix4x4(m);
    }


    double lower[4][4] = {0};
    double upper[4][4] = {0};
    // or with memset...


    lower[0][0] = m[0][0];
    for(int j = 1; j < 4; j++)
    {
        lower[j][0] = m[j][0];
        upper[0][j] = m[0][j] / lower[0][0];
    }

    /* wrong ----
    // int sum;
    // for(int i = 0; i < 4; i++)
    // {
    //     // upper triangular
    //     for(int k = i; k < 4; k++)
    //     {
    //         sum = 0;
    //         for(int j = 0; j < i; j++)
    //         {
    //             sum += (lower[i][j] * upper[j][k]);
    //         }
    //         upper[i][k] = m[i][k] - sum;
    //     } // -- upper triangular

    //     // Lower Triangular
	// 	for(int k = i; k < 4; k++)
    //     {
	// 		if(i == k)
	// 			lower[i][i] = 1; // Diagonal as 1
	// 		else
    //         {
	// 			// Summation of L(k, j) * U(j, i)
	// 			sum = 0;
	// 			for(int j = 0; j < i; j++)
	// 				sum += (lower[k][j] * upper[j][i]);

	// 			// Evaluating L(k, i)
	// 			lower[k][i] = (m[k][i] - sum) / upper[i][i];
	// 		}
	// 	}
    // }



    if(DEBUG)
    {
        printf("upper:\n");
        display_matrix4x4(upper);
        printf("lower:\n");
        display_matrix4x4(lower);
    }

    // inversion
    double d[4] = {0};
    double inverse[4][4] = {0};
    double I[4][4] = {{ 1.0, 0.0, 0.0, 0.0},
                      { 0.0, 1.0, 0.0, 0.0},
                      { 0.0, 0.0, 1.0, 0.0},
                      { 0.0, 0.0, 0.0, 1.0}};

    for(int column = 0; column < 4; column++)
    {
        // substitution on L (d) = column_from_I
        d[0] = I[0][column];
        d[1] = I[1][column] - (lower[1][0] * d[0]);
        d[2] = I[2][column] - (lower[2][0] * d[0]) - (lower[2][1] * d[1]);
        d[3] = I[3][column] - (lower[3][0] * d[0]) - (lower[3][1] * d[1]) - (lower[3][2] * d[2]);

        // substition on U (column_from_inv) = (d)
        inverse[3][column] = d[3] / upper[3][3];
        inverse[2][column] = (d[2] - (upper[2][3] * inverse[3][column]))
                            / upper[2][2];
        inverse[1][column] = (d[1] - (upper[1][2] * inverse[2][column]) - (upper[1][3] * inverse[3][column]))
                            / upper[1][1];
        inverse[0][column] = (d[0] - (upper[0][1] * inverse[1][column]) - (upper[0][2] * inverse[2][column])
                                    - (upper[0][3] * inverse[3][column]))
                            / upper[0][0];
    }
    // printf("inverse:\n");
    // display_matrix4x4(inverse);

    // double inverse1d[16];
    int index;
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
        {
            index = column + (4 * row);
            inverse1d[index] = inverse[row][column];
        }
    }
    // display_matrix(inverse1d);
}
*/
// https://www.geeksforgeeks.org/doolittle-algorithm-lu-decomposition/
// https://www.gamedev.net/tutorials/_/technical/math-and-physics/matrix-inversion-using-lu-decomposition-r3637/

#endif /* MATRICES_C */
