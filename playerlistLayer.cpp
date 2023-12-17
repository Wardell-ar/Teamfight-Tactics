#include "playerlistLayer.h"

Layer* playerlistLayer::createLayer() {
	return playerlistLayer::create();
}


bool playerlistLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	return true;
}