// Pham.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Pham.h"

//#include "post/hdr.hpp"


#if 0
/*
class PhamApp : public Granite::Application, public Granite::EventHandler
{
public:


	Granite::CubeMesh m_cube;

	PhamApp( const std::string &path )
	{
		EVENT_MANAGER_REGISTER_LATCH( PhamApp, on_device_created, on_device_destroyed, Vulkan::DeviceCreatedEvent );
	}


	void on_device_destroyed( const Vulkan::DeviceCreatedEvent &e )
	{
	}

	void on_device_created( const Vulkan::DeviceCreatedEvent &e )
	{
		//Granite::SceneViewerApplication::on_device_created(e);

		auto &device = e.get_device();
		auto &ui = Util::UI::UIManager::get();
		ui.reset_children();



		auto window = Util::make_abstract_handle<Util::UI::Widget, Util::UI::Window>();
		ui.add_child( window );

		auto &win = static_cast<Util::UI::Window &>( *window );
		win.set_fullscreen( true );
		win.show_title_bar( false );
		win.set_floating( false );
		win.set_background_color( glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) );
		win.set_background_image( device.get_texture_manager().request_texture( "builtin://textures/checkerboard.png" ) );


		auto button = Util::make_abstract_handle<Util::UI::Widget, Util::UI::ClickButton>();
		win.add_child( button );


		auto &btn0 = static_cast<Util::UI::ClickButton &>( *button );
		btn0.set_floating( true );
		btn0.set_text( "THIS IS A COOL BUTTON." );
		btn0.set_floating_position( glm::vec2( 50.0f ) );

		//*

		button = Util::make_abstract_handle<Util::UI::Widget, Util::UI::ClickButton>();
		win.add_child( button );
		auto &btn1 = static_cast<Util::UI::ClickButton &>( *button );
		btn1.set_floating( true );
		btn1.set_text( "THIS IS ALSO A COOL BUTTON." );
		btn1.set_floating_position( glm::vec2( 50.0f, 80.0f ) );

		button = Util::make_abstract_handle<Util::UI::Widget, Util::UI::ClickButton>();
		win.add_child( button );
		auto &btn2 = static_cast<Util::UI::ClickButton &>( *button );
		btn2.set_text( "#0" );

		button = Util::make_abstract_handle<Util::UI::Widget, Util::UI::ClickButton>();
		win.add_child( button );
		auto &btn3 = static_cast<Util::UI::ClickButton &>( *button );
		btn3.set_text( "#1" );

		auto slider = Util::make_abstract_handle<Util::UI::Widget, Util::UI::Slider>();
		win.add_child( slider );


		{
			auto &sli = static_cast<Util::UI::Slider &>( *slider );
			sli.set_floating( true );
			sli.set_floating_position( glm::vec2( 100.0f ) );
			sli.set_text( "Value" );
			sli.set_size( glm::vec2( 200.0f, 30.0f ) );
			sli.set_label_slider_gap( 10.0f );
			sli.set_color( glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
			sli.set_orientation( Util::UI::Slider::Orientation::Horizontal );
			sli.set_background_color( glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
			sli.show_label( false );
			sli.show_value( false );
			sli.set_margin( 5.0f );
			sli.show_tooltip( true );
			sli.set_background_image( device.get_texture_manager().request_texture( "builtin://textures/checkerboard.png" ) );
			sli.set_background_color( glm::vec4( 1.0f ) );
		}

		slider = Util::make_abstract_handle<Util::UI::Widget, Util::UI::Slider>();
		win.add_child( slider );
		{
			auto &sli = static_cast<Util::UI::Slider &>( *slider );
			sli.set_floating( true );
			sli.set_floating_position( glm::vec2( 500.0f, 100.0f ) );
			sli.set_text( "Value" );
			sli.set_size( glm::vec2( 30.0f, 200.0f ) );
			sli.set_label_slider_gap( 0.0f );
			sli.set_color( glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
			sli.set_orientation( Util::UI::Slider::Orientation::Vertical );
			sli.set_background_color( glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
			sli.show_label( false );
			sli.show_value( false );
			sli.set_margin( 5.0f );
			sli.show_tooltip( true );
			sli.set_background_image( device.get_texture_manager().request_texture( "builtin://textures/checkerboard.png" ) );
			sli.set_background_color( glm::vec4( 1.0f ) );
		}
		//* /

		button = Util::make_abstract_handle<Util::UI::Widget, Util::UI::ToggleButton>();
		win.add_child( button );
		{
			auto &btn = static_cast<Util::UI::ToggleButton &>( *button );
			btn.set_floating_position( glm::vec2( 100.0f, 500.0f ) );
			btn.set_floating( true );
			btn.set_background_color( glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
			btn.set_text( "Mjuu" );
			btn.set_toggled_font_color( glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) );
			btn.set_untoggled_font_color( glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
			btn.set_background_image( device.get_texture_manager().request_texture( "builtin://textures/checkerboard.png" ) );
			btn.set_background_color( glm::vec4( 1.0f ) );
		}


		{
			
			//auto plane = Util::make_abstract_handle<AbstractRenderable, TexturePlane>(
			//	Path::relpath( path, info["normalMap"].GetString() ) );

			auto entity = scene->create_renderable( plane, nullptr );

			auto *texture_plane = static_cast<TexturePlane *>( plane.get() );

			vec3 center = vec3( info["center"][0].GetFloat(), info["center"][1].GetFloat(), info["center"][2].GetFloat() );
			vec3 normal = vec3( info["normal"][0].GetFloat(), info["normal"][1].GetFloat(), info["normal"][2].GetFloat() );
			vec3 up = vec3( info["up"][0].GetFloat(), info["up"][1].GetFloat(), info["up"][2].GetFloat() );
			vec3 emissive = vec3( info["baseEmissive"][0].GetFloat(), info["baseEmissive"][1].GetFloat(), info["baseEmissive"][2].GetFloat() );
			float rad_up = info["radiusUp"].GetFloat();
			float rad_x = info["radiusAcross"].GetFloat();
			float zfar = info["zFar"].GetFloat();

			texture_plane->set_plane( center, normal, up, rad_up, rad_x );
			texture_plane->set_zfar( zfar );

			if( info.HasMember( "reflectionName" ) )
				texture_plane->set_reflection_name( info["reflectionName"].GetString() );
			if( info.HasMember( "refractionName" ) )
				texture_plane->set_refraction_name( info["refractionName"].GetString() );

			texture_plane->set_resolution_scale( info["resolutionScale"][0].GetFloat(), info["resolutionScale"][1].GetFloat() );

			texture_plane->set_base_emissive( emissive );
			entity->free_component<UnboundedComponent>();
			entity->allocate_component<RenderPassSinkComponent>();
			auto *cull_plane = entity->allocate_component<CullPlaneComponent>();
			cull_plane->plane = texture_plane->get_plane();

			auto *rpass = entity->allocate_component<RenderPassComponent>();
			rpass->creator = texture_plane;

		
		
		
		}



	}

	void render_frame( double ft, double et)
	{
		//Granite::SceneViewerApplication::render_frame( ft, et );

		m_cube.re
		auto &device = get_wsi().get_device();
		auto cmd = device.request_command_buffer();
		auto rp = device.get_swapchain_render_pass( Vulkan::SwapchainRenderPass::Depth );
		cmd->begin_render_pass( rp );
		Util::UI::UIManager::get().render( *cmd );
		cmd->end_render_pass();
		device.submit( cmd );
	}
};
*/




