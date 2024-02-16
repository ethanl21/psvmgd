project('godot-cpp', 'cpp', version: '4.2',
  default_options: ['cpp_std=c++17'])

add_project_arguments([
  '-Wno-unused-parameter',
  '-Wno-extra-semi',
  '-Wno-gnu-anonymous-struct',
  '-Wno-nested-anon-types',

  ], language: 'cpp', )

fs = import('fs')

includes = [
      'include/',
      'gdextension/',
      'gen/include/',
]

python3_exe = find_program('python', 'python3')

# Determine the names of the generated source files
generated_sources = run_command([python3_exe, '-c', 'import binding_generator; binding_generator.print_file_list("gdextension/extension_api.json", "", headers=False, sources=True)'], capture: true, check: true).stdout().strip().replace('gen/include/godot_cpp/core/ext_wrappers.gen.inc;', '').split(';')

# Find all the non-generated source files
core_sources = run_command([python3_exe, 'core_src_grabber.py', 'src'], check: true, capture: true).stdout().strip().split(';')

# binding_generator generates all sources and headers in one step,
# so this is a hack to prevent Meson from erroring out when
# gen/include does not exist
if not fs.exists(generated_sources[0])
  message('Generating Godot classes by api.json')
  run_command('meson-bindings-generator.py', 'gdextension/extension_api.json', '.', check: true)
endif

godot_cpp_lib = static_library(
  'godot-cpp',
  core_sources + generated_sources,
  include_directories: include_directories(includes)
)

godot_cpp_dep = declare_dependency(
  include_directories: include_directories(includes),
  link_with: [godot_cpp_lib]
)

meson.override_dependency(
  'godot-cpp',
  godot_cpp_dep)
