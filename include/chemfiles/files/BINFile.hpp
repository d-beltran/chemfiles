// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#ifndef CHEMFILES_BIN_FILE_HPP
#define CHEMFILES_BIN_FILE_HPP

#include <string>
#include <vector>

#include "chemfiles/files/BinaryFile.hpp"

#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

namespace chemfiles {

  /// BIN files
  class BINFile final : public LittleEndianFile {
    public:
      BINFile(std::string path, File::Mode mode);
      ~BINFile() = default;

    private:
      std::fstream file_stream;
  };

} // namespace chemfiles

#endif
