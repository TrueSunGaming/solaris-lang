#include "../RuntimeState.hpp"

STEP_DEFINITION(PUSH_TEMP) {
    Object *obj = getObject(args[0]);
    if (obj) return pushTemp(obj);

    moveTemp(createObject(args[0]));
}