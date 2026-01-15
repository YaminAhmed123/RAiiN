project(
  'mesontest',
  'cpp',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : [
    'cpp_std=c++20',
    'buildtype=release',
    'warning_level=3',
  ],
)

# Platform-specific compiler args
compiler_args = []
cpp = meson.get_compiler('cpp')

if cpp.get_id() == 'msvc'
  compiler_args += ['/arch:AVX512', '/Oi', '/Ot', '/wd4100', '/wd4189']
elif cpp.get_id() == 'clang'
  compiler_args += ['-march=native', '-O3', '-Wno-unused-parameter']
else # GCC
  compiler_args += ['-march=native', '-O3', '-Wno-unused-parameter']
endif

add_project_arguments(compiler_args, language: 'cpp')

# Include dirs
incdir = include_directories(
  'include',
  'Engine/tools',
  'Engine/engine/vulkanaid/include',
  'Engine/engine/render_engine/include',
  'Engine/tools',
)

# Dependencies
if host_machine.system() == 'windows'
  glfw_dep = declare_dependency(
    include_directories: incdir,
    link_args: [meson.project_source_root() / 'lib/glfw3_mt.lib']
  )
  vulkan_dep = declare_dependency(
    include_directories: incdir,
    link_args: [meson.project_source_root() / 'lib/vulkan-1.lib']
  )
else
  # On Linux, use pkg-config to find glfw3 and Vulkan
  glfw_dep = dependency('glfw3', required: true)
  vulkan_dep = dependency('vulkan', required: true)
endif

dependencies = [glfw_dep, vulkan_dep]

# Sources
sources = [
  'src/main2.cpp',
  'Engine/engine/vulkanaid/src/vulkanaid.cpp',
  'Engine/engine/vulkanaid/src/vulkanaidraii.cpp',
  'Engine/engine/vulkanaid/src/createvkinstance.cpp',
  'Engine/engine/vulkanaid/src/setupvkvalidationlayer.cpp',
  'Engine/engine/vulkanaid/src/createvksurface.cpp',
  'Engine/engine/vulkanaid/src/findqueuefamilyindices.cpp',
  'Engine/engine/vulkanaid/src/selectvkphysicaldevice.cpp',
  'Engine/engine/vulkanaid/src/createvklogicaldevice.cpp',
  'Engine/engine/vulkanaid/src/setupvkswapchain.cpp',
  'Engine/engine/render_engine/src/render_engine.cpp',
  'Engine/engine/render_engine/src/graphics_pipeline.cpp',
  'Engine/engine/render_engine/src/render_pass.cpp',
  'Engine/engine/render_engine/src/create_framebuffers.cpp',
  'Engine/engine/render_engine/src/create_commandpoll.cpp',
  'Engine/engine/render_engine/src/create_commandbuffer.cpp',
  'Engine/engine/render_engine/src/draw_frame.cpp',
  'Engine/engine/render_engine/src/create_sync_objects.cpp',
  'Engine/engine/render_engine/src/swapchain_recreation.cpp',
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