PhamApp::PhamApp()
	: forward_renderer( Granite::RendererType::GeneralForward ),
	deferred_renderer( Granite::RendererType::GeneralDeferred ),
	depth_renderer( Granite::RendererType::DepthOnly )
{

	animation_system = scene_loader.consume_animation_system();
	context.set_lighting_parameters( &lighting );
	cam.set_depth_range( 0.1f, 1000.0f );

	auto &scene = scene_loader.get_scene();

	//auto plane = Util::make_abstract_handle<AbstractRenderable, Granite::CubeMesh>(
	//	Path::relpath( path, info["normalMap"].GetString() ) );

	scene.set_root_node( scene.create_node() );

	/*
	for(auto i = 0; i < 1000; ++i)
	{
		auto cube = Util::make_abstract_handle<Granite::AbstractRenderable, Granite::SphereMesh>();

		auto node = scene.create_node();

		auto root = scene.get_root_node();


		root->add_child(node);      

		node->transform.translation.x = rand() & 511;
		node->transform.translation.y = rand() & 511;
		node->transform.translation.z = rand() & 511;

		auto entity = scene.create_renderable( cube, node.get() );
	}
	*/

	//node->

	//auto *rpass = entity->allocate_component<Granite::RenderPassComponent>();
	//rpass->creator = static_cast<Granite::CubeMesh *>( entity.get());

	//auto *rpass = entity.allocate_component<RenderPassComponent>();
	//rpass->creator = texture_plane;

	// Create a dummy background if there isn't any background.
	if( scene_loader.get_scene().get_entity_pool().get_component_group<Granite::UnboundedComponent>().empty() )
	{
		auto cylinder = Util::make_abstract_handle<Granite::AbstractRenderable, Granite::SkyCylinder>( "builtin://textures/background.png" );
		static_cast<Granite::SkyCylinder *>( cylinder.get() )->set_xz_scale( 8.0f / Granite::pi<float>() );
		scene_loader.get_scene().create_renderable( cylinder, nullptr );
	}


	auto *environment = scene_loader.get_scene().get_environment();
	if( environment )
		lighting.fog = environment->fog;
	else
		lighting.fog = {};

	cam.look_at( Granite::vec3( 26.0f, 38.0f, 38.0f ), Granite::vec3( 0.0f ) , gr::vec3(0,0,1) );

	// Pick a camera to show.
	selected_camera = &cam;
	auto &scene_cameras = scene_loader.get_scene().get_entity_pool().get_component_group<Granite::CameraComponent>();
	if( !scene_cameras.empty() )
		selected_camera = &std::get<0>( scene_cameras.front() )->camera;

	context.set_camera( *selected_camera );

	EVENT_MANAGER_REGISTER_LATCH( PhamApp, on_swapchain_changed, on_swapchain_destroyed, Vulkan::SwapchainParameterEvent );
	EVENT_MANAGER_REGISTER_LATCH( PhamApp, on_device_created, on_device_destroyed, Vulkan::DeviceCreatedEvent );
}

