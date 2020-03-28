#pragma once
#include "Define.h"
#include <vector>

const static float INIT_X = CENTER_X;
const static float INIT_Y = -100;
const static float BOSS_DEFAULT_X = CENTER_X;
const static float BOSS_DEFAULT_Y = OUT_H / 6;
const static float HP_X = IN_X + 24;
const static float HP_W = IN_W - 24 * 2;
const static float HP_Y = WIN_H - 30;
const static int IMG_POS_W = 80;
const static int IMG_POS_H = 40;
const static int INF_HP = 99999999;

#define MAXSPELLNUM_PER_STAGE 50

const int HP[eLevel_Num][eStage_Num][MAXSPELLNUM_PER_STAGE] = {
	{ 
	/*01*/{ 25000,	23000,	32000,	35000,	23000,	55000,	},
	/*02*/{ 25000,	25000,	40000,	25000,	40000,	25000,	65000,	25000,	65000,	},
	/*03*/{ 20000,	35000,	25000,	38000,	30000,	60000,	45000,	50000,	35000,	25000,	33000,	55000,	},
	/*04*/{ 25000,	53000,	25000,	30000,	27000,	70000,	30000,	70000,	33000,	65000,	33000, INF_HP,	},
	/*05*/{ 35000,	45000,	40000,	90000,	45000,	45000,	39000,	42000,	30000,	75000,	
			42000,	62000,	52000,	70000,	40000,  90000, INF_HP, },
	/*EX*/{ 35000,	45000,	35000,	50000,
		/*059妖飛　*/25000,	35000, 45000, 38000, 60000,
		/*064濤子　*/27000,	40000, 37000, 50000, 52000,
		/*069幽々巳*/20000,	45000, 26000, 50000, 50000,
		/*074妲己　*/20000, 50000, 37000, 30000, 65000, 200000,
	},
	/*PH*/{ 10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000, },
	},
	{ 
	/*01*/{ 25000,	23000,	32000,	35000,	23000,	55000, },
	/*02*/{ 25000,	25000,	40000,	25000,	40000,	25000,	75000,	25000,	65000, },
	/*03*/{ 20000,	35000,	25000,	38000,	30000,	60000,	35000,	50000,	35000,	35000,	33000,	60000, },
	/*04*/{ 25000,	53000,	25000,	30000,	27000,	70000,	30000,	85000,	33000,	65000,	33000, INF_HP, },
	/*05*/{ 35000,	45000,	40000,	90000,	45000,	45000,	39000,	50000,	30000,	75000,	
			35000,	62000,	37000,	60000,	37000,  90000, INF_HP, },
	/*EX*/{ 35000,	45000,	35000,	50000,
			/*059妖飛　*/38000,	45000, 55000, 58000, 75000,	
			/*064濤子　*/27000,	48000, 27000, 60000, 60000,
			/*069幽々巳*/25000,	55000, 32000, 60000, 70000,
			/*074妲己　*/25000, 60000, 40000, 38000, 65000, 240000,
	},
	/*PH*/{ 25000,	40000,	25000,	40000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000, },
	},
	{
		/*01*/{ 25000,	23000,	32000,	35000,	23000,	55000, },
		/*02*/{ 25000,	25000,	40000,	25000,	40000,	25000,	90000,	25000,	65000, },
		/*03*/{ 20000,	35000,	25000,	38000,	30000,	60000,	35000,	50000,	35000,	35000,	33000,	80000, },
		/*04*/{ 25000,	53000,	25000,	30000,	27000,	70000,	30000,	85000,	33000,	65000,	33000, INF_HP, },
		/*05*/{ 35000,	45000,	40000,	90000,	45000,	45000,	39000,	50000,	30000,	75000,
				35000,	62000,	37000,	60000,	37000,  90000, INF_HP, },
		/*EX*/{ 35000,	45000,	35000,	50000,
		/*059妖飛　*/38000,	45000, 55000, 58000, 75000,
		/*064濤子　*/27000,	48000, 27000, 60000, 60000,
		/*069幽々巳*/25000,	55000, 32000, 60000, 70000,
		/*074妲己　*/25000, 60000, 40000, 38000, 65000, 240000,
		},
		/*PH*/{ 25000,	40000,	25000,	40000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000, },
	},
};
const static int APPEAR_N = 3;
const int APPEAR_TIME[eStage_Num][APPEAR_N] = {
	/*01*/{ 2150,3700,6120 },
	/*02*/{ 1850,4580,5850 },
	/*03*/{ 2200,4150,6150 },
	/*04*/{ 2300,4750,7420 },
	/*05*/{ 2300,5000,8300, },
	/*EX*/{ 3080,6700,9200, },
	/*PH*/{ 10000,10000,10000, },
};
const int BOSS_CLEAR_N[eStage_Num][APPEAR_N] = {
	/*01*/{ 1,2,6 },
	/*02*/{ 1,3,9 },
	/*03*/{ 2,4,12 },
	/*04*/{ 2,4,12 },
	/*05*/{ 2,4,17 },
	/*EX*/{ 2,4,25 },
	/*PH*/{ 2,4, 5 },
};
const int BOSS_DEAD_N[eStage_Num] = {	
	BOSS_CLEAR_N[0][2],
	BOSS_CLEAR_N[1][2],
	BOSS_CLEAR_N[2][2],
	BOSS_CLEAR_N[3][2],
	BOSS_CLEAR_N[4][2],
	BOSS_CLEAR_N[5][2],
	BOSS_CLEAR_N[6][2]
};
const static int SPELL_BACK[eStage_Num][MAXSPELLNUM_PER_STAGE] = {
	//中1  中2  ラスト
	/*01*/{ 0,   0,   0,1,0,1 },
	/*02*/{ 0,   0,1, 0,1,0,1,0,1 },
	/*03*/{ 0,1, 0,1, 0,1,0,1,0,1,0,1 },
	/*04*/{ 0,1, 0,1, 0,1,0,1,0,1,0,1 },
	/*05*/{ 0,1, 0,1, 0,1,0,1,0,1,0,1,0,1,0,1,1 },
	/*EX*/{ 0,1, 0,1, /*妖飛*/0,0,1,1,1, /*濤子*/0,1,0,1,1, /*幽々巳*/0,1,0,1,1, /*妲己*/0,1,0,1,1,1 },
	/*PH*/{},
};

