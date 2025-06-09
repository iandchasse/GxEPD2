file(GLOB_RECURSE GXEPD2_SOURCES "src/*.cpp" "idf/*.cpp")

idf_component_register(
    SRCS ${GXEPD2_SOURCES}
    INCLUDE_DIRS "src" "idf"
    REQUIRES driver freertos
)
