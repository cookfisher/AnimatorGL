#include "stdafx.h"

// Apply acceleration on both particles in one sweep
void Particle::add_acceleration_pairwise(Particle& interacting_particle) {

	// We calculate the acceleration instead of the forces for faster calculation

	// Get distances
	float dx = interacting_particle.x_ - x_;
	float dy = interacting_particle.y_ - y_;
	float dz = interacting_particle.z_ - z_;

	// Square of distances
	float distance_square = dx * dx + dy * dy + dz * dz;

	// Keep a minimum square of distance
	if (distance_square < MIN_DISTANCE)
		distance_square = MIN_DISTANCE;

	float distance = sqrt(distance_square);

	velocity_x_ = dx / distance;
	velocity_y_ = dy / distance;
	velocity_z_ = dz / distance;

	// Use the mass of the other particle
	float acceleration_factor = (GRAVITATIONAL_CONSTANT / distance_square) * interacting_particle.mass_;
	float interacting_acceleration_factor = (GRAVITATIONAL_CONSTANT / distance_square) * mass_;

	// Apply accelerations
	acceleration_x_ -= acceleration_factor * velocity_x_;
	acceleration_y_ -= acceleration_factor * velocity_y_;
	acceleration_z_ -= acceleration_factor * velocity_z_;

	interacting_particle.acceleration_x_ += interacting_acceleration_factor * velocity_x_;
	interacting_particle.acceleration_y_ += interacting_acceleration_factor * velocity_y_;
	interacting_particle.acceleration_z_ += interacting_acceleration_factor * velocity_z_;
}

// Aquire the distance of the particle from another particle
float Particle::get_distance(const Particle& second_particle) const {
	// Get distances
	float dx = x_ - second_particle.x_;
	float dy = y_ - second_particle.y_;
	float dz = z_ - second_particle.z_;

	// Square of distances
	float distance_square = dx * dx + dy * dy + dz * dz;

	// Keep a minimum square of distance
	if (distance_square < MIN_DISTANCE)
		distance_square = MIN_DISTANCE;

	return sqrt(distance_square);
}

// Apply acceleration on one particle from a center of mass
void Particle::add_acceleration(float total_mass, float center_of_mass_x, float center_of_mass_y, float center_of_mass_z) {

	// We calculate the acceleration instead of the forces for faster calculation

	// Get distances
	float dx = center_of_mass_x - x_;
	float dy = center_of_mass_y - y_;
	float dz = center_of_mass_z - z_;

	// Square of distances
	float distance_square = dx * dx + dy * dy + dz * dz;

	// Keep a minimum square of distance
	if (distance_square < MIN_DISTANCE)
		distance_square = MIN_DISTANCE;

	float distance = sqrt(distance_square);

	velocity_x_ = dx / distance;
	velocity_y_ = dy / distance;
	velocity_z_ = dz / distance;

	// Use the mass of the other particle
	float acceleration_factor = (GRAVITATIONAL_CONSTANT / distance_square) * total_mass;

	// Apply accelerations
	acceleration_x_ -= acceleration_factor * velocity_x_;
	acceleration_y_ -= acceleration_factor * velocity_y_;
	acceleration_z_ -= acceleration_factor * velocity_z_;
}

// Apply acceleration on one particle from forces of another particle
void Particle::add_acceleration(const Particle& interacting_particle) {

	// We calculate the acceleration instead of the forces for faster calculation

	// Get distances
	float dx = interacting_particle.x_ - x_;
	float dy = interacting_particle.y_ - y_;
	float dz = interacting_particle.z_ - z_;

	// Square of distances
	float distance_square = dx * dx + dy * dy + dz * dz;

	// Keep a minimum square of distance
	if (distance_square < MIN_DISTANCE)
		distance_square = MIN_DISTANCE;

	float distance = sqrt(distance_square);

	velocity_x_ = dx / distance;
	velocity_y_ = dy / distance;
	velocity_z_ = dz / distance;

	// Use the mass of the other particle
	float acceleration_factor = (GRAVITATIONAL_CONSTANT / distance_square) * interacting_particle.mass_;

	// Apply accelerations
	acceleration_x_ -= acceleration_factor * velocity_x_;
	acceleration_y_ -= acceleration_factor * velocity_y_;
	acceleration_z_ -= acceleration_factor * velocity_z_;
}

// Moves the current particle for a specific time
void Particle::advance(float time_step) {

	// Add accelerations on velocities
	velocity_x_ += time_step * acceleration_x_;
	velocity_y_ += time_step * acceleration_y_;
	velocity_z_ += time_step * acceleration_z_;

	// Get the new position
	x_ += velocity_x_ * time_step;
	y_ += velocity_y_ * time_step;
	z_ += velocity_z_ * time_step;

	// If out of grid limits, reverse direction and set valid position
	if (x_ < 0) {
		velocity_x_ *= -1;
		//x_ *= -1;		
		x_ = 0;
	}
	else if (x_ > UNIVERSE_SIZE_X) {
		velocity_x_ *= -1;
		//x_ -= UNIVERSE_SIZE_X;
		x_ = UNIVERSE_SIZE_X;
	}

	if (y_ < 0) {
		velocity_y_ *= -1;
		//y_ *= -1;
		y_ = 0;
	}
	else if (y_ > UNIVERSE_SIZE_Y) {
		velocity_y_ *= -1;
		//y_ -= UNIVERSE_SIZE_Y;
		y_ = UNIVERSE_SIZE_Y;
	}
	
	if (z_ < 0) {
		velocity_z_ *= -1;
		//z_ *= -1;
		z_ = 0;
	}
	else if (z_ > UNIVERSE_SIZE_Z) {
		velocity_z_ *= -1;
		//z_ -= UNIVERSE_SIZE_Z;
		z_ = UNIVERSE_SIZE_Z;
	}

	// Reset accelerations
	acceleration_x_ = 0.0;
	acceleration_y_ = 0.0;
	acceleration_z_ = 0.0;
}

// Combine two particles into one by adding them
Particle Particle::operator+(const Particle& r) const {
	return Particle(x_ + r.x_, y_ + r.y_, z_ + r.z_,
		velocity_x_ + r.velocity_x_, velocity_y_ + r.velocity_y_, velocity_z_ + r.velocity_z_,
		mass_ + r.mass_,
		acceleration_x_ + r.acceleration_x_, acceleration_y_ + r.acceleration_y_, acceleration_z_ + r.acceleration_z_);
}

// Combine two particles into one by substracting them
Particle Particle::operator-(const Particle& r) const {
	return Particle(x_ - r.x_, y_ - r.y_, z_ - r.z_,
		velocity_x_ - r.velocity_x_, velocity_y_ - r.velocity_y_, velocity_z_ - r.velocity_z_,
		mass_ - r.mass_,
		acceleration_x_ - r.acceleration_x_, acceleration_y_ - r.acceleration_y_, acceleration_z_ - r.acceleration_z_);
}

// Multiply a particle by a scalar number
Particle Particle::operator*(float r) const {
	return Particle(x_ * r, y_ * r, z_ * r,
		velocity_x_ * r, velocity_y_ * r, velocity_z_ * r,
		mass_ * r, 
		acceleration_x_ * r, acceleration_y_ * r, acceleration_z_ * r);
}