void PhamApp::loop_animations()
{
}

void PhamApp::rescale_scene( float radius )
{
	scene_loader.get_scene().update_cached_transforms();

	Granite::AABB aabb( Granite::vec3( FLT_MAX ), Granite::vec3( -FLT_MAX ) );
	auto &objects = scene_loader.get_scene().get_entity_pool().get_component_group<Granite::CachedSpatialTransformComponent, Granite::RenderableComponent>();
	for( auto &caster : objects )
		aabb.expand( std::get<0>( caster )->world_aabb );

	float scale_factor = radius / aabb.get_radius();
	auto root_node = scene_loader.get_scene().get_root_node();
	auto new_root_node = scene_loader.get_scene().create_node();
	new_root_node->transform.scale = Granite::vec3( scale_factor );
	new_root_node->add_child( root_node );
	scene_loader.get_scene().set_root_node( new_root_node );

	// TODO: Make this more configurable.
	cascade_cutoff_distance = 0.25f * radius;
}

void PhamApp::on_device_created( const Vulkan::DeviceCreatedEvent &device )
{
	if( !skydome_reflection.empty() )
		reflection = device.get_device().get_texture_manager().request_texture( skydome_reflection );
	if( !skydome_irradiance.empty() )
		irradiance = device.get_device().get_texture_manager().request_texture( skydome_irradiance );
	graph.set_device( &device.get_device() );

	//m_cube.on_device_created( device );
	auto &scene = scene_loader.get_scene();

	const auto pos = cb::Vec3( 0.0f, 0.0f, 0.0f );

	m_cubit.genWorld( pos );
	m_cubit.genGeo( &device.get_device(), &scene, pos );

}

void PhamApp::on_device_destroyed( const Vulkan::DeviceCreatedEvent& device )
{
	reflection = nullptr;
	irradiance = nullptr;
	graph.set_device( nullptr );

	//m_cube.on_device_created( device );
}

