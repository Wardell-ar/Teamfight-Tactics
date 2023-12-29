#include "json.h"

extern rapidjson::Document document;
extern rapidjson::Document documentGamein;

extern int BuildRoom;
extern int JoinRoom;
extern int GameinProgress;
extern int Gamein;

extern cocos2d::Vector<Hero*> allMyHeroes;//我方所有英雄
extern cocos2d::Vector<Hero*> allEnemyHeroes;//敌方所有英雄

extern playerroleLayer* myrole_;
extern playerroleLayer* enemyrole_;


void writeVec2ToJSON(const Vec2& vec, rapidjson::Value& value, Document::AllocatorType& allocator)
{
    value.SetObject();
    value.AddMember("x", vec.x, allocator);
    value.AddMember("y", vec.y, allocator);
}

void readVec2FromJSON(const rapidjson::Value& value, Vec2& vec) {
    vec.x = value["x"].GetFloat();
    vec.y = value["y"].GetFloat();
}


void SendJSONstring(rapidjson::Document& document)   /*发送JSON字符串*/
{
    // 创建 RapidJSON 文档
    document.SetObject();

    

    document.AddMember("Gamein", Gamein, document.GetAllocator());

    document.AddMember("BuildRoom", BuildRoom, document.GetAllocator());

    document.AddMember("JoinRoom", JoinRoom, document.GetAllocator());

    document.AddMember("GameinProgress", GameinProgress, document.GetAllocator());

    return;
}

void SendJSONstringGamein()   /*发送JSON字符串*/
{
    // 创建 RapidJSON 文档
    documentGamein.SetObject();
    Gamein = 1;
    /*我方英雄*/
    // 将每个 Hero 结构体转换为 JSON 对象并添加到数组中
    /*rapidjson::Value MyHeroesArray(kArrayType);
    for (const auto& hero : allMyHeroes) {
        rapidjson::Value MyHeroesValue(kObjectType);
        MyHeroesValue.AddMember("blood", hero->getBlood(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("max_blood", hero->getMaxBlood(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("each_magic", hero->getEachMagic(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("start_magic", hero->getStartMagic(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("magic", hero->getMagic(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("level", hero->getLevel(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("camp", hero->getCamp(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("heroType", hero->GetheroType(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("weapon", hero->getWeapon(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("power", hero->getPower(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("skill", hero->getSkill(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("inBoard", hero->isInBoard(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("seatIndex", hero->GetIndex(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("Die", hero->isDead(), documentGamein.GetAllocator());
        MyHeroesValue.AddMember("click", hero->IsClicked(), documentGamein.GetAllocator());

        MyHeroesArray.PushBack(MyHeroesValue, documentGamein.GetAllocator());
    }
    documentGamein.AddMember("MyHeroes", MyHeroesArray, documentGamein.GetAllocator());*/

    /*我方小小英雄*/
    //rapidjson::Value MyPlayerroleArray(kArrayType);
    //rapidjson::Value MyPlayerroleValue(kObjectType);

    /*我方小小英雄位置*/
    documentGamein.AddMember("Gamein", Gamein, documentGamein.GetAllocator());

    documentGamein.AddMember("positionX", myrole_->getCurPos().x, documentGamein.GetAllocator());
    documentGamein.AddMember("positionY", myrole_->getCurPos().y, documentGamein.GetAllocator());

    //MyPlayerroleArray.PushBack(MyPlayerroleValue, documentGamein.GetAllocator());

    //documentGamein.AddMember("MyPlayerrole", MyPlayerroleArray, documentGamein.GetAllocator());



    return;
}

bool ReceiveJSONstring(std::string receivedData)
{
    // 使用 RapidJSON 解析接收到的 JSON 数据
    Document receivedDoc;
    receivedDoc.Parse(receivedData.c_str());

    // 检查解析是否成功
    if (!receivedDoc.IsObject()) {
        std::cerr << "Error parsing JSON." << std::endl;
        return 1;
    }   
    

    BuildRoom = receivedDoc["BuildRoom"].GetInt();
    JoinRoom = receivedDoc["JoinRoom"].GetInt();
    GameinProgress = receivedDoc["GameinProgress"].GetInt();

    
}

bool ReceiveJSONstringGamein(std::string received) {
    // 使用 RapidJSON 解析接收到的 JSON 数据
    Document receivedD;
    receivedD.Parse(received.c_str());

    // 检查解析是否成功
    if (!receivedD.IsObject()) {
        std::cerr << "Error parsing JSON." << std::endl;
        return 1;
    }
    /*
        // 获取数组
        const rapidjson::Value& EnemyHeroesArray = receivedDoc["MyHeroes"];
        if (!EnemyHeroesArray.IsArray()) {
            std::cerr << "Error: 'MyHeroes' is not an array." << std::endl;
            return 1;
        }

        // 遍历数组
        cocos2d::Vector<Hero*> EnemyHeroes;
        for (SizeType i = 0; i < EnemyHeroesArray.Size(); i++) {
            const rapidjson::Value& heroObject = EnemyHeroesArray[i];

            Hero* hero;
            hero->setBlood(heroObject["blood"].GetFloat());
            //hero->setMax_Blood(heroObject["max_blood"].GetFloat());/////////////
            //hero->setEach_Magic(heroObject["each_magic"].GetInt());///////////////
            //hero->setStart_Magic(heroObject["start_magic"].GetInt());/////////////////
            hero->setMagic(heroObject["magic"].GetInt());
            //hero->setLevel(heroObject["level"].GetInt());////////////
            //hero->setCamp(heroObject["camp"].GetInt());/////////////
            //hero->setHeroType(heroObject["heroType"].GetInt());////////////////
            //hero->setWeapon(heroObject["weapon"].GetInt());/////////////
            //hero->setPower(heroObject["power"].GetInt());///////////
            //hero->setSkill(heroObject["skill"].GetInt());///////////
            //hero->setBoard(heroObject["inBoard"].GetBool());///////////////////////////
            hero->setIndex(heroObject["seatIndex"].GetInt());
            hero->setDie(heroObject["Die"].GetInt());
            //hero->setClicked(heroObject["click"].GetInt());////////////////

            EnemyHeroes.pushBack(hero);
        }

        allEnemyHeroes = EnemyHeroes;*/
    
   
    enemyrole_->cur_position.x = receivedD["positionX"].GetFloat();
    enemyrole_->cur_position.y = receivedD["positionY"].GetFloat();

  
}