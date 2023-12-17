#include "storeLayer.h"

Layer* storeLayer::createLayer() {
	return storeLayer::create();
}

bool storeLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}
