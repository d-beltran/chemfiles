// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#include <string>
#include <vector>

#include "chemfiles/files/BINFile.hpp"

#include "chemfiles/error_fmt.hpp"
#include "chemfiles/external/span.hpp"
#include "chemfiles/warnings.hpp"

#include <iostream>

using namespace chemfiles;

BINFile::BINFile(std::string path, File::Mode mode) : LittleEndianFile(std::move(path), mode) {
    // Open the stream towards our target file
    // The second argument of the function are flags to set the stream as an input binary stream (respectively)
    std::string file_path = File::path();
    file_stream.open(file_path, std::ios_base::in | std::ios::binary);
    // If we could not open the stream then stop here
    if (!file_stream.is_open()) {
        std::cout << "Unable to open the file " << file_path << std::endl;
    }
}

// A 32 bit float will always size 4 bytes
int f32_byte_size = 4;
// Read the next 32 bit float in the file stream
// NEVER FORGET: We are using our own implementation since the builtin chemfiles read_f32 function from little endian files
//  has a remarkable accuracy error
void BINFile::read_f32_accurate(float* data) {
    file_stream.read((char*)&(*data), f32_byte_size);
}