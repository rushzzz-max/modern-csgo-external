
class c_entity {
public:
	c_entity( ) = default;

	auto get_health( ) -> int {
		return memory->read<int>( reinterpret_cast< int >( this ) + hazedumper::netvars::m_iHealth );
	}
	auto is_dormant( ) -> bool {
		return memory->read<bool>( reinterpret_cast< bool >( this ) + hazedumper::signatures::m_bDormant );
	}
	auto get_origin( ) -> vec3_t {
		return memory->read<vec3_t>( reinterpret_cast< std::uint32_t >( this ) + hazedumper::netvars::m_vecOrigin );
	}
	//Networktable needed to get access to the ClassID Class 
	auto get_network_table( ) -> INetworkTable* {
		return memory->read<INetworkTable*>( reinterpret_cast< std::uintptr_t >( this ) + 0x8 );
	}

	auto get_bone_matrix( ) -> std::uint32_t {
		return memory->read<std::uint32_t>( reinterpret_cast< std::uint32_t >( this ) + hazedumper::netvars::m_dwBoneMatrix );
	}

	auto get_entity_team( ) -> std::int32_t {
		return memory->read<std::int32_t>( reinterpret_cast< std::int32_t >( this ) + hazedumper::netvars::m_iTeamNum );
	}


	auto get_bone_pos( uintptr_t bone_matrix, int boneID ) -> vec3_t {
		DWORD tempBoneMatrix = memory->read<std::uint32_t>( reinterpret_cast<std::uint32_t>( this ) + hazedumper::netvars::m_dwBoneMatrix );
		return vec3_t(
			memory->read<float>( tempBoneMatrix + ( 0x30 * boneID ) + 0x0C ),
			memory->read<float>( tempBoneMatrix + ( 0x30 * boneID ) + 0x1C ),
			memory->read<float>( tempBoneMatrix + ( 0x30 * boneID ) + 0x2C )
		);
	}
};
//truncation
struct info {
	c_entity* entity;
	c_base_player* local_player;
	int health;
	int dormant;
};

struct cached_game {
	std::vector<info>players;
	std::vector<info>temp_players;
};