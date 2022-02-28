
================================================================
================================================================
<< [Zookie Wizard, Launch options] >>

 * "/AUTOPARSER <path>"
  -> launches ZookieWizard (Elephant Engine Editor) in auto-parsing mode.
   The text file from `<path>` is opened by the "ArCustomParser" module.
   The program exits after all the messages have been parsed,
   or if an error has occurred.


================================================================
================================================================
<< [Kao the Kangaroo: Round 2]: How "NodeRefLinker" masks work >>

  - starts with '/' sign :
   trim this character and search from the scene root instead of the current node.
   Current node is changed to the scene root node, and next cases are checked.

  - exactly "." :
   return the current node.

  - exactly ".." , exactly "../" :
   returns current node's parent.

  - starts with "*/" :
   trim this beginnig of the mask and search recursively using the other part of the mask.
   Current node must be "eGroup" or its child types.

  - mask contains '?' sign :
   any character from the Node's name will match it (required to use when node name contains '/').

  - mask contains '*' sign :
   works as a commonly known wildcard character that matches any number of characters.

 * The mask "..*" is invalid because of a broken implementation that makes the game crash.
  It was supposed to find the first parent that matches the sought "TypeInfo".
  Other invalid masks include: "*/*/", "/" (double slashes, slash at the beginning [excluding the scene root marking]).


