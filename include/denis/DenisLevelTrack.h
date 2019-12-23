#ifndef H_DENIS_LEVEL_TRACK
#define H_DENIS_LEVEL_TRACK

#include <denis/Denis.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: tracks sub-structures
    ////////////////////////////////////////////////////////////////

    struct DenisLevelTrack_A
    {
        /*** Properties ***/

            /* <<< 0x3C elements >>> */

            uint8_t dummy[0x3C];

        /*** Methods ***/

            DenisLevelTrack_A();

            void serialize(DenisFileOperator &file);
    };

    struct DenisLevelTrack_B
    {
        /*** Properties ***/

            /* <<< 0x58 elements >>> */

            uint8_t dummy[0x58];

        /*** Methods ***/

            DenisLevelTrack_B();

            void serialize(DenisFileOperator &file);
    };
    
    struct DenisLevelTrack_C
    {
        /*** Properties ***/

            /* <<< 0x10 elements >>> */

            uint8_t dummy[0x10];

        /*** Methods ***/

            DenisLevelTrack_C();

            void serialize(DenisFileOperator &file);
    };
    
    struct DenisLevelTrack_D
    {
        /*** Properties ***/

            /* <<< 0x08 elements >>> */

            uint8_t dummy[0x08];

        /*** Methods ***/

            DenisLevelTrack_D();

            void serialize(DenisFileOperator &file);
    };
    
    struct DenisLevelTrack_E
    {
        /*** Properties ***/

            /* <<< 0x10 elements >>> */

            uint8_t dummy[0x10];

        /*** Methods ***/

            DenisLevelTrack_E();

            void serialize(DenisFileOperator &file);
    };
    
    struct DenisLevelTrack_F
    {
        /*** Properties ***/

            /* <<< 0x10 elements >>> */
            
            uint8_t dummy[0x10];

        /*** Methods ***/

            DenisLevelTrack_F();

            void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: track structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelTrack
    {
        /*** Properties ***/

            int32_t dummy_00;
            int32_t dummy_04;
            int32_t dummy_08;
            int32_t dummy_0C;

            int32_t groupA_Count;
            DenisLevelTrack_A* groupA;

            int32_t groupB_Count;
            DenisLevelTrack_B* groupB;

            int32_t groupC_Count;
            DenisLevelTrack_C* groupC;

            int32_t groupD_Count;
            DenisLevelTrack_D* groupD;

            int32_t groupE_Count;
            DenisLevelTrack_E* groupE;

            int32_t groupF_Count;
            DenisLevelTrack_F* groupF;

        /*** Methods ***/

            DenisLevelTrack();
            ~DenisLevelTrack();

            void serialize(DenisFileOperator &file);
    };

}

#endif
