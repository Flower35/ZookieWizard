#include <kao2ar/kao2ar.h>

#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: ePoint2
    ////////////////////////////////////////////////////////////////

    bool ePoint2::operator == (const ePoint2 &point) const
    {
        return (point.u == u) && (point.v == v);
    }


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


    bool ePoint3::operator == (const ePoint3 &point) const
    {
        return (point.x == x) && (point.y == y) && (point.z == z);
    }

    ePoint3 ePoint3::operator + (const ePoint3 &point) const
    {
        return ePoint3
        (
            x + point.x,
            y + point.y,
            z + point.z
        );
    }

    ePoint3& ePoint3::operator += (const ePoint3 &point)
    {
        x += point.x;
        y += point.y;
        z += point.z;

        return *this;
    }

    ePoint3 ePoint3::operator - (const ePoint3 &point) const
    {
        return ePoint3
        (
            x - point.x,
            y - point.y,
            z - point.z
        );
    }

    ePoint3& ePoint3::operator -= (const ePoint3 &point)
    {
        x -= point.x;
        y -= point.y;
        z -= point.z;

        return *this;
    }

    ePoint3 ePoint3::operator * (float scalar) const
    {
        return ePoint3
        (
            x * scalar,
            y * scalar,
            z * scalar
        );
    }

    ePoint3::ePoint3(const ePoint4 &point)
    {
        x = point.x;
        y = point.y;
        z = point.z;
    }

    ePoint3& ePoint3::operator += (const ePoint4 &point)
    {
        x += point.x;
        y += point.y;
        z += point.z;

        return *this;
    }

    ePoint3& ePoint3::operator -= (const ePoint4 &point)
    {
        x -= point.x;
        y -= point.y;
        z -= point.z;

        return *this;
    }

    float ePoint3::getLength() const
    {
        return sqrtf((x * x) + (y * y) + (z * z));
    }

    void ePoint3::normalize()
    {
        float length = getLength();

        if (0 != length)
        {
            x = x / length;
            y = y / length;
            z = z / length;
        }
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

    ePoint4 ePoint4::operator + (const ePoint4 &point) const
    {
        return ePoint4
        (
            x + point.x,
            y + point.y,
            z + point.z,
            w + point.w
        );
    }

    ePoint4& ePoint4::operator += (const ePoint4 &point)
    {
        x += point.x;
        y += point.y;
        z += point.z;
        w += point.w;

        return *this;
    }

    ePoint4 ePoint4::operator - (const ePoint4 &point) const
    {
        return ePoint4
        (
            x - point.x,
            y - point.y,
            z - point.z,
            w - point.w
        );
    }

    ePoint4& ePoint4::operator -= (const ePoint4 &point)
    {
        x -= point.x;
        y -= point.y;
        z -= point.z;
        w -= point.w;

        return *this;
    }

    ePoint4 ePoint4::operator * (float scalar) const
    {
        return ePoint4
        (
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        );
    }

    ePoint4::ePoint4(const ePoint3 &point)
    {
        x = point.x;
        y = point.y;
        z = point.z;
        w = 0;
    }

    ePoint4& ePoint4::operator += (const ePoint3 &point)
    {
        x += point.x;
        y += point.y;
        z += point.z;

        return *this;
    }

    ePoint4& ePoint4::operator -= (const ePoint3 &point)
    {
        x -= point.x;
        y -= point.y;
        z -= point.z;

        return *this;
    }

    float ePoint4::getLength() const
    {
        return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
    }

    void ePoint4::normalize()
    {
        float length = getLength();

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

    ePoint3 crossProduct(const ePoint3 &a, const ePoint3 &b)
    {
        return ePoint3
        {
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        };
    }

    float dotProduct(const ePoint3 &a, const ePoint3 &b)
    {
        return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
    }

    float angleBetweenVectors(const ePoint3 &a, const ePoint3 &b)
    {
        double length_a = a.getLength();
        double length_b = b.getLength();

        if ((0 != length_a) && (0 != length_b))
        {
            return (float)std::acos(dotProduct(a, b) / length_a / length_b);
        }
        return 0;
    }

    void calculateBoundaryBox
    (
        ePoint3 &min,
        ePoint3 &max,
        int32_t v_count,
        const ePoint4* vertices,
        int32_t i_count,
        const ushort* indices
    )
    {
        int32_t a, b;

        if (nullptr != vertices)
        {
            if (nullptr != indices)
            {
                b = indices[0];

                min = {vertices[b].x, vertices[b].y, vertices[b].z};
                max = min;

                for (a = 1; a < i_count; a++)
                {
                    b = indices[a];

                    if (vertices[b].x < min.x) min.x = vertices[b].x;
                    if (vertices[b].y < min.y) min.y = vertices[b].y;
                    if (vertices[b].z < min.z) min.z = vertices[b].z;
                    if (vertices[b].x > max.x) max.x = vertices[b].x;
                    if (vertices[b].y > max.y) max.y = vertices[b].y;
                    if (vertices[b].z > max.z) max.z = vertices[b].z;
                }
            }
            else
            {
                min = {vertices[0].x, vertices[0].y, vertices[0].z};
                max = min;

                for (a = 1; a < v_count; a++)
                {
                    if (vertices[a].x < min.x) min.x = vertices[a].x;
                    if (vertices[a].y < min.y) min.y = vertices[a].y;
                    if (vertices[a].z < min.z) min.z = vertices[a].z;
                    if (vertices[a].x > max.x) max.x = vertices[a].x;
                    if (vertices[a].y > max.y) max.y = vertices[a].y;
                    if (vertices[a].z > max.z) max.z = vertices[a].z;
                }
            }
        }
        else
        {
            min = {0, 0, 0};
            max = {1.0f, 1.0f, 1.0f};
        }
    }


    ////////////////////////////////////////////////////////////////
    // Kao2 data structure: Axis Aligned Boundary Box
    ////////////////////////////////////////////////////////////////

    eABB::eABB()
    {
        leftNode = 0x80000000;
        rightNode = 0xC0000001;
    }

    bool eABB::operator == (const eABB &box) const
    {
        return ((box.min.x == min.x) && (box.min.y == min.y) && (box.min.z == min.z)
          && (box.max.x == max.x) && (box.max.y == max.y) && (box.max.z == max.z));
    }

    bool eABB::fitsMeFromLeft(const eABB &box) const
    {
        return ((box.min.x <= min.x) || (box.min.y <= min.y) || (box.min.z <= min.z));
    }

    bool eABB::fitsMeFromRight(const eABB &box) const
    {
        return ((box.max.x >= max.x) || (box.max.y >= max.y) || (box.max.z >= max.z));
    }

    bool eABB::isIntersecting(const eABB &box) const
    {
        return ((min.x <= box.max.x) && (min.y <= box.max.y) && (min.z <= box.max.z)
          && (max.x >= box.min.x) && (max.y >= box.min.y) && (max.z >= box.min.z));
    }

    void eABB::expandBoundaries(const eABB &box, bool change_min, bool change_max)
    {
        if (change_min)
        {
            if (box.min.x < min.x) min.x = box.min.x;
            if (box.min.y < min.y) min.y = box.min.y;
            if (box.min.z < min.z) min.z = box.min.z;
        }

        if (change_max)
        {
            if (box.max.x > max.x) max.x = box.max.x;
            if (box.max.y > max.y) max.y = box.max.y;
            if (box.max.z > max.z) max.z = box.max.z;
        }
    }

    bool eABB::insertLeaf(int32_t current_id, int32_t &empty_id, eABB* nodes, const eABB &box)
    {
        if ((0x80000000 & leftNode) && (0x80000000 & rightNode))
        {
            /* Changing leaf to a branch */

            if (fitsMeFromLeft(box) || (box == (*this)))
            {
                nodes[empty_id + 0] = box;
                nodes[empty_id + 1] = (*this);

                leftNode = (empty_id + 0);
                rightNode = (empty_id + 1);
                expandBoundaries(box, true, true);
                nodes[current_id] = (*this);

                empty_id += 2;
                return true;
            }
            else if (fitsMeFromRight(box))
            {
                nodes[empty_id + 0] = (*this);
                nodes[empty_id + 1] = box;

                leftNode = (empty_id + 0);
                rightNode = (empty_id + 1);
                expandBoundaries(box, true, true);
                nodes[current_id] = (*this);

                empty_id += 2;
                return true;
            }
        }
        else
        {
            if (false == (0x80000000 & leftNode))
            {
                if (nodes[leftNode].isIntersecting(box) || nodes[leftNode].fitsMeFromLeft(box))
                {
                    if (nodes[leftNode].insertLeaf(leftNode, empty_id, nodes, box))
                    {
                        expandBoundaries(nodes[leftNode], true, true);

                        return true;
                    }
                }
            }

            if (false == (0x80000000 & rightNode))
            {
                if (nodes[rightNode].insertLeaf(rightNode, empty_id, nodes, box))
                {
                    expandBoundaries(nodes[rightNode], true, true);

                    return true;
                }
            }
        }

        return false;
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

    eQuat eQuat::operator + (const eQuat &quaternion) const
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

    eQuat eQuat::operator - (const eQuat &quaternion) const
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

    eQuat eQuat::operator * (const eQuat &quat) const
    {
        return eQuat
        (
            (y * quat.z - z * quat.y) + (w * quat.x) + (quat.w * x),
            (z * quat.x - x * quat.z) + (w * quat.y) + (quat.w * y),
            (x * quat.y - y * quat.x) + (w * quat.z) + (quat.w * z),
            (w * quat.w) - (x * quat.x + y * quat.y + z * quat.z)
        );
    }

    eQuat eQuat::operator * (float scalar) const
    {
        return eQuat
        (
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        );
    }

    float eQuat::getLength() const
    {
        return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
    }

    void eQuat::normalize()
    {
        float length = getLength();

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

        alpha /= 2.0f;
        beta /= 2.0f;
        gamma /= 2.0f;

        float s1 = std::sinf(alpha);
        float s2 = std::sinf(beta);
        float s3 = std::sinf(gamma);
        float c1 = std::cosf(alpha);
        float c2 = std::cosf(beta);
        float c3 = std::cosf(gamma);

        x = t * (c2 * c3 * s1 - c1 * s2 * s3);
        y = t * (c2 * s1 * s3 + c1 * c3 * s2);
        z = t * (c1 * c2 * s3 - c3 * s1 * s2);
        w = c1 * c2 * c3 + s1 * s2 * s3;
    }

    void eQuat::fromAxisAngle(ePoint3 &axis, float angle)
    {
        float length = axis.getLength();
        float s;

        if (length > 0)
        {
            angle /= 2.0f;

            s = std::sinf(angle);

            x = axis.x / length * s;
            y = axis.y / length * s;
            z = axis.z / length * s;
            w = std::cosf(angle);
        }
        else
        {
            eQuat();
        }
    }

    void eQuat::toEulerAngles(bool inverse, float &alpha, float &beta, float &gamma) const
    {
        double a, b;
        float x = inverse ? (- (this->x)) : (this->x);
        float y = inverse ? (- (this->y)) : (this->y);
        float z = inverse ? (- (this->z)) : (this->z);

        /* [X] angle */
        a = 2 * (w * x + y * z);
        b = 1 - 2 * (x * x + y * y);
        alpha = (float)std::atan2(a, b);

        /* [Y] angle */
        a = 2 * (w * y - z * x);
        if (std::abs(a) >= 1)
        {
            beta = (float)std::copysign(M_PI / 2.0, a);
        }
        else
        {
            beta = (float)std::asin(a);
        }

        /* [Z] angle */
        a = 2 * (w * z + x * y);
        b = 1 - 2 * (y * y + z * z);
        gamma = (float)std::atan2(a, b);
    }

    /* <kao2.004AB070> */
    ePoint3 operator * (const ePoint3 &pos, const eQuat &rot)
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

    eMatrix4x4 operator * (const eMatrix4x4 &a, const eMatrix4x4 &b)
    {
        eMatrix4x4 c;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                c.m[i][j] = 0;

                for (int k = 0; k < 4; k++)
                {
                    c.m[i][j] += a.m[i][k] * b.m[k][j];
                }
            }
        }

        return c;
    }

    ePoint4 operator * (const eMatrix4x4 &a, const ePoint4 &p)
    {
        return ePoint4
        {
            (a.m[0][0] * p.x) + (a.m[0][1] * p.y) + (a.m[0][2] * p.z) + (a.m[0][3] * p.w),
            (a.m[1][0] * p.x) + (a.m[1][1] * p.y) + (a.m[1][2] * p.z) + (a.m[1][3] * p.w),
            (a.m[2][0] * p.x) + (a.m[2][1] * p.y) + (a.m[2][2] * p.z) + (a.m[2][3] * p.w),
            (a.m[3][0] * p.x) + (a.m[3][1] * p.y) + (a.m[3][2] * p.z) + (a.m[3][3] * p.w)
        };
    }

    void eMatrix4x4::transpose(float result[16]) const
    {
        result[0] = m[0][0];
        result[1] = m[1][0];
        result[2] = m[2][0];
        result[3] = m[3][0];

        result[4] = m[0][1];
        result[5] = m[1][1];
        result[6] = m[2][1];
        result[7] = m[3][1];

        result[8] = m[0][2];
        result[9] = m[1][2];
        result[10] = m[2][2];
        result[11] = m[3][2];

        result[12] = m[0][3];
        result[13] = m[1][3];
        result[14] = m[2][3];
        result[15] = m[3][3];
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

    eMatrix4x4 eSRP::getMatrix() const
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
    eMatrix4x4 eSRP::getInverseMatrix() const
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
    eSRP eSRP::applyAnotherSRP(const eSRP &parent) const
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

    void operator << (eString &str, FileOperator &fo)
    {
        int32_t i;
        char test[2] = {0x00, 0x00};
        eString result;

        do
        {
            fo.read(&(test[0]), 0x01);
            result += test;
        }
        while (('\n' != test[0]) && (!fo.endOfFileReached()));

        i = result.getLength() - 1;

        while (i >= 0)
        {
            if (result.getText()[i] < 0x20)
            {
                result = result.getSubstring(0, i);

                i--;
            }
            else
            {
                i = (-1);
            }
        }

        str = result;
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

    int32_t ArFunctions::splitString(eString &source, eString* destination, int32_t max_entries)
    {
        int32_t counter = 0;
        int32_t parts = 0;
        int32_t start = 0;
        int32_t middle = 0;
        int32_t end = source.getLength() - 1;
        char* text = source.getText();

        while ((counter < 2) && (start < end))
        {
            counter = 0;

            if (text[start] <= 0x20)
            {
                start++;
            }
            else
            {
                counter++;
            }

            if (text[end] <= 0x20)
            {
                end--;
            }
            else
            {
                counter++;
            }
        }

        while ((parts + 1) < max_entries)
        {
            middle = start + 1;

            while ((middle <= end) && (text[middle] > 0x20))
            {
                middle++;
            }

            destination[parts] = source.getSubstring(start, middle - start);
            parts++;

            if (middle > end)
            {
                return parts;
            }

            start = middle;
            counter = 0;

            while ((counter < 1) && (start < end))
            {
                if (text[start] <= 0x20)
                {
                    start++;
                }
                else
                {
                    counter = 1;
                }
            }
        }

        if (start <= end)
        {
            /* Could be a line containing only the LF symbol */
            if (text[start] > 0x20)
            {
                destination[parts] = source.getSubstring(start, end - start + 1);
                parts++;
            }
        }

        return parts;
    }

    int32_t ArFunctions::propertyString(eString &source, eString* destination, int32_t max_entries, int32_t line_number)
    {
        int32_t counter, start[2], middle, end;
        eString dummy;
        char* text;

        if (max_entries < 2)
        {
            throw ErrorMessage
            (
                "String parsing error (line %d):\n" \
                "expected at least 2 entries! (before and after the `=` sign)",
                line_number
            );
            return 0;
        }

        end = source.getLength() - 1;
        text = source.getText();

        start[0] = (-1);
        start[1] = (-1);
        middle = (-1);

        for (counter = 0; counter < end; counter++)
        {
            if ('=' == text[counter])
            {
                if (counter <= 0)
                {
                    throw ErrorMessage
                    (
                        "String parsing error (line %d):\n" \
                        "`=` sign found at the beginning!",
                        line_number
                    );
                    return 0;
                }
                else if (middle < 0)
                {
                    middle = counter;
                }
                else
                {
                    throw ErrorMessage
                    (
                        "String parsing error (line %d):\n" \
                        "multiple `=` signs found!",
                        line_number
                    );
                    return 0;
                }
            }
        }

        if (middle < 0)
        {
            throw ErrorMessage
            (
                "String parsing error (line %d):\n" \
                "`=` sign not found!",
                line_number
            );
            return 0;
        }

        for (counter = 0; (start[1] < 0) && (counter < middle); counter++)
        {
            if (text[counter] > 0x20)
            {
                if (start[0] < 0)
                {
                    start[0] = counter;
                }
            }
            else if (text[counter] <= 0x20)
            {
                if (start[0] >= 0)
                {
                    start[1] = counter;
                }
            }
        }

        if (start[0] < 0)
        {
            throw ErrorMessage
            (
                "String parsing error (line %d):\n" \
                "Nothing found on the left side of `=` sign!",
                line_number
            );
            return 0;
        }

        if (start[1] < 0)
        {
            start[1] = middle;
        }

        destination[0] = source.getSubstring(start[0], start[1] - start[0]);
        dummy = source.getSubstring(middle + 1, 0);
        return splitString(dummy, &(destination[1]), max_entries - 1);
    }

}
