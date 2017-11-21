project(geometry)

file(GLOB geometry_SRC "*.hpp")

add_library(geometry INTERFACE)
target_sources(geometry INTERFACE ${geometry_SRC})

