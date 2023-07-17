auto calc_angle( vec3_t src, vec3_t dst ) -> vec3_t {
	vec3_t retAngle;
	vec3_t delta = src - dst;
	float hyp = sqrtf( delta.x * delta.x + delta.y * delta.y );
	retAngle.x = ( float )( atan( delta.z / hyp ) * ( 180.0f / M_PI ) );
	retAngle.y = ( float )( atan( delta.y / delta.x ) * ( 180.0f / M_PI ) );
	retAngle.z = 0.f;
	if ( delta.x >= 0.f )
		retAngle.y += 180.f;

	retAngle.normalize( );

	return retAngle;
}

class c_client_state {
public:
	auto get_view_angle( ) -> vec3_t {
		return memory->read<vec3_t>( reinterpret_cast< std::uint32_t >( this ) + hazedumper::signatures::dwClientState_ViewAngles );
	}
};