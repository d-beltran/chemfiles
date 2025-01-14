// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#include "chemfiles/File.hpp"
#include "chemfiles/Frame.hpp"
#include "chemfiles/FormatMetadata.hpp"

#include "chemfiles/files/BINFile.hpp"
#include "chemfiles/formats/BIN.hpp"

#include <iostream>

using namespace chemfiles;

template<> const FormatMetadata& chemfiles::format_metadata<BINFormat>() {
    static FormatMetadata metadata;
    metadata.name = "BIN";
    metadata.extension = ".bin";
    metadata.description = "BIN format";
    metadata.reference = "https://bioexcel-cv19.bsc.es/#/help";

    metadata.read = true;
    metadata.write = false;
    metadata.memory = false;

    metadata.positions = true;
    metadata.velocities = false;
    metadata.unit_cell = false;
    metadata.atoms = false;
    metadata.bonds = false;
    metadata.residues = false;
    return metadata;
}

// Set the bytes size of each coordinate (32 bit floats)
const int bytes_per_coord = 4;
// Set the number of coordinates per atom (x, y, z)
const int coords_per_atom = 3;
// Set a float (by default 32 bits) to store the coordinates read by the stream
float buffer;

BINFormat::BINFormat(std::string path, File::Mode mode, File::Compression compression)
    : file_(std::move(path), mode) {}

void BINFormat::read_step(size_t step, Frame& frame) {
    // Calculated the offset of bytes given the specified frame
    size_t offset = bytes_per_frame * step;
    // Move to the calculated position in the trajectory file
    file_.seek(offset);
    // Start to read the trajectory file
    read(frame);
}

void BINFormat::read(Frame& frame) {
    // Reserve space in the current frame for the expected number of atoms
    frame.resize(n_atoms);
    // Set the frame positions (i.e. atom coordinates)
    auto positions = frame.positions();
    for (size_t i = 0; i < n_atoms; i++) {
        double x = 0, y = 0, z = 0;
        // Get the next coordinate (x)
        file_.read_f32(&buffer, 1); // 1 stands for 4 bytes already
        x = static_cast<double>(buffer);
        // Get the next coordinate (y)
        file_.read_f32(&buffer, 1); // 1 stands for 4 bytes already
        y = static_cast<double>(buffer);
        // Get the next coordinate (z)
        file_.read_f32(&buffer, 1); // 1 stands for 4 bytes already
        z = static_cast<double>(buffer);
        // Add coordinates to the current frame position
        positions[i][0] = x;
        positions[i][1] = y;
        positions[i][2] = z;
    }
}

size_t BINFormat::nsteps() {
    if (bytes_per_frame == 0) {
        return 0;
    }
    return file_.file_size() / bytes_per_frame;
}

void BINFormat::set_natoms(size_t natoms) {
    // Set the number of atoms
    n_atoms = natoms;
    // Calculate the size of bytes for each frame
    bytes_per_frame = n_atoms * coords_per_atom * bytes_per_coord;
}