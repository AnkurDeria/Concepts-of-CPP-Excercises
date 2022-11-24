#include "vm.h"

#include <iostream>
#include <limits>

#include "util.h"


namespace vm {


vm_state create_vm(bool debug) {
    vm_state state;
    // enable vm debugging
    state.debug = debug;


    register_instruction(state, "PRINT", [](vm_state& vmstate, const item_t /*arg*/) {
        std::cout << vmstate.stack.top() << std::endl;
        return true;
    });


    // TODO create instructions
    register_instruction(state, "LOAD_CONST", [](vm_state& vmstate, const item_t item) {
        vmstate.stack.push(item);
    return true;
        });

    register_instruction(state, "EXIT", [](vm_state& vmstate, const item_t ) {
		return false;
        });

    register_instruction(state, "POP", [](vm_state& vmstate, const item_t ) {
        if (vmstate.stack.empty()) {
            throw vm_stackfail{ std::string{"Empty stack"} };
        }
        vmstate.stack.pop();
    return true;
        });
    register_instruction(state, "ADD", [](vm_state& vmstate, const item_t) {
        
        const item_t item1 = get_item_from_stack(vmstate.stack);
		vmstate.stack.pop();
		const item_t item2 = get_item_from_stack(vmstate.stack);
        vmstate.stack.pop();
        vmstate.stack.push(item1 + item2);
		return true;
        });

    register_instruction(state, "DIV", [](vm_state& vmstate, const item_t) {
        
        const item_t item1 = get_item_from_stack(vmstate.stack);
        if(item1 == 0)
        {
            throw div_by_zero{ std::string{"Divide by zero exception"} };
        }
	    vmstate.stack.pop();
	    const item_t item2 = get_item_from_stack(vmstate.stack);
	    vmstate.stack.pop();
	    vmstate.stack.push(item2 / item1);
	    return true;
        });


    register_instruction(state, "EQ", [](vm_state& vmstate, const item_t) {
        if (vmstate.stack.empty()) {
            throw vm_stackfail{ std::string{"Empty stack"} };
        }
        const item_t item1 = get_item_from_stack(vmstate.stack);
	    vmstate.stack.pop();
	    const item_t item2 = get_item_from_stack(vmstate.stack);
	    vmstate.stack.pop();
	    vmstate.stack.push((item1 == item2)?1:0);
	    return true;
        });

    register_instruction(state, "NEQ", [](vm_state& vmstate, const item_t) {
        if (vmstate.stack.empty()) {
            throw vm_stackfail{ std::string{"Empty stack"} };
        }
        const item_t item1 = get_item_from_stack(vmstate.stack);
	    vmstate.stack.pop();
	    const item_t item2 = get_item_from_stack(vmstate.stack);
	    vmstate.stack.pop();
	    vmstate.stack.push((item1 == item2) ? 0 : 1);
	    return true;
        });

    register_instruction(state, "DUP", [](vm_state& vmstate, const item_t) {
	    vmstate.stack.push(get_item_from_stack(vmstate.stack));
	    return true;
        });

    register_instruction(state, "JMP", [](vm_state& vmstate, const item_t addr) {
        
        vmstate.pc = addr;
		return true;
        });

    register_instruction(state, "JMPZ", [](vm_state& vmstate, const item_t addr) {
        
	    if (get_item_from_stack(vmstate.stack) == 0)
	    {
	        vmstate.pc = addr;
	    }

        vmstate.stack.pop();
		return true;
        });

    register_instruction(state, "WRITE", [](vm_state& vmstate, const item_t) {
        vmstate.output += std::to_string(get_item_from_stack(vmstate.stack));
		return true;
        });

    register_instruction(state, "WRITE_CHAR", [](vm_state& vmstate, const item_t) {
        vmstate.output += get_item_from_stack(vmstate.stack);
    return true;
        });
    return state;
}

item_t get_item_from_stack(std::stack<item_t> stack)
{
    if (stack.empty()) {
        throw vm_stackfail{ std::string{"Empty stack"} };
    }
    return stack.top();
}

void register_instruction(vm_state& state, std::string_view name,
                          const op_action_t& action) {
    size_t op_id = state.next_op_id++;

    // TODO make instruction available to vm
    state.instruction_ids.emplace(name, op_id);
    //auto add = action;
    state.instruction_actions.emplace(op_id, action);
    //state.instruction_actions.at(op_id)
    state.instruction_names.emplace(op_id, name);
}


code_t assemble(const vm_state& state, std::string_view input_program) {
    code_t code;

    // convert each line separately
    for (auto& line : util::split(input_program, '\n')) {

        auto line_words = util::split(line, ' ');

        // only support instruction and one argument
        if (line_words.size() >= 3) {
            throw invalid_instruction{std::string{"more than one instruction argument: "} + line};
        }

        // look up instruction id
        auto& op_name = line_words[0];
        auto find_op_id = state.instruction_ids.find(op_name);
        if (find_op_id == std::end(state.instruction_ids)) {
            throw invalid_instruction{std::string{"unknown instruction: "} + op_name};
        }
        op_id_t op_id = find_op_id->second;

        // parse the argument
        item_t argument{0};
        if (line_words.size() == 2) {
            argument = std::stoll(line_words[1]);
        }

        // and save the instruction to the code store
        code.emplace_back(op_id, argument);
    }

    return code;
}


std::tuple<item_t, std::string> run(vm_state& vm, const code_t& code) {
    // to help you debugging the code!
    if (vm.debug) {
        std::cout << "=== running vm ======================" << std::endl;
        std::cout << "disassembly of run code:" << std::endl;
        for (const auto &[op_id, arg] : code) {
            if (not vm.instruction_names.contains(op_id)) {
                std::cout << "could not disassemble - op_id unknown..." << std::endl;
                std::cout << "turning off debug mode." << std::endl;
                vm.debug = false;
                break;
            }
            std::cout << vm.instruction_names[op_id] << " " << arg << std::endl;
        }
        std::cout << "=== end of disassembly" << std::endl << std::endl;
    }


   
    // execution loop for the machine
    while (true) {

        if(vm.pc < 0 || vm.pc >= code.size() )
        {
            throw vm_segfault{ std::string{"Invalid memory address"} };
        }
        auto& [op_id, arg] = code[vm.pc];

        if (vm.debug) {
            std::cout << "-- exec " << vm.instruction_names[op_id] << " arg=" << arg << " at pc=" << vm.pc << std::endl;
        }
        // increase the program counter here so its value can be overwritten
        // by the instruction when it executes!
        vm.pc += 1;
        // TODO execute instruction and stop if the action returns false.
        if (!vm.instruction_actions[op_id](vm, arg))
        {
            break;
        }
       
    }

    return {get_item_from_stack(vm.stack), vm.output}; // TODO: return tuple(exit value, output text)
}


} // namespace vm
