// SPDX-License-Identifier: GPL-3.0-only

/// @file
/// BattleSimulator GDScript class implementation

#include "BattleSimulator.h"

using namespace godot;

void BattleSimulator::_bind_methods()
{
    ClassDB::bind_method( D_METHOD( "write_message", "p_id", "p_message" ),
                          &BattleSimulator::write_message );
    ClassDB::bind_method( D_METHOD( "create_battle" ), &BattleSimulator::create_battle );

    ADD_SIGNAL( MethodInfo( "simulator_response", PropertyInfo( Variant::STRING, "id" ),
                            PropertyInfo( Variant::STRING, "message" ) ) );
}

BattleSimulator::BattleSimulator() : simulator( new ShowdownService() )
{
    std::function<void( std::string, std::string )> callback = [this]( const std::string &id,
                                                                       const std::string &msg ) {
        emit_signal( "simulator_response", String( id.c_str() ), String( msg.c_str() ) );
    };

    this->simulator->setSimulatorOnResponseCallback( callback );
}

BattleSimulator::~BattleSimulator()
{
}

/**
 * @brief Creates a new battle
 * @return UUID that represents the new battle
 */
String BattleSimulator::create_battle()
{
    auto uuid = this->simulator->CreateBattle();
    return { uuid.c_str() };
}

/**
 * @brief Writes a message to the simulator
 * @param p_id UUID of the battle to write to
 * @param p_message message to insert into the battle stream
 */
void BattleSimulator::write_message( const String &p_id, const String &p_message )
{
    std::string id( p_id.utf8().get_data() );
    std::string msg( p_message.utf8().get_data() );

    this->simulator->WriteMessage( id, msg );
}