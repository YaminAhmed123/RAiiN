project(
  'mesontest',
  'cpp',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'buildtype=release',  # release build
    'cpp_std=vc++20',
  ],
)

# Compiler args
compiler_args = ['/arch:AVX512', '/Oi', '/Ot', '/MT']
add_project_arguments(compiler_args, language: 'cpp')

# Include dirs
incdir = include_directories('include', 'Engine/tools')

# Dependencies
# All deps are defined here under this comment only if the need linkage
glfw_dep = declare_dependency(
  include_directories: incdir,
  link_args: [meson.project_source_root() / 'lib/glfw3_mt.lib']
)

vulkan_dep = declare_dependency(
  include_directories: incdir,
  link_args: [meson.project_source_root() / 'lib/vulkan-1.lib']
)

dependencies = [glfw_dep, vulkan_dep]

# Executable
exe = executable(
  'HATE',
  'src/main.cpp',
  include_directories: incdir,
  dependencies: dependencies,
  install: true,
)

test('test', exe)