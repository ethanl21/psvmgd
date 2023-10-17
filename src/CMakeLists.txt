# SPDX-License-Identifier: Unlicense

target_sources(${PROJECT_NAME}
        PRIVATE
        GDExample.h
        GDExample.cpp
        ShowdownService.h
        ShowdownService.cpp
        GDExtensionTemplate.h
        GDExtensionTemplate.cpp
        RegisterExtension.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        "src"
)
