#ifndef H_KAO2_COLLECTION
#define H_KAO2_COLLECTION

#include <ElephantBase/kao2ar.h>

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

            Collection(int32_t new_size = 0);
            ~Collection();

        private:

            void createFromOtherObject(const Collection<Func> &other);

        public:

            Collection(const Collection<Func> &other);
            Collection<Func>& operator = (const Collection<Func> &other);
            Collection<Func>& deepCopy(const Collection<Func> &other);

            /* << Collection >> */

            void clear();

            void serialize(Archive &ar, TypeInfo* t);

            int32_t getSize() const;
            void setIthChild(int32_t i, eRefCounter* o);
            eRefCounter* getIthChild(int32_t i) const;
            void appendChild(eRefCounter* o);
            void deleteIthChild(int32_t i);
            void findAndDeleteChild(eRefCounter* o);
            void swapForward(int32_t i);
            void swapBackward(int32_t i);
    };

}

#endif
