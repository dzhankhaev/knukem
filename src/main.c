#include "engine.h"

int main()
{
	t_engine engine;

	if (init_engine(&engine) != 0)
		return (1);
	start_game(&engine);
	clean_up(&engine);
	return (0);
}
