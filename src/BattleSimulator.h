// SPDX-License-Identifier: GPL-3.0-only

#ifndef PSVMGD_BATTLESIMULATOR_H
#define PSVMGD_BATTLESIMULATOR_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <memory>
#include <psvm/psvm.hpp>

namespace godot
{

    class BattleSimulator : public RefCounted
    {
        GDCLASS( BattleSimulator, RefCounted )

    private:
        std::unique_ptr<ShowdownService> simulator;

    protected:
        static void _bind_methods();
        void write_message( const String &p_id, const String &p_message );
        String create_battle();
        void delete_battle( const String &p_id );
        void delete_all_battles();

    public:
        BattleSimulator();
        ~BattleSimulator();
    };
}

#endif // PSVMGD_BATTLESIMULATOR_H
