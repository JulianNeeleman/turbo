project(structures)

file(GLOB structures_SRC "*.hpp")

add_library(structures INTERFACE)
target_sources(structures INTERFACE ${structures_SRC})

