#pragma once
#include "Particle.h"
#include <vector>
#include <tbb/concurrent_vector.h>
#include "OctParticleTree.h"


// Handles conversions, allocations and image saving of various particle collections
class ParticleHandler
{
public:
	static void allocate_random_particles(size_t particle_count, std::vector<Particle>& particles, size_t size_x, size_t size_y, size_t size_z);
	static tbb::concurrent_vector<Particle> to_concurrent_vector(const std::vector<Particle>& input_particles);
	static std::vector<Particle> to_vector(const tbb::concurrent_vector<Particle>& input_particles);
	static bool are_equal(const std::vector<Particle>& first_particles, const std::vector<Particle>& second_particles);
	static OctParticleTree* to_octant_tree(const std::vector<Particle>& input_particles, size_t size_x, size_t size_y, size_t size_z);
};