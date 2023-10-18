# SPDX-License-Identifier: GPL-3.0-only

target_sources(${PROJECT_NAME}
        PRIVATE
        BattleSimulator.h
        BattleSimulator.cpp
        GDExtensionTemplate.h
        GDExtensionTemplate.cpp
        RegisterExtension.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        "src"
)