void PhamApp::render_main_pass( Vulkan::CommandBuffer &cmd, const Granite::mat4 &proj, const Granite::mat4 &view )
{
	auto &scene = scene_loader.get_scene();
	context.set_camera( proj, view );
	visible.clear();
	scene.gather_visible_opaque_renderables( context.get_visibility_frustum(), visible );
	scene.gather_background_renderables( visible );
	scene.gather_visible_render_pass_sinks( context.get_render_parameters().camera_position, visible );

#if RENDERER == RENDERER_FORWARD
	forward_renderer.set_mesh_renderer_options_from_lighting( lighting );
	forward_renderer.begin();
	forward_renderer.push_renderables( context, visible );
	forward_renderer.flush( cmd, context );
#else
	deferred_renderer.begin();
	deferred_renderer.push_renderables( context, visible );
	deferred_renderer.flush( cmd, context );
#endif
}

void PhamApp::render_transparent_objects( Vulkan::CommandBuffer &cmd, const Granite::mat4 &proj, const Granite::mat4 &view )
{
	auto &scene = scene_loader.get_scene();
	context.set_camera( proj, view );
	visible.clear();
	scene.gather_visible_transparent_renderables( context.get_visibility_frustum(), visible );
	forward_renderer.set_mesh_renderer_options_from_lighting( lighting );
	forward_renderer.begin();
	forward_renderer.push_renderables( context, visible );
	forward_renderer.flush( cmd, context );
}

static inline std::string tagcat( const std::string &a, const std::string &b )
{
	return a + "-" + b;
}

void PhamApp::add_main_pass( Vulkan::Device &device, const std::string &tag, MainPassType type )
{
#if RENDERER == RENDERER_FORWARD
	Granite::AttachmentInfo color, depth;
	color.format = VK_FORMAT_B10G11R11_UFLOAT_PACK32;
	depth.format = device.get_default_depth_format();
	color.samples = 4;
	depth.samples = 4;

	auto resolved = color;
	resolved.samples = 1;

	auto &lighting = graph.add_pass( tagcat( "lighting", tag ), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT );
	lighting.add_color_output( tagcat( "HDR-MS", tag ), color );
	lighting.add_resolve_output( tagcat( "HDR", tag ), resolved );
	lighting.set_depth_stencil_output( tagcat( "depth", tag ), depth );

	lighting.set_get_clear_depth_stencil( []( VkClearDepthStencilValue *value ) -> bool {
		if( value )
		{
			value->depth = 1.0f;
			value->stencil = 0;
		}
		return true;
	} );

	lighting.set_get_clear_color( []( unsigned, VkClearColorValue *value ) -> bool {
		if( value )
			memset( value, 0, sizeof( *value ) );
		return true;
	} );

	lighting.set_build_render_pass( [ this, type ]( Vulkan::CommandBuffer &cmd ) {
		uint32_t flags = 0;

		if( this->lighting.environment_irradiance && this->lighting.environment_radiance )
			flags |= Granite::Renderer::ENVIRONMENT_ENABLE_BIT;
		//if( this->lighting.shadow_far )
		//	flags |= Granite::Renderer::SHADOW_ENABLE_BIT;
		//if( this->lighting.shadow_near && this->lighting.shadow_far )
		//	flags |= Granite::Renderer::SHADOW_CASCADE_ENABLE_BIT;
		if( this->lighting.fog.falloff > 0.0f )
			flags |= Granite::Renderer::FOG_ENABLE_BIT;

		forward_renderer.set_mesh_renderer_options( flags );
		render_main_pass( cmd, selected_camera->get_projection(), selected_camera->get_view() );
		render_transparent_objects( cmd, selected_camera->get_projection(), selected_camera->get_view() );
	} );

	/*
	lighting.add_texture_input( "shadow-main" );
	if( type == MainPassType::Main )
	{
		lighting.add_texture_input( "shadow-near" );
		scene_loader.get_scene().add_render_pass_dependencies( graph, lighting );
	}
	*/

#elif RENDERER == RENDERER_DEFERRED
	AttachmentInfo emissive, albedo, normal, pbr, depth;
	emissive.format = VK_FORMAT_B10G11R11_UFLOAT_PACK32;
	albedo.format = VK_FORMAT_R8G8B8A8_SRGB;
	normal.format = VK_FORMAT_A2B10G10R10_UNORM_PACK32;
	pbr.format = VK_FORMAT_R8G8_UNORM;
	depth.format = device.get_default_depth_stencil_format();

	auto &gbuffer = graph.add_pass( tagcat( "gbuffer", tag ), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT );
	gbuffer.add_color_output( tagcat( "emissive", tag ), emissive );
	gbuffer.add_color_output( tagcat( "albedo", tag ), albedo );
	gbuffer.add_color_output( tagcat( "normal", tag ), normal );
	gbuffer.add_color_output( tagcat( "pbr", tag ), pbr );
	gbuffer.set_depth_stencil_output( tagcat( "depth", tag ), depth );
	gbuffer.set_build_render_pass( [ this, type ]( Vulkan::CommandBuffer &cmd ) {
		render_main_pass( cmd, selected_camera->get_projection(), selected_camera->get_view() );
	} );

	gbuffer.set_get_clear_depth_stencil( []( VkClearDepthStencilValue *value ) -> bool {
		if( value )
		{
			value->depth = 1.0f;
			value->stencil = 0;
		}
		return true;
	} );

	gbuffer.set_get_clear_color( []( unsigned, VkClearColorValue *value ) -> bool {
		if( value )
		{
			value->float32[0] = 0.0f;
			value->float32[1] = 0.0f;
			value->float32[2] = 0.0f;
			value->float32[3] = 0.0f;
		}
		return true;
	} );

	auto &lighting = graph.add_pass( tagcat( "lighting", tag ), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT );
	lighting.add_color_output( tagcat( "HDR-lighting", tag ), emissive, tagcat( "emissive", tag ) );
	lighting.add_attachment_input( tagcat( "albedo", tag ) );
	lighting.add_attachment_input( tagcat( "normal", tag ) );
	lighting.add_attachment_input( tagcat( "pbr", tag ) );
	lighting.add_attachment_input( tagcat( "depth", tag ) );
	lighting.set_depth_stencil_input( tagcat( "depth", tag ) );

	//lighting.add_texture_input( "shadow-main" );
	//lighting.add_texture_input( "shadow-near" );
	scene_loader.get_scene().add_render_pass_dependencies( graph, gbuffer );

	lighting.set_build_render_pass( [ this, type ]( Vulkan::CommandBuffer &cmd ) {
		DeferredLightRenderer::render_light( cmd, context );
	} );

	auto &transparent = graph.add_pass( tagcat( "transparent", tag ), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT );
	transparent.add_color_output( tagcat( "HDR", tag ), emissive, tagcat( "HDR-lighting", tag ) );
	transparent.set_depth_stencil_input( tagcat( "depth", tag ) );
	transparent.set_build_render_pass( [ this, type ]( Vulkan::CommandBuffer &cmd ) {
		render_transparent_objects( cmd, selected_camera->get_projection(), selected_camera->get_view() );
	} );
#endif
}

