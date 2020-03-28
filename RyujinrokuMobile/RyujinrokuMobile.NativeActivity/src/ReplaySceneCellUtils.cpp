#include "ReplaySceneCellUtils.h"

bool is1On(ReplayHeader *header) {
	if (!header->isSpellPractice && header->stage == eStage1) {
		return true;
	}
	return false;
}

bool is2On(ReplayHeader *header) {
	if (!header->isSpellPractice) {
		if (header->stage == eStage1 && header->clearStageN >= 1) {
			return true;
		}
		if (header->stage == eStage2) {
			return true;
		}
	}
	return false;
}

bool is3On(ReplayHeader *header) {
	if (!header->isSpellPractice) {
		if (header->stage == eStage1 && header->clearStageN >= 2) {
			return true;
		}
		if (header->stage == eStage3) {
			return true;
		}
	}
	return false;
}

bool is4On(ReplayHeader *header) {
	if (!header->isSpellPractice) {
		if (header->stage == eStage1 && header->clearStageN >= 3) {
			return true;
		}
		if (header->stage == eStage4) {
			return true;
		}
	}
	return false;
}

bool is5On(ReplayHeader *header) {
	if (!header->isSpellPractice) {
		if (header->stage == eStage1 && header->clearStageN >= 4) {
			return true;
		}
		if (header->stage == eStage5) {
			return true;
		}
	}
	return false;
}

bool is6On(ReplayHeader *header) {
	if (!header->isSpellPractice) {
		if (header->stage == eStageEX) {
			return true;
		}
	}
	return false;
}

bool is7On(ReplayHeader *header) {
	if (!header->isSpellPractice) {
		if (header->stage == eStagePH) {
			return true;
		}
	}
	return false;
}
