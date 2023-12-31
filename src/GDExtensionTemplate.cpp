// SPDX-License-Identifier: GPL-3.0-only

#include "godot_cpp/core/class_db.hpp"

#include "GDExtensionTemplate.h"
#include "Version.h"

/// @file
/// GDExtensionTemplate example implementation.

/*!
@brief Get the version string for this extension.

@details
The version string is generated by cmake using src/Version.h.in.

It uses the form "<project name> <last tag>-<# commits since last tag>-<short commit hash>".
If there are no commits since the last tag, only the tag is shown.

@return The version string (e.g. "Foo v1.2.3-gdedbd01").
*/
godot::String GDExtensionTemplate::version()
{
    return VersionInfo::VERSION_STR.data();
}

/// Bind our methods so GDScript can access them.
void GDExtensionTemplate::_bind_methods()
{
    godot::ClassDB::bind_static_method( "GDExtensionTemplate", godot::D_METHOD( "version" ),
                                        &GDExtensionTemplate::version );
}
