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

    bool DenisFileOperator::isInReadMode()
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
        x = 0;
        y = 0;
        z = 0;
    }

    void DenisEulerRotation::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&x, 0x02);
        file.readOrWrite(&y, 0x02);
        file.readOrWrite(&z, 0x02);
    }

}
