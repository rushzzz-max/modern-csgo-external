cached_game c_game;

#include <mutex>
#include <shared_mutex>

// Ok this is meme. But I want to make something fast so its fine by now xD
vec3_t screen_size( 1920, 1080, 0 );

std::shared_mutex mtx;

auto cache_loop( ) -> void {
	while ( true ) {
		
		c_game.temp_players.clear( );

		auto local_player = memory->read<c_base_player*>( globals::client_dll + hazedumper::signatures::dwLocalPlayer );
		//auto client_state = memory->read<c_client_state*>( globals::client_dll + hazedumper::signatures::dwClientState );
		for ( int i = 0; i < 64; i++ ) { 
			auto entity = memory->read<c_entity*>( globals::client_dll + hazedumper::signatures::dwEntityList + i * 0x10 );

			auto entity_health = entity->get_health( );
			if ( !entity_health )
				continue;

			auto dormant = entity->is_dormant( );



			info ent;
			ent.entity = entity;
			ent.local_player = local_player;
			ent.dormant = dormant;
			ent.health = entity_health;
			//ent.client_state = client_state;
			c_game.temp_players.push_back( ent );
		}
		
		{
			std::unique_lock lock(mtx);
			c_game.players = c_game.temp_players;
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
	}
}

auto esp_loop( ) -> void {
	while ( true ) {
		std::shared_lock lock(mtx);
		for ( auto& entity : c_game.players ) {
		
			//If our health is invalid we continue
			if ( !entity.health )
				continue;

			if ( entity.entity->is_dormant( ) )
				continue;

			//std::cout << health << std::endl;

			if ( entity.entity->get_entity_team( ) == entity.local_player->local_team( ) )
				continue;

			auto origin = entity.entity->get_origin( );

			auto local_origin = entity.local_player->get_origin( );

		
			//std::cout << bone_matrix << std::endl;

			vec3_t head_position = entity.entity->get_bone_pos( entity.entity->get_bone_matrix( ), 8  );

			vec3_t screen_top, screen_bottom;

			auto view_matrix = memory->read<view_matrix_t>( globals::client_dll + hazedumper::signatures::dwViewMatrix );

			if ( !world_to_screen( screen_size, origin, screen_bottom, view_matrix ) || !world_to_screen( screen_size, head_position, screen_top, view_matrix ) )
				continue;

			//Box Calculation
			int box_height = screen_bottom.y - screen_top.y;
			int box_width = box_height / 2;
			//HeadBox Calculation
			int head_box_size = box_height / 8;
			int head_box_left = screen_top.x - ( box_width / 2 ) + ( box_width - head_box_size ) / 2;
			int head_box_top = screen_top.y;
			int head_box_width = head_box_size;
			int head_box_height = head_box_size;

			memory->draw_rect( screen_top.x - box_width / 2, screen_top.y, box_width, box_height, 1, 255, 0, 0 );

			memory->draw_rect( head_box_left, head_box_top, head_box_width, head_box_height, 1, 255, 255, 0 );
		}
		//Sleep( 3000 );
	}

}

auto aimbot_thread( ) -> void {
	while ( true ) {
		{
			std::shared_lock lock(mtx);
			auto client_state = memory->read < c_client_state*>( globals::client_dll + hazedumper::signatures::dwClientState );
			auto view_angle = client_state->get_view_angle( );

			float BestFov = 10.f;
			vec3_t final_aim_angle{ 0,0,0 };
			vec3_t smoothedAngle;

			for ( auto& players : c_game.players ) {
				auto local_origin = players.local_player->get_origin( );
				auto vec_view_offset = players.local_player->get_vec_view_offset( );
				auto head_position = local_origin + vec_view_offset;
			
				if ( !players.health )
					continue;
				
				if ( players.entity->get_entity_team( ) == players.local_player->local_team( ) )
					continue;

				vec3_t entity_head = players.entity->get_bone_pos( players.entity->get_bone_matrix( ), 8 );
				vec3_t aim_angle = calc_angle( head_position, entity_head );
				vec3_t relative_angle = aim_angle - view_angle;
				float Fov = std::hypot( relative_angle.x, relative_angle.y );

				if ( Fov < BestFov ) {
					BestFov = Fov;
					final_aim_angle = aim_angle;
				}
			
			}
		}
		/*if ( !final_aim_angle.is_zero( ) && GetAsyncKeyState( 0x06 ) ) {
			memory->write<vec3_t>(client_state->get_view_angle( ), final_aim_angle );

		}*/
		std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
	}
}
