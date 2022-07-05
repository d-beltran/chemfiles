// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#ifndef CHEMFILES_BIN_FORMAT_HPP
#define CHEMFILES_BIN_FORMAT_HPP

#include <string>

#include "chemfiles/File.hpp"
#include "chemfiles/Format.hpp"

#include "chemfiles/files/BINFile.hpp"

    namespace chemfiles {
    class Frame;
    class FormatMetadata;

    /// BIN file format reader and writer
    class BINFormat final: public Format {
        public:
            BINFormat(std::string path, File::Mode mode, File::Compression compression);

            void read_step(size_t step, Frame& frame) override;
            void read(Frame& frame) override;
            size_t nsteps() override;
            void set_natoms(size_t natoms) override;

            size_t n_atoms;
            size_t bytes_per_frame;

        private:
            /// Associated binary file
            BINFile file_;
    };

    template<> const FormatMetadata& format_metadata<BINFormat>();

} // namespace chemfiles

#endif
