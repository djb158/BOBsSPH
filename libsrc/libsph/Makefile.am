INCLUDES= -I$(top_srcdir)/include -I/home/djb/SPH/ann_1.1.2/include/ANN

LIBS =  libutil \
	libANN

LDADD = -lANN

lib_LTLIBRARIES = libsph.la

libsph_la_SOURCES = \
	calculate_divergence_v.c \
	calculate_divergence_v_thread_wrapper.c \
	calculate_particle_acceleration_boundary.c \
	calculate_particle_acceleration_interior.c \
	calculate_particle_acceleration_interior_thread_wrapper.c \
	calculate_particle_energy_deriv_boundary.c \
	calculate_particle_energy_deriv_interior.c \
	calculate_particle_energy_deriv_interior_thread_wrapper.c \
	calculate_particle_vorticity.c \
	copy_h.c \
	create_particles.c \
	dfdx.c \
	dfdy.c \
	dfdz.c \
	dwdf.c \
	d2wdf2.c \
	dwdx.c \
	dwdy.c \
	dwdz.c \
	equation_of_state.c \
	free_matrix.c \
	free_node_info.c \
	free_particles.c \
	free_particles_nn.c \
	get_pars.c \
	get_particle_acceleration.c \
	get_particle_energy.c \
	get_particle_energy_deriv.c \
	get_particle_position.c \
	get_particle_velocity.c \
	get_node_info_struct.c \
	integrate_particle_acceleration_boundary.c \
	integrate_particle_acceleration_interior.c \
	integrate_particle_energy_boundary.c \
	integrate_particle_energy_interior.c \
	integrate_particle_velocity_boundary.c \
	integrate_particle_velocity_interior.c \
	nearest_integer.c \
	pull_n.c \
	push_and_pull_divv.c \
	push_and_pull_h.c \
	push_and_pull_n_and_x.c \
	push_and_pull_p.c \
	push_and_pull_rho.c \
	push_and_pull_u.c \
	push_and_pull_v.c \
	read_node_info.c \
	read_particle_info.c \
	set_n.c \
	set_particle_acceleration.c \
	set_particle_density_boundary.c \
	set_particle_density_interior.c \
	set_particle_density_interior_thread_wrapper.c \
	set_particle_energy.c \
	set_particle_energy_deriv.c \
	set_particle_id_1D.c \
	set_particle_id_2D.c \
	set_particle_id_3D.c \
	set_particle_position.c \
	set_particle_velocity.c \
	set_initial_particles_state_1D.c \
	set_initial_particles_state_2D.c \
	set_initial_particles_state_3D.c \
        synchronize_node_info.c \
	update_kernel.c \
	update_neighbour_nodes.c \
	update_rij.cpp \
	w.c \
	w2D.c \
	write_node_info.c \
	write_particle_info.c
