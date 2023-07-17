#pragma once
#define M_PI 3.14159265358979323846
#include <cmath>

struct vec3_t {
	float x = 0, y = 0, z = 0;

	vec3_t( );
	vec3_t( float _x, float _y, float _z );

	vec3_t operator+( const vec3_t& other );
	vec3_t operator+=( const vec3_t& other );

	vec3_t operator-( const vec3_t& other );
	vec3_t operator-=( const vec3_t& other );

	vec3_t operator*( float factor );
	vec3_t operator*( const vec3_t& other );
	vec3_t operator*=( float factor );
	vec3_t operator*=( const vec3_t& other );

	vec3_t operator/( float factor );
	vec3_t operator/( const vec3_t& other );
	vec3_t operator/=( float factor );
	vec3_t operator/=( const vec3_t& other );

	bool is_zero( );

	float dot( const vec3_t& other );
	float dist( const vec3_t& other );
	float length( );
	float length_sqr( );
	void normalize( );
	void clamp( );
};

struct view_matrix_t {
	float* operator[ ]( int index ) {
		return matrix[ index ];
	}

	float matrix[ 4 ][ 4 ];
};




bool world_to_screen( const vec3_t& screen_size, const vec3_t& pos, vec3_t& out, view_matrix_t matrix );