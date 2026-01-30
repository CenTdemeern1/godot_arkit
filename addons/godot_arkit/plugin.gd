@tool
extends EditorPlugin

func _enter_tree():
	if OS.get_name() == "iOS":
		add_autoload_singleton("ARKitInterfaceSingleton", "autoload.gd")

func _exit_tree():
	if OS.get_name() == "iOS":
		remove_autoload_singleton("ARKitInterfaceSingleton")
