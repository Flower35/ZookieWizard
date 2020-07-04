#include <kao2ar/eAnimate.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTrack.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Structure constructor
    // <kao2.004B68E0>
    ////////////////////////////////////////////////////////////////
    eAnimate::eAnimate()
    {
        /*[0x10]*/ animStateA = nullptr;
        /*[0x14]*/ animStateB = nullptr;
        /*[0x18]*/ unknown_18 = false;
        /*[0x34]*/ unknown_34 = 0;
        /*[0x38]*/ unknown_38 = 0;
        /*(kao3)[0x0120]*/ animStatesCount = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Structure destructor
    // <kao2.004B6920>
    ////////////////////////////////////////////////////////////////
    eAnimate::~eAnimate()
    {
        clearAnimStateContainers();
    }


    ////////////////////////////////////////////////////////////////
    // eAnimate: clear "AnimState" type "double" pointers
    ////////////////////////////////////////////////////////////////
    void eAnimate::clearAnimStateContainers()
    {
        /* Originally there is a structure with `eAnimState *` dynamic object. */
        /* But for correct "eAnimate" serialization we only need another "pointer layer". */

        if (nullptr != animStateA)
        {
            if (nullptr != (*animStateA))
            {
                (*animStateA)->decRef();
            }
        }

        if (nullptr != animStateB)
        {
            if (nullptr != animStateB)
            {
                (*animStateB)->decRef();
            }
        }

        /* In basically every case, `animStateB` is a direct copy of the `animStateA`. */

        if (nullptr != animStateA)
        {
            delete(animStateA);
        }

        if ((animStateB != animStateA) && (nullptr != animStateB))
        {
            delete(animStateB);
        }

        animStateA = nullptr;
        animStateB = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // Sub-serialization of anim states
    // <kao2.004B7720>
    ////////////////////////////////////////////////////////////////
    void ArFunctions::serialize_AnimStates(Archive &ar, eAnimState** &s)
    {
        int32_t a, b;

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
                                "ePivot::eAnimate::serialize():\n" \
                                "too many AnimStates! (expected 1)"
                            );
                        }
                    }

                    ar.serialize((eObject**)&(*s), &E_ANIMSTATE_TYPEINFO);

                    if (nullptr != (*s))
                    {
                        (*s)->incRef();
                    }

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

                    if (nullptr != (*s))
                    {
                        (*s)->incRef();
                    }

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

        if (ar.isInReadMode())
        {
            clearAnimStateContainers();
        }

        if (ar.getVersion() >= 0x8B)
        {
            /* Kao3, newer version */

            ar.readOrWrite(&animStatesCount, 0x04);

            if (animStatesCount > 1)
            {
                throw ErrorMessage
                (
                    "ePivot::eAnimate::serialize():\n" \
                    "too many AnimStates! (expected 1)"
                );
            }

            for (i = 0; i < animStatesCount; i++)
            {
                currentAnimState[i].serialize(ar);
            }

            if (ar.isInReadMode())
            {
                /* Kao2, backwards compatibility */

                if (animStatesCount >= 1)
                {
                    animStateB = animStateA = new (eAnimState*);
                    (*animStateA) = new eAnimState;

                    (**animStateA).incRef();
                    (**animStateB).incRef();

                    (**animStateA) = currentAnimState[0];
                }
            }
        }
        else
        {
            /* Kao2, older verion */

            ArFunctions::serialize_AnimStates(ar, animStateA);
            ArFunctions::serialize_AnimStates(ar, animStateB);

            if (ar.isInReadMode())
            {
                /* Kao3, forwards compatibility */

                if (nullptr != animStateA)
                {
                    if (nullptr != (*animStateA))
                    {
                        currentAnimState[0] = (**animStateA);

                        /* DO NOT increase refCount this time */
                        /* We copied from pointer to direct/internal structure */

                        animStatesCount = 1;
                    }
                }
            }
        }

        tracks.serialize(ar, &E_TRACK_TYPEINFO);

        ar.readOrWrite(&unknown_18, 0x01);

        ar.readOrWrite(&unknown_34, 0x04);
        ar.readOrWrite(&unknown_38, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // eAnimate: set animation timer (time is passed in frames)
    ////////////////////////////////////////////////////////////////
    void eAnimate::setAnimation(int32_t anim_id, float time)
    {
        eTrack* test_track;
        float first_frame;
        float length_in_frames;

        if ((anim_id >= 0) && (anim_id < tracks.getSize()))
        {
            currentAnimState[0].setAnimId(anim_id);

            test_track = (eTrack*)tracks.getIthChild(anim_id);

            if (nullptr != test_track)
            {
                first_frame = test_track->getStartFrame();
                length_in_frames = test_track->getEndFrame() - first_frame;
                time = first_frame + ((length_in_frames > 0) ? fmod(time, length_in_frames) : 0);

                currentAnimState[0].setTime(time);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eAnimate: rebuild "eAnimState" to be valid in Kao2
    ////////////////////////////////////////////////////////////////
    void eAnimate::rebuildEmptyAnimState()
    {
        clearAnimStateContainers();

        /* Reset current Anim State */

        currentAnimState[0] = eAnimState();
        animStatesCount = 1;

        /* Create new Anim State "containers" */

        animStateB = animStateA = new (eAnimState*);
        (*animStateA) = new eAnimState;

        (**animStateA).incRef();
        (**animStateB).incRef();

        /* "eAnimate" is now valid ("backwards-compatible" with Kao2) */
    }

}
