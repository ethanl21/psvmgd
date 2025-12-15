extends Node

var sim: BattleSimulator

var callback_fns = {}


# Called when the node enters the scene tree for the first time.
func _ready():
	sim = BattleSimulator.new()
	sim.connect("simulator_response", _on_response)


func _on_response(id: String, msg: String):
	if id in callback_fns.keys():
		callback_fns[id].call(msg)


func create_battle(id: String):
	sim.create_battle(id)


func register_callback(id: String, cb: Callable):
	callback_fns[id] = cb


func write_message(id: String, message: String):
	sim.write_message(id, message)
