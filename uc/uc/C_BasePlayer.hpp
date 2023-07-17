//LocalPlayer Class
//Basically the same stuff as in C_Entity.hpp. 
class c_base_player {
public:
	auto get_health( ) -> std::int32_t {
		return memory->read<int>( reinterpret_cast< std::int32_t >( this ) + hazedumper::netvars::m_iHealth );
	}
	auto is_dormant( ) -> bool {
		return memory->read<bool>( reinterpret_cast< bool >( this ) + hazedumper::signatures::m_bDormant );
	}
	auto get_origin( ) -> vec3_t {
		return memory->read<vec3_t>( reinterpret_cast< std::uint32_t >( this ) + hazedumper::netvars::m_vecOrigin );
	}

	auto get_bone_matrix( ) -> std::uint32_t {
		return memory->read<std::uint32_t>( reinterpret_cast< std::uintptr_t >( this ) + hazedumper::netvars::m_dwBoneMatrix );
	}

	auto local_team( ) -> std::int32_t {
		return memory->read<std::int32_t>( reinterpret_cast< std::int32_t >( this ) + hazedumper::netvars::m_iTeamNum );
	}

	auto get_vec_view_offset( ) -> vec3_t {
		return memory->read<vec3_t>( reinterpret_cast< std::uint32_t >( this ) + hazedumper::netvars::m_vecViewOffset );
	}


	auto get_bone_pos( int bone_id ) -> vec3_t {
		auto bone_matrix = this->get_bone_matrix( );
		return vec3_t(
			memory->read<float>( bone_matrix + ( 0x30 * bone_id ) + 0x0C ),
			memory->read<float>( bone_matrix + ( 0x30 * bone_id ) + 0x1C ),
			memory->read<float>( bone_matrix + ( 0x30 * bone_id ) + 0x2C )
		);
	}
};