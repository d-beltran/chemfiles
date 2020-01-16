// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#include <catch.hpp>
#include <chemfiles.hpp>
using namespace chemfiles;

TEST_CASE() {
    // [no-run]
    // [example]
    auto trajectory_memory = Trajectory::memory_writer("SMI");

    auto ethane = Frame();
    ethane.add_atom(Atom("C"), {0, 0, 0});
    ethane.add_atom(Atom("C"), {0, 0, 0});
    ethane.add_bond(0, 1, Bond::SINGLE);

    trajectory_memory.write(ethane);

    CHECK(*(trajectory_memory.internal_file()) == "CC\n");

    // This function will return nullopt if opened with a regular file
    auto trajectory_file = Trajectory("ethane.smi", 'w');
    CHECK(trajectory_file.internal_file() == nullopt);

    // [example]
}