enum EX_BOSS_IMAGE {
	BOSS_IMAGE_YOHI,
	BOSS_IMAGE_TOKO,
	BOSS_IMAGE_YUYUMI,
	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_LAUNCHAR,
	EX_BOSS_IMAGE_NUM,
};

const static int EX_BOSS_IMAGE_TYPE[MAXSPELLNUM_PER_STAGE] = {
	BOSS_IMAGE_LAUNCHAR,
	BOSS_IMAGE_LAUNCHAR,
	BOSS_IMAGE_LAUNCHAR,
	BOSS_IMAGE_LAUNCHAR,

	BOSS_IMAGE_YOHI,
	BOSS_IMAGE_YOHI,
	BOSS_IMAGE_YOHI,
	BOSS_IMAGE_YOHI,
	BOSS_IMAGE_YOHI,

	BOSS_IMAGE_TOKO,
	BOSS_IMAGE_TOKO,
	BOSS_IMAGE_TOKO,
	BOSS_IMAGE_TOKO,
	BOSS_IMAGE_TOKO,

	BOSS_IMAGE_YUYUMI,
	BOSS_IMAGE_YUYUMI,
	BOSS_IMAGE_YUYUMI,
	BOSS_IMAGE_YUYUMI,
	BOSS_IMAGE_YUYUMI,

	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_DAKKI,
	BOSS_IMAGE_DAKKI,
};

