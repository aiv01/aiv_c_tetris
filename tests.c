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
	tetramino_shape_init(tetramino_group, &tetris_map, O_SHAPE)

#define TETRAMINO_INIT_SHAPE(width, height, shape) \
	tetramino_t tetramino_group[TETRAMINI];        \
	tetris_map_t tetris_map;                       \
	tetris_map_init(&tetris_map, width, height);   \
	tetramino_shape_init(tetramino_group, &tetris_map, shape)

#define ASSERT_FIRST__BLOCK_POSITION(_x, _y) \
	ASSERT_THAT(tetramino_group[0].x == _x); \
	ASSERT_THAT(tetramino_group[0].y == _y);

#define ASSERT_SECOND_BLOCK_POSITION(_x, _y) \
	ASSERT_THAT(tetramino_group[1].x == _x); \
	ASSERT_THAT(tetramino_group[1].y == _y);

#define ASSERT_THIRD__BLOCK_POSITION(_x, _y) \
	ASSERT_THAT(tetramino_group[2].x == _x); \
	ASSERT_THAT(tetramino_group[2].y == _y);

#define ASSERT_FOURTH_BLOCK_POSITION(_x, _y) \
	ASSERT_THAT(tetramino_group[3].x == _x); \
	ASSERT_THAT(tetramino_group[3].y == _y);

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
// WHY NOT
TEST(check_row_filled_1x1)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}

// Why is this test passing?
// WHY NOOOOT
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
	TETRAMINO_BOX_GROUP_SETUP(4, 4);

	/*

	This is a "box" tetramino
	And those are the tetramini's positions:

	|-----------|
	|  2  |  3  |
	|-----------|
	|  0  |  1  |
	|-----------|

	It will be spawned at the top-center part of the map
	With one row of space like the Nintendo Tetris system
	So for instance if you have a map that is 4 x 4:

	X X X X
	X 2 3 X
	X 0 1 X
	X X X X

	*/

	ASSERT_THAT(tetramino_group[0].x == 1);
	ASSERT_THAT(tetramino_group[0].y == 2);

	ASSERT_THAT(tetramino_group[1].x == 2);
	ASSERT_THAT(tetramino_group[1].y == 2);

	ASSERT_THAT(tetramino_group[2].x == 1);
	ASSERT_THAT(tetramino_group[2].y == 1);

	ASSERT_THAT(tetramino_group[3].x == 2);
	ASSERT_THAT(tetramino_group[3].y == 1);
}

TEST(tetramino_group_move_down)
{
	TETRAMINO_BOX_GROUP_SETUP(2, 3);
	tetramino_group_move_down(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 2);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 2);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 1);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 1);
}

// Tests to make:

TEST(tetramino_group_move_left)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 3);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 2);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 2);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 1);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 1);
}

TEST(tetramino_group_move_left_blocked)
{
	TETRAMINO_BOX_GROUP_SETUP(2, 2);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 2);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 2);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 1);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 1);
}

TEST(tetramino_group_move_left_multiple)
{
	TETRAMINO_BOX_GROUP_SETUP(4, 4);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);

	tetramino_group_move_left(tetramino_group, &tetris_map);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 0);
	ASSERT_THAT(tetramino_group[0].y == 3);

	ASSERT_THAT(tetramino_group[1].x == 1);
	ASSERT_THAT(tetramino_group[1].y == 3);

	ASSERT_THAT(tetramino_group[2].x == 0);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 1);
	ASSERT_THAT(tetramino_group[3].y == 2);
}

TEST(tetramino_group_move_right)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 4);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 1);
	ASSERT_THAT(tetramino_group[0].y == 3);

	ASSERT_THAT(tetramino_group[1].x == 2);
	ASSERT_THAT(tetramino_group[1].y == 3);

	ASSERT_THAT(tetramino_group[2].x == 1);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 2);
	ASSERT_THAT(tetramino_group[3].y == 2);
}

TEST(tetramino_group_move_right_blocked)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 4);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 1);
	ASSERT_THAT(tetramino_group[0].y == 3);

	ASSERT_THAT(tetramino_group[1].x == 2);
	ASSERT_THAT(tetramino_group[1].y == 3);

	ASSERT_THAT(tetramino_group[2].x == 1);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 2);
	ASSERT_THAT(tetramino_group[3].y == 2);
}

// Confused about this
TEST(tetramino_group_move_right_multiple)
{
	TETRAMINO_BOX_GROUP_SETUP(4, 4);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group[0].x == 2);
	ASSERT_THAT(tetramino_group[0].y == 3);

	ASSERT_THAT(tetramino_group[1].x == 3);
	ASSERT_THAT(tetramino_group[1].y == 3);

	ASSERT_THAT(tetramino_group[2].x == 2);
	ASSERT_THAT(tetramino_group[2].y == 2);

	ASSERT_THAT(tetramino_group[3].x == 3);
	ASSERT_THAT(tetramino_group[3].y == 2);
}

// not really sure about this
TEST(tetramino_group_move_down_wrong_value)
{
	TETRAMINO_BOX_GROUP_SETUP(2, 3);

	tetramino_group->y = 100;
	tetramino_group_move_down(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group->y == 100);
}

TEST(tetramino_group_busy_cell)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 3);
	tetramino_group_move_down(tetramino_group, &tetris_map);

	tetramino_t tetramino_group2[TETRAMINI];
	tetramino_shape_init(tetramino_group2, &tetris_map, O_SHAPE);

	tetramino_group_move_down(tetramino_group2, &tetris_map);

	ASSERT_THAT(tetramino_group2->y == 1);
}

// New tests!

TEST(tetramino_group_init_s_shape)
{
	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	// The first piece (0) is our rotation pivot
	// Tetraminos always spawn one row at the bottom
	// At the center of the map horizontally
	// (On the left if is the number is even)

	// X X X X X X
	// X X 0 3 X X
	// X 1 2 X X X
	// X X X X X X

	// I also added macros for blocks positions
	// It's a basically a new language now lol

	//                           X  Y
	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_init_i_shape)
{
	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

	// X X X X X X
	// X 1 0 2 3 X
	// X X X X X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 1);
	ASSERT_THIRD__BLOCK_POSITION(3, 1);
	ASSERT_FOURTH_BLOCK_POSITION(4, 1);
}

