#include "../RuntimeState.hpp"

STEP_DEFINITION(PUSH_TEMP) {
    Object *obj = getObject(args[0]);
    if (globalScope->ownsObject(obj)) return pushTemp(obj);

    moveTemp(obj ? obj->clone() : createObject(args[0]));
}