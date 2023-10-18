extends Node
"""
	Test scene to demonstrate the functionality of psvmgd.
"""

# Lines to insert into the simulator for testing purposes
var data = [
	""">start {"formatid":"gen9customgame"}""",
	""">player p1 {"name":"Bot 1","team":"Samurott||AssaultVest|Torrent|knockoff,flipturn,grassknot,hydropump||85,85,85,85,85,85||||88|,,,,,Dark]Azumarill||SitrusBerry|HugePower|liquidation,aquajet,playrough,bellydrum||85,85,85,85,85,85||||82|,,,,,Water]Meowscarada||ChoiceBand|Protean|knockoff,playrough,flowertrick,uturn||85,85,85,85,85,85||||78|,,,,,Grass]Iron Valiant||LifeOrb|QuarkDrive|swordsdance,spiritbreak,knockoff,closecombat||85,85,85,85,85,85|N|||79|,,,,,Fighting]Clodsire||Leftovers|Unaware|recover,curse,earthquake,gunkshot||85,85,85,85,85,85||||81|,,,,,Ground]Ampharos||ChoiceSpecs|Static|focusblast,voltswitch,thunderbolt,dazzlinggleam||85,,85,85,85,85||,0,,,,||88|,,,,,Fairy"}""",
	""">player p2 {"name":"Bot 2","team":"Jolteon||Leftovers|VoltAbsorb|substitute,terablast,calmmind,thunderbolt||85,,85,85,85,85||,0,,,,||84|,,,,,Ice]Greedent||SitrusBerry|CheekPouch|bodyslam,earthquake,psychicfangs,swordsdance||85,85,85,85,85,85||||87|,,,,,Psychic]Lurantis||Leftovers|Contrary|knockoff,leafstorm,synthesis,superpower||85,85,85,85,85,85||||91|,,,,,Fighting]Polteageist||WhiteHerb|CursedBody|shadowball,storedpower,gigadrain,shellsmash||85,,85,85,85,85|N|,0,,,,||79|,,,,,Psychic]Gurdurr||Eviolite|Guts|drainpunch,knockoff,machpunch,bulkup||85,85,85,85,85,85||||85|,,,,,Steel]Glastrier||ChoiceBand|ChillingNeigh|iciclecrash,highhorsepower,closecombat,heavyslam||81,85,85,85,85,85|N|||86|,,,,,Fighting"}""",
]

# uuid of the active battle
var battle_id: String

# Used to color the output labels
var _output_label_settings: LabelSettings
var _input_label_settings: LabelSettings

# Control nodes used to interact with the battle
@onready var messages_vbox := $Control/MarginContainer/MainVBox/ScrollContainer/MessagesVBox
@onready var messages_scroll_container := $Control/MarginContainer/MainVBox/ScrollContainer
@onready var input_line_edit := $Control/MarginContainer/MainVBox/InputHBox/LineEdit


# Auto-scroll to the bottom of the container when adding a new line
func _handle_scroll_changed():
	messages_scroll_container.scroll_vertical = (
		messages_scroll_container.get_v_scroll_bar().max_value
	)


func _ready():
	# Auto-scroll
	messages_scroll_container.get_v_scroll_bar().connect("changed", _handle_scroll_changed)

	# Init label style settings
	_output_label_settings = LabelSettings.new()
	_output_label_settings.font_size = 18

	_input_label_settings = LabelSettings.new()
	_input_label_settings.font_size = 18
	_input_label_settings.font_color = Color.DIM_GRAY

	# Create a new battle
	battle_id = ShowdownService.create_battle()

	# Register the output callback
	ShowdownService.register_callback(battle_id, _append_message)

	# Insert lines to start a Gen IX battle
	for line in data:
		ShowdownService.write_message(battle_id, line)


func _on_input_submit(message: String):
	_append_message(message, false)

	if message[0] == ">":  # inputs should always start with >
		ShowdownService.write_message(battle_id, message)


func _append_message(message: String, is_output = true):
	var lines := message.split("\n")

	if is_output:
		for line in lines:
			var msg_line = Label.new()
			msg_line.vertical_alignment = VERTICAL_ALIGNMENT_BOTTOM
			msg_line.label_settings = _output_label_settings
			msg_line.text = line

			messages_vbox.add_child(msg_line)
	else:
		var msg_line = Label.new()
		msg_line.vertical_alignment = VERTICAL_ALIGNMENT_BOTTOM
		msg_line.label_settings = _input_label_settings
		msg_line.text = "    " + message

		messages_vbox.add_child(msg_line)


func _on_line_edit_text_submitted(new_text):
	_on_input_submit(new_text)
	input_line_edit.clear()


func _on_submit_button_pressed():
	_on_input_submit(input_line_edit.text)
	input_line_edit.clear()
