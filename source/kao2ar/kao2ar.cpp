#include <kao2ar/kao2ar.h>

#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: ePoint3
    // <kao2.00422780> (serialize)
    ////////////////////////////////////////////////////////////////

    ePoint3::ePoint3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    ePoint3::ePoint3(float initializer)
    : x(initializer), y(initializer), z(initializer)
    {}

    ePoint3::ePoint3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
    {}

    ePoint3 ePoint3::operator + (const ePoint3 &point)
    {
        return ePoint3
        (
            x + point.x,
            y + point.y,
            z + point.z
        );
    }

    ePoint3 ePoint3::operator - (const ePoint3 &point)
    {
        return ePoint3
        (
            x - point.x,
            y - point.y,
            z - point.z
        );
    }

    ePoint3 ePoint3::operator * (float scalar)
    {
        return ePoint3
        (
            x * scalar,
            y * scalar,
            z * scalar
        );
    }

    void ePoint3::serialize(Archive &ar)
    {
        ar.readOrWrite(&x, 0x04);
        ar.readOrWrite(&y, 0x04);
        ar.readOrWrite(&z, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: ePoint4
    ////////////////////////////////////////////////////////////////

    ePoint4::ePoint4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    ePoint4::ePoint4(float initializer)
    : x(initializer), y(initializer), z(initializer), w(initializer)
    {}

    ePoint4::ePoint4(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
    {}

    ePoint4 ePoint4::operator + (const ePoint4 &point)
    {
        return ePoint4
        (
            x + point.x,
            y + point.y,
            z + point.z,
            w + point.w
        );
    }

    ePoint4 ePoint4::operator * (float scalar)
    {
        return ePoint4
        (
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        );
    }

    void ePoint4::normalize()
    {
        float length = sqrtf((x * x) + (y * y) + (z * z) + (w * w));

        if (0 != length)
        {
            x = x / length;
            y = y / length;
            z = z / length;
            w = w / length;
        }
    }

    void ePoint4::serialize(Archive &ar)
    {
        ar.readOrWrite(&x, 0x04);
        ar.readOrWrite(&y, 0x04);
        ar.readOrWrite(&z, 0x04);
        ar.readOrWrite(&w, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: eQuat
    ////////////////////////////////////////////////////////////////

    eQuat::eQuat()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 1.0f;
    }

    eQuat::eQuat(float initializer)
    : x(initializer), y(initializer), z(initializer), w(initializer)
    {}

    eQuat::eQuat(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
    {}

    eQuat eQuat::operator + (const eQuat &quaternion)
    {
        eQuat result
        (
            x + quaternion.x,
            y + quaternion.y,
            z + quaternion.z,
            w + quaternion.w
        );

        result.normalize();

        return result;
    }

    eQuat eQuat::operator - (const eQuat &quaternion)
    {
        eQuat result
        (
            x - quaternion.x,
            y - quaternion.y,
            z - quaternion.z,
            w - quaternion.w
        );

        result.normalize();

        return result;
    }

    eQuat eQuat::operator * (const eQuat &quat)
    {
        return eQuat
        (
            (y * quat.z - z * quat.y) + (w * quat.x) + (quat.w * x),
            (z * quat.x - x * quat.z) + (w * quat.y) + (quat.w * y),
            (x * quat.y - y * quat.x) + (w * quat.z) + (quat.w * z),
            (w * quat.w) - (x * quat.x + y * quat.y + z * quat.z)
        );
    }

    eQuat eQuat::operator * (float scalar)
    {
        return eQuat
        (
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        );
    }

    void eQuat::normalize()
    {
        float length = sqrtf((x * x) + (y * y) + (z * z) + (w * w));

        if (0 != length)
        {
            x = x / length;
            y = y / length;
            z = z / length;
            w = w / length;
        }
        else
        {
            w = 1.0f;
        }
    }

    void eQuat::fromEulerAngles(bool transposed, float alpha, float beta, float gamma)
    {
        /* [X][Y][Z] rotation order */

        float t = transposed ? (-1.0f) : 1.0f;

        float s1 = std::sinf(alpha / 2);
        float s2 = std::sinf(beta / 2);
        float s3 = std::sinf(gamma / 2);
        float c1 = std::cosf(alpha / 2);
        float c2 = std::cosf(beta / 2);
        float c3 = std::cosf(gamma / 2);

        x = t * (c2 * c3 * s1 - c1 * s2 * s3);
        y = t * (c2 * s1 * s3 + c1 * c3 * s2);
        z = t * (c1 * c2 * s3 - c3 * s1 * s2);
        w = c1 * c2 * c3 + s1 * s2 * s3;
    }
    
    /* <kao2.004AB070> */
    ePoint3 operator * (ePoint3 pos, eQuat rot)
    {
        ePoint3 result;

        result.x
            = (1.0f - (2 * rot.z * rot.z + 2 * rot.y * rot.y)) * pos.x
            + (2 * rot.y * rot.x + 2 * rot.z * rot.w) * pos.y
            + (2 * rot.z * rot.x - 2 * rot.y * rot.w) * pos.z;
        result.y
            = (2 * rot.y * rot.x - 2 * rot.z * rot.w) * pos.x
            + (1.0f - (2 * rot.z * rot.z + 2 * rot.x * rot.x)) * pos.y
            + (2 * rot.z * rot.y + 2 * rot.x * rot.w) * pos.z;
        result.z
            = (2 * rot.z * rot.x + 2 * rot.y * rot.w) * pos.x
            + (2 * rot.z * rot.y - 2 * rot.x * rot.w) * pos.y
            + (1.0f - (2 * rot.x * rot.x + 2 * rot.y * rot.y)) * pos.z;

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: Matrix [4x4]
    ////////////////////////////////////////////////////////////////

    eMatrix4x4::eMatrix4x4()
    {
        identity();
    }

    void eMatrix4x4::identity()
    {
        m[0][0] = 1.0f; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 1.0f; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1.0f; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1.0f;
    }

    eMatrix4x4 operator * (eMatrix4x4 a, eMatrix4x4 b)
    {
        eMatrix4x4 c;
        int32_t i, j, k;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                c.m[i][j] = 0;

                for (k = 0; k < 4; k++)
                {
                    c.m[i][j] += a.m[i][k] * b.m[k][j];
                }
            }
        }

        return c;
    }
    
    ePoint4 operator * (eMatrix4x4 a, ePoint4 p)
    {
        float b[4] = {p.x, p.y, p.z, p.w};
        float c[4];
        int32_t i, j;

        for (i = 0; i < 4; i++)
        {
            c[i] = 0;

            for (j = 0; j < 4; j++)
            {
                c[i] += a.m[i][j] * b[j];
            }
        }

        return ePoint4(c[0], c[1], c[2], c[3]);
    }

    void eMatrix4x4::transpose(float result[16])
    {
        int32_t columns;
        int32_t rows;

        for (rows = 0; rows < 4; rows++)
        {
            for (columns = 0; columns < 4; columns++)
            {
                result[4 * columns + rows] = m[rows][columns];
            }
        }
    }

    void eMatrix4x4::serialize(Archive &ar)
    {
        int32_t columns;
        int32_t rows;

        for (rows = 0; rows < 4; rows++)
        {
            for (columns = 0; columns < 4; columns++)
            {
                /* Matrices for Bones are stored in transposition */
                 ar.readOrWrite(&(m[columns][rows]), 0x04);
            }
        }
    }

    void eMatrix4x4::setRotationZ(float angle)
    {
        float cosinus = std::cosf(angle);
        float sinus = std::sinf(angle);

        m[0][0] = cosinus;
        m[0][1] = (- sinus);
        m[0][2] = 0;
        m[0][3] = 0;

        m[1][0] = sinus;
        m[1][1] = cosinus;
        m[1][2] = 0;
        m[1][3] = 0;

        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 1.0f;
        m[2][3] = 0;

        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1.0f;
    }

    void eMatrix4x4::setRotationY(float angle)
    {
        float cosinus = std::cosf(angle);
        float sinus = std::sinf(angle);

        m[0][0] = cosinus;
        m[0][1] = 0;
        m[0][2] = sinus;
        m[0][3] = 0;

        m[1][0] = 0;
        m[1][1] = 1.0f;
        m[1][2] = 0;
        m[1][3] = 0;

        m[2][0] = (- sinus);
        m[2][1] = 0;
        m[2][2] = cosinus;
        m[2][3] = 0;

        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1.0f;
    }

    void eMatrix4x4::setRotationX(float angle)
    {
        float cosinus = std::cosf(angle);
        float sinus = std::sinf(angle);

        m[0][0] = 1.0f;
        m[0][1] = 0;
        m[0][2] = 0;
        m[0][3] = 0;

        m[1][0] = 0;
        m[1][1] = cosinus;
        m[1][2] = (- sinus);
        m[1][3] = 0;

        m[2][0] = 0;
        m[2][1] = sinus;
        m[2][2] = cosinus;
        m[2][3] = 0;

        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1.0f;
    }

    /* Global Bones Matrices */
    eMatrix4x4 theBonesMatrices[40];


    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: Scale Rotation Position
    ////////////////////////////////////////////////////////////////

    eSRP::eSRP()
    {
        scale = 1.0f;
    }

    eSRP::eSRP(float initializer)
    : scale(initializer), rot(initializer), pos(initializer)
    {}

    void eSRP::serialize(Archive &ar)
    {
        ar.readOrWrite(&scale, 0x04);

        ar.readOrWrite(&(rot.x), 0x04);
        ar.readOrWrite(&(rot.y), 0x04);
        ar.readOrWrite(&(rot.z), 0x04);
        ar.readOrWrite(&(rot.w), 0x04);

        ar.readOrWrite(&(pos.x), 0x04);
        ar.readOrWrite(&(pos.y), 0x04);
        ar.readOrWrite(&(pos.z), 0x04);
    }

    eMatrix4x4 eSRP::getMatrix()
    {
        eMatrix4x4 transformMatrix;
        
        /* Inverse quaternion */

        float invquat_x = - rot.x;
        float invquat_y = - rot.y;
        float invquat_z = - rot.z;
        float invquat_w = rot.w;

        /* (T x (R x (S x Vector))) */

        transformMatrix.m[0][0] = scale * (1 - 2 * (invquat_y * invquat_y + invquat_z * invquat_z));
        transformMatrix.m[0][1] = scale * (2 * (invquat_x * invquat_y - invquat_z * invquat_w));
        transformMatrix.m[0][2] = scale * (2 * (invquat_x * invquat_z + invquat_y * invquat_w));
        transformMatrix.m[0][3] = pos.x;

        transformMatrix.m[1][0] = scale * (2 * (invquat_x * invquat_y + invquat_z * invquat_w));
        transformMatrix.m[1][1] = scale * (1 - 2 * (invquat_x * invquat_x + invquat_z * invquat_z));
        transformMatrix.m[1][2] = scale * (2 * (invquat_y * invquat_z - invquat_x * invquat_w));
        transformMatrix.m[1][3] = pos.y;

        transformMatrix.m[2][0] = scale * (2 * (invquat_x * invquat_z - invquat_y * invquat_w));
        transformMatrix.m[2][1] = scale * (2 * (invquat_y * invquat_z + invquat_x * invquat_w));
        transformMatrix.m[2][2] = scale * (1 - 2 * (invquat_x * invquat_x + invquat_y * invquat_y));
        transformMatrix.m[2][3] = pos.z;

        return transformMatrix;
    }

    /* <kao2.004AB580> */
    eMatrix4x4 eSRP::getInverseMatrix()
    {
        eMatrix4x4 result;

        float inv_scale = 1.0f / scale;

        result.m[0][0] = inv_scale * (1 - 2 * (rot.y * rot.y + rot.z * rot.z));
        result.m[0][1] = inv_scale * (2 * (rot.x * rot.y - rot.z * rot.w));
        result.m[0][2] = inv_scale * (2 * (rot.x * rot.z + rot.y * rot.w));

        result.m[1][0] = inv_scale * (2 * (rot.x * rot.y + rot.z * rot.w));
        result.m[1][1] = inv_scale * (1 - 2 * (rot.x * rot.x + rot.z * rot.z));
        result.m[1][2] = inv_scale * (2 * (rot.y * rot.z - rot.x * rot.w));

        result.m[2][0] = inv_scale * (2 * (rot.x * rot.z - rot.y * rot.w));
        result.m[2][1] = inv_scale * (2 * (rot.y * rot.z + rot.x * rot.w));
        result.m[2][2] = inv_scale * (1 - 2 * (rot.x * rot.x + rot.y * rot.y));

        result.m[0][3] = - (result.m[0][0] * pos.x + result.m[0][1] * pos.y + result.m[0][2] * pos.z);
        result.m[1][3] = - (result.m[1][0] * pos.x + result.m[1][1] * pos.y + result.m[1][2] * pos.z);
        result.m[2][3] = - (result.m[2][0] * pos.x + result.m[2][1] * pos.y + result.m[2][2] * pos.z);

        return result;
    }

    /* <kao2.004AB070> */
    eSRP eSRP::applyAnotherSRP(const eSRP &parent)
    {
        eSRP result;

        /* Change current rotation */

        result.rot = rot * parent.rot;

        /* Apply parent rotation, scale and position to current position */

        result.pos = (((pos * parent.rot) * parent.scale) + parent.pos);

        /* Multiply current scale and parent scale */

        result.scale = scale * parent.scale;

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // String operations (macros) for scripts
    ////////////////////////////////////////////////////////////////

    FileOperator& operator << (FileOperator &fo, const char* str)
    {
        fo.write((void*)str, StringFunctions::getCharArrayLength(str));

        return fo;
    }

    FileOperator& operator << (FileOperator &fo, const eString &str)
    {
        fo.write(str.getText(), str.getLength());

        return fo;
    }

    void ArFunctions::writeIndentation(FileOperator &fo, int32_t indentation)
    {
        int32_t i;
        eString result;

        for (i = 0; i < indentation; i++)
        {
            result += "    ";
        }

        fo << result;
    }
    
    void ArFunctions::writeNewLine(FileOperator &fo, int32_t indentation)
    {
        /* "\n" is automatically changed to "\r\n" by `std::fstream` */

        fo << "\n";
        
        writeIndentation(fo, indentation);
    }

}
