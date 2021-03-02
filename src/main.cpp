
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstdio>

#include <xlang++/Layout.h>

/*
    The file is part of the lccc project. 
    Copyright (C) 2020-2021, Lightning Creations

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>

#include <Definitions.hpp>

using namespace std::string_view_literals;

enum class OptimizationLevel : std::uint8_t
{

    FirstReserved = 240,

    // -Og
    Debug = 250,
    // -Ofast, not necessarily compliant
    Fast = 252,
    // -Os
    Size = 253,
    // -Oz
    Zize = 254,
    // -Oextra, not stacked borrows compliant for rust
    Extra = 255
};

enum class DebugLevel : std::uint8_t
{
    Off = 0,
    LineTables = 1,
    Full = 2,
};

enum class LTOLevel : std::uint8_t
{
    Off = 0,
    Thin = 1,
    Full = 2
};

enum class WarningLevel
{
    Off,
    Warn,
    Error,
    Forbid
};

enum class TargetStage
{
    Preprocess,
    TypeCheck,
    XIR,
    Assembly,
    Compile,
    CompileAndLink,
    Dependencies,
    ModuleServer
};

enum class DependencyStyle
{
    Makefile,
    Ninjafile,
    CannonModules,
    XIRModules,
    // Yes, this produces a <name>.xmanifest file
    Manifest,
    // This produces .rmanifest file
    RustManifest,
    // This produces lang.rtable
    RustLangItems,
    // These produce the above outputs, but as object files.
    SharedManfiest,
    SharedRustManfiest,
    SharedRustLangItems
};

enum class OutputFormat
{
    Executable,
    Object,
    PositionIndependentExecutable,
    Shared,
    SharedWithManifest,
    SharedWithRustManifest,
    StaticWithManifest,
    StaticWithRustManifest,
};

int main(int argc, char **argv)
{
    std::optional<std::string_view> sysroot{};
    lccc::string_view target{LCCC_DEFAULT_TARGET};
    lccc::string_view cxxlib{LCCC_DEFAULT_CXXLIB};
    std::vector<lccc::string_view> input_files{};
    std::vector<std::string> link_files{};
    std::vector<lccc::string_view> preprocessor_options{};
    std::vector<lccc::string_view> linker_options{};
    std::map<lccc::string_view, std::string> source_file_map{};
    std::string_view output_file{};
    OptimizationLevel opt_lvl{};
    DebugLevel dbg_level{};
    LTOLevel lto_level{};
    std::map<std::string, bool> codegen_options{};
    std::map<std::string, WarningLevel> warnings{};
    WarningLevel global_warning_level{};
    std::string_view use_linker{};
    TargetStage target_stage{TargetStage::CompileAndLink};
    DependencyStyle dep_style{};
    OutputFormat output_format{};

    if (argc < 1)
        std::abort();
    std::string_view prg_name{argv[0]};

    std::string_view lang_name{};

    if (prg_name.substr(prg_name.rfind("rustc"sv)) == "rustc"sv)
    {
        lang_name = "rust"sv;
        std::cerr << "rustc CLI is not implemented yet\n";
        return 0;
    }
    else
    {
        if (prg_name.substr(prg_name.rfind("c++"sv)) == "c++"sv)
            lang_name = "c++"sv;
        argv++;
        for (; *argv; argv++)
        {
            std::string_view arg = *argv;
            if (arg[0] != '-')
            {
                input_files.emplace_back(arg);
                auto suffix = arg.substr(arg.rfind("."sv));
                auto main = arg.substr(0, arg.rfind("."sv));
                if ((suffix == ".o"sv) || (suffix == ".a"sv) || (suffix == ".so"sv))
                    linker_options.emplace_back(arg);
                else
                {
                    FILE *f;
                    do
                    {
                        std::tmpnam((source_file_map[arg] = std::string(L_tmpnam, ' ')).data());
                    } while (f = std::fopen(source_file_map[arg].c_str(), "wx"));
                    linker_options.emplace_back(source_file_map[arg]);
                }
            }
            else if (arg == "--version")
            {
                std::cout << "lccc v" LCCC_VERSION "\n"
                          << "Copyright (C) 2020 Lightning Creations. This program is a free software released under the terms of the GNU General Public License\n"
                          << "This program comes AS-IS, with absolutely NO WARRANTY\n";
                return 0;
            }
            else if (arg == "--help")
            {
                //TODO
                return 0;
            }
            else if (arg == "--sysroot")
            {
                if (!argv[1])
                {
                    return 1;
                }
                sysroot = *++argv;
            }
            else if (arg == "--target")
            {
                if (!argv[1])
                {
                    return 1;
                }
                target = *++argv;
            }

            else
            {
                arg = arg.substr(1);
                for (; arg.length() != 0; arg = arg.substr(1))
                {
                    if (arg[0] == 'c')
                        target_stage = TargetStage::Compile;
                    else if (arg[0] == 'S')
                        target_stage = TargetStage::Assembly;
                    else if (arg[0] == 'E')
                        target_stage = TargetStage::Preprocess;
                    else if (arg[0] == 'x')
                    {
                        arg = arg.substr(1);
                        if (arg == ""sv)
                        {
                            if (argv[1])
                                lang_name = *++argv;
                            else
                                return 1;
                        }
                        else
                            lang_name = arg;
                        break;
                    }
                }
            }
        }
    }

    for (auto &&a : source_file_map)
    {
    }
}
