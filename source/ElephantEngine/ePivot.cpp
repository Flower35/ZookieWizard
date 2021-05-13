#include <ElephantEngine/ePivot.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/eTrack.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePivot interface
    // <kao2.00485CC0> (constructor)
    // <kao2.004860E0> (destructor)
    ////////////////////////////////////////////////////////////////

    extern TypeInfo E_PIVOT_TYPEINFO
    (
        E_PIVOT_ID,
        "ePivot",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new ePivot;
        }
    );

    TypeInfo* ePivot::getType() const
    {
        return &E_PIVOT_TYPEINFO;
    }

    ePivot::ePivot()
    : eTransform()
    {
        flags |= 0x00071000;
    }

    ePivot::~ePivot()
    {}


    ////////////////////////////////////////////////////////////////
    // ePivot: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePivot::createFromOtherObject(const ePivot &other)
    {
        animations = other.animations;
    }

    ePivot::ePivot(const ePivot &other)
    : eTransform(other)
    {
        createFromOtherObject(other);
    }

    ePivot& ePivot::operator = (const ePivot &other)
    {
        if ((&other) != this)
        {
            eTransform::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePivot::cloneFromMe() const
    {
        return new ePivot(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: serialization
    // <kao2.00486660>
    ////////////////////////////////////////////////////////////////
    void ePivot::serialize(Archive &ar)
    {
        int32_t a;

        eTransform::serialize(ar);

        if (ar.getVersion() < 0x7D)
        {
            throw ErrorMessage
            (
                "ePivot::serialize():\n" \
                "ar.version() 125 required!"
            );
        }

        /* Animations */
        animations.serialize(ar);

        /* Unknown group */
        a = 0x00;
        ar.readOrWrite(&a, 0x04);
        if (0 != a)
        {
            throw ErrorMessage
            (
                "ePivot::serialize():\n" \
                "non-empty group member is not supported!"
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: export readable structure
    ////////////////////////////////////////////////////////////////
    void ePivot::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        int32_t a;
        eNode* child_node;
        eTrack* test_track;

        char bufor[128];
        eString test_str;

        /* "eTransform": parent class */

        eTransform::writeStructureToTextFile(file, indentation, true);

        /* "ePivot": additional info */

        for (a = 0; a < animations.tracks.getSize(); a++)
        {
            if (nullptr != (test_track = (eTrack*)animations.tracks.getIthChild(a)))
            {
                sprintf_s
                (
                    bufor, 128,
                    " - track [%d]: \"%s\" [%.2f, %.2f]",
                    a,
                    test_track->getStringRepresentation().getText(),
                    test_track->getStartFrame(),
                    test_track->getEndFrame()
                );

                ArFunctions::writeIndentation(file, indentation);
                file << bufor;
                ArFunctions::writeNewLine(file, 0);
            }
        }

        /****************/

        if (!group_written)
        {
            MACRO_KAO2_GROUP_FOREACH_NODE({ child_node->writeStructureToTextFile(file, (indentation + 1), false); })
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: update before rendering [[vptr]+0x38]
    ////////////////////////////////////////////////////////////////
    void ePivot::updateBeforeRendering(eDrawContext &draw_context)
    {
        eAnimate* previous_animate = draw_context.getAnimateObject();

        if (GUI::drawFlags::DRAW_FLAG_ANIMS & draw_context.getDrawFlags())
        {
            animations.setAnimation(GUI::animationID, GUI::timerGetFrames());
        }

        draw_context.setAnimateObject(&animations);

        eTransform::updateBeforeRendering(draw_context);

        draw_context.setAnimateObject(previous_animate);
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: render this node
    ////////////////////////////////////////////////////////////////
    void ePivot::renderNode(eDrawContext &draw_context) const
    {
        eAnimate* previous_animate = draw_context.getAnimateObject();

        draw_context.setAnimateObject(&animations);

        eTransform::renderNode(draw_context);

        draw_context.setAnimateObject(previous_animate);
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: preparing just-created node
    ////////////////////////////////////////////////////////////////
    void ePivot::editingNewNodeSetup()
    {
        animations.rebuildEmptyAnimState(false);

        eTransform::editingNewNodeSetup();
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: rebuild "eAnimState"(s) in "eAnimate"
    ////////////////////////////////////////////////////////////////
    void ePivot::rebuildEmptyAnimState(bool is_root)
    {
        animations.rebuildEmptyAnimState(is_root);
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: custom TXT parser
    ////////////////////////////////////////////////////////////////
    int32_t ePivot::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test[2];
        float dummy_floats[2];
        eString dummy_name;

        if (1 != (test[0] = eTransform::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test[0];
        }

        if (message.compareExact("animClearTracks", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "animClearTracks", 0);
                return 2;
            }

            /********************************/

            animations.tracks.clear();
            return 0;
        }
        else if (message.compareExact("animAddTrack", true))
        {
            if (4 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "animAddTrack", 3);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "animAddTrack", 1, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[0]));

            if ((test[1] = animations.tracks.getSize()) != test[0])
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"animAddTrack\" message: expected track ID %d, but the resulting ID would be %d...", test[0], (1 + test[1]));
                return 2;
            }

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "animAddTrack", 2, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[1].getValue(&dummy_name);

            /********************************/

            if (params[2].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[2].getValue(&(test[0]));
                dummy_floats[0] = (float)test[0];
            }
            else if (params[2].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[2].getValue(&(dummy_floats[0]));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "animAddTrack", 3, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (params[3].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[3].getValue(&(test[0]));
                dummy_floats[1] = (float)test[0];
            }
            else if (params[3].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[3].getValue(&(dummy_floats[1]));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "animAddTrack", 4, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            animAddTrack(dummy_name.trimWhitespace(), dummy_floats[0], dummy_floats[1]);
            return 0;
        }
        else if (message.compareExact("animRemoveTrack", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "animRemoveTrack", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "animRemoveTrack", 0, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[0].getValue(&dummy_name);

            /********************************/

            animRemoveTrack(dummy_name.trimWhitespace());
            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: changing the number of animation tracks
    ////////////////////////////////////////////////////////////////

    void ePivot::animClearTracks()
    {
        animations.tracks.clear();
    }

    void ePivot::animAddTrack(eString anim_name, float first_frame, float frames_count)
    {
        eTrack* dummy_track = new eTrack;

        if (first_frame < 0)
        {
            first_frame = 0;
        }

        if (frames_count < 0)
        {
            frames_count = (-frames_count);
        }

        dummy_track->setName(anim_name);
        dummy_track->setStartFrame(first_frame);
        dummy_track->setEndFrame(first_frame + frames_count);

        animations.tracks.appendChild(dummy_track);

        ctrlExpandAnimTracks(animations.tracks.getSize());
    }

    void ePivot::animRemoveTrack(eString anim_name)
    {
        int result = (-1);
        eTrack* dummy_track;

        for (int i = 0; (result < 0) && (i < animations.tracks.getSize()); i++)
        {
            dummy_track = (eTrack*)animations.tracks.getIthChild(i);

            if ((nullptr != dummy_track) && (dummy_track->getStringRepresentation().compareExact(anim_name, true)))
            {
                result = i;
            }
        }

        if (result >= 0)
        {
            animations.tracks.deleteIthChild(result);

            ctrlRemoveAnimTrack(result);
        }
    }

}
