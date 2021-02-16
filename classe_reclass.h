#pragma once
#include <cstdint>

class entList_class
{
public:
	class crewmate_class* EntList[15]; //0x0000
};

class crewmate_class
{
public:
	char pad_0000[4]; //0x0000
	bool is_enemy; //0x0004
	char pad_0005[3]; //0x0005
	float x_coord_model; //0x0008
	float y_coord_model; //0x000C
	char pad_0010[8]; //0x0010
	float x_coord_pos; //0x0018
	float y_coord_pos; //0x001C
	char pad_0020[8]; //0x0020
	float health; //0x0028
	float max_health; //0x002C
	char pad_0030[8]; //0x0030
	int32_t x_coord_prev; //0x0038
	int32_t y_coord_prev; //0x003C
	char pad_0040[20]; //0x0040
	float walking_distance; //0x0054
	char pad_0058[28]; //0x0058
	bool is_selected; //0x0074
	char pad_0075[3]; //0x0075
	int32_t room_nr; //0x0078
	int32_t special_room_nr; //0x007C
	char pad_0080[16]; //0x0080
	int32_t x_coord_green; //0x0090
	int32_t y_coord_green; //0x0094
	char pad_0098[272]; //0x0098
	int32_t room_nr2; //0x01A8
	int32_t special_room_nr2; //0x01AC
	char* race; //0x01B0
	uint32_t race_length; //0x01B4
	char pad_01B8[80]; //0x01B8
	class room_class* proom; //0x0208
	char pad_020C[192]; //0x020C
	char* name; //0x02CC
	uint32_t name_length; //0x02D0
	char pad_02D4[20]; //0x02D4
	char* name2; //0x02E8
	int32_t name_length2; //0x02EC
	char pad_02F0[36]; //0x02F0
	class skill_class* pskill; //0x0314
	char pad_0318[508]; //0x0318
	class N00000A05* N0000098E; //0x0514
	char pad_0518[808]; //0x0518
}; //Size: 0x0840

