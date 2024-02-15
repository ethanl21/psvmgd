[![GitHub](https://img.shields.io/github/license/ethanl21/psvmgd)](LICENSE) ![Build](https://github.com/ethanl21/psvmgd/actions/workflows/main.yml/badge.svg)

# psvmgd

psvmgd is a Godot 4 GDExtension addon that
uses [smogon's Pokémon Showdown Simulator](https://github.com/smogon/pokemon-showdown) provided
by [psvm](https://github.com/ethanl21/psvm).

## Usage

Install the addon from the Godot Asset Library (todo submit and document here). Enable the plugin and reload your
project, then interact with the simulator via the `ShowdownService` autoload scene. For example:

```gdscript
func on_sim_output(message: String):
    print(message)

# Create a new battle
var battle_id := ShowdownService.create_battle()

# Register an output callback function
ShowdownService.register_callback(battle_id, on_sim_output)

# Write input to the simulator
var sim_input = [ "..." ]
for line in sim_input:
    ShowdownService.write_message(battle_id, line)
```

A demo project is provided. To use it:

(outdated instructions, todo update)

1. Compile the project with Meson (see below)
2. Copy the `lib` directory and the `psvmgd.gdextension` file from the output of the previous step to
   the `demo/addons/psvmgd` directory of this repository.
3. Open `demo/project.godot` using the Godot Engine editor.

## Build

To build psvmgd, you will need the following:

- **[CMake](https://cmake.org/)** v3.22+
- C++ Compiler with at least **C++17** support (any recent compiler)
  - For Windows builds, use MinGW to cross-compile on a Linux host.
- [Node.js](https://nodejs.org/en), (build-time dependency, not required at runtime)

```bash
git clone https://github.com/ethanl21/psvmgd.git
cd psvmgd
meson setup builddir --buildtype debug # or release
meson compile -C builddir
```

#### For Windows

```bash
git clone https://github.com/ethanl21/psvmgd.git
cd psvmgd
meson setup --cross-file cross/x86_64-w64-mingw32.txt builddir --buildtype debug # or release
meson compile -C builddir
```

## Attribution

psvmgd is distributed under the MIT license.

psvmgd uses the following open-source libraries:

- [ethanl21/psvm](https://github.com/ethanl21/psvm), which is licensed under the MIT license.
- [godotengine/godot-cpp](https://github.com/godotengine/godot-cpp), which is licensed under the MIT license.
