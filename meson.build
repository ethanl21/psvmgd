project('psvmgd', ['cpp', 'c'], version: '0.1', default_options: [
    'cpp_std=c++17',
    'b_lto=true'
])

# Build Universal binary on macOS
if meson.is_subproject() == false
    if build_machine.system() == 'darwin'
        add_global_arguments(['-arch', 'x86_64', '-arch', 'arm64'], language: ['c', 'cpp', 'objcpp'])
        add_global_link_arguments(['-arch', 'x86_64', '-arch', 'arm64'], language: ['c', 'cpp', 'objcpp'])
    endif
endif

godot_dep = dependency('godot-cpp')

git_exe = find_program('git')
semver = meson.project_version().split('.') + ['0', '0', '0']
version_h_cfg = configuration_data({
    'UPPER_PROJECT_NAME': meson.project_name(),
    'PROJECT_NAME': meson.project_name(),
    'PROJECT_VERSION_MAJOR': semver[0],
    'PROJECT_VERSION_MINOR': semver[1],
    'PROJECT_VERSION_PATCH': semver[2],
    'GIT_SHORT': run_command([git_exe, 'rev-parse', '--short', 'HEAD']).stdout().strip(),
    'GIT_SHA1': run_command([git_exe, 'rev-parse', 'HEAD']).stdout().strip(),
})
version_h = configure_file(input: 'src/Version.h.in', output: 'Version.h', configuration: version_h_cfg)

gdextension_cfg = configuration_data({
    'PROJECT_NAME': meson.project_name(),
    'MODE': get_option('buildtype')
})
gdextension = configure_file(input: 'templates/template.gdextension.in', output: meson.project_name() + '.gdextension', configuration: gdextension_cfg)


# psvm dependency
psvm_proj = subproject('psvm')
psvm_dep = psvm_proj.get_variable('psvm_dep')

psvmgd_src = files('src/BattleSimulator.cpp', 'src/RegisterExtension.cpp', 'src/GDExtensionTemplate.cpp')
psvmgd_inc = include_directories('src')

# library file name
if host_machine.system() == 'darwin'
libname = '.'.join(['psvmgd', host_machine.system(), get_option('buildtype')])
else
libname = '.'.join(['psvmgd', host_machine.system(), host_machine.cpu_family(), get_option('buildtype')])
endif

psvmgd_lib = shared_library(libname, sources: [psvmgd_src, version_h], include_directories: psvmgd_inc, dependencies: [godot_dep, psvm_dep])


