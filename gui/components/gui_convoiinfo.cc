/*
 * Copyright (c) 1997 - 2001 Hansj�rg Malthaner
 *
 * This file is part of the Simutrans project under the artistic licence.
 * (see licence.txt)
 */

/*
 * Convoi info stats, like loading status bar
 */

#include "gui_convoiinfo.h"

#include "../../simworld.h"
#include "../../vehicle/simvehicle.h"
#include "../../simconvoi.h"
#include "../../simcolor.h"
#include "../../display/simgraph.h"
#include "../../display/viewport.h"
#include "../../player/simplay.h"
#include "../../simline.h"

#include "../../dataobj/translator.h"

#include "../../utils/simstring.h"
#include "../gui_frame.h"
#include "../schedule_gui.h"


gui_convoiinfo_t::gui_convoiinfo_t(convoihandle_t cnv, bool show_line_name)
{
	this->cnv = cnv;
	this->show_line_name = show_line_name;

	filled_bar.set_pos(scr_coord(2, 33));
	filled_bar.set_size(scr_size(100, 4));
	filled_bar.add_color_value(&cnv->get_loading_limit(), COL_YELLOW);
	filled_bar.add_color_value(&cnv->get_loading_level(), COL_GREEN);
}

/**
 * Events werden hiermit an die GUI-components
 * gemeldet
 * @author Hj. Malthaner
 */
bool gui_convoiinfo_t::infowin_event(const event_t *ev)
{
	if(cnv.is_bound()) {
		if(IS_LEFTRELEASE(ev)) {
			cnv->show_info();
			return true;
		}
		else if(IS_RIGHTRELEASE(ev)) {
			welt->get_viewport()->change_world_position(cnv->get_pos());
			return true;
		}
	}
	return false;
}


/**
 * Draw the component
 * @author Hj. Malthaner
 */
void gui_convoiinfo_t::draw(scr_coord offset)
{
	clip_dimension clip = display_get_clip_wh();
	if(! ((pos.y+offset.y) > clip.yy ||  (pos.y+offset.y) < clip.y-32) &&  cnv.is_bound()) {
		int w = 0;
		if (skinverwaltung_t::alerts) {
			switch (cnv->get_state()) {
				case convoi_t::EMERGENCY_STOP:
					display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(2), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("Waiting for clearance!"));
					w += 14;
					break;
				case convoi_t::WAITING_FOR_CLEARANCE_ONE_MONTH:
				case convoi_t::CAN_START_ONE_MONTH:
					display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(3), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("Waiting for clearance!"));
					w += 14;
					break;
				case convoi_t::WAITING_FOR_CLEARANCE_TWO_MONTHS:
				case convoi_t::CAN_START_TWO_MONTHS:
					display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(4), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("clf_chk_stucked"));
					w += 14;
					break;
				case convoi_t::OUT_OF_RANGE:
				case convoi_t::NO_ROUTE:
				case convoi_t::NO_ROUTE_TOO_COMPLEX:
					display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(4), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("clf_chk_noroute"));
					w += 14;
					break;
				default:
					break;
			}
			if (cnv->get_withdraw()){
				display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(2), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("withdraw"));
				w += 14;
			}
			else if (cnv->get_no_load() && !cnv->in_depot()) {
				display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(2), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("No load setting"));
				w += 14;
			}
			if (cnv->get_replace()) {
				display_color_img_with_tooltip(skinverwaltung_t::alerts->get_image_id(1), pos.x + offset.x + 2 + w, pos.y + offset.y + 6, 0, false, false, translator::translate("Replacing"));
				w += 14;
			}
		}
		// name, use the convoi status color for redraw: Possible colors are YELLOW (not moving) BLUE: obsolete in convoi, RED: minus income, BLACK: ok
		int max_x = display_proportional_clip(pos.x+offset.x+2+w, pos.y+offset.y+6, cnv->get_name(), ALIGN_LEFT, cnv->get_status_color(), true)+2;

		w = display_proportional_clip(pos.x+offset.x+2,pos.y+offset.y+6+LINESPACE, translator::translate("Gewinn"), ALIGN_LEFT, SYSCOL_TEXT, true)+2;
		char buf[256];
		money_to_string(buf, cnv->get_jahresgewinn() / 100.0 );
		w += display_proportional_clip(pos.x+offset.x+2+w+5,pos.y+offset.y+6+LINESPACE, buf, ALIGN_LEFT, cnv->get_jahresgewinn()>0?MONEY_PLUS:MONEY_MINUS, true);
		max_x = max(max_x,w+5);

		// only show assigned line, if there is one!
		if (cnv->in_depot()) {
			const char *txt = translator::translate("(in depot)");
			w = display_proportional_clip(pos.x+offset.x+2, pos.y+offset.y+6+2*LINESPACE,txt,ALIGN_LEFT, SYSCOL_TEXT, true)+2;
			max_x = max(max_x,w);
		}
		else if(cnv->get_line().is_bound() && show_line_name) {
			w = display_proportional_clip( pos.x+offset.x+2, pos.y+offset.y+6+2*LINESPACE, translator::translate("Line"), ALIGN_LEFT, SYSCOL_TEXT, true)+2;
			w += display_proportional_clip( pos.x+offset.x+2+w+5, pos.y+offset.y+6+2*LINESPACE, cnv->get_line()->get_name(), ALIGN_LEFT, cnv->get_line()->get_state_color(), true);
			max_x = max(max_x,w+5);
		}
		else{
			// "Destination"
			static cbuffer_t info_buf;
			info_buf.clear();
			info_buf.append(translator::translate("Fahrtziel"));
			info_buf.append(": ");
			const schedule_t *schedule = cnv->get_schedule();
			schedule_gui_t::gimme_short_stop_name(info_buf, cnv->get_owner(), schedule, schedule->get_current_stop(), max_x);
			display_proportional_ellipse(scr_rect(pos.x + offset.x + 2, pos.y+offset.y+6+2* LINESPACE, max(190, max_x), LINESPACE), info_buf, ALIGN_LEFT, SYSCOL_TEXT, true);
		}

		// we will use their images offsets and width to shift them to their correct position
		// this should work with any vehicle size ...
		const int xoff = max(190, max_x);
		int left = pos.x+offset.x+xoff+4;
		for(unsigned i=0; i<cnv->get_vehicle_count();i++) {
			scr_coord_val x, y, w, h;
			const image_id image=cnv->get_vehicle(i)->get_loaded_image();
			display_get_base_image_offset(image, &x, &y, &w, &h );
			display_base_img(image,left-x,pos.y+offset.y+13-y-h/2,cnv->get_owner()->get_player_nr(),false,true);
			left += (w*2)/3;
		}

		// since the only remaining object is the loading bar, we can alter its position this way ...
		filled_bar.draw(pos+offset+scr_coord(xoff,0));
	}
}