const std::vector<std::vector<const char*>> SPELL_NAME = {
	{//1面
		"[1]  扇蝶嵐",
		"[2]  錐蝶堆",
		"[3]  夢蝶散",
		"[4]  蝶踊る風塵のさざめき",
		"[5]  追蝶走",
		"[6]  その蝶の舞は宴のように",
	},
	{//2面
		"[1]  烈火反照",
		"[2]  試作の半花",
		"[3]  一尺玉",
		"[4]  轟き火炎旋風",
		"[5]  スターマインサンドイッチ",
		"[6]  豪炎狂い咲き",
		"[7]  濤子スペシャルファイヤー",
		"[8]  焔一文字",
		"[9]  ナイアガラα",
	},
	{//3面
		"[1]  宗純の呪い数珠",
		"[2]  飛鷹も逃さぬ陀羅尼札",
		"[3]  五大拈華微笑",
		"[4]  万象を救う光明の船",
		"[5]  劫を孕む鎖龕",
		"[6]  六道十界の輪廻",
		"[7]  刹那の頓悟",
		"[8]  無明を晴らすは智慧の光",
		"[9]  導きの法輪",
		"[10] 憑依鬼ごっこ",
		"[11] 等活地獄",
		"[12] 穢土を逃れし餓鬼の千手",
	},
	{//4面
		"[1]  レインボーグリント",
		"[2]  オールオール・スターライトロード",
		"[3]  レインボーブリリアント",
		"[4]  サーチ・アンド・アステロイド",
		"[5]  スペクトラム・ブルーシフト",
		"[6]  オールトクラウド・スイングバイ",
		"[7]  オーバーコメット",
		"[8]  イクイノックス・コンバージェンス",
		"[9]  デュアルコメット",
		"[10] ブリンクパルサー",
		"[11] トゥインクル・スターダスト",
		"[12] ミッドナイト・レインボー",
	},
	{//5面
		"[1]  龍の裂爪",
		"[2]  龍翼の羽ばたき",
		"[3]  龍の捻爪",
		"[4]  天の階",
		"[5]  龍の散爪",
		"[6]  龍の虹彩",
		"[7]  龍の互鱗",
		"[8]  七色の龍巻",
		"[9]  龍の逆鱗",
		"[10] 全力お天道",
		"[11] 龍の覇気",
		"[12] 輝く龍の針髭",
		"[13] 龍の咆哮",
		"[14] 花散るリンドウ",
		"[15] 龍式追いかけっこ",
		"[16] 封魔無敵のアミュレット",
		"[17] 龍・弾幕結界",
	},
	{//EX
		"[1]  侵入者排除第二種戦闘配備",
		"[2]  弾幕開花宣言",
		"[3]  侵入者排除第一種戦闘配備",
		"[4]  死界の領域",
		"[5]  眠れぬ森の胡蝶",
		"[6]  死霊蝶ネスト",
		"[7]  月光蝶の祝福",
		"[8]  マジカルサーチ",
		"[9]  音程ライン精密テスト",
		"[10] 日課の仕掛け花火",
		"[11] 新作波紫陽花",
		"[12] 二連牡丹",
		"[13] 濤子ホイールオブフォーチュン",
		"[14] 花火師の道楽",
		"[15] 付き纏い呪符",
		"[16] 霊魂実体化の怪",
		"[17] 頭光歪む信仰",
		"[18] 漂う妖魂、描く惆悵",
		"[19] 月輪の世界",
		"[20] コメットパーティクル",
		"[21] プラネタリウム",
		"[22] 星の花道",
		"[23] １２星座宇宙旅行",
		"[24] 真夏の流星群",
		"[25] 地下駆ける銀河鉄道",
		"[26]",
	},
	{//Phantasm
		"[1] 通常",
		"[2] スペル",
		"[3] 通常",
		"[4] スペル",
		"[5] 通常",
		"[6] スペル",
		"[7] 通常",
		"[8] スペル",
		"[9] 通常",
		"[10] スペル",
		"[11] 通常",
		"[12] スペル",
		"[13]",
	},
};

const int EX_BOSS_APPEAR_TYPE[] = {
	eStageEX,
	eStageEX,
	eStageEX,
	eStageEX,

	eStage1,
	eStage1,
	eStage1,
	eStage1,
	eStage1,

	eStage2,
	eStage2,
	eStage2,
	eStage2,
	eStage2,

	eStage3,
	eStage3,
	eStage3,
	eStage3,
	eStage3,

	eStage4,
	eStage4,
	eStage4,
	eStage4,
	eStage4,
	eStage4,
};
