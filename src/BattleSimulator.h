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
        std::unique_ptr<psvm::ShowdownService> simulator;

    protected:
        static void _bind_methods();
        void write_message( const String &p_id, const String &p_message );
        void create_battle( const String &p_id );
        void delete_battle( const String &p_id );
        void delete_all_battles();

    public:
        BattleSimulator();
        ~BattleSimulator();
    };
}

#endif // PSVMGD_BATTLESIMULATOR_H
