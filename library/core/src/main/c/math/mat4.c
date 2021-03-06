//
// Created by showtime on 9/12/2017.
//

#include "mat4.h"

#include <string.h>
#include <math.h>
#include <assert.h>

float* mat4_get(mat4 *mat, int row, int col)
{
    return (float*)mat + (row + (col << 2));
}

void mat4_identity(mat4 *mat)
{
    memset(mat, 0, sizeof(*mat) * 4 * 4);

    for (int i = 0; i < 4; i++)
    {
        *mat4_get(mat, i, i) = 1.0f;
    }
}

void mat4_multiply(mat4 *dst, mat4 *src1, mat4 *src2)
{
    mat4 mat;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            *mat4_get(&mat, i, j) =
                    *mat4_get(src1, i, 0) * *mat4_get(src2, 0, j) +
                    *mat4_get(src1, i, 1) * *mat4_get(src2, 1, j) +
                    *mat4_get(src1, i, 2) * *mat4_get(src2, 2, j) +
                    *mat4_get(src1, i, 3) * *mat4_get(src2, 3, j);
        }

    }

    memcpy(dst, &mat, sizeof(mat4));
}

/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glFrustum.xml
*
* perspective matrix:
*
* /   2 * nearVal                                \
* |  ------------       0            A      0    |
* |  right - left                                |
* |                                              |
* |                 2 * nearVal                  |
* |       0        ------------      B      0    |
* |                top - bottom                  |
* |                                              |
* |       0             0            C      D    |
* |                                              |
* |       0             0           -1      0    |
* \                                              /
*
*     right + left
* A = ------------
*     right - left
*
*     top + bottom
* B = ------------
*     top - bottom
*
*       farVal + nearVal
* C = - ----------------
*       farVal - nearVal
*
*       2 * farVal * nearVal
* D = - --------------------
*         farVal - nearVal
*
*/
void mat4_frustum(mat4 *mat, float left, float right, float bottom, float top, float nearVal, float farVal)
{
    assert(left != right && top != bottom && farVal != nearVal);

    float A = (right + left) / (right - left);
    float B = (top + bottom) / (top - bottom);
    float C = - (farVal + nearVal) / (farVal - nearVal);
    float D = - (2.0f * farVal * nearVal) / (farVal - nearVal);

    memset(mat, 0, sizeof(*mat) * 4 * 4);
    *mat4_get(mat, 0, 0) = (2.0f * nearVal) / (right - left);
    *mat4_get(mat, 0, 2) = A;
    *mat4_get(mat, 1, 1) = (2.0f * nearVal) / (top - bottom);
    *mat4_get(mat, 1, 2) = B;
    *mat4_get(mat, 2, 2) = C;
    *mat4_get(mat, 2, 3) = D;
    *mat4_get(mat, 3, 2) = -1.0f;
}

/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml
*
* f = cotangent(fovy / 2)
*
* perspective matrix:
*
* /    f                                                  \
* |  ------       0          0                 0          |
* |  aspect                                               |
* |                                                       |
* |    0          f          0                 0          |
* |                                                       |
* |                     zFar + zNear    2 * zFar * zNear  |
* |    0          0    --------------  ------------------ |
* |                     zNear - zFar      zNear - zFar    |
* |                                                       |
* |    0          0         -1                 0          |
* \                                                       /
*
*/
void mat4_perspective(mat4 *mat, float fovy, float aspect, float zNear, float zFar)
{
    float f = (1.0f / (float)tan(fovy / 2.0));
    memset(mat, 0, sizeof(*mat) * 4 * 4);

    assert(aspect != 0.0 && zNear != zFar);

    *mat4_get(mat, 0, 0) = f / aspect;
    *mat4_get(mat, 1, 1) = f;
    *mat4_get(mat, 2, 2) = (zFar + zNear) / (zNear - zFar);
    *mat4_get(mat, 2, 3) = (2.0f * zFar * zNear) / (zNear - zFar);
    *mat4_get(mat, 3, 2) = -1.0f;
}

void mat4_perspective_default(mat4 *mat)
{
    mat4_perspective(mat, deg2rad(60), 1, 0.03f, 1000);
}

