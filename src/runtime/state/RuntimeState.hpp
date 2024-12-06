#pragma once

#include <stack>
#include <optional>
#include "../../universal/assembly/Instruction.hpp"
#include "FunctionReturnState.hpp"
#include "../data/scope/Scope.hpp"
#include "AbstractFunctionCaller.hpp"
#include "TempStack.hpp"

#define STEP_FUNCTION(x) step##x(const std::vector<std::string>& args)
#define STEP_DECLARATION(x) void STEP_FUNCTION(x)
#define STEP_DEFINITION(x) void RuntimeState::STEP_FUNCTION(x)
#define OBJ_OPERATION(lhs, rhs, op, valType, type) std::make_unique<Object>(ValueType::valType, new type(lhs->getValueAs<type>() op rhs->getValueAs<type>()))

class RuntimeState : public AbstractFunctionCaller {
    private:
        std::vector<Instruction> instructions;
        std::stack<FunctionReturnState> returnStack;
        size_t line = 0;
        std::unique_ptr<Scope> globalScope;
        Scope *activeScope = nullptr;
        std::vector<std::unique_ptr<Scope>> scopes;
        TempStack tempStack;

        static std::vector<Instruction> load(const std::string& filename);
        std::vector<Object *> parseArgs(std::vector<std::string> args);

        std::unique_ptr<Object> createObject(const std::string& val);
        Object *getOrCreateObject(const std::string& val, std::vector<std::unique_ptr<Object>>& created);
        
        ValueType determineType(const std::vector<std::string>& args) const;

        STEP_DECLARATION(DECLARE);
        STEP_DECLARATION(PUSH_TEMP);
        STEP_DECLARATION(POP_TEMP);
        STEP_DECLARATION(DEFINE_FUNCTION);
        STEP_DECLARATION(END_DEFINE_FUNCTION);
        STEP_DECLARATION(ADD_FUNCTION_ARGUMENT);
        STEP_DECLARATION(CALL);
        STEP_DECLARATION(RETURN);
        STEP_DECLARATION(NAMESPACE_ACCESS);
        STEP_DECLARATION(ADD);
        STEP_DECLARATION(SUBTRACT);
        STEP_DECLARATION(MULTIPLY);
        STEP_DECLARATION(DIVIDE);
        STEP_DECLARATION(MODULO);
        STEP_DECLARATION(EXPONENT);
        STEP_DECLARATION(SET);
        
    public:
        RuntimeState(const std::string& filename);

        size_t getLine() const;
        void step();
        void jump(size_t line) override;
        void ret();
        void pushReturn(size_t functionID) override;
        void pushTemp(Object *obj);
        void moveTemp(Object *obj);
        void moveTemp(std::unique_ptr<Object> obj);
        void popTemp();
        Object *getTemp(size_t idx);
        std::vector<Object *> getTemp(const std::vector<size_t>& idxs);
        Object *getReturnObject();
        Object *getObject(const std::string& name);
        void setObject(const std::string& name, Object *value) override;
        Scope *getGlobalScope();
        Scope *getCurrentScope();
        void createScope() override;

        SolarisFunction *getFunction(size_t id);
};