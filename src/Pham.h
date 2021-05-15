



//#include "cubit.h"





#if 0



class PhamApp : public Granite::Application, public Granite::EventHandler
{
public:
	PhamApp();
	void render_frame( double frame_time, double elapsed_time ) override;
	void rescale_scene( float radius );
	void loop_animations();

protected:
	void update_scene( double frame_time, double elapsed_time );
	void render_scene();

	Granite::RenderContext context;
	Granite::RenderContext depth_context;
	Granite::Renderer forward_renderer;
	Granite::Renderer deferred_renderer;
	Granite::Renderer depth_renderer;
	Granite::LightingParameters lighting;
	Granite::FPSCamera cam;
	Granite::VisibilityList visible;
	Granite::VisibilityList depth_visible;
	Granite::SceneLoader scene_loader;
	std::unique_ptr<Granite::AnimationSystem> animation_system;

	Granite::Camera *selected_camera = nullptr;

	void on_device_created( const Vulkan::DeviceCreatedEvent &e );
	void on_device_destroyed( const Vulkan::DeviceCreatedEvent &e );
	void on_swapchain_changed( const Vulkan::SwapchainParameterEvent &e );
	void on_swapchain_destroyed( const Vulkan::SwapchainParameterEvent &e );
	Granite::RenderGraph graph;

	Vulkan::Texture *reflection = nullptr;
	Vulkan::Texture *irradiance = nullptr;

	bool need_shadow_map_update = true;
	void update_shadow_map();
	std::string skydome_reflection;
	std::string skydome_irradiance;
	Granite::AABB shadow_scene_aabb;

	void update_shadow_scene_aabb();
	void render_shadow_map_near( Vulkan::CommandBuffer &cmd );
	void render_shadow_map_far( Vulkan::CommandBuffer &cmd );
	void render_main_pass( Vulkan::CommandBuffer &cmd, const Granite::mat4 &proj, const Granite::mat4 &view );
	void render_transparent_objects( Vulkan::CommandBuffer &cmd, const Granite::mat4 &proj, const Granite::mat4 &view );

	enum class MainPassType
	{
		Main,
		Reflection,
		Refraction
	};
	void add_main_pass( Vulkan::Device &device, const std::string &tag, MainPassType type );

	enum class DepthPassType
	{
		Main,
		Near
	};
	void add_shadow_pass( Vulkan::Device &device, const std::string &tag, DepthPassType type );

	float cascade_cutoff_distance = 10.0f;

	//Granite::CubeMesh m_cube;

	vox::CubitPlane m_cubit;
};
#endif