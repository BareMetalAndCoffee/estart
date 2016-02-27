project(EEPROM_EXAMPLE)

include_directories(
    ${STATE4C_SOURCE_DIR}
)

add_executable(eeprom
    main.c
)

target_link_libraries(eeprom state4c)
