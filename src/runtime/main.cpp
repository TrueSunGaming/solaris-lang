#include "state/RuntimeState.hpp"
#include <stdexcept>

int main(int argc, char *argv[]) {
    if (argc < 2) throw std::runtime_error("Please provide an assembly file as an argument");

    RuntimeState runtime = RuntimeState(argv[1]);
}