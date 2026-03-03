import os

env = SConscript("godot-cpp/SConstruct").Clone()

# Add support for generating compilation database files
#env.Tool("compilation_db")
#compiledb = env.CompilationDatabase("compile_commands.json")
#env.Alias("compiledb", compiledb)

def is_ios():
    return env["platform"] == "ios"

if is_ios():
    # Compile flags
    env.Append(LINKFLAGS="-framework Foundation")
    env.Append(LINKFLAGS="-framework UIKit")
    env.Append(LINKFLAGS="-framework ARKit")
    env.Append(LINKFLAGS="-framework AVFoundation")
    env.Append(LINKFLAGS="-framework CoreGraphics")
    #env.Append(LINKFLAGS="-framework CoreMotion")
    env.Append(LINKFLAGS="-framework CoreVideo")
else:
    # Stub build on everything except iOS
    env.Append(CPPDEFINES="ARKIT_DUMMY")

# Compile with debugging symbols
if ARGUMENTS.get("debugging_symbols") == 'true':
    if "-O2" in env["CCFLAGS"]:
        env["CCFLAGS"].remove("-O2")
    env.Append(CCFLAGS=["-g", "-O0"])

# Setup variant build dir for each setup
def remove_prefix(s, prefix):
    return s[len(prefix):] if s.startswith(prefix) else s

build_dir = "build/{}".format(remove_prefix(env["suffix"], "."))
VariantDir(build_dir, 'src', duplicate=False)

if is_ios():
    # Build Objective-C GDExtension
    source_directories = ["."]
    sources = [
        Glob("{}/{}/*.cpp".format(build_dir, directory)) + Glob("{}/{}/*.mm".format(build_dir, directory))
        for directory in source_directories
    ]
else:
    # Build dummy
    # This happens to currently be all the .cpp files...
    sources = ["src/main.cpp", "src/arkit_module.cpp", "src/dummy_arkit_interface.cpp", "src/arkit_anchor_mesh.cpp", "src/arkit_anchor_image.cpp"]

library = env.SharedLibrary(
    "addons/godot_arkit/build/libobjcgdextension{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
    source=sources,
)

Default(library)