void PhamApp::add_shadow_pass( Vulkan::Device &, const std::string &tag, DepthPassType type )
{
	Granite::AttachmentInfo shadowmap;
	shadowmap.format = VK_FORMAT_D16_UNORM;
	shadowmap.samples = 1;
	shadowmap.size_class = Granite::SizeClass::Absolute;

	if( type == DepthPassType::Main )
	{
		shadowmap.size_x = 2048.0f;
		shadowmap.size_y = 2048.0f;
	}
	else
	{
		shadowmap.size_x = 1024.0f;
		shadowmap.size_y = 1024.0f;
	}

	auto &shadowpass = graph.add_pass( tagcat( "shadow", tag ), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT );


	shadowpass.set_depth_stencil_output( tagcat( "shadow", tag ), shadowmap );
	shadowpass.set_build_render_pass( [ this, type ]( Vulkan::CommandBuffer &cmd ) {
		/*
		if( type == DepthPassType::Main )
		{
			render_shadow_map_far( cmd );
		}
		else
		{
			render_shadow_map_near( cmd );
		}
		*/
	} );

	shadowpass.set_get_clear_depth_stencil( []( VkClearDepthStencilValue *value ) -> bool {
		if( value )
		{
			value->depth = 1.0f;
			value->stencil = 0;
		}
		return true;
	} );

	shadowpass.set_need_render_pass( [ this, type ]() {
		return type == DepthPassType::Main ? need_shadow_map_update : true;
	} );
}