void mat4_lookat(mat4 *mat, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;

    // Normalize f
    float rlf = 1.0f / length(fx, fy, fz);
    fx *= rlf;
    fy *= rlf;
    fz *= rlf;

    // compute s = f x up (x means "cross product")
    float sx = fy * upZ - fz * upY;
    float sy = fz * upX - fx * upZ;
    float sz = fx * upY - fy * upX;

    // and normalize s
    float rls = 1.0f / length(sx, sy, sz);
    sx *= rls;
    sy *= rls;
    sz *= rls;

    // compute u = s x f
    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    *mat4_get(mat, 0, 0) = sx;
    *mat4_get(mat, 0, 1) = ux;
    *mat4_get(mat, 0, 2) = -fx;
    *mat4_get(mat, 0, 3) = 0.0f;

    *mat4_get(mat, 1, 0) = sy;
    *mat4_get(mat, 1, 1) = uy;
    *mat4_get(mat, 1, 2) = -fy;
    *mat4_get(mat, 1, 3) = 0.0f;

    *mat4_get(mat, 2, 0) = sz;
    *mat4_get(mat, 2, 1) = uz;
    *mat4_get(mat, 2, 2) = -fz;
    *mat4_get(mat, 2, 3) = 0.0f;

    *mat4_get(mat, 3, 0) = 0.0f;
    *mat4_get(mat, 3, 1) = 0.0f;
    *mat4_get(mat, 3, 2) = 0.0f;
    *mat4_get(mat, 3, 3) = 1.0f;

    for (int i = 0 ; i < 4 ; i++)
    {
        *mat4_get(mat, i, 3) = *mat4_get(mat, 0, i) * -eyeX + *mat4_get(mat, 1, i) * -eyeY + *mat4_get(mat, 2, i) * -eyeZ;
    }

}


/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml
*
* /              \
* |  1  0  0  x  |
* |              |
* |  0  1  0  y  |
* |              |
* |  0  0  1  z  |
* |              |
* |  0  0  0  1  |
* \              /
*
*/
void mat4_translate(mat4 *mat, float x, float y, float z)
{
    memset(mat, 0, sizeof(*mat) * 4 * 4);
    *mat4_get(mat, 0, 0) = 1.0;
    *mat4_get(mat, 1, 1) = 1.0;
    *mat4_get(mat, 2, 2) = 1.0;
    *mat4_get(mat, 3, 3) = 1.0;
    *mat4_get(mat, 0, 3) = x;
    *mat4_get(mat, 1, 3) = y;
    *mat4_get(mat, 2, 3) = z;
}

/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml
*
* perspective matrix:
*
* /                                                          \
* | x^2*(1-c) + c     x*y*(1-c) - z*s   x*z*(1-c) + y*s   0  |
* |                                                          |
* | y*x*(1-c) + z*s   y^2*(1-c) + c     y*z*(1-c) - x*s   0  |
* |                                                          |
* | x*z*(1-c) - y*s   y*z*(1-c) + x*s   z^2*(1-c) + c     0  |
* |                                                          |
* |       0                  0                 0          1  |
* \                                                          /
*
* c = cos(angle), s = sin(angle)
*
*/
void mat4_rotate(mat4 *mat, float angle, float x, float y, float z)
{
    float c = (float)cos(angle);
    float omc = 1.0f - c;
    float s = (float)sin(angle);
    memset(mat, 0, sizeof(*mat) * 4 * 4);
    *mat4_get(mat, 0, 0) = (x * x * omc) + c;
    *mat4_get(mat, 0, 1) = (x * y * omc) - z * s;
    *mat4_get(mat, 0, 2) = (x * z * omc) + y * s;
    *mat4_get(mat, 1, 0) = (y * x * omc) + z * s;
    *mat4_get(mat, 1, 1) = (y * y * omc) + c;
    *mat4_get(mat, 1, 2) = (y * z * omc) - x * s;
    *mat4_get(mat, 2, 0) = (z * x * omc) - y * s;
    *mat4_get(mat, 2, 1) = (z * y * omc) + x * s;
    *mat4_get(mat, 2, 2) = (z * z * omc) + c;
    *mat4_get(mat, 3, 3) = 1.0;
}
