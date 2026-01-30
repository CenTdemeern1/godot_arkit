@tool
extends Node


var ArKitInterfaceSingleton_instance

func _enter_tree():
	if OS.get_name() == "iOS":
		var ArKitInterfaceSingleton_class = load("ARKitInterfaceSingleton.gd")
		ArKitInterfaceSingleton_instance = ArKitInterfaceSingleton_class.new()
		add_child(ArKitInterfaceSingleton_instance)

func _exit_tree():
	if OS.get_name() == "iOS":
		if ArKitInterfaceSingleton_instance:
			ArKitInterfaceSingleton_instance.queue_free()
