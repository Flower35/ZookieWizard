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


    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: Matrix
    ////////////////////////////////////////////////////////////////

    eMatrix::eMatrix()
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

    eMatrix operator * (eMatrix a, eMatrix b)
    {
        eMatrix c;
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

    void eMatrix::transpose(float result[16])
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

    eMatrix eSRP::getMatrix()
    {
        eMatrix rotationMatrix;
        eMatrix translationMatrix;
        eMatrix scaleMatrix;

        rotationMatrix.m[0][0] = 1 - 2 * rot.y * rot.y - 2 * rot.z * rot.z;
        rotationMatrix.m[1][0] = 2 * rot.x * rot.y - 2 * rot.z * rot.w;
        rotationMatrix.m[2][0] = 2 * rot.x * rot.z + 2 * rot.y * rot.w;
        rotationMatrix.m[3][0] = 0;

        rotationMatrix.m[0][1] = 2 * rot.x * rot.y + 2 * rot.z * rot.w;
        rotationMatrix.m[1][1] = 1 - 2 * rot.x * rot.x - 2 * rot.z * rot.z;
        rotationMatrix.m[2][1] = 2 * rot.y * rot.z - 2 * rot.x * rot.w;
        rotationMatrix.m[3][1] = 0;

        rotationMatrix.m[0][2] = 2 * rot.x * rot.z - 2 * rot.y * rot.w;
        rotationMatrix.m[1][2] = 2 * rot.y * rot.z + 2 * rot.x * rot.w;
        rotationMatrix.m[2][2] = 1 - 2 * rot.x * rot.x - 2 * rot.y * rot.y;
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

        /* Matrices must be applied in reverse order */
        /* ((T x R) x S) */

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