void PhamApp::on_swapchain_changed( const Vulkan::SwapchainParameterEvent &swap )
{
	auto physical_buffers = graph.consume_physical_buffers();
	graph.reset();
	graph.set_device( &swap.get_device() );

	Granite::ResourceDimensions dim;
	dim.width = swap.get_width();
	dim.height = swap.get_height();
	dim.format = swap.get_format();
	graph.set_backbuffer_dimensions( dim );
	Granite::AttachmentInfo backbuffer;

	const char *backbuffer_source = getenv( "GRANITE_SURFACE" );
	graph.set_backbuffer_source( backbuffer_source ? backbuffer_source : "tonemapped" );

	scene_loader.get_scene().add_render_passes( graph );

	//add_shadow_pass( swap.get_device(), "main", DepthPassType::Main );
	//add_shadow_pass( swap.get_device(), "near", DepthPassType::Near );
	add_main_pass( swap.get_device(), "reflection", MainPassType::Reflection );
	add_main_pass( swap.get_device(), "refraction", MainPassType::Refraction );
	add_main_pass( swap.get_device(), "main", MainPassType::Main );
	Granite::setup_hdr_postprocess( graph, "HDR-main", "tonemapped" );

	graph.bake();
	graph.log();
	graph.install_physical_buffers( move( physical_buffers ) );

	//need_shadow_map_update = true;
}

void PhamApp::on_swapchain_destroyed( const Vulkan::SwapchainParameterEvent & )
{
}


static Granite::vec3 light_direction()
{
	return normalize( Granite::vec3( 0.5f, 1.2f, 0.8f ) );
}

void PhamApp::update_shadow_scene_aabb()
{
	// Get the scene AABB for shadow casters.
	auto &scene = scene_loader.get_scene();
	auto &shadow_casters =
		scene.get_entity_pool().get_component_group<Granite::CachedSpatialTransformComponent, Granite::RenderableComponent, Granite::CastsStaticShadowComponent>();
	Granite::AABB aabb( Granite::vec3( FLT_MAX ), Granite::vec3( -FLT_MAX ) );
	for( auto &caster : shadow_casters )
		aabb.expand( std::get<0>( caster )->world_aabb );
	shadow_scene_aabb = aabb;
}

void PhamApp::update_shadow_map()
{
	auto &scene = scene_loader.get_scene();
	depth_visible.clear();

	Granite::mat4 view = mat4_cast( Granite::look_at( -light_direction(), Granite::vec3( 0.0f, 0.0f, 1.0f ) ) );

	// Project the scene AABB into the light and find our ortho ranges.
	Granite::AABB ortho_range = shadow_scene_aabb.transform( view );
	Granite::mat4 proj = ortho( ortho_range );

	// Standard scale/bias.
	lighting.shadow.far_transform = glm::translate( Granite::vec3( 0.5f, 0.5f, 0.0f ) ) * glm::scale( Granite::vec3( 0.5f, 0.5f, 1.0f ) ) * proj * view;
	depth_context.set_camera( proj, view );

	depth_renderer.begin();
	scene.gather_visible_static_shadow_renderables( depth_context.get_visibility_frustum(), depth_visible );
	depth_renderer.push_renderables( depth_context, depth_visible );
}

void PhamApp::render_shadow_map_far( Vulkan::CommandBuffer &cmd )
{
	update_shadow_map();
	depth_renderer.flush( cmd, depth_context );
}

void PhamApp::render_shadow_map_near( Vulkan::CommandBuffer &cmd )
{
	auto &scene = scene_loader.get_scene();
	depth_visible.clear();
	Granite::mat4 view = mat4_cast( Granite::look_at( -light_direction(), Granite::vec3( 0.0f, 1.0f, 0.0f ) ) );
	Granite::AABB ortho_range_depth = shadow_scene_aabb.transform( view ); // Just need this to determine Zmin/Zmax.

	auto near_camera = *selected_camera;
	near_camera.set_depth_range( near_camera.get_znear(), cascade_cutoff_distance );
	Granite::vec4 sphere = Granite::Frustum::get_bounding_sphere( inverse( near_camera.get_projection() ), inverse( near_camera.get_view() ) );
	Granite::vec2 center_4d = ( view * Granite::vec4( sphere.x, sphere.y, sphere.z, 1.0f ) );

	Granite::vec2 center_xy( center_4d.x, center_4d.y );

	sphere.w *= 1.01f;

	Granite::vec2 texel_size = Granite::vec2( 2.0f * sphere.w ) * Granite::vec2( 1.0f / lighting.shadow_near->get_image().get_create_info().width,
		1.0f / lighting.shadow_near->get_image().get_create_info().height );

	// Snap to texel grid.
	center_xy = round( center_xy / texel_size ) * texel_size;

	Granite::AABB ortho_range = Granite::AABB( Granite::vec3( center_xy - Granite::vec2( sphere.w ), ortho_range_depth.get_minimum().z ),
		Granite::vec3( center_xy + Granite::vec2( sphere.w ), ortho_range_depth.get_maximum().z ) );

	Granite::mat4 proj = ortho( ortho_range );
	lighting.shadow.near_transform = glm::translate( Granite::vec3( 0.5f, 0.5f, 0.0f ) ) * glm::scale( Granite::vec3( 0.5f, 0.5f, 1.0f ) ) * proj * view;
	depth_context.set_camera( proj, view );
	depth_renderer.begin();
	scene.gather_visible_dynamic_shadow_renderables( depth_context.get_visibility_frustum(), depth_visible );
	depth_renderer.push_renderables( depth_context, depth_visible );
	depth_renderer.flush( cmd, depth_context );
}

