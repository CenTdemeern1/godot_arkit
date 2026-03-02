@tool
extends Node

var ARKitInterfaceSingleton_instance

func _enter_tree():
	if OS.get_name() == "iOS":
		var ARKitInterfaceSingleton_class = load("res://addons/godot_arkit/ARKitInterfaceSingleton.gd")
		ARKitInterfaceSingleton_instance = ARKitInterfaceSingleton_class.new()
		add_child(ARKitInterfaceSingleton_instance)

func _exit_tree():
	if OS.get_name() == "iOS":
		if ARKitInterfaceSingleton_instance:
			ARKitInterfaceSingleton_instance.queue_free()
