#pragma once
// SPDX-License-Identifier: GPL-3.0-only

#include "godot_cpp/classes/object.hpp"

namespace godot
{
    class ClassDB;
};

class GDExtensionTemplate : public godot::Object
{
    GDCLASS( GDExtensionTemplate, godot::Object )

public:
    static godot::String version();

private:
    static void _bind_methods();
};
