
void 												
World::build(void) {

	int num_samples = 100;

    vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new MultiJittered(num_samples));

	
	background_color = white;
	tracer_ptr = new SingleSphere(this); 
	
	sphere.set_center(0);
	sphere.set_radius(5);
	
	float vpd = 100;
	Pinhole* left_camera_ptr = new Pinhole;
	left_camera_ptr->set_view_distance(vpd);
	

	Pinhole* right_camera_ptr = new Pinhole;
	right_camera_ptr->set_view_distance(vpd);
	
	StereoCamera* camera_ptr = new StereoCamera;
	camera_ptr->set_left_camera(left_camera_ptr);
	camera_ptr->set_right_camera(right_camera_ptr);
	camera_ptr->use_parallel_viewing();
	
	camera_ptr->set_pixel_gap(5);
	camera_ptr->set_eye(0, 0, 180);
	camera_ptr->set_lookat(0);    
	
	camera_ptr->compute_uvw();
	camera_ptr->set_stereo_angle(0.75);
	camera_ptr->setup_cameras();	  
	set_camera(camera_ptr);
}
