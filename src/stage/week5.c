	/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week5.h"

#include "../archive.h"
#include "../mem.h"

//Week 5 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Back wall
	Gfx_Tex tex_back1; //Second floor
	Gfx_Tex tex_back2; //Lower bop
	Gfx_Tex tex_back3; //Santa
	Gfx_Tex tex_back4; //Upper bop
} Back_Week5;

//Week 5 background functions
void Back_Week5_DrawBG(StageBack *back)
{
	Back_Week5 *this = (Back_Week5*)back;
	
	fixed_t fx, fy;
	
	fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;
	
	//Draw Santa
	
	//Draw snow
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT snow_src = {0, 0, 0, 0};
	RECT_FIXED snow_dst = {
		FIXED_DEC(-350,1) - fx,
		FIXED_DEC(44,1) - fy,
		FIXED_DEC(570,1),
		FIXED_DEC(27,1)
	};
	

	//Draw boppers
	static const struct Back_Week5_LowerBop
	{
		RECT src;
		RECT_FIXED dst;
	} lbop_piece[] = {
		{{0, 0, 162, 241}, {FIXED_DEC(-100,1), FIXED_DEC(-100,1), FIXED_DEC(55,1), FIXED_DEC(75,1)}},
	};
	
	const struct Back_Week5_LowerBop *lbop_p = lbop_piece;
	for (size_t i = 0; i < COUNT_OF(lbop_piece); i++, lbop_p++)
	{
		RECT_FIXED lbop_dst = {
			lbop_p->dst.x - fx - (beat_bop << 1),
			lbop_p->dst.y - fy + (beat_bop << 3),
			lbop_p->dst.w + (beat_bop << 2),
			lbop_p->dst.h - (beat_bop << 3),
		};
		Stage_DrawTex(&this->tex_back2, &lbop_p->src, &lbop_dst, stage.camera.bzoom);
	}
	
	//Draw second floor
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	static const struct Back_Week5_FloorPiece
	{
		RECT src;
		fixed_t scale;
	} floor_piece[] = {
		{{  0, 0, 0, 0}, FIXED_DEC(14,10)},
		{{  0, 0,   0,   0}, FIXED_DEC(7,1)},
		{{  0, 0,   0,   0}, FIXED_DEC(14,10)},
	};
	
	RECT_FIXED floor_dst = {
		FIXED_DEC(-500,1) - fx,
		FIXED_DEC(-500,1) - fy,
		0, //????
		FIXED_DEC(250,1) //How big it is on the Y axis
	};
	
	const struct Back_Week5_FloorPiece *floor_p = floor_piece;
	for (size_t i = 0; i < COUNT_OF(floor_piece); i++, floor_p++)
	{
		floor_dst.w = floor_p->src.w ? (floor_p->src.w * floor_p->scale) : floor_p->scale;
		Stage_DrawTex(&this->tex_back1, &floor_p->src, &floor_dst, stage.camera.bzoom);
		floor_dst.x += floor_dst.w;
	}
	
	//Draw boppers
	static const struct Back_Week5_UpperBop
	{
		RECT src;
		RECT_FIXED dst;
	} ubop_piece[] = {
		{{0, 0,   0,  0}, {FIXED_DEC(-200,1), FIXED_DEC(-132,1), FIXED_DEC(256,1)*6/7, FIXED_DEC(76,1)*6/7}},
		{{0,  0,   0,  0}, {FIXED_DEC(50,1), FIXED_DEC(-132,1), FIXED_DEC(256,1)*6/7, FIXED_DEC(76,1)*6/7}}
	};
	
	const struct Back_Week5_UpperBop *ubop_p = ubop_piece;
	for (size_t i = 0; i < COUNT_OF(ubop_piece); i++, ubop_p++)
	{
		RECT_FIXED ubop_dst = {
			ubop_p->dst.x - fx,
			ubop_p->dst.y - fy + (beat_bop << 2),
			ubop_p->dst.w,
			ubop_p->dst.h - (beat_bop << 2),
		};
		Stage_DrawTex(&this->tex_back4, &ubop_p->src, &ubop_dst, stage.camera.bzoom);
	}
	
	//Draw back wall
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	static const struct Back_Week5_WallPiece
	{
		RECT src;
		fixed_t scale;
	} wall_piece[] = {
		{{  0, 0,   0,   0}, FIXED_DEC(1,1)},
		{{  0, 0,   0,   0}, FIXED_DEC(1,1)},
		{{  0, 0,   0,   0}, FIXED_DEC(1,1)},
	};
	
	RECT_FIXED wall_dst = {
		FIXED_DEC(-130,1) - fx,
		FIXED_DEC(-80,1) - fy,
		0,
		FIXED_DEC(200,1)
	};


	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT wall_src = {0, 0, 256, 256};
	RECT_FIXED wall_fill;
	wall_fill.x = FIXED_DEC(-242,1) - fx,
	wall_fill.y = FIXED_DEC(-140,1) - fy,
	wall_fill.w = FIXED_DEC(415,1);
	wall_fill.h = FIXED_DEC(290,1);
	Stage_DrawTex(&this->tex_back1, &wall_src, &wall_fill, stage.camera.bzoom);
	
	const struct Back_Week5_WallPiece *wall_p = wall_piece;
	for (size_t i = 0; i < COUNT_OF(wall_piece); i++, wall_p++)
	{
		wall_dst.w = wall_p->src.w ? (wall_p->src.w * wall_p->scale) : wall_p->scale;
		Stage_DrawTex(&this->tex_back1, &wall_p->src, &wall_dst, stage.camera.bzoom);
		wall_dst.x += wall_dst.w;
	}
}

void Back_Week5_Free(StageBack *back)
{
	Back_Week5 *this = (Back_Week5*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week5_New()
{
	//Allocate background structure
	Back_Week5 *this = (Back_Week5*)Mem_Alloc(sizeof(Back_Week5));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = NULL;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week5_DrawBG;
	this->back.free = Back_Week5_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK5\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
	Gfx_LoadTex(&this->tex_back4, Archive_Find(arc_back, "back4.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
