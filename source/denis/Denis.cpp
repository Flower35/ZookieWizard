#include <denis/Denis.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Serialization/Deserialization opeartor
    ////////////////////////////////////////////////////////////////

    DenisFileOperator& DenisFileOperator::operator = (const DenisFileOperator &new_file)
    {
        workingDirectory = new_file.workingDirectory;

        return *this;
    }

    DenisFileOperator::DenisFileOperator(eString new_dir)
    {
        int32_t test_length;
        char* test_text;

        /* Set mode to READ */

        mode = 0;

        /* Save working directory */

        workingDirectory = new_dir;

        test_length = workingDirectory.getLength();
        test_text = workingDirectory.getText();

        if (test_length > 0)
        {
            switch (test_text[test_length - 1])
            {
                case '/':
                case '\\':
                {
                    break;
                }

                default:
                {
                    workingDirectory += "/";
                }
            }
        }
    }

    DenisFileOperator::~DenisFileOperator()
    {
        close();
    }

    bool DenisFileOperator::isInReadMode() const
    {
        return (0 == mode);
    }

    void DenisFileOperator::readOrWrite(void* ptr, int32_t size)
    {
        if (isInReadMode())
        {
            myFile.read(ptr, size);
        }
        else
        {
            myFile.write(ptr, size);
        }
    }

    bool DenisFileOperator::open(eString path)
    {
        fileName = workingDirectory + path;

        return myFile.open
        (
            fileName.getText(),
            (FILE_OPERATOR_MODE_READ | FILE_OPERATOR_MODE_BINARY)
        );
    }

    void DenisFileOperator::close()
    {
        myFile.close();
    }

    bool DenisFileOperator::checkIfExists(eString path)
    {
        fileName = workingDirectory + path;

        bool response = myFile.open
        (
            fileName.getText(),
            (FILE_OPERATOR_MODE_READ | FILE_OPERATOR_MODE_BINARY)
        );

        myFile.close();

        return response;
    }

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: object types in level
    ////////////////////////////////////////////////////////////////

    const int DENIS_LEVEL_OBJECT_ID[DENIS_LEVEL_OBJECT_TYPES] =
    {
        DENIS_LEVEL_OBJECT_TYPE_STATIC,
        DENIS_LEVEL_OBJECT_TYPE_PUSHABLE,
        DENIS_LEVEL_OBJECT_TYPE_MOVING
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: vertex structure
    ////////////////////////////////////////////////////////////////

    DenisVertex::DenisVertex()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    void DenisVertex::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&x, 0x04);
        file.readOrWrite(&y, 0x04);
        file.readOrWrite(&z, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: color structure
    ////////////////////////////////////////////////////////////////

    DenisColor::DenisColor()
    {
        color_blue = 0xFF;
        color_green = 0xFF;
        color_red = 0xFF;
        alpha = 0xFF;
    }

    void DenisColor::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&color_blue, 0x01);
        file.readOrWrite(&color_green, 0x01);
        file.readOrWrite(&color_red, 0x01);
        file.readOrWrite(&alpha, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: geo vertex
    ////////////////////////////////////////////////////////////////

    void DenisGeoVertex::serialize(DenisFileOperator &file)
    {
        v.serialize(file);
        c.serialize(file);
    }


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: boundary box structure
    ////////////////////////////////////////////////////////////////

    void DenisBoundBox::serialize(DenisFileOperator &file)
    {
        min.serialize(file);
        max.serialize(file);
    }


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: geo face
    ////////////////////////////////////////////////////////////////

    DenisGeoFace::DenisGeoFace()
    {
        dotProduct = 0;

        index[0] = 0;
        index[1] = 0;
        index[2] = 0;
        index[3] = 0;

        collisionType = 0;
        dummy = 0;
    }

    void DenisGeoFace::serialize(DenisFileOperator &file)
    {
        normalVector.serialize(file);
        file.readOrWrite(&dotProduct, 0x04);

        file.readOrWrite(&(index[0]), 0x02);
        file.readOrWrite(&(index[1]), 0x02);
        file.readOrWrite(&(index[2]), 0x02);
        file.readOrWrite(&(index[3]), 0x02);

        file.readOrWrite(&collisionType, 0x04);
        file.readOrWrite(&dummy, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: euler rotation
    ////////////////////////////////////////////////////////////////

    DenisEulerRotation::DenisEulerRotation()
    {
        alpha = 0;
        beta = 0;
        gamma = 0;
    }

    void DenisEulerRotation::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&alpha, 0x02);
        file.readOrWrite(&beta, 0x02);
        file.readOrWrite(&gamma, 0x02);
    }

    void DenisEulerRotation::toEulerAngles(bool isAnimmesh, float &x, float &y, float &z) const
    {
        if (isAnimmesh)
        {
            /* Clockwise rotation, originally [X] and [Z] angles are negated */
            /* For CCW rotatnion we need [Y] angle to be negative */

            x = alpha / float(0x8000) * float(M_PI);
            y = ((-beta) & 0x0000FFFF) / float(0x8000) * float(M_PI);
            z = gamma / float(0x8000) * float(M_PI);
        }
        else
        {
            /* "max mesh" angles are stored in [Z][Y][X] order */
            /* This order of matrix multiplications gives [X][Y][Z] rotation in result */
            /* For CCW rotation we need all angles to be negative */

            z = ((-alpha) & 0x0000FFFF) / float(0x8000) * float(M_PI);
            y = ((-beta) & 0x0000FFFF) / float(0x8000) * float(M_PI);
            x = ((-gamma) & 0x0000FFFF) / float(0x8000) * float(M_PI);
        }
    }

    void DenisEulerRotation::toQuaternion(float result[4]) const
    {
        /* <kao.00410590> */

        float s1 = std::sinf((-alpha) / 2.0f);
        float s2 = std::sinf(beta / 2.0f);
        float s3 = std::sinf((-gamma) / 2.0f);
        float c1 = std::cosf((-alpha) / 2.0f);
        float c2 = std::cosf(beta / 2.0f);
        float c3 = std::cosf((-gamma) / 2.0f);

        result[0] = c2 * c3 * s1 - c1 * s2 * s3;
        result[1] = - (c2 * s1 * s3 + c1 * c3 * s2);
        result[2] = c1 * c2 * s3 - c3 * s1 * s2;
        result[3] = c1 * c2 * c3 + s1 * s2 * s3;
    }

}
