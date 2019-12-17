#include <kao2ar/eAnimate.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Structure constructor
    // <kao2.004B68E0>
    ////////////////////////////////////////////////////////////////
    eAnimate::eAnimate()
    {
        /*[0x10]*/ stateA = nullptr;
        /*[0x14]*/ stateB = nullptr;
        /*[0x18]*/ unknown18 = false;
        /*[0x34]*/ unknown34 = 0;
        /*[0x38]*/ unknown38 = 0;
        /*(kao3)[0x0120]*/ states_count = 1;
    }

    ////////////////////////////////////////////////////////////////
    // Structure destructor
    // <kao2.004B6920>
    ////////////////////////////////////////////////////////////////
    eAnimate::~eAnimate()
    {
        if (nullptr != stateA)
        {
            (*stateA)->decRef();
            delete(stateA);
        }

        if ((stateB != stateA) && (nullptr != stateB))
        {
            (*stateB)->decRef();
            delete(stateB);
        }
    }

    ////////////////////////////////////////////////////////////////
    // Sub-serialization of anim states
    // <kao2.004B7720>
    ////////////////////////////////////////////////////////////////
    void ArFunctions::serialize_AnimStates(Archive &ar, eAnimState** &s)
    {
        int32_t a;
        int32_t b;

        if (ar.isInReadMode())
        {
            ar.readOrWrite(&a, 0x04);

            switch (a)
            {
                case 0x00:
                {
                    s = new (eAnimState*);
                    (*s) = nullptr;

                    ar.addItem(s, AR_ITEM_TYPE_OTHER);

                    /* Skipping the reccursion */

                    for (b = 0; b < 2; b++)
                    {
                        a = 0x01;
                        
                        ar.readOrWrite(&a, 0x04);

                        if (0x01 != a)
                        {
                            throw ErrorMessage
                            (
                                "ePivot::serialize():\n" \
                                "too many AnimStates! (expected 1)"
                            );
                        }
                    }

                    ar.serialize((eObject**)&(*s), &E_ANIMSTATE_TYPEINFO);
                    (*s)->incRef();

                    return;
                }

                case 0x01:
                {
                    s = nullptr;

                    return;
                }

                default:
                {
                    s = (eAnimState**)ar.getItem((a - 2), AR_ITEM_TYPE_OTHER);

                    return;
                }
            }
        }
        else
        {
            /* Writing mode */

            if (nullptr != s)
            {
                a = ar.findItem(s);

                if (a < 0)
                {
                    ar.addItem(s, AR_ITEM_TYPE_OTHER);

                    a = 0x00;
                    ar.readOrWrite(&a, 0x04);

                    for (b = 0; b < 2; b++)
                    {
                        a = 0x01;
                        ar.readOrWrite(&a, 0x04);
                    }

                    ar.serialize((eObject**)&(*s), &E_ANIMSTATE_TYPEINFO);
                }
                else
                {
                    a += 2;
                    ar.readOrWrite(&a, 0x04);
                }
            }
            else
            {
                a = 0x01;
                ar.readOrWrite(&a, 0x04);
            }
        }
    }

    ////////////////////////////////////////////////////////////////
    // Structure serialization
    // <kao2.004B6F50> <kao_tw.00450E90>
    ////////////////////////////////////////////////////////////////
    void eAnimate::serialize(Archive &ar)
    {
        int i;

        if (ar.getVersion() >= 0x8B)
        {
            /* Kao3, newer version */

            ar.readOrWrite(&states_count, 0x04);

            if (ar.isInReadMode())
            {
                if (states_count > 1)
                {
                    throw ErrorMessage
                    (
                        "ePivot::serialize():\n" \
                        "too many AnimStates! (expected 1)"
                    );
                }
            }

            for (i = 0; i < states_count; i++)
            {
                state[i].serialize(ar);
            }

            if (ar.isInReadMode())
            {
                /* Kao2, backwards compatibility */

                if (states_count >= 1)
                {
                    stateB = stateA = new (eAnimState*);
                    (*stateA) = new eAnimState;
                    (**stateA) = state[0];
                    (**stateA).incRef();
                }
            }
        }
        else
        {
            /* Kao2, older verion */
            
            ArFunctions::serialize_AnimStates(ar, stateA);
            ArFunctions::serialize_AnimStates(ar, stateB);

            if (ar.isInReadMode())
            {
                /* Kao3, forwards compatibility */

                if (nullptr != stateA)
                {
                    if (nullptr != (*stateA))
                    {
                        state[0] = (**stateA);

                        /* DO NOT increase pointer this time */
                        /* We copied from pointer to direct/internal structure */
                    }
                }
            }
        }

        tracks.serialize(ar, &E_TRACK_TYPEINFO);

        ar.readOrWrite(&unknown18, 0x01);

        ar.readOrWrite(&unknown34, 0x04);
        ar.readOrWrite(&unknown38, 0x01);
    }
}
