#include "json.h"

extern rapidjson::Document document;
extern rapidjson::Document documentGamein;

extern int BuildRoom;
extern int JoinRoom;
extern int GameinProgress;
extern int Gamein;

extern cocos2d::Vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern cocos2d::Vector<Hero*> allEnemyHeroes;//�з�����Ӣ��

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


void SendJSONstring(rapidjson::Document& document)   /*����JSON�ַ���*/
{
    // ���� RapidJSON �ĵ�
    document.SetObject();

    

    document.AddMember("Gamein", Gamein, document.GetAllocator());

    document.AddMember("BuildRoom", BuildRoom, document.GetAllocator());

    document.AddMember("JoinRoom", JoinRoom, document.GetAllocator());

    document.AddMember("GameinProgress", GameinProgress, document.GetAllocator());

    return;
}

void SendJSONstringGamein()   /*����JSON�ַ���*/
{
    // ���� RapidJSON �ĵ�
    documentGamein.SetObject();
    Gamein = 1;
    /*�ҷ�Ӣ��*/
    // ��ÿ�� Hero �ṹ��ת��Ϊ JSON ������ӵ�������
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

    /*�ҷ�ССӢ��*/
    //rapidjson::Value MyPlayerroleArray(kArrayType);
    //rapidjson::Value MyPlayerroleValue(kObjectType);

    /*�ҷ�ССӢ��λ��*/
    documentGamein.AddMember("Gamein", Gamein, documentGamein.GetAllocator());

    documentGamein.AddMember("positionX", myrole_->getCurPos().x, documentGamein.GetAllocator());
    documentGamein.AddMember("positionY", myrole_->getCurPos().y, documentGamein.GetAllocator());

    //MyPlayerroleArray.PushBack(MyPlayerroleValue, documentGamein.GetAllocator());

    //documentGamein.AddMember("MyPlayerrole", MyPlayerroleArray, documentGamein.GetAllocator());



    return;
}

bool ReceiveJSONstring(std::string receivedData)
{
    // ʹ�� RapidJSON �������յ��� JSON ����
    Document receivedDoc;
    receivedDoc.Parse(receivedData.c_str());

    // �������Ƿ�ɹ�
    if (!receivedDoc.IsObject()) {
        std::cerr << "Error parsing JSON." << std::endl;
        return 1;
    }   
    

    BuildRoom = receivedDoc["BuildRoom"].GetInt();
    JoinRoom = receivedDoc["JoinRoom"].GetInt();
    GameinProgress = receivedDoc["GameinProgress"].GetInt();

    
}

bool ReceiveJSONstringGamein(std::string received) {
    // ʹ�� RapidJSON �������յ��� JSON ����
    Document receivedD;
    receivedD.Parse(received.c_str());

    // �������Ƿ�ɹ�
    if (!receivedD.IsObject()) {
        std::cerr << "Error parsing JSON." << std::endl;
        return 1;
    }
    /*
        // ��ȡ����
        const rapidjson::Value& EnemyHeroesArray = receivedDoc["MyHeroes"];
        if (!EnemyHeroesArray.IsArray()) {
            std::cerr << "Error: 'MyHeroes' is not an array." << std::endl;
            return 1;
        }

        // ��������
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