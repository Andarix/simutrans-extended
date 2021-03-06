/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef OBJ_LABEL_H
#define OBJ_LABEL_H


#include "../simobj.h"
#include "../display/simimg.h"


/*
 * Object which shows the label that indicates that the ground is owned by somebody
 */
class label_t : public obj_t
{
public:
	label_t(loadsave_t *file);
	label_t(koord3d pos, player_t *player, const char *text);
	~label_t();

	void finish_rd();

	void show_info();

	typ get_typ() const { return obj_t::label; }

	image_id get_image() const;
};

#endif