================================================================
================================================================
<< [Zookie Wizard, Custom Instructions Parser] >>
<< List of types >>

 * integer: a number ranging from (-2147483648) to (+2147483647)
  -> can be written in a hexidecimal format: `0x????????`
  -> case-insensitive boolean identifiers: `TRUE` (1) or `FALSE` (0).

 * float: floating-point number
  -> can be writen in square brackets: `[ ??? ]`

 * floatPair: two floating-point numbers, acting as one argument
  -> written in square brackets with at least one space in between the numbers:
  `[1 2]`

 * floatTriple: three floating-point numbers, acting as one argument
  -> in square brackets with at least one space in between each number:
  `[1 2 3]`

 * floatQuadruple: four floating-point numbers, acting as one argument
  -> in square brackets with at least one space in between each number:
  `[1 2 3 4]`

 * string: can be writen with regular quotes: " ??? "
 or in multiple lines with ``` symbols
  -> single line strings must end on the same line
  -> multiline strings are trimmed of the whitespace characters

 * nodeRef: an identifier to previously added or located "eNode" object

 * nodeType: an identifier of one of the "eNode" derived classes in Kao2


================================================================
================================================================
<< [Zookie Wizard, Custom Instructions Parser] >>
<< List of keywords >>

 * Single line comments are marked with `//`

 * Multiline comments are marked from `/*` to `*/`

 * `FindNode nodeType nodeRef (string)`
  -> string is a mask for Kao2's "NodeRefLinker"

 * `AddNode nodeType nodeRef (parameters)`
  -> "nodeRef" is optional, use it if you want to refer to this node later
  -> "parameters" follow the "identifier = some_type" scheme,
     with at least one space between each param

 * `NodeMsg nodeRef (parameters)`

 * `NodeSetCollision nodeRef (status)`
  -> `TRUE` (1) to rebuild collision, `FALSE` (0) to destroy collision entry

 * `RemoveNode nodeRef`
  -> the node must have a valid parent, otherwise it cannot be deleted

 * `ImportWavefrontOBJ (parameters)`
  -> first argument is required, others are optional
  -> [1] string      // path to the ".obj" file,
     either absolute or relative to the current script file
  -> [2] nodeRef     // the `eGroup` parent node,
     where all the meshes will be attached to (default is parser's parent)
  -> [3] integer     // additional import flags:
     `0x01` = whether to attach the OBJ filename to all the meshes;
     `0x02` = whether to regroup meshes that have multiple materials;
     `0x04` = makes all the materials 2-sided;
     (default is ALL FLAGS ENABLED = `0x07`)
  -> [4] float       // the scale of the imported models (default is `1`)
  -> [5] floatTriple OR floatQuadruple
       // the XYZ rotation angles (default is `[0 0 0]`)
       // or XYZW Quaternion (default is `[0 0 0 1]`)
  -> [5] floatTriple // the XYZ rotation angles (default is `[0 0 0]`)
  -> [6] floatTriple // the XYZ offset (defaut is `[0 0 0]`)

 * `OptimizeBitmaps`
 * `OptimizeTextures`
 * `OptimizeMaterials nodeRef`

 * `IgnoreCurrentSymbols`

 * `SwitchAr (parameters)`
  -> first argument is required, others are optional
  -> [1] string      // path to the ".ar" file,
     either absolute or relative to the current script file
  -> [2] string      // path to the "Media" directory,
     overrides current Editor setting

 * `SaveAr (parameters)`
  -> first argument is required, others are optional
  -> [1] string      // path to the ".ar" file,
     either absolute or relative to the current script file
  -> [2] integer     // saved AR version override,
     default is the version the current archive had when it wa loaded

 * `CloseAr`

 * `GenerateEmptyScene (parameters)`
  -> all arguments are optional
  -> [1] string      // path to the "Media" directory,
     overrides current Editor setting

 * `#include string`
  -> temporarily close current textfile and open a sub-textfile containing
    parser instructions - the parser remembers all stored nodeRefs


================================================================
================================================================
<< [Zookie Wizard, Custom Instructions Parser] >>
<< Styles and advices >>

  -> identifiers are written without quotes!

  -> you can use the indenting style of your choice:

********************************

    FindNode eEnvironment GlobalEnv("/global_env")

    FindNode
      eScene
      root
      ( "/." )

    AddNode  eCylNode
    (
        parent = GlobalEnv
        name   =   "cylinder"

        radius=10.0
        height = [ 20.0 ]
    )

    AddNode eGroup test_group ( parent = x flags = 0x1000249D )

    NodeMsg test_group setName ( ```
        My Group!
    ``` )

    NodeMsg
    GlobalEnv
    clearNodes()

    AddNode
      Actor(
      script = ```

          ?actor dummy
          {

          }
      ```)

    NodeMsg root setBackgroundColor([0 1 1])

    /* etc. */

********************************


================================================================
================================================================
<< [Zookie Wizard, Custom Instructions Parser] >>
<< List of node properties and node messages >>


****************************************************************
[eNode]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  parent = nodeRef // "eGroup" (or derived class) type

  name = string

  flags = integer // simpler to write in hexadecimal format,
                  // overrides default flags

  collisionFlags = integer
    // default is 0x00FF
    // ("NO_CAMERA" + "NO_HERO" + "NO_COLLIDE" + "NO_OTHERS" + 0x0F)

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setParent
  (
    nodeRef // new parent, "eGroup" (or derived class) type
  )

  setName
  (
    string
  )

  setFlags
  (
    integer // simpler to write in hexadecimal format
  )

  setCollisionFlags
  (
    integer // simpler to write in hexadecimal format
  )

  visCtrlClear
  (
    integer // animation ID, [-1] to completely clear all keyfrmaes
  )

  visCtrlSetStatic
  (
    float // opacity value, [0] to [1]
  )

  visCtrlSetLoopType
  (
    integer // animation ID, [-1] for default controller

    integer // 0 = Constant, 1 = Cycle, 2 = Loop, 3 = Ping Pong,
            // 4 = Linear, 5 = Relative Repeat
  )

  visCtrlAddKeyframe
  (
    integer // animation ID, [-1] for default controller
    float   // time in keyframes (animations run at 30 fps)
    float   // new opacity falue for this keyframe
  )


****************************************************************
[eNode::eBezierSplineNode]

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  clearVertices
  ()

  addVertex
  (
    floatTriple // XYZ, control point on the bezier spline
    floatTriple // XYZ, cubic bezier curve param (point backwards)
    floatTriple // XYZ, cubic bezier curve param (point forwards)
    string      // point name, used with `eSplineWalk.isAtNavi(...)`
  )


****************************************************************
[eNode::eGeometry]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  materialFlags = integer
    // 0x01 = "2-SIDED",
    // 0x02 = "BLEND, 0x04 = "ADDITIVE", 0x02+0x04 = "OPAQUE",
    // 0x08 = "ALPHA_TEST"

  materialCollision = string
    // valid names: "NORMAL", "ICE", "CLIMB", "EARWALK",
    // "SWAMP", "SWAMP_WALL", "HURT_GROUND", "HURT_OBJECT",
    // "SWAMP_RAMP", "KILL_WATER", "GIRAFFE_WATER", "ICE_JUMP",
    // "SWAMP_SLOW", "HURT_LAVA", "KILL_OBJECT", "DESTROYABLE"

  materialSound = string
    // valid names: "GRASS", "WOOD", "METAL", "STONE", "SNOW", "SAND"

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  rebuildCollision
  ()

  setMaterialFlags
  (
    integer // look above
  )

  setMaterialCollision
  (
    string // look above
  )

  setMaterialSound
  (
    string // look above
  )


****************************************************************
[eNode::eGeometry::eCylNode]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  radius = float

  height = float

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setRadius
  (
    float
  )

  setHeight
  (
    float
  )


****************************************************************
[eNode::eGeometry::eGeoEdge]

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  clearEdges
  ()

  addEdge
  (
    floatTriple // XYZ, one point of a line
    floatTriple // XYZ, other point of a line
  )


****************************************************************
[eNode::eGeometry::eSphNode]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  radius = float

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setRadius
  (
    float
  )


****************************************************************
[eNode::eGroup]

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  clearNodes
  ()

  updateDrawPassFlags
  ()

  removeUnreferencedGroups
  ()


****************************************************************
[eNode::eGroup::eEnvironment]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  fogColor = floatTriple // RGB, each channel mapped from [0] do [1]

  fogStart = float

  fogEnd = float

  fogMax = float

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  clearLights
  ()

  addLight
  (
    nodeRef // "eLight" type
  )

  removeLight
  (
    nodeRef // "eLight" type
  )

  setFogColor
  (
    floatTriple // RGB
  )

  setFogStart
  (
    float
  )

  setFogEnd
  (
    float
  )

  setFogMax
  (
    float
  )


****************************************************************
[eNode::eGroup::eNPCMap]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  min = floatTriple // Boundary Box corner, XYZ

  max = floatTriple // Boundary Box corner, XYZ

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setBoundaryBox
  (
    floatTriple // XYZ min
    floatTriple // XYZ max
  )


****************************************************************
[eNode::eGroup::eTransform]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  pos = floatTriple // XYZ position, default is [0 0 0]

  rot = floatTriple OR floatQuadruple
      // XYZ Euler angles, default is [0 0 0]
      // or XYZW Quaternion, default is [0 0 0 1]

  scl = float // scale, default is 1.0

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setPos
  (
    floatTriple // new "eSRP" position, XYZ
  )

  setRot
  (
    floatTriple OR floatQuadruple // new "eSRP" rotation
                                  // XYZ Euler angles or XYZW Quaternion
  )

  setScl
  (
    float // new "eSRP" scale
  )

  ctrlClearKeyframes
  (
    integer // animation ID, [-1] to completely clear all keyfrmaes
  )

  ctrlSetStaticScale
  (
    float // static scale for all animations
  )

  ctrlSetStaticRotation
  (
    floatTriple OR floatQuadruple // static rotation for all animations
  )

  ctrlSetStaticPosition
  (
    floatTriple // static position for all animations
  )

  ctrlSetLoopType
  (
    integer // animation ID, [-1] for default controller

    integer // 0 = Constant, 1 = Cycle, 2 = Loop, 3 = Ping Pong,
            // 4 = Linear, 5 = Relative Repeat

    integer // controller selection: 1 for Scale, 2 for Rotation,
            // 4 for Position  (1+2=[3], 1+4=[5], 2+4=[6], 1+2+4=[7])
  )

  ctrlAddKeyframe
  (
    integer // animation ID, [-1] for default controller
    float // time in keyframes (animations run at 30 fps)

    floatTriple // new XYZ position
    floatTriple OR floatQuadruple // new XYZ Euler rotation
                                  // or new XYZW Quaternion (more precise)
    float // new scale

    integer // argument selection: 1 for Scale, 2 for Rotation,
            // 4 for Position  (1+2=[3], 1+4=[5], 2+4=[6], 1+2+4=[7])
  )


****************************************************************
[eNode::eGroup::eTransform::eObserver]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  fov = float

  nearPlane = float

  farPlane = float

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setFieldOfView
  (
    float
  )

  setNearPlane
  (
    float
  )

  setFarPlane
  (
    float
  )

  setSpline
  (
    nodeRef // "eBezierSplineNode" type
            // (pass no argument to disable the spline)
  )


****************************************************************
[eNode::eGroup::eTransform::eObserver::eCamera]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  followCurrentActor = boolean // 0 or 1

  target = nodeRef // "eTransform" (or derived class) type

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  followCurrentActor
  (
    boolean // 0 or 1
  )

  setTarget
  (
    nodeRef // "eTransform" (or derived class) type
            // (pass no argument to disable the target)
  )


****************************************************************
[eNode::eGroup::eTransform::ePivot]

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  animClearTracks
  ()

  animAddTrack
  (
    integer // expected ID
    string  // animation name
    float   // first keyframe
    float   // duration in keyframes
  )

  animRemoveTrack
  (
    string // animation name
  )


****************************************************************
[eNode::eGroup::eTransform::ePivot::Actor]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  script = string // Kao2 supports direct scripting
                  // if the name starts with "?"

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setScript
  (
    string // Kao2 supports direct scripting
           // if the name starts with "?"
  )


****************************************************************
[eNode::eGroup::eTransform::ePivot::eScene]

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setBackgroundColor
  (
    floatTriple // RGB
  )

  setAmbientColor
  (
    floatTriple // RGB
  )

  setCompileStrings
  (
    string // usually contains information about the level creation
           // (can contain a special ".COMPILED." directive)
    string // should contain the archive (stream/level) name
           // (full path or file extensions are optional)
  )

  clearVisPortals
  ()


****************************************************************
[eNode::eGroup::eTransform::eProxy]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  link = string // path to a ".ar" file or ".def" script file

  category = string
    // valid options: "particle", "hero", "powerup",
    // "enemy", "fluff", "geoproxy", "object"

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setLinkAndCategory
  (
    string // link
    string // category
  )


****************************************************************
[eNode::eLight]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  diffuseColor = floatTriple // RGB

  ambientColor = floatTriple // RGB

  specularColor = floatTriple // RGB

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setDiffuseColor
  (
    floatTriple // RGB
  )

  setAmbientColor
  (
    floatTriple // RGB
  )

  setSpecularColor
  (
    floatTriple // RGB
  )


****************************************************************
[eNode::eLight::eDirectionalLight]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  pos = floatTriple // XYZ

  target = nodeRef // "eTransform" (or derived class) type

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setPos
  (
    floatTriple // new XYZ position
  )

  setTarget
  (
    nodeRef // "eTransform" (or derived class) type
            // (pass no argument to disable the target)
  )


****************************************************************
[eNode::eLight::eOmniLight]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  pos = floatTriple // XYZ

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setPos
  (
    floatTriple // new XYZ position
  )


****************************************************************
[eNode::eTriMesh]

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  assertTextureMappingTypes
  (
    integer // parameters are optional: when run with no params, all texture mappings
    integer // are removed. when running with 2 or 3 args, later texture mappings
    integer // are removed. when run with more args than the GeoSet has texture mapping,
    integer // new texture mappings will be appended. Accepted values are:
            //  [0] = normal UV
            //  [1] = reflection (env) mapping
  )

  clearMorpherModifier
  ()


****************************************************************
[eNode::eZone]

 - - - - - - - - - - - - - - - -
 * `AddNode` creation parameters:

  min = floatTriple // Boundary Box corner, XYZ

  max = floatTriple // Boundary Box corner, XYZ

 - - - - - - - - - - - - - - - -
 * `NodeMsg` custom messages:

  setBoundaryBox
  (
    floatTriple // XYZ min
    floatTriple // XYZ max
  )

  clearEnterActions
  ()

  clearLeaveActions
  ()

  addEnterAction
  (
    nodeRef OR string // use a string to refer to special nodes
                      // that are not available in current scene,
                      // for example: "$hero", "$observer"

    string // the message to be sent when entering the Zone
  )

  addLeaveAction
  (
    nodeRef OR string

    string // the message to be sent when leaving the Zone
  )


================================================================
================================================================