void PhamApp::update_scene( double total_time, double elapsed_time )
{
	auto &scene = scene_loader.get_scene();

	if( reflection )
		lighting.environment_radiance = &reflection->get_image()->get_view();
	if( irradiance )
		lighting.environment_irradiance = &irradiance->get_image()->get_view();
	lighting.shadow.inv_cutoff_distance = 1.0f / cascade_cutoff_distance;
	lighting.environment.intensity = 1.0f;
	lighting.environment.mipscale = 9.0f;
	lighting.refraction.falloff = Granite::vec3( 1.0f / 1.5f, 1.0f / 2.5f, 1.0f / 5.0f );
	lighting.directional.direction = light_direction();
	lighting.directional.color = Granite::vec3( 6.0f, 5.5f, 4.5f );

	context.set_camera( *selected_camera );
	scene.set_render_pass_data( &forward_renderer, &context );

	if (animation_system)
	{
		animation_system->animate( elapsed_time );
	}


	scene.update_cached_transforms();
	scene.refresh_per_frame( context );
}

void PhamApp::render_scene()
{
	auto &wsi = get_wsi();
	auto &device = wsi.get_device();
	auto &scene = scene_loader.get_scene();

	//if( need_shadow_map_update )
	//	update_shadow_scene_aabb();

	graph.setup_attachments( device, &device.get_swapchain_view() );
	//lighting.shadow_far = &graph.get_physical_texture_resource( graph.get_texture_resource( "shadow-main" ).get_physical_index() );
	//lighting.shadow_near = &graph.get_physical_texture_resource( graph.get_texture_resource( "shadow-near" ).get_physical_index() );
	scene.bind_render_graph_resources( graph );
	graph.enqueue_render_passes( device );

	//need_shadow_map_update = false;
}

void PhamApp::render_frame( double frame_time, double elapsed_time )
{
	update_scene( frame_time, elapsed_time );
	render_scene();
}












#include <vox/vox.h>


int main(int argc, char **argv)
{

/*
#ifdef ASSET_DIRECTORY
	const char *asset_dir = getenv( "ASSET_DIRECTORY" );
	if( !asset_dir )
		asset_dir = ASSET_DIRECTORY;

#endif
*/


	vox::testVox();



	const char * const pAssetDir = "assets";

	Granite::Filesystem::get().register_protocol( "assets", std::unique_ptr<Granite::FilesystemBackend>( new Granite::OSFilesystem( pAssetDir ) ) );

	try
	{
		const char * pScene = "assets/samples/busterDrone/busterDrone.gltf";

		if( argc != 2 )
		{
			LOGE( "Usage: %s <glTF/scene file>\n", argv ? argv[0] : "viewer" );
		}
		else
		{
			pScene = argv[1];
		}


		auto path = std::string( "file://" ) + pScene;



		auto *app = new PhamApp();

		if( !app->init_wsi( std::unique_ptr<Vulkan::WSIPlatform>( Granite::make_platform( 1280, 720 ) ) ) )
			return 1;


		//app->rescale_scene( 5.0f );
		//app->loop_animations();

		while( app->poll() )
		{
			app->run_frame();
		}


	}
	catch( const std::exception &e )
	{
		LOGE( "application_create() threw exception: %s\n", e.what() );
	}
	
	return 0;
}
#endif
