#include "../RuntimeState.hpp"

STEP_DEFINITION(NAMESPACE_ACCESS) {
    Object *ns = getObject(args[0]);
    if (!ns) throw std::runtime_error("Could not get namespace " + args[0]);

    Object *name = getObject(args[1]);
    bool nameValid = name && name->getType() == ValueType::STRING;

    bool argIsString = args[1][0] == args[1][args[1].size() - 1] && (args[1][0] == '"' || args[1][0] == '\'');

    if (!nameValid && !argIsString) throw std::runtime_error("Could not get name from " + args[1]);
    std::string memberName = nameValid ? name->getValueAs<std::string>() : args[1].substr(1, args[1].size() - 2);

    std::unordered_map<std::string, std::unique_ptr<Object>>& members = ns->getMembers();
    if (!members.contains(memberName)) throw std::runtime_error("Namespace " + args[0] + " does not contain member " + memberName);

    pushTemp(members.at(memberName).get());
}