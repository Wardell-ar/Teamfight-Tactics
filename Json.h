#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <rapidjson/document.h>
#include "networkScene.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "cocos2d.h"
#include "heroSprite.h"
#include "playerroleLayer.h"

using namespace rapidjson;




void writeVec2ToJSON(const Vec2& vec, rapidjson::Value& value, Document::AllocatorType& allocator);

void readVec2FromJSON(const rapidjson::Value& value, Vec2& vec);

void SendJSONstring(rapidjson::Document& document);

bool ReceiveJSONstring(std::string receivedData);

void SendJSONstringGamein();

bool ReceiveJSONstringGamein(std::string receivedData);

