#ifndef H_ELEPHANT_TYPEINFO
#define H_ELEPHANT_TYPEINFO

#include <ElephantBase/kao2ar.h>

namespace ZookieWizard
{
    class eObject;

    ////////////////////////////////////////////////////////////////
    // ELEPHANT ENGINE: TYPEINFO
    ////////////////////////////////////////////////////////////////

    struct TypeInfo
    {
        /*** Properties ***/

        public:

            /*[0x00]*/ uint32_t id;
            /*[0x04]*/ const char* name;
            /*[0x08]*/ TypeInfo* parent;
            /*[0x10]*/ eObject* (*create)();

        /*** Methods ***/

        public:

            TypeInfo(int _id, const char* _name, TypeInfo* _parent, eObject* (*_create)());

            bool checkHierarchy(const TypeInfo* assumed_type) const;
    };


    ////////////////////////////////////////////////////////////////
    // ELEPHANT ENGINE: INTERFACES LIST
    ////////////////////////////////////////////////////////////////

    static const int MAX_INTERFACES = 288;

    struct ElephantInterfaces
    {
        /*** Properties ***/

        private:

            int32_t interfacesCount;
            TypeInfo* list[MAX_INTERFACES];

        /*** Methods ***/

        private:

            bool registerTypeInfo(const TypeInfo* info);

        public:

            bool registerInterfaces();

            const TypeInfo* getTypeInfo(int id) const;
            const TypeInfo* getTypeInfo(const char* name) const;
    };

    extern ElephantInterfaces theElephantInterfaces;

}

#endif
