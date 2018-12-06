#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRAMINO_SETUP(height) \
	tetramino_t tetramino;      \
	tetris_map_t tetris_map;    \
	tetramino_init(&tetramino); \
	tetris_map_init(&tetris_map, height)

TEST(tetramino_init)
{
	tetramino_t tetramino;
	tetramino_init(&tetramino);

	ASSERT_THAT(tetramino.y == -1);
}

TEST(tetramino_move_down)
{
	TETRAMINO_SETUP(1);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 0);
}

TEST(tetramino_move_down_wrong_value)
{
	TETRAMINO_SETUP(1);
	tetramino.y = 100;
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 100);
}

TEST(tetramino_busy_cell)
{
	TETRAMINO_SETUP(1);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_t tetramino2;
	tetramino_init(&tetramino2);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	ASSERT_THAT(tetramino2.y == -1);
}

TEST(tetramino_fill_two_blocks)
{
	TETRAMINO_SETUP(2);
	tetramino_t tetramino2;
	tetramino_init(&tetramino2);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 1);

	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	ASSERT_THAT(tetramino2.y == 0);
}

TEST(tetramino_dead)
{
	TETRAMINO_SETUP(2);

	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_DEAD);
}

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}
int main(int argc, char **argv)
{
	RUN_TEST(tetramino_init);
	RUN_TEST(tetramino_move_down);
	RUN_TEST(tetramino_move_down_wrong_value);
	RUN_TEST(tetramino_map_init);
	RUN_TEST(tetramino_busy_cell);
	RUN_TEST(tetramino_fill_two_blocks);
	RUN_TEST(tetramino_dead);
	PRINT_TEST_RESULTS();
	return 0;
}
