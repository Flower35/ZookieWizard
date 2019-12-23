#ifndef H_KAO2_COLLECTION
#define H_KAO2_COLLECTION

#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{

    class Archive;
    class eRefCounter;
    struct TypeInfo;


    ////////////////////////////////////////////////////////////////
    // COLLECTION OF CLASSES
    ////////////////////////////////////////////////////////////////

    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    struct Collection
    {
        /*** Properties ***/

        private:

            int32_t count;
            int32_t maxLength;
            eRefCounter** children;

        /*** Methods ***/

        public:

            Collection<Func>();
            ~Collection<Func>();

            void serialize(Archive &ar, TypeInfo* t);

            int32_t getSize();
            eRefCounter* getIthChild(int32_t i);
            void appendChild(eRefCounter* o);
            void deleteIthChild(int32_t i);
            void findAndDeleteChild(eRefCounter* o);
    };

}

#endif
