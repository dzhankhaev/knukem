#include "engine.h"
#include "arg_defines.h"
#include "math_utilits.h"
int main()
{
	t_engine engine;

	if (init_engine(&engine) != 0)
		return (1);
	game_loop(&engine);
	clean_up(&engine);
	return (0);
}
