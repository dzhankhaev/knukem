#include "engine.h"

void	render_cross(t_engine *engine)
{
	render_line((t_line){(W >> 1) - 20, (W >> 1) + 20, (H >> 1) - 2,
				(H >> 1) - 2, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 20, (W >> 1) + 20, (H >> 1) + 1,
				(H >> 1) + 1, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 20, (W >> 1) - 20, (H >> 1) - 2,
				(H >> 1) + 1, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) + 20, (W >> 1) + 20, (H >> 1) - 2,
				(H >> 1) + 1, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 2, (W >> 1) - 2, (H >> 1) - 20,
				(H >> 1) + 20, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) + 1, (W >> 1) + 1, (H >> 1) - 20,
				(H >> 1) + 20, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 2, (W >> 1) + 1, (H >> 1) - 20,
				(H >> 1) - 20, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 2, (W >> 1) + 1, (H >> 1) + 20,
				(H >> 1) + 20, 0}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 19, (W >> 1) + 19, (H >> 1) - 1,
				(H >> 1) - 1, 0xffffff}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 19, (W >> 1) + 19, H >> 1,
				H >> 1, 0xffffff}, engine->screen, engine->borders);
	render_line((t_line){(W >> 1) - 1, (W >> 1) - 1, (H >> 1) - 19,
				(H >> 1) + 19, 0xffffff}, engine->screen, engine->borders);
	render_line((t_line){W >> 1, W >> 1, (H >> 1) - 19,
				(H >> 1) + 19, 0xffffff}, engine->screen, engine->borders);
}