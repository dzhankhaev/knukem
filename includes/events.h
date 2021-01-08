#ifndef EVENTS_H

# define EVENTS_H

#include "engine.h"

void			keys_manager(t_engine *engine);
void			event_edit(t_player *player, t_edit *edit);
void			event_edit2(t_player *player, t_edit *edit);
void			event_movement(t_engine *engine);

#endif