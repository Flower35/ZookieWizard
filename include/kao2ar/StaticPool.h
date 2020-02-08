#ifndef H_KAO2AR_STATICPOOL
#define H_KAO2AR_STATICPOOL

namespace ZookieWizard
{
    class Gadget;

    struct TypeInfo;

    class Archive;

    ////////////////////////////////////////////////////////////////
    // KAO2 STATIC POOL
    ////////////////////////////////////////////////////////////////

    static const int MAX_INSTANCES = 8;

    struct Kao2StaticPool
    {
        /*** Properties ***/

        private:

            int gadgetsCount;
            Gadget* list[MAX_INSTANCES];

        /*** Methods ***/

    private:

        bool registerGadget(Gadget* gadget);

        int findGadget(TypeInfo* info) const;

    public:

        bool registerStaticGadgets();

        void serializeGadget(Archive &ar, Gadget** gadget) const;
    };

    extern Kao2StaticPool StaticPool;

}

#endif
