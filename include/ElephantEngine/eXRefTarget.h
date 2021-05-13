#ifndef H_KAO2AR_XREFTARGET
#define H_KAO2AR_XREFTARGET

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{
    class eScene;

    ////////////////////////////////////////////////////////////////
    // eXRefTarget interface
    // <kao2.005D1F34> (vptr)
    ////////////////////////////////////////////////////////////////

    class eXRefTarget : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/
            /*(...)*/
            /*[0x14]*/ eScene* scene;
            /*[0x18]*/ eString fileName;
            /*(...)*/
            /*[0x24]*/

        /*** Methods ***/

        public:

            eXRefTarget();
            ~eXRefTarget();

        private:

            void createFromOtherObject(const eXRefTarget &other);

        public:

            eXRefTarget(const eXRefTarget &other);
            eXRefTarget& operator = (const eXRefTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eXRefTarget >> */

            void renderXRefScene(eDrawContext &draw_context) const;

            eXRefTarget* loadTarget(const eString &media_dir, const eString &model_name, int32_t ar_version, int32_t ar_flags);
            void exportTarget(const eString &media_dir, int32_t ar_version, int32_t ar_flags) const;

            eScene* getLocalScene() const;
    };


    ////////////////////////////////////////////////////////////////
    // eXRefTarget TypeInfo
    // <kao2.004AD180> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFTARGET_ID = 0x87EF0001;

    extern TypeInfo E_XREFTARGET_TYPEINFO;

}

#endif
