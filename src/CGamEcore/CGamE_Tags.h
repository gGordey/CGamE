#ifndef CGamE_tags_h
#define CGamE_tags_h

#include <CGamE.h>

// temporary object are destroyed at the end of frame
// it's for better memory usage
#define CGE_OBJECT_TAG_TEMPORARY    0x00000001
// eternal objects cannot be destroyed
// it's to make sure that some thing important won't be accidentally destroyed
#define CGE_OBJECT_TAG_ETERNAL      0x00000002

// Destroys all objects with tag CGE_OBJECT_TAG_TEMPORARY
CGE_API void CGE_DestroyTemporaryObjectes (CGE_Context *Context);

#endif