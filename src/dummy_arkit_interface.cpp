#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/core/version.hpp>
#include <godot_cpp/classes/surface_tool.hpp>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/cubemap.hpp>

#include "arkit_interface.h"

#include <dlfcn.h>

#ifdef ARKIT_DUMMY
ARKitInterface::ARKitInterface() {
	initialized = false;
	session_was_started = false;
	plane_detection_is_enabled = false;
	light_estimation_is_enabled = false;
	z_near = 0.01;
	z_far = 1000.0;
	projection.set_perspective(60.0, 1.0, z_near, z_far, false);
	anchors = NULL;
	num_anchors = 0;
	ambient_intensity = 1.0;
	ambient_color_temperature = 1.0;
	exposure_offset = 0.0;
	image_width[0] = 0;
	image_width[1] = 0;
	image_height[0] = 0;
	image_height[1] = 0;
}

ARKitInterface::~ARKitInterface() {
	remove_all_anchors();

	// and make sure we cleanup if we haven't already
	if (_is_initialized()) {
		_uninitialize();
	}
}

void ARKitInterface::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_notification", "what"), &ARKitInterface::_notification);

	ClassDB::bind_method(D_METHOD("set_light_estimation_is_enabled", "enable"), &ARKitInterface::set_light_estimation_is_enabled);
	ClassDB::bind_method(D_METHOD("get_light_estimation_is_enabled"), &ARKitInterface::get_light_estimation_is_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "light_estimation"), "set_light_estimation_is_enabled", "get_light_estimation_is_enabled");

	ClassDB::bind_method(D_METHOD("set_image_tracking_is_enabled", "enable"), &ARKitInterface::set_image_tracking_is_enabled);
	ClassDB::bind_method(D_METHOD("get_image_tracking_is_enabled"), &ARKitInterface::get_image_tracking_is_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "image_tracking"), "set_image_tracking_is_enabled", "get_image_tracking_is_enabled");
	
	ClassDB::bind_method(D_METHOD("set_reference_images", "images", "physical_widths"), &ARKitInterface::set_reference_images);
	
	ClassDB::bind_method(D_METHOD("get_ambient_intensity"), &ARKitInterface::get_ambient_intensity);
	ClassDB::bind_method(D_METHOD("get_ambient_color_temperature"), &ARKitInterface::get_ambient_color_temperature);
	ClassDB::bind_method(D_METHOD("get_exposure_offset"), &ARKitInterface::get_exposure_offset);

	ClassDB::bind_method(D_METHOD("raycast", "screen_coord"), &ARKitInterface::raycast);

	ClassDB::bind_method(D_METHOD("get_image_planes"), &ARKitInterface::get_image_planes);

	ClassDB::bind_method(D_METHOD("get_environment_map"), &ARKitInterface::get_environment_map);
}

void ARKitInterface::start_session() {}
void ARKitInterface::stop_session() {}
bool ARKitInterface::_get_anchor_detection_is_enabled() const {
	return false;
}
void ARKitInterface::_set_anchor_detection_is_enabled(bool p_enable) {}
int32_t ARKitInterface::_get_camera_feed_id() const {
    return 0;
}
bool ARKitInterface::get_light_estimation_is_enabled() const {
	return false;
}
void ARKitInterface::set_light_estimation_is_enabled(bool p_enable) {}
bool ARKitInterface::get_image_tracking_is_enabled() const {
	return false;
}
void ARKitInterface::set_image_tracking_is_enabled(bool p_enable) {}
void ARKitInterface::set_reference_images(TypedArray<Image> images, TypedArray<Vector2> physical_widths) {}
real_t ARKitInterface::get_ambient_intensity() const {
	return 0;
}
real_t ARKitInterface::get_ambient_color_temperature() const {
	return 0;
}
real_t ARKitInterface::get_exposure_offset() const {
	return 0;
}
TypedArray<Image> ARKitInterface::get_image_planes() const {
	return TypedArray<Image>();
}
void ARKitInterface::set_image_planes() {}
Ref<Cubemap> ARKitInterface::get_environment_map() const {
	return Ref<Cubemap>();
}
StringName ARKitInterface::_get_name() const {
	return "ARKit";
}
uint32_t ARKitInterface::_get_capabilities() const {
	return 0;
}
ScreenOrientation ARKitInterface::get_screen_orientation() const {}
Array ARKitInterface::raycast(Vector2 p_screen_coord) {
    return Array();
}
bool ARKitInterface::_is_initialized() const {
	return false;
}
bool ARKitInterface::_initialize() {
    return false;
}
void ARKitInterface::_uninitialize() {}
Size2 ARKitInterface::_get_render_target_size() {
	Size2 target_size = DisplayServer::get_singleton()->screen_get_size();
	return target_size;
}
uint32_t ARKitInterface::_get_view_count() {
	return 1;
}
Transform3D ARKitInterface::_get_camera_transform() {
	return transform;
}
Transform3D ARKitInterface::_get_transform_for_view(uint32_t p_view, const Transform3D &p_cam_transform) {
	return transform;
}
PackedFloat64Array ARKitInterface::_get_projection_for_view(uint32_t p_view, double p_aspect, double p_z_near, double p_z_far) {
	return PackedFloat64Array();
}
void ARKitInterface::_post_draw_viewport(const RID &p_render_target, const Rect2 &p_screen_rect) {}
Ref<XRPositionalTracker> ARKitInterface::get_anchor_for_uuid(const unsigned char *p_uuid, Ref<XRPositionalTracker> tracker) {
    return Ref<XRPositionalTracker>();
}
void ARKitInterface::remove_anchor_for_uuid(const unsigned char *p_uuid) {}
void ARKitInterface::remove_all_anchors() {}
void ARKitInterface::_process() {}
void ARKitInterface::_add_or_update_anchor(GodotARAnchor *p_anchor) {}
void ARKitInterface::_remove_anchor(GodotARAnchor *p_anchor) {}
void set_ycbcr_images(Ref<CameraFeed> feed, const Ref<Image> &p_y_img, const Ref<Image> &p_cbcr_img) {}
#endif /* ARKIT_DUMMY */
