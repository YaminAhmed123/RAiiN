project(
  'mesontest',
  'cpp',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : [
    'cpp_std=vc++20',
    'b_vscrt=mt',          # matches /MT
    'buildtype=release',
    'warning_level=3',
  ],
)

# Compiler args
compiler_args = ['/arch:AVX512', '/Oi', '/Ot']
add_project_arguments(compiler_args, language: 'cpp')

# Include dirs
incdir = include_directories('include', 'Engine/tools', 'Engine/engine/vulkanaid/include', 'Engine/engine/render_engine/include')

# Dependencies
glfw_dep = declare_dependency(
  include_directories: incdir,
  link_args: [meson.project_source_root() / 'lib/glfw3_mt.lib']
)

vulkan_dep = declare_dependency(
  include_directories: incdir,
  link_args: [meson.project_source_root() / 'lib/vulkan-1.lib']
)

dependencies = [glfw_dep, vulkan_dep]

# Sources
sources = [
  'src/main2.cpp',
  'Engine/engine/vulkanaid/src/vulkanaid.cpp',
  'Engine/engine/vulkanaid/src/vulkanaidraii.cpp',
  'Engine/engine/render_engine/src/render_engine.cpp',
]

# Executable
exe = executable(
  'HATE',
  sources,
  include_directories: incdir,
  dependencies: dependencies,
  install: true,
)

test('test', exe)
