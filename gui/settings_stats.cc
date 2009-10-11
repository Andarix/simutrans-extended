/*
 * Copyright (c) 1997 - 2003 Hansj�rg Malthaner
 *
 * This file is part of the Simutrans project under the artistic licence.
 * (see licence.txt)
 */

#include "../dataobj/einstellungen.h"
#include "../dataobj/umgebung.h"
#include "settings_stats.h"



// just free memory
void settings_stats_t::free_all()
{
	while(  !label.empty()  ) {
		delete label.remove_first();
	}
	while(  !numinp.empty()  ) {
		delete numinp.remove_first();
	}
	while(  !button.empty()  ) {
		delete button.remove_first();
	}
}




/* Nearly automatic lists with controls:
 * BEWARE: The init exit pair MUST match in the same order or else!!!
 */
void settings_general_stats_t::init(einstellungen_t *sets)
{
	INIT_INIT
//	INIT_BOOL( "drive_left", umgebung_t::drive_on_left );	//cannot be switched after loading paks
	INIT_NUM( "autosave", umgebung_t::autosave, 0, 12, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "frames_per_second",umgebung_t::fps, 10, 25, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "fast_forward", umgebung_t::max_acceleration, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_BOOL( "numbered_stations", sets->get_numbered_stations() );
	INIT_NUM( "show_names", umgebung_t::show_names, 0, 3, gui_numberinput_t::AUTOLINEAR, true );
	INIT_NUM( "show_month", umgebung_t::show_month, 0, 5, gui_numberinput_t::AUTOLINEAR, true );
	SEPERATOR
	INIT_NUM( "bits_per_month", sets->get_bits_per_month(), 16, 24, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "use_timeline", sets->get_use_timeline(), 0, 2, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "starting_year", sets->get_starting_year(), 0, 2999, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "starting_month", sets->get_starting_month(), 0, 11, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_NUM( "water_animation_ms", umgebung_t::water_animation, 50, 1000, 25, true );
	INIT_NUM( "random_grounds_probability", umgebung_t::ground_object_probability, 0, 0x7FFFFFFFul, gui_numberinput_t::POWER2, false );
	INIT_NUM( "random_wildlife_probability", umgebung_t::moving_object_probability, 0, 0x7FFFFFFFul, gui_numberinput_t::POWER2, false );
	SEPERATOR
	INIT_BOOL( "pedes_and_car_info", umgebung_t::verkehrsteilnehmer_info );
	INIT_BOOL( "tree_info", umgebung_t::tree_info );
	INIT_BOOL( "ground_info", umgebung_t::ground_info );
	INIT_BOOL( "townhall_info", umgebung_t::townhall_info );
	INIT_BOOL( "only_single_info", umgebung_t::single_info );
	SEPERATOR
	INIT_BOOL( "window_buttons_right", umgebung_t::window_buttons_right );
	INIT_BOOL( "window_frame_active", umgebung_t::window_frame_active );
	SEPERATOR
	INIT_BOOL( "show_tooltips", umgebung_t::show_tooltips );
	INIT_NUM( "tooltip_background_color", umgebung_t::tooltip_color, 0, 255, gui_numberinput_t::AUTOLINEAR, 0 );
	INIT_NUM( "tooltip_text_color", umgebung_t::tooltip_textcolor, 0, 255, gui_numberinput_t::AUTOLINEAR, 0 );
	SEPERATOR
	INIT_NUM( "cursor_overlay_color", umgebung_t::cursor_overlay_color, 0, 255, gui_numberinput_t::AUTOLINEAR, 0 );
	INIT_BOOL( "left_to_right_graphs", umgebung_t::left_to_right_graphs );

	set_groesse( settings_stats_t::get_groesse() );
}

void settings_general_stats_t::read(einstellungen_t *sets)
{
	EXIT_INIT
//	EXIT_BOOL_VALUE( umgebung_t::drive_on_left );	//cannot be switched after loading paks
	EXIT_NUM_VALUE( umgebung_t::autosave );
	EXIT_NUM_VALUE( umgebung_t::fps );
	EXIT_NUM_VALUE( umgebung_t::max_acceleration );

	EXIT_BOOL( sets->set_numbered_stations );
	EXIT_NUM_VALUE( umgebung_t::show_names );
	EXIT_NUM_VALUE( umgebung_t::show_month );

	EXIT_NUM( sets->set_bits_per_month );
	EXIT_NUM( sets->set_use_timeline );
	EXIT_NUM( sets->set_starting_year );
	EXIT_NUM( sets->set_starting_month );

	EXIT_NUM_VALUE( umgebung_t::water_animation );
	EXIT_NUM_VALUE( umgebung_t::ground_object_probability );
	EXIT_NUM_VALUE( umgebung_t::moving_object_probability );

	EXIT_BOOL_VALUE( umgebung_t::verkehrsteilnehmer_info );
	EXIT_BOOL_VALUE( umgebung_t::tree_info );
	EXIT_BOOL_VALUE( umgebung_t::ground_info );
	EXIT_BOOL_VALUE( umgebung_t::townhall_info );
	EXIT_BOOL_VALUE( umgebung_t::single_info );

	EXIT_BOOL_VALUE( umgebung_t::window_buttons_right );
	EXIT_BOOL_VALUE( umgebung_t::window_frame_active );

	EXIT_BOOL_VALUE( umgebung_t::show_tooltips );
	EXIT_NUM_VALUE( umgebung_t::tooltip_color );
	EXIT_NUM_VALUE( umgebung_t::tooltip_textcolor );

	EXIT_NUM_VALUE( umgebung_t::cursor_overlay_color );
	EXIT_BOOL_VALUE( umgebung_t::left_to_right_graphs );
}




void settings_routing_stats_t::init(einstellungen_t *sets)
{
	INIT_INIT
	INIT_BOOL( "seperate_halt_capacities", sets->is_seperate_halt_capacities() );
	INIT_BOOL( "avoid_overcrowding", sets->is_avoid_overcrowding() );
	INIT_BOOL( "no_routing_over_overcrowded", sets->is_no_routing_over_overcrowding() );
	INIT_NUM( "station_coverage", sets->get_station_coverage(), 1, 8, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_NUM( "max_route_steps", sets->get_max_route_steps(), 0, 0x7FFFFFFFul, gui_numberinput_t::POWER2, false );
	INIT_NUM( "max_hops", sets->get_max_hops(), 100, 65000, gui_numberinput_t::POWER2, false );
	INIT_NUM( "max_transfers", sets->get_max_transfers(), 1, 100, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_NUM( "way_straight", sets->way_count_straight, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_curve", sets->way_count_curve, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_double_curve", sets->way_count_double_curve, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_90_curve", sets->way_count_90_curve, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_slope", sets->way_count_slope, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_tunnel", sets->way_count_tunnel, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_max_bridge_len", sets->way_max_bridge_len, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "way_leaving_road", sets->way_count_leaving_road, 1, 1000, gui_numberinput_t::AUTOLINEAR, false );
	set_groesse( settings_stats_t::get_groesse() );
}

void settings_routing_stats_t::read(einstellungen_t *sets)
{
	EXIT_INIT
	EXIT_BOOL( sets->set_seperate_halt_capacities );
	EXIT_BOOL( sets->set_avoid_overcrowding );
	EXIT_BOOL( sets->set_no_routing_over_overcrowding );
	EXIT_NUM( sets->set_station_coverage );
	EXIT_NUM( sets->set_max_route_steps );
	EXIT_NUM( sets->set_max_hops );
	EXIT_NUM( sets->set_max_transfers );
	EXIT_NUM_VALUE( sets->way_count_straight );
	EXIT_NUM_VALUE( sets->way_count_curve );
	EXIT_NUM_VALUE( sets->way_count_double_curve );
	EXIT_NUM_VALUE( sets->way_count_90_curve );
	EXIT_NUM_VALUE( sets->way_count_slope );
	EXIT_NUM_VALUE( sets->way_count_tunnel );
	EXIT_NUM_VALUE( sets->way_max_bridge_len );
	EXIT_NUM_VALUE( sets->way_count_leaving_road );
}




void settings_economy_stats_t::init(einstellungen_t *sets)
{
	INIT_INIT
	INIT_COST( "starting_money", sets->get_starting_money(), 1, 0x7FFFFFFFul, 10000, false );
	INIT_BOOL( "first_beginner", sets->get_beginner_mode() );
	INIT_NUM( "beginner_price_factor", sets->get_beginner_price_factor(), 1, 25000, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_BOOL( "just_in_time", sets->get_just_in_time() );
	INIT_BOOL( "crossconnect_factories", sets->is_crossconnect_factories() );
	INIT_NUM( "crossconnect_factories_percentage", sets->get_crossconnect_factor(), 0, 100, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "factory_spacing", sets->get_factory_spacing(), 1, 32767, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "electric_promille", sets->get_electric_promille(), 0, 1000, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_NUM( "passenger_factor",  sets->get_passenger_factor(), 0, 16, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "factory_worker_radius", sets->get_factory_worker_radius(), 0, 32767, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "factory_worker_percentage", sets->get_factory_worker_percentage(), 0, 100, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "tourist_percentage", sets->get_tourist_percentage(), 0, 100, gui_numberinput_t::AUTOLINEAR, false );
	SEPERATOR
	INIT_NUM( "passenger_multiplier", sets->get_passenger_multiplier(), 0, 100, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "mail_multiplier", sets->get_mail_multiplier(), 0, 100, gui_numberinput_t::AUTOLINEAR, false );
	INIT_NUM( "goods_multiplier", sets->get_goods_multiplier(), 0, 100, gui_numberinput_t::AUTOLINEAR, false );
//	INIT_NUM( "electricity_multiplier", sets->get_electricity_multiplier(), 0, 10000, 10, false );
	SEPERATOR
	INIT_NUM( "growthfactor_villages", sets->get_growthfactor_small(), 1, 10000, 10, false );
	INIT_NUM( "growthfactor_cities", sets->get_growthfactor_medium(), 1, 10000, 10, false );
	INIT_NUM( "growthfactor_capitals", sets->get_growthfactor_large(), 1, 10000, 10, false );
	SEPERATOR
	INIT_BOOL( "random_pedestrians", sets->get_random_pedestrians() );
	INIT_BOOL( "stop_pedestrians", sets->get_show_pax() );
	INIT_NUM( "default_citycar_life", sets->get_stadtauto_duration(), 1, 1200, 12, false );
	set_groesse( settings_stats_t::get_groesse() );
}

void settings_economy_stats_t::read( einstellungen_t *sets )
{
	EXIT_INIT
	EXIT_COST( sets->set_starting_money );
	EXIT_BOOL( sets->set_beginner_mode );
	EXIT_NUM( sets->set_beginner_price_factor );
	EXIT_BOOL( sets->set_just_in_time );
	EXIT_BOOL( sets->set_crossconnect_factories );
	EXIT_NUM( sets->set_crossconnect_factor );
	EXIT_NUM( sets->set_factory_spacing );
	EXIT_NUM( sets->set_electric_promille );
	EXIT_NUM( sets->set_passenger_factor );
	EXIT_NUM( sets->set_factory_worker_radius );
	EXIT_NUM( sets->set_factory_worker_percentage );
	EXIT_NUM( sets->set_tourist_percentage );
	EXIT_NUM( sets->set_passenger_multiplier );
	EXIT_NUM( sets->set_mail_multiplier );
	EXIT_NUM( sets->set_goods_multiplier );
//	EXIT_NUM( sets->set_electricity_multiplier );
	EXIT_NUM( sets->set_growthfactor_small );
	EXIT_NUM( sets->set_growthfactor_medium );
	EXIT_NUM( sets->set_growthfactor_large );
	EXIT_BOOL( sets->set_random_pedestrians );
	EXIT_BOOL( sets->set_show_pax );
	EXIT_NUM( sets->set_stadtauto_duration );
}



