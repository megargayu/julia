project('julia', 'cpp')

sources = [
  'src/main.cpp',
  'src/shader.cpp',
  'src/configSwitcher.cpp'
]

headers = [
  'include/shader.hpp',
  'include/configSwitcher.hpp'
]

headersDep = declare_dependency(
    sources : headers
)

cpp = meson.get_compiler('cpp')
include = include_directories('include')

sfml_dep = dependency('sfml')

# load yaml-cpp
cmake = import('cmake')
yaml_dep = cmake.subproject('yaml-cpp-0.8.0').dependency('yaml-cpp')

executable(
  'demo', 
  sources : sources, 
  dependencies : [sfml_dep, yaml_dep, headersDep], 
  include_directories : include
)
