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

            void clear();

            void serialize(Archive &ar, TypeInfo* t);

            int32_t getSize() const;
            eRefCounter* getIthChild(int32_t i) const;
            void appendChild(eRefCounter* o);
            void deleteIthChild(int32_t i);
            void findAndDeleteChild(eRefCounter* o);
    };

}

#endif
