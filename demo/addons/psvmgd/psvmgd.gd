@tool
extends EditorPlugin

const AUTOLOAD_NAME = "ShowdownService"


func _enter_tree():
	# Initialization of the plugin goes here.
	add_autoload_singleton(AUTOLOAD_NAME, "res://addons/psvmgd/autoload/showdown_service.tscn")


func _exit_tree():
	# Clean-up of the plugin goes here.
	remove_autoload_singleton(AUTOLOAD_NAME)