TEST(tetramino_group_init_l_shape)
{
	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

	// X X X X X X
	// X 1 0 2 X X
	// X X X 3 X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 1);
	ASSERT_THIRD__BLOCK_POSITION(3, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

TEST(tetramino_group_init_t_shape)
{
	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

	// X X X X X X
	// X X 2 X X X
	// X 1 0 3 X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(1, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

TEST(tetramino_group_init_z_shape)
{
	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

	// X X X X X X
	// X 1 0 X X X
	// X X 2 3 X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 1);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

TEST(tetramino_group_init_j_shape)
{
	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

	// X X X X X X
	// X 1 0 3 X X
	// X 2 X X X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 1);
	ASSERT_THIRD__BLOCK_POSITION(1, 2);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_o_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, O_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 1 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(3, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_o_shape_left_blocked)
{
	TETRAMINO_INIT_SHAPE(6, 4, O_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 1 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(3, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_o_shape_left_multiple)
{
	TETRAMINO_INIT_SHAPE(6, 4, O_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 1 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(3, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_o_shape_right)
{
	TETRAMINO_INIT_SHAPE(6, 4, O_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 1 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(3, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_o_shape_right_blocked)
{
	TETRAMINO_INIT_SHAPE(6, 4, O_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 1 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(3, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_o_shape_right_multiple)
{
	TETRAMINO_INIT_SHAPE(6, 4, O_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 1 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(3, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_s_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	// X X 1 X X X
	// X X 0 2 X X
	// X X X 3 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(2, 0);
	ASSERT_THIRD__BLOCK_POSITION(3, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

TEST(tetramino_group_rotate_s_shape_left_blocked)
{
	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
	tetramino_group_move_left(tetramino_group, &tetris_map);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	// We're now in this situation:

	// 1 X X X X X
	// 0 2 X X X X
	// X 3 X X X X
	// X X X X X X

	// When I rotate the Tetramino, it will be "bumped"
	// Because it is at the edge of the board
	// So in this case it will be moved one cell on the right

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	// The end position will be this:

	// X X X X X X
	// X 0 3 X X X
	// 1 2 X X X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(1, 1);
	ASSERT_SECOND_BLOCK_POSITION(0, 2);
	ASSERT_THIRD__BLOCK_POSITION(1, 2);
	ASSERT_FOURTH_BLOCK_POSITION(2, 1);
}

TEST(tetramino_group_rotate_s_shape_left_multiple)
{
	// Since the s shape has only two rotations
	// It will return at the original spawn position

	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	// X X X X X X
	// X X 0 3 X X
	// X 1 2 X X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_s_shape_right)
{
	// The s shape has just two rotations
	// So the left and the right will be the same

	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	// X X 1 X X X
	// X X 0 2 X X
	// X X X 3 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(2, 0);
	ASSERT_THIRD__BLOCK_POSITION(3, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

TEST(tetramino_group_rotate_s_shape_right_blocked)
{
	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
	tetramino_group_move_left(tetramino_group, &tetris_map);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	// Same as above:

	// 1 X X X X X
	// 0 2 X X X X
	// X 3 X X X X
	// X X X X X X

	// But this time I rotate on the right

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	// X X X X X X
	// X 0 3 X X X
	// 1 2 X X X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(1, 1);
	ASSERT_SECOND_BLOCK_POSITION(0, 2);
	ASSERT_THIRD__BLOCK_POSITION(1, 2);
	ASSERT_FOURTH_BLOCK_POSITION(2, 1);
}

TEST(tetramino_group_rotate_s_shape_right_multiple)
{
	// This will be the same as the left rotation
	// As the s shape has only two rotations

	TETRAMINO_INIT_SHAPE(6, 4, S_SHAPE);

	// X X X X X X
	// X X 0 3 X X
	// X 1 2 X X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(1, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

TEST(tetramino_group_rotate_i_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

	// X X 1 X X X
	// X X 2 X X X
	// X X 0 X X X
	// X X 3 X X X

	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(2, 0);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(2, 3);
}

TEST(tetramino_group_rotate_i_shape_left_blocked)
{
	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

	// X X X X X X
	// X X X X X X
	// X 1 0 2 3 X
	// X X X X X X

	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
	tetramino_group_move_left(tetramino_group, &tetris_map);
	tetramino_group_move_left(tetramino_group, &tetris_map);

	// Now we have this situation

	// 1 X X X X X
	// 2 X X X X X
	// 0 X X X X X
	// 3 X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	// And we have this now

	// X X X X X X
	// X X X X X X
	// 1 0 2 3 X X
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(1, 2);
	ASSERT_SECOND_BLOCK_POSITION(0, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

// TEST(tetramino_group_rotate_i_shape_left_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

// 	// X X X X X X
// 	// X 1 0 2 3 X
// 	// X X X X X X
// 	// X X X X X X

// 	tetramino_group_move_down(tetramino_group, &tetris_map);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_i_shape_right)
{
	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

	// X X 1 X X X
	// X X 2 X X X
	// X X 0 X X X
	// X X 3 X X X

	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(2, 0);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(2, 3);
}

TEST(tetramino_group_rotate_i_shape_right_blocked)
{
	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

	// X X X 1 X X
	// X X X 2 X X
	// X X X 0 X X
	// X X X 3 X X

	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);
	tetramino_group_move_right(tetramino_group, &tetris_map);

	// Now this

	// X X X X X 1
	// X X X X X 2
	// X X X X X 0
	// X X X X X 3

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	// And this

	// X X X X X X
	// X X X X X X
	// X X 3 0 2 1
	// X X X X X X

	ASSERT_FIRST__BLOCK_POSITION(3, 2);
	ASSERT_SECOND_BLOCK_POSITION(5, 2);
	ASSERT_THIRD__BLOCK_POSITION(4, 2);
	ASSERT_FOURTH_BLOCK_POSITION(2, 2);
}

// TEST(tetramino_group_rotate_i_shape_right_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, I_SHAPE);

// 	// X X X X X X
// 	// X 1 0 2 3 X
// 	// X X X X X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_l_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

	// X X X X X X
	// X X 2 3 X X
	// X X 0 X X X
	// X X 1 X X X

	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(2, 3);
	ASSERT_THIRD__BLOCK_POSITION(2, 1);
	ASSERT_FOURTH_BLOCK_POSITION(3, 1);
}

// TEST(tetramino_group_rotate_l_shape_left_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

// 	// X X X X X X
// 	// X 1 0 2 X X
// 	// X X X 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_l_shape_left_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

// 	// X X X X X X
// 	// X 1 0 2 X X
// 	// X X X 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_l_shape_right)
{
	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

	// X X 1 X X X
	// X X 0 X X X
	// X 3 2 X X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(2, 0);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(1, 2);
}

// TEST(tetramino_group_rotate_l_shape_right_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

// 	// X X X X X X
// 	// X 1 0 2 X X
// 	// X X X 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_l_shape_right_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, L_SHAPE);

// 	// X X X X X X
// 	// X 1 0 2 X X
// 	// X X X 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_t_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

	// X X X X X X
	// X X 1 X X X
	// X 3 0 X X X
	// X X 2 X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(2, 1);
	ASSERT_THIRD__BLOCK_POSITION(2, 3);
	ASSERT_FOURTH_BLOCK_POSITION(1, 2);
}

// TEST(tetramino_group_rotate_t_shape_left_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

// 	// X X X X X X
// 	// X X 2 X X X
// 	// X 1 0 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_t_shape_left_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

// 	// X X X X X X
// 	// X X 2 X X X
// 	// X 1 0 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_t_shape_right)
{
	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

	// X X X X X X
	// X X 1 X X X
	// X X 0 3 X X
	// X X 2 X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 2);
	ASSERT_SECOND_BLOCK_POSITION(2, 1);
	ASSERT_THIRD__BLOCK_POSITION(2, 3);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

// TEST(tetramino_group_rotate_t_shape_right_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

// 	// X X X X X X
// 	// X X 2 X X X
// 	// X 1 0 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_t_shape_right_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, T_SHAPE);

// 	// X X X X X X
// 	// X X 2 X X X
// 	// X 1 0 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_z_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

	// X X X 1 X X
	// X X 0 2 X X
	// X X 3 X X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(3, 0);
	ASSERT_THIRD__BLOCK_POSITION(3, 1);
	ASSERT_FOURTH_BLOCK_POSITION(2, 2);
}

// TEST(tetramino_group_rotate_z_shape_left_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

// 	// X X X X X X
// 	// X 1 0 X X X
// 	// X X 2 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_z_shape_left_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

// 	// X X X X X X
// 	// X 1 0 X X X
// 	// X X 2 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_z_shape_right)
{
	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

	// X X X 1 X X
	// X X 0 2 X X
	// X X 3 X X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(3, 0);
	ASSERT_THIRD__BLOCK_POSITION(3, 1);
	ASSERT_FOURTH_BLOCK_POSITION(2, 2);
}

// TEST(tetramino_group_rotate_z_shape_right_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

// 	// X X X X X X
// 	// X 1 0 X X X
// 	// X X 2 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_z_shape_right_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, Z_SHAPE);

// 	// X X X X X X
// 	// X 1 0 X X X
// 	// X X 2 3 X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_j_shape_left)
{
	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

	// X X 2 X X X
	// X X 0 X X X
	// X X 1 3 X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(2, 2);
	ASSERT_THIRD__BLOCK_POSITION(2, 0);
	ASSERT_FOURTH_BLOCK_POSITION(3, 2);
}

// TEST(tetramino_group_rotate_j_shape_left_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

// 	// X X X X X X
// 	// X 1 0 3 X X
// 	// X 2 X X X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_j_shape_left_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

// 	// X X X X X X
// 	// X 1 0 3 X X
// 	// X 2 X X X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, -1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

TEST(tetramino_group_rotate_j_shape_right)
{
	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

	// X 3 1 X X X
	// X X 0 X X X
	// X X 2 X X X
	// X X X X X X

	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

	ASSERT_FIRST__BLOCK_POSITION(2, 1);
	ASSERT_SECOND_BLOCK_POSITION(2, 0);
	ASSERT_THIRD__BLOCK_POSITION(2, 2);
	ASSERT_FOURTH_BLOCK_POSITION(1, 0);
}

// TEST(tetramino_group_rotate_j_shape_right_blocked)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

// 	// X X X X X X
// 	// X 1 0 3 X X
// 	// X 2 X X X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// TEST(tetramino_group_rotate_j_shape_right_multiple)
// {
// 	TETRAMINO_INIT_SHAPE(6, 4, J_SHAPE);

// 	// X X X X X X
// 	// X 1 0 3 X X
// 	// X 2 X X X X
// 	// X X X X X X

// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);
// 	tetramino_group_rotate(tetramino_group, &tetris_map, 1);

// 	ASSERT_FIRST__BLOCK_POSITION(0, 0);
// 	ASSERT_SECOND_BLOCK_POSITION(0, 0);
// 	ASSERT_THIRD__BLOCK_POSITION(0, 0);
// 	ASSERT_FOURTH_BLOCK_POSITION(0, 0);
// }

// ---------------------- //
//  PIERA YOU'RE DONE <3  //
// ---------------------- //

// this won't work but i have to push
TEST(tetramino_group_fill_two_blocks)
{
	TETRAMINO_BOX_GROUP_SETUP(4, 4);
	tetramino_group_move_down(tetramino_group, &tetris_map);
	tetramino_group_move_down(tetramino_group, &tetris_map);

	ASSERT_THAT(tetramino_group->y == 3);

	tetramino_t tetramino_group2[TETRAMINI];
	tetramino_shape_init(tetramino_group2, &tetris_map, O_SHAPE);
	tetramino_group_move_down(tetramino_group2, &tetris_map);
	tetramino_group_move_down(tetramino_group2, &tetris_map);

	ASSERT_THAT(tetramino_group2->y == 1);
}

TEST(tetramino_group_dead)
{
	TETRAMINO_BOX_GROUP_SETUP(3, 3);

	ASSERT_THAT(tetramino_group_move_down(tetramino_group, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_group_move_down(tetramino_group, &tetris_map) == TETRAMINO_DEAD);
	ASSERT_THAT(tetramino_group_move_down(tetramino_group, &tetris_map) == TETRAMINO_DEAD);
}

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1, 1);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}

int main(int argc, char **argv)
{
	// TETRAMINO INIT AND MOVEMENTS
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
	// TETRAMINI INIT AND MOVEMENTS
	RUN_TEST(tetramino_group_init);
	RUN_TEST(tetramino_group_move_down);
	RUN_TEST(tetramino_group_move_left);
	RUN_TEST(tetramino_group_move_left_blocked);
	RUN_TEST(tetramino_group_move_left_multiple);
	RUN_TEST(tetramino_group_move_right);
	RUN_TEST(tetramino_group_move_right_blocked);
	RUN_TEST(tetramino_group_move_right_multiple);
	RUN_TEST(tetramino_group_move_down_wrong_value);
	// RUN_TEST(tetramino_group_busy_cell); // WHY IS IT BROKEN???
	// SHAPE INITS
	RUN_TEST(tetramino_group_init_s_shape);
	RUN_TEST(tetramino_group_init_i_shape);
	RUN_TEST(tetramino_group_init_l_shape);
	RUN_TEST(tetramino_group_init_t_shape);
	RUN_TEST(tetramino_group_init_z_shape);
	RUN_TEST(tetramino_group_init_j_shape);
	// O SHAPE
	RUN_TEST(tetramino_group_rotate_o_shape_left);
	RUN_TEST(tetramino_group_rotate_o_shape_left_blocked);
	RUN_TEST(tetramino_group_rotate_o_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_o_shape_right);
	RUN_TEST(tetramino_group_rotate_o_shape_right_blocked);
	RUN_TEST(tetramino_group_rotate_o_shape_right_multiple);
	// S SHAPE
	RUN_TEST(tetramino_group_rotate_s_shape_left);
	RUN_TEST(tetramino_group_rotate_s_shape_left_blocked);
	RUN_TEST(tetramino_group_rotate_s_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_s_shape_right);
	RUN_TEST(tetramino_group_rotate_s_shape_right_blocked);
	RUN_TEST(tetramino_group_rotate_s_shape_right_multiple);
	// I SHAPE
	RUN_TEST(tetramino_group_rotate_i_shape_left);
	RUN_TEST(tetramino_group_rotate_i_shape_left_blocked);
	// RUN_TEST(tetramino_group_rotate_i_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_i_shape_right);
	// RUN_TEST(tetramino_group_rotate_i_shape_right_blocked);
	// RUN_TEST(tetramino_group_rotate_i_shape_right_multiple);
	// L SHAPE
	RUN_TEST(tetramino_group_rotate_l_shape_left);
	// RUN_TEST(tetramino_group_rotate_l_shape_left_blocked);
	// RUN_TEST(tetramino_group_rotate_l_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_l_shape_right);
	// RUN_TEST(tetramino_group_rotate_l_shape_right_blocked);
	// RUN_TEST(tetramino_group_rotate_l_shape_right_multiple);
	// T SHAPE
	RUN_TEST(tetramino_group_rotate_t_shape_left);
	// RUN_TEST(tetramino_group_rotate_t_shape_left_blocked);
	// RUN_TEST(tetramino_group_rotate_t_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_t_shape_right);
	// RUN_TEST(tetramino_group_rotate_t_shape_right_blocked);
	// RUN_TEST(tetramino_group_rotate_t_shape_right_multiple);
	// Z SHAPE
	RUN_TEST(tetramino_group_rotate_z_shape_left);
	// RUN_TEST(tetramino_group_rotate_z_shape_left_blocked);
	// RUN_TEST(tetramino_group_rotate_z_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_z_shape_right);
	// RUN_TEST(tetramino_group_rotate_z_shape_right_blocked);
	// RUN_TEST(tetramino_group_rotate_z_shape_right_multiple);
	// J SHAPE
	RUN_TEST(tetramino_group_rotate_j_shape_left);
	// RUN_TEST(tetramino_group_rotate_j_shape_left_blocked);
	// RUN_TEST(tetramino_group_rotate_j_shape_left_multiple);
	RUN_TEST(tetramino_group_rotate_j_shape_right);
	// RUN_TEST(tetramino_group_rotate_j_shape_right_blocked);
	// RUN_TEST(tetramino_group_rotate_j_shape_right_multiple);
	// RNG
	// RUN_TEST(check_queue_init);
	// RUN_TEST(check_queue_next;
	// RUN_TEST(check_queue_swap;
	// OTHER STUFF
	RUN_TEST(check_row_filled_1x1);
	RUN_TEST(check_row_filled_2x2);
	// RUN_TEST(tetramino_group_fill_two_blocks);
	// RUN_TEST(tetramino_group_dead);
	PRINT_TEST_RESULTS();
	return 0;
}
