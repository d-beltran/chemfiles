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

BINFile::BINFile(std::string path, File::Mode mode) : LittleEndianFile(std::move(path), mode) {}