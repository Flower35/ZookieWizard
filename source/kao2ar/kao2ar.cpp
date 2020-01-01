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

    ePoint3& ePoint3::operator + (const ePoint3 &point)
    {
        x = x + point.x;
        y = y + point.y;
        z = z + point.z;

        return *this;
    }

    ePoint3& ePoint3::operator - (const ePoint3 &point)
    {
        x = x - point.x;
        y = y - point.y;
        z = z - point.z;

        return *this;
    }

    ePoint3& ePoint3::operator * (float scalar)
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;

        return *this;
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

    eQuat& eQuat::operator + (const eQuat &quaternion)
    {
        x = x + quaternion.x;
        y = y + quaternion.y;
        z = z + quaternion.z;
        w = w + quaternion.w;

        normalize();

        return *this;
    }

    eQuat& eQuat::operator - (const eQuat &quaternion)
    {
        x = x - quaternion.x;
        y = y - quaternion.y;
        z = z - quaternion.z;
        w = w - quaternion.w;

        normalize();

        return *this;
    }

    eQuat& eQuat::operator * (float scalar)
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        w = w * scalar;

        return *this;
    }

    void eQuat::normalize()
    {
        float length = sqrtf((x *x) + (y * y) + (z * z) + (w * w));

        if (0 != length)
        {
            x = x / length;
            y = y / length;
            z = z / length;
            w = w / length;
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

    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: Matrix [4x4]
    ////////////////////////////////////////////////////////////////

    eMatrix4x4::eMatrix4x4()
    {
        identity();
    }

    void eMatrix4x4::identity()
    {
        float value;
        int32_t rows;
        int32_t columns;

        for (rows = 0; rows < 4; rows++)
        {
            for (columns = 0; columns < 4; columns++)
            {
                value = (rows != columns) ? 0 : 1.0f;

                m[rows][columns] = value;
            }
        }
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
        eMatrix4x4 rotationMatrix;
        eMatrix4x4 translationMatrix;
        eMatrix4x4 scaleMatrix;

        rotationMatrix.m[0][0] = 1 - 2 * (rot.y * rot.y + rot.z * rot.z);
        rotationMatrix.m[1][0] = 2 * (rot.x * rot.y - rot.z * rot.w);
        rotationMatrix.m[2][0] = 2 * (rot.x * rot.z + rot.y * rot.w);
        rotationMatrix.m[3][0] = 0;

        rotationMatrix.m[0][1] = 2 * (rot.x * rot.y + rot.z * rot.w);
        rotationMatrix.m[1][1] = 1 - 2 * (rot.x * rot.x + rot.z * rot.z);
        rotationMatrix.m[2][1] = 2 * (rot.y * rot.z - rot.x * rot.w);
        rotationMatrix.m[3][1] = 0;

        rotationMatrix.m[0][2] = 2 * (rot.x * rot.z - rot.y * rot.w);
        rotationMatrix.m[1][2] = 2 * (rot.y * rot.z + rot.x * rot.w);
        rotationMatrix.m[2][2] = 1 - 2 * (rot.x * rot.x + rot.y * rot.y);
        rotationMatrix.m[3][2] = 0;

        rotationMatrix.m[0][3] = 0;
        rotationMatrix.m[1][3] = 0;
        rotationMatrix.m[2][3] = 0;
        rotationMatrix.m[3][3] = 1.0f;

        translationMatrix.m[0][0] = 1.0f;
        translationMatrix.m[1][0] = 0;
        translationMatrix.m[2][0] = 0;
        translationMatrix.m[3][0] = 0;
        
        translationMatrix.m[0][1] = 0;
        translationMatrix.m[1][1] = 1.0f;
        translationMatrix.m[2][1] = 0;
        translationMatrix.m[3][1] = 0;
        
        translationMatrix.m[0][2] = 0;
        translationMatrix.m[1][2] = 0;
        translationMatrix.m[2][2] = 1.0f;
        translationMatrix.m[3][2] = 0;
        
        translationMatrix.m[0][3] = pos.x;
        translationMatrix.m[1][3] = pos.y;
        translationMatrix.m[2][3] = pos.z;
        translationMatrix.m[3][3] = 1.0f;

        scaleMatrix.m[0][0] = scale;
        scaleMatrix.m[1][0] = 0;
        scaleMatrix.m[2][0] = 0;
        scaleMatrix.m[3][0] = 0;

        scaleMatrix.m[0][1] = 0;
        scaleMatrix.m[1][1] = scale;
        scaleMatrix.m[2][1] = 0;
        scaleMatrix.m[3][1] = 0;

        scaleMatrix.m[0][2] = 0;
        scaleMatrix.m[1][2] = 0;
        scaleMatrix.m[2][2] = scale;
        scaleMatrix.m[3][2] = 0;

        scaleMatrix.m[0][3] = 0;
        scaleMatrix.m[1][3] = 0;
        scaleMatrix.m[2][3] = 0;
        scaleMatrix.m[3][3] = 1.0f;

        /* Matrices must be multiplied in reverse order */
        /* (T x (R x (S x Vector))) */

        return ((translationMatrix * rotationMatrix) * scaleMatrix);
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
