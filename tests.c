#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRAMINO_SETUP(width, height)           \
	tetramino_t tetramino;                       \
	tetris_map_t tetris_map;                     \
	tetris_map_init(&tetris_map, width, height); \
	tetramino_init(&tetramino, &tetris_map)

#define TETRAMINO_BOX_GROUP_SETUP(width, height) \
	tetramino_t tetramino_group[TETRAMINI];      \
	tetris_map_t tetris_map;                     \
	tetris_map_init(&tetris_map, width, height); \
	tetramino_o_shape_init(tetramino_group, &tetris_map)

TEST(tetramino_init)
{
	TETRAMINO_SETUP(1, 1);

	ASSERT_THAT(tetramino.y == -1);
}

TEST(tetramino_move_down)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 0);
}

TEST(tetramino_move_right_blocked)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_right(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_right)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_right_multiple)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_right(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_left_blocked)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_left(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_left(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left_multiple)
{
	TETRAMINO_SETUP(3, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_left(&tetramino, &tetris_map);
	tetramino_move_left(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_down_wrong_value)
{
	TETRAMINO_SETUP(1, 1);
	tetramino.y = 100;
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 100);
}

TEST(tetramino_busy_cell)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_t tetramino2;
	tetramino_init(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	ASSERT_THAT(tetramino2.y == -1);
}

TEST(tetramino_fill_two_blocks)
{
	TETRAMINO_SETUP(2, 2);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 1);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	SDL_Log("%d", tetramino2.y);

	ASSERT_THAT(tetramino2.y == 0);
}

TEST(tetramino_dead)
{
	TETRAMINO_SETUP(1, 2);

	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_DEAD);
}

// Why is this test passing?
TEST(check_row_filled_1x1)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}

// Why is this test passing?
TEST(check_row_filled_2x2)
{
	TETRAMINO_SETUP(2, 2);
	tetramino_move_left(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, &tetris_map);
	tetramino_move_right(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	ASSERT_THAT(tetris_map.cell[2] == 0);
	ASSERT_THAT(tetris_map.cell[3] == 0);
}

// ----------------------- //
//  PIERA START FROM HERE  //
// ----------------------- //

TEST(tetramino_group_init)
{
	TETRAMINO_BOX_GROUP_SETUP(2, 2);

	/*

	This is a "box" tetramino
	And those are the tetramini's positions:

	|-----------|
	|  0  |  1  |
	|-----------|
	|  2  |  3  |
	|-----------|

	It will be spawned at the top-center part of the map
	So for instance if you have a map that is 4 x 4:

	X O O X
	X O O X
	X X X X
	X X X X

	(O is the tetramino)

	*/

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 0);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 0);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 1);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 1);
}

TEST(tetramino_group_move_down)
{
	TETRAMINO_BOX_GROUP_SETUP(2, 3);
	tetramino_group_move_down(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 1);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 1);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 2);
}

// Tests to make:

// TEST(tetramino_group_move_left)
TEST(tetramino_group_move_left)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 3);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 1);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 1);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 2);
}
// TEST(tetramino_group_move_left_blocked)
TEST(tetramino_group_move_left_blocked)
{
	TETRAMINO_BOX_GROUP_SETUP(2, 2);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 0);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 0);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 1);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 1);
}
// TEST(tetramino_group_move_left_multiple)
// TEST(tetramino_group_move_right)
TEST(tetramino_group_move_right)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 3);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 1);
	ASSERT_THAT(tetramino_group[0].y == 1);

	ASSERT_THAT(tetramino_group[1].x == 2);
	ASSERT_THAT(tetramino_group[1].y == 1);

	ASSERT_THAT(tetramino_group[2].x == 1);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 2);
	ASSERT_THAT(tetramino_group[3].y == 2);

}
// TEST(tetramino_group_move_right_blocked)
// TEST(tetramino_group_move_right_multiple)
// TEST(tetramino_group_move_down_wrong_value)
// TEST(tetramino_group_busy_cell)
// TEST(tetramino_group_fill_two_blocks)
// TEST(tetramino_group_dead)

// ---------------------- //
//  PIERA YOU'RE DONE <3  //
// ---------------------- //

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1, 1);

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
	RUN_TEST(tetramino_move_right);
	RUN_TEST(tetramino_move_right_blocked);
	RUN_TEST(tetramino_move_right_multiple);
	RUN_TEST(tetramino_move_left_blocked);
	RUN_TEST(tetramino_move_left);
	RUN_TEST(tetramino_move_left_multiple);
	RUN_TEST(check_row_filled_1x1);
	RUN_TEST(check_row_filled_2x2);
	RUN_TEST(tetramino_group_init);
	RUN_TEST(tetramino_group_move_down);
	RUN_TEST(tetramino_group_move_right);
	RUN_TEST(tetramino_group_move_left);
	RUN_TEST(tetramino_group_move_left_blocked);
	PRINT_TEST_RESULTS();
	return 0;
}
