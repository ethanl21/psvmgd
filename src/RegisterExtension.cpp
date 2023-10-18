#include "gdextension_interface.h"

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

#include "BattleSimulator.h"
#include "GDExtensionTemplate.h"

using namespace godot;

/// @file
/// Register our classes with Godot.

/// @brief Called by Godot to let us register our classes with Godot.
///
/// @param p_level the level being initialized by Godot
///
/// @see GDExtensionInit
void initialize_gdextension_types( ModuleInitializationLevel p_level )
{
    if ( p_level != MODULE_INITIALIZATION_LEVEL_SCENE )
    {
        return;
    }
    ClassDB::register_class<BattleSimulator>();
    ClassDB::register_class<GDExtensionTemplate>();
}

/// @brief Called by Godot to let us do any cleanup.
///
/// @see GDExtensionInit
void uninitialize_gdextension_types( ModuleInitializationLevel p_level )
{
    if ( p_level != MODULE_INITIALIZATION_LEVEL_SCENE )
    {
        return;
    }
}

extern "C"
{
    /// @brief This is the entry point for the shared library.
    ///
    /// @note The name of this function must match the "entry_symbol" in
    /// templates/template.*.gdextension.in
    ///
    /// @param p_get_proc_address the interface (need more info)
    /// @param p_library the library (need more info)
    /// @param r_initialization the intialization (need more info)
    ///
    /// @returns GDExtensionBool
    GDExtensionBool GDE_EXPORT GDExtensionInit(
        GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization )
    {
        GDExtensionBinding::InitObject init_obj( p_get_proc_address, p_library, r_initialization );
        init_obj.register_initializer( initialize_gdextension_types );
        init_obj.register_terminator( uninitialize_gdextension_types );
        init_obj.set_minimum_library_initialization_level( MODULE_INITIALIZATION_LEVEL_SCENE );

        return init_obj.init();
    }
}
