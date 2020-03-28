#include "BackgroundFactory.h"
#include "Background01.h"
#include "Background01Spell.h"
#include "Background02.h"
#include "Background02Spell.h"
#include "Background03.h"
#include "Background04.h"
#include "Background05.h"
#include "BackgroundEX.h"
#include "BackgroundPH.h"


BackgroundFactory::BackgroundFactory()
{
}


BackgroundFactory::~BackgroundFactory()
{
}

void BackgroundFactory::create(int stage, Background **background, Background **backgroundSpell) {
	switch (stage) {
	case 0:
		*background = new Background01();
		*backgroundSpell = new Background01spell();
		break;
	case 1:
		*background = new Background02();
		*backgroundSpell = new Background01spell();
		break;
	case 2:
		*background = new Background03();
		*backgroundSpell = new Background01spell();
		break;
	case 3:
		*background = new Background04();
		*backgroundSpell = new Background01spell();
		break;
	case 4:
		*background = new Background05();
		*backgroundSpell = new Background01spell();
		break;
	case 5:
		*background = new BackgroundEX();
		*backgroundSpell = new Background01spell();
		break;
	case 6:
		*background = new BackgroundPH();
		*backgroundSpell = new Background01spell();
		break;
	}
}
