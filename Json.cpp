#include "json.h"

extern rapidjson::Document document;
extern rapidjson::Document documentGamein;

extern int BuildRoom;
extern int JoinRoom;
extern int GameinProgress;
extern int Gamein;

extern int mydata[14][7];
extern int enemydata[14][7];

extern playerroleLayer* myrole_;
extern playerroleLayer* enemyrole_;

/*
需要的英雄数据
1.英雄类型
2.英雄星级
3.英雄位置（inBoard、index）
4.英雄携带的武器

传递数组
data[14][7]  (总共14个位置，其中没有英雄的位置数组第一个数据设为-1来标志)

需要接收做出改变的数据
1.allEnemyHeroes
2.seat3、seat4
*/


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

    document.AddMember("hero1Type", -1, document.GetAllocator());
    document.AddMember("hero1Level", -1, document.GetAllocator());
    document.AddMember("hero1inBoard", -1, document.GetAllocator());
    document.AddMember("hero1Index", -1, document.GetAllocator());
    document.AddMember("hero1Weapon1", -1, document.GetAllocator());
    document.AddMember("hero1Weapon2", -1, document.GetAllocator());
    document.AddMember("hero1Weapon3", -1, document.GetAllocator());

    document.AddMember("hero2Type", -1, document.GetAllocator());
    document.AddMember("hero2Level", -1, document.GetAllocator());
    document.AddMember("hero2inBoard", -1, document.GetAllocator());
    document.AddMember("hero2Index", -1, document.GetAllocator());
    document.AddMember("hero2Weapon1", -1, document.GetAllocator());
    document.AddMember("hero2Weapon2", -1, document.GetAllocator());
    document.AddMember("hero2Weapon3", -1, document.GetAllocator());

    document.AddMember("hero3Type", -1, document.GetAllocator());
    document.AddMember("hero3Level", -1, document.GetAllocator());
    document.AddMember("hero3inBoard", -1, document.GetAllocator());
    document.AddMember("hero3Index", -1, document.GetAllocator());
    document.AddMember("hero3Weapon1", -1, document.GetAllocator());
    document.AddMember("hero3Weapon2", -1, document.GetAllocator());
    document.AddMember("hero3Weapon3", -1, document.GetAllocator());

    document.AddMember("hero4Type", -1, document.GetAllocator());
    document.AddMember("hero4Level", -1, document.GetAllocator());
    document.AddMember("hero4inBoard", -1, document.GetAllocator());
    document.AddMember("hero4Index", -1, document.GetAllocator());
    document.AddMember("hero4Weapon1", -1, document.GetAllocator());
    document.AddMember("hero4Weapon2", -1, document.GetAllocator());
    document.AddMember("hero4Weapon3", -1, document.GetAllocator());

    document.AddMember("hero5Type", -1, document.GetAllocator());
    document.AddMember("hero5Level", -1, document.GetAllocator());
    document.AddMember("hero5inBoard", -1, document.GetAllocator());
    document.AddMember("hero5Index", -1, document.GetAllocator());
    document.AddMember("hero5Weapon1", -1, document.GetAllocator());
    document.AddMember("hero5Weapon2", -1, document.GetAllocator());
    document.AddMember("hero5Weapon3", -1, document.GetAllocator());

    document.AddMember("hero6Type", -1, document.GetAllocator());
    document.AddMember("hero6Level", -1, document.GetAllocator());
    document.AddMember("hero6inBoard", -1, document.GetAllocator());
    document.AddMember("hero6Index", -1, document.GetAllocator());
    document.AddMember("hero6Weapon1", -1, document.GetAllocator());
    document.AddMember("hero6Weapon2", -1, document.GetAllocator());
    document.AddMember("hero6Weapon3", -1, document.GetAllocator());

    document.AddMember("hero7Type", -1, document.GetAllocator());
    document.AddMember("hero7Level", -1, document.GetAllocator());
    document.AddMember("hero7inBoard", -1, document.GetAllocator());
    document.AddMember("hero7Index", -1, document.GetAllocator());
    document.AddMember("hero7Weapon1", -1, document.GetAllocator());
    document.AddMember("hero7Weapon2", -1, document.GetAllocator());
    document.AddMember("hero7Weapon3", -1, document.GetAllocator());

    document.AddMember("hero8Type", -1, document.GetAllocator());
    document.AddMember("hero8Level", -1, document.GetAllocator());
    document.AddMember("hero8inBoard", -1, document.GetAllocator());
    document.AddMember("hero8Index", -1, document.GetAllocator());
    document.AddMember("hero8Weapon1", -1, document.GetAllocator());
    document.AddMember("hero8Weapon2", -1, document.GetAllocator());
    document.AddMember("hero8Weapon3", -1, document.GetAllocator());

    document.AddMember("hero9Type", -1, document.GetAllocator());
    document.AddMember("hero9Level", -1, document.GetAllocator());
    document.AddMember("hero9inBoard", -1, document.GetAllocator());
    document.AddMember("hero9Index", -1, document.GetAllocator());
    document.AddMember("hero9Weapon1", -1, document.GetAllocator());
    document.AddMember("hero9Weapon2", -1, document.GetAllocator());
    document.AddMember("hero9Weapon3", -1, document.GetAllocator());

    document.AddMember("hero10Type", -1, document.GetAllocator());
    document.AddMember("hero10Level", -1, document.GetAllocator());
    document.AddMember("hero10inBoard", -1, document.GetAllocator());
    document.AddMember("hero10Index", -1, document.GetAllocator());
    document.AddMember("hero10Weapon1", -1, document.GetAllocator());
    document.AddMember("hero10Weapon2", -1, document.GetAllocator());
    document.AddMember("hero10Weapon3", -1, document.GetAllocator());

    document.AddMember("hero11Type", -1, document.GetAllocator());
    document.AddMember("hero11Level", -1, document.GetAllocator());
    document.AddMember("hero11inBoard", -1, document.GetAllocator());
    document.AddMember("hero11Index", -1, document.GetAllocator());
    document.AddMember("hero11Weapon1", -1, document.GetAllocator());
    document.AddMember("hero11Weapon2", -1, document.GetAllocator());
    document.AddMember("hero11Weapon3", -1, document.GetAllocator());

    document.AddMember("hero12Type", -1, document.GetAllocator());
    document.AddMember("hero12Level", -1, document.GetAllocator());
    document.AddMember("hero12inBoard", -1, document.GetAllocator());
    document.AddMember("hero12Index", -1, document.GetAllocator());
    document.AddMember("hero12Weapon1", -1, document.GetAllocator());
    document.AddMember("hero12Weapon2", -1, document.GetAllocator());
    document.AddMember("hero12Weapon3", -1, document.GetAllocator());

    document.AddMember("hero13Type", -1, document.GetAllocator());
    document.AddMember("hero13Level", -1, document.GetAllocator());
    document.AddMember("hero13inBoard", -1, document.GetAllocator());
    document.AddMember("hero13Index", -1, document.GetAllocator());
    document.AddMember("hero13Weapon1", -1, document.GetAllocator());
    document.AddMember("hero13Weapon2", -1, document.GetAllocator());
    document.AddMember("hero13Weapon3", -1, document.GetAllocator());

    document.AddMember("hero14Type", -1, document.GetAllocator());
    document.AddMember("hero14Level", -1, document.GetAllocator());
    document.AddMember("hero14inBoard", -1, document.GetAllocator());
    document.AddMember("hero14Index", -1, document.GetAllocator());
    document.AddMember("hero14Weapon1", -1, document.GetAllocator());
    document.AddMember("hero14Weapon2", -1, document.GetAllocator());
    document.AddMember("hero14Weapon3", -1, document.GetAllocator());


    document.AddMember("positionX", 0, document.GetAllocator());
    document.AddMember("positionY", 0, document.GetAllocator());
    document.AddMember("Gamein", Gamein, document.GetAllocator());
    document.AddMember("BuildRoom", BuildRoom, document.GetAllocator());
    document.AddMember("JoinRoom", JoinRoom, document.GetAllocator());
    document.AddMember("GameinProgress", GameinProgress, document.GetAllocator());

    return;
}

void SendJSONstringGamein()   /*发送JSON字符串*/
{
    rapidjson::Value& hero1type = document["hero1Type"];
    hero1type.SetInt(mydata[0][0]);
    if (mydata[0][0] != -1) {
        rapidjson::Value& hero1level = document["hero1Level"];
        hero1level.SetInt(mydata[0][1]);
        rapidjson::Value& hero1inboard = document["hero1inBoard"];
        hero1inboard.SetInt(mydata[0][2]);
        rapidjson::Value& hero1index = document["hero1Index"];
        hero1index.SetInt(mydata[0][3]);
        rapidjson::Value& hero1weapon1 = document["hero1Weapon1"];
        hero1weapon1.SetInt(mydata[0][4]);
        rapidjson::Value& hero1weapon2 = document["hero1Weapon2"];
        hero1weapon2.SetInt(mydata[0][5]);
        rapidjson::Value& hero1weapon3 = document["hero1Weapon3"];
        hero1weapon3.SetInt(mydata[0][6]);
    }

    rapidjson::Value& hero2type = document["hero2Type"];
    hero2type.SetInt(mydata[1][0]);
    if (mydata[1][0] != -1) {
        rapidjson::Value& hero2level = document["hero2Level"];
        hero2level.SetInt(mydata[1][1]);
        rapidjson::Value& hero2inboard = document["hero2inBoard"];
        hero2inboard.SetInt(mydata[1][2]);
        rapidjson::Value& hero2index = document["hero2Index"];
        hero2index.SetInt(mydata[1][3]);
        rapidjson::Value& hero2weapon1 = document["hero2Weapon1"];
        hero2weapon1.SetInt(mydata[1][4]);
        rapidjson::Value& hero2weapon2 = document["hero2Weapon2"];
        hero2weapon2.SetInt(mydata[1][5]);
        rapidjson::Value& hero2weapon3 = document["hero2Weapon3"];
        hero2weapon3.SetInt(mydata[1][6]);
    }

    rapidjson::Value& hero3type = document["hero3Type"];
    hero3type.SetInt(mydata[2][0]);
    if (mydata[2][0] != -1) {
        rapidjson::Value& hero1level = document["hero3Level"];
        hero1level.SetInt(mydata[2][1]);
        rapidjson::Value& hero1inboard = document["hero3inBoard"];
        hero1inboard.SetInt(mydata[2][2]);
        rapidjson::Value& hero1index = document["hero3Index"];
        hero1index.SetInt(mydata[2][3]);
        rapidjson::Value& hero1weapon1 = document["hero3Weapon1"];
        hero1weapon1.SetInt(mydata[2][4]);
        rapidjson::Value& hero1weapon2 = document["hero3Weapon2"];
        hero1weapon2.SetInt(mydata[2][5]);
        rapidjson::Value& hero1weapon3 = document["hero3Weapon3"];
        hero1weapon3.SetInt(mydata[2][6]);
    }

    rapidjson::Value& hero4type = document["hero4Type"];
    hero4type.SetInt(mydata[3][0]);
    if (mydata[3][0] != -1) {
        rapidjson::Value& hero4level = document["hero4Level"];
        hero4level.SetInt(mydata[3][1]);
        rapidjson::Value& hero4inboard = document["hero4inBoard"];
        hero4inboard.SetInt(mydata[3][2]);
        rapidjson::Value& hero4index = document["hero4Index"];
        hero4index.SetInt(mydata[3][3]);
        rapidjson::Value& hero4weapon1 = document["hero4Weapon1"];
        hero4weapon1.SetInt(mydata[3][4]);
        rapidjson::Value& hero4weapon2 = document["hero4Weapon2"];
        hero4weapon2.SetInt(mydata[3][5]);
        rapidjson::Value& hero4weapon3 = document["hero4Weapon3"];
        hero4weapon3.SetInt(mydata[3][6]);
    }

    rapidjson::Value& hero5type = document["hero5Type"];
    hero5type.SetInt(mydata[4][0]);
    if (mydata[4][0] != -1) {
        rapidjson::Value& hero5level = document["hero5Level"];
        hero5level.SetInt(mydata[4][1]);
        rapidjson::Value& hero5inboard = document["hero5inBoard"];
        hero5inboard.SetInt(mydata[4][2]);
        rapidjson::Value& hero5index = document["hero5Index"];
        hero5index.SetInt(mydata[4][3]);
        rapidjson::Value& hero5weapon1 = document["hero5Weapon1"];
        hero5weapon1.SetInt(mydata[4][4]);
        rapidjson::Value& hero5weapon2 = document["hero5Weapon2"];
        hero5weapon2.SetInt(mydata[4][5]);
        rapidjson::Value& hero5weapon3 = document["hero5Weapon3"];
        hero5weapon3.SetInt(mydata[4][6]);
    }

    rapidjson::Value& hero6type = document["hero6Type"];
    hero6type.SetInt(mydata[5][0]);
    if (mydata[5][0] != -1) {
        rapidjson::Value& hero6level = document["hero6Level"];
        hero6level.SetInt(mydata[5][1]);
        rapidjson::Value& hero6inboard = document["hero6inBoard"];
        hero6inboard.SetInt(mydata[5][2]);
        rapidjson::Value& hero6index = document["hero6Index"];
        hero6index.SetInt(mydata[5][3]);
        rapidjson::Value& hero6weapon1 = document["hero6Weapon1"];
        hero6weapon1.SetInt(mydata[5][4]);
        rapidjson::Value& hero6weapon2 = document["hero6Weapon2"];
        hero6weapon2.SetInt(mydata[5][5]);
        rapidjson::Value& hero6weapon3 = document["hero6Weapon3"];
        hero6weapon3.SetInt(mydata[5][6]);
    }

    rapidjson::Value& hero7type = document["hero7Type"];
    hero7type.SetInt(mydata[6][0]);
    if (mydata[6][0] != -1) {
        rapidjson::Value& hero7level = document["hero7Level"];
        hero7level.SetInt(mydata[6][1]);
        rapidjson::Value& hero7inboard = document["hero7inBoard"];
        hero7inboard.SetInt(mydata[6][2]);
        rapidjson::Value& hero7index = document["hero7Index"];
        hero7index.SetInt(mydata[6][3]);
        rapidjson::Value& hero7weapon1 = document["hero7Weapon1"];
        hero7weapon1.SetInt(mydata[6][4]);
        rapidjson::Value& hero7weapon2 = document["hero7Weapon2"];
        hero7weapon2.SetInt(mydata[6][5]);
        rapidjson::Value& hero7weapon3 = document["hero7Weapon3"];
        hero7weapon3.SetInt(mydata[6][6]);
    }

    rapidjson::Value& hero8type = document["hero8Type"];
    hero8type.SetInt(mydata[7][0]);
    if (mydata[7][0] != -1) {
        rapidjson::Value& hero8level = document["hero8Level"];
        hero8level.SetInt(mydata[7][1]);
        rapidjson::Value& hero8inboard = document["hero8inBoard"];
        hero8inboard.SetInt(mydata[7][2]);
        rapidjson::Value& hero8index = document["hero8Index"];
        hero8index.SetInt(mydata[7][3]);
        rapidjson::Value& hero8weapon1 = document["hero8Weapon1"];
        hero8weapon1.SetInt(mydata[7][4]);
        rapidjson::Value& hero8weapon2 = document["hero8Weapon2"];
        hero8weapon2.SetInt(mydata[7][5]);
        rapidjson::Value& hero8weapon3 = document["hero8Weapon3"];
        hero8weapon3.SetInt(mydata[7][6]);
    }

    rapidjson::Value& hero9type = document["hero9Type"];
    hero9type.SetInt(mydata[8][0]);
    if (mydata[8][0] != -1) {
        rapidjson::Value& hero9level = document["hero9Level"];
        hero9level.SetInt(mydata[8][1]);
        rapidjson::Value& hero9inboard = document["hero9inBoard"];
        hero9inboard.SetInt(mydata[8][2]);
        rapidjson::Value& hero9index = document["hero9Index"];
        hero9index.SetInt(mydata[8][3]);
        rapidjson::Value& hero9weapon1 = document["hero9Weapon1"];
        hero9weapon1.SetInt(mydata[8][4]);
        rapidjson::Value& hero9weapon2 = document["hero9Weapon2"];
        hero9weapon2.SetInt(mydata[8][5]);
        rapidjson::Value& hero9weapon3 = document["hero9Weapon3"];
        hero9weapon3.SetInt(mydata[8][6]);
    }

    rapidjson::Value& hero10type = document["hero10Type"];
    hero10type.SetInt(mydata[9][0]);
    if (mydata[9][0] != -1) {
        rapidjson::Value& hero10level = document["hero10Level"];
        hero10level.SetInt(mydata[9][1]);
        rapidjson::Value& hero10inboard = document["hero10inBoard"];
        hero10inboard.SetInt(mydata[9][2]);
        rapidjson::Value& hero10index = document["hero10Index"];
        hero10index.SetInt(mydata[9][3]);
        rapidjson::Value& hero10weapon1 = document["hero10Weapon1"];
        hero10weapon1.SetInt(mydata[9][4]);
        rapidjson::Value& hero10weapon2 = document["hero10Weapon2"];
        hero10weapon2.SetInt(mydata[9][5]);
        rapidjson::Value& hero10weapon3 = document["hero10Weapon3"];
        hero10weapon3.SetInt(mydata[9][6]);
    }

    rapidjson::Value& hero11type = document["hero11Type"];
    hero11type.SetInt(mydata[10][0]);
    if (mydata[10][0] != -1) {
        rapidjson::Value& hero11level = document["hero11Level"];
        hero11level.SetInt(mydata[10][1]);
        rapidjson::Value& hero11inboard = document["hero11inBoard"];
        hero11inboard.SetInt(mydata[10][2]);
        rapidjson::Value& hero11index = document["hero11Index"];
        hero11index.SetInt(mydata[10][3]);
        rapidjson::Value& hero11weapon1 = document["hero11Weapon1"];
        hero11weapon1.SetInt(mydata[10][4]);
        rapidjson::Value& hero11weapon2 = document["hero11Weapon2"];
        hero11weapon2.SetInt(mydata[10][5]);
        rapidjson::Value& hero11weapon3 = document["hero11Weapon3"];
        hero11weapon3.SetInt(mydata[10][6]);
    }

    rapidjson::Value& hero12type = document["hero12Type"];
    hero12type.SetInt(mydata[11][0]);
    if (mydata[11][0] != -1) {
        rapidjson::Value& hero12level = document["hero12Level"];
        hero12level.SetInt(mydata[11][1]);
        rapidjson::Value& hero12inboard = document["hero12inBoard"];
        hero12inboard.SetInt(mydata[11][2]);
        rapidjson::Value& hero12index = document["hero12Index"];
        hero12index.SetInt(mydata[11][3]);
        rapidjson::Value& hero12weapon1 = document["hero12Weapon1"];
        hero12weapon1.SetInt(mydata[11][4]);
        rapidjson::Value& hero12weapon2 = document["hero12Weapon2"];
        hero12weapon2.SetInt(mydata[11][5]);
        rapidjson::Value& hero12weapon3 = document["hero12Weapon3"];
        hero12weapon3.SetInt(mydata[11][6]);
    }

    rapidjson::Value& hero13type = document["hero13Type"];
    hero13type.SetInt(mydata[12][0]);
    if (mydata[12][0] != -1) {
        rapidjson::Value& hero13level = document["hero13Level"];
        hero13level.SetInt(mydata[12][1]);
        rapidjson::Value& hero13inboard = document["hero13inBoard"];
        hero13inboard.SetInt(mydata[12][2]);
        rapidjson::Value& hero13index = document["hero13Index"];
        hero13index.SetInt(mydata[12][3]);
        rapidjson::Value& hero13weapon1 = document["hero13Weapon1"];
        hero13weapon1.SetInt(mydata[12][4]);
        rapidjson::Value& hero13weapon2 = document["hero13Weapon2"];
        hero13weapon2.SetInt(mydata[12][5]);
        rapidjson::Value& hero13weapon3 = document["hero13Weapon3"];
        hero13weapon3.SetInt(mydata[12][6]);
    }

    rapidjson::Value& hero14type = document["hero14Type"];
    hero14type.SetInt(mydata[13][0]);
    if (mydata[13][0] != -1) {
        rapidjson::Value& hero14level = document["hero14Level"];
        hero14level.SetInt(mydata[13][1]);
        rapidjson::Value& hero14inboard = document["hero14inBoard"];
        hero14inboard.SetInt(mydata[13][2]);
        rapidjson::Value& hero14index = document["hero14Index"];
        hero14index.SetInt(mydata[13][3]);
        rapidjson::Value& hero14weapon1 = document["hero14Weapon1"];
        hero14weapon1.SetInt(mydata[13][4]);
        rapidjson::Value& hero14weapon2 = document["hero14Weapon2"];
        hero14weapon2.SetInt(mydata[13][5]);
        rapidjson::Value& hero14weapon3 = document["hero14Weapon3"];
        hero14weapon3.SetInt(mydata[13][6]);
    }

    /*我方小小英雄位置*/
    rapidjson::Value& positionx = document["positionX"];
    positionx.SetFloat(864 * 2 - myrole_->getCurPos().x);
    rapidjson::Value& positiony = document["positionY"];
    positiony.SetFloat(606 * 2 - myrole_->getCurPos().y);
    rapidjson::Value& gamein1 = document["Gamein"];
    gamein1.SetInt(1);

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
    Gamein = receivedDoc["Gamein"].GetInt();

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


    enemydata[0][0] = receivedD["hero1Type"].GetInt();
    enemydata[0][1] = receivedD["hero1Level"].GetInt();
    enemydata[0][2] = receivedD["hero1inBoard"].GetInt();
    enemydata[0][3] = receivedD["hero1Index"].GetInt();
    enemydata[0][4] = receivedD["hero1Weapon1"].GetInt();
    enemydata[0][5] = receivedD["hero1Weapon2"].GetInt();
    enemydata[0][6] = receivedD["hero1Weapon3"].GetInt();

    enemydata[1][0] = receivedD["hero2Type"].GetInt();
    enemydata[1][1] = receivedD["hero2Level"].GetInt();
    enemydata[1][2] = receivedD["hero2inBoard"].GetInt();
    enemydata[1][3] = receivedD["hero2Index"].GetInt();
    enemydata[1][4] = receivedD["hero2Weapon1"].GetInt();
    enemydata[1][5] = receivedD["hero2Weapon2"].GetInt();
    enemydata[1][6] = receivedD["hero2Weapon3"].GetInt();

    enemydata[2][0] = receivedD["hero3Type"].GetInt();
    enemydata[2][1] = receivedD["hero3Level"].GetInt();
    enemydata[2][2] = receivedD["hero3inBoard"].GetInt();
    enemydata[2][3] = receivedD["hero3Index"].GetInt();
    enemydata[2][4] = receivedD["hero3Weapon1"].GetInt();
    enemydata[2][5] = receivedD["hero3Weapon2"].GetInt();
    enemydata[2][6] = receivedD["hero3Weapon3"].GetInt();

    enemydata[3][0] = receivedD["hero4Type"].GetInt();
    enemydata[3][1] = receivedD["hero4Level"].GetInt();
    enemydata[3][2] = receivedD["hero4inBoard"].GetInt();
    enemydata[3][3] = receivedD["hero4Index"].GetInt();
    enemydata[3][4] = receivedD["hero4Weapon1"].GetInt();
    enemydata[3][5] = receivedD["hero4Weapon2"].GetInt();
    enemydata[3][6] = receivedD["hero4Weapon3"].GetInt();

    enemydata[4][0] = receivedD["hero5Type"].GetInt();
    enemydata[4][1] = receivedD["hero5Level"].GetInt();
    enemydata[4][2] = receivedD["hero5inBoard"].GetInt();
    enemydata[4][3] = receivedD["hero5Index"].GetInt();
    enemydata[4][4] = receivedD["hero5Weapon1"].GetInt();
    enemydata[4][5] = receivedD["hero5Weapon2"].GetInt();
    enemydata[4][6] = receivedD["hero5Weapon3"].GetInt();

    enemydata[5][0] = receivedD["hero6Type"].GetInt();
    enemydata[5][1] = receivedD["hero6Level"].GetInt();
    enemydata[5][2] = receivedD["hero6inBoard"].GetInt();
    enemydata[5][3] = receivedD["hero6Index"].GetInt();
    enemydata[5][4] = receivedD["hero6Weapon1"].GetInt();
    enemydata[5][5] = receivedD["hero6Weapon2"].GetInt();
    enemydata[5][6] = receivedD["hero6Weapon3"].GetInt();

    enemydata[6][0] = receivedD["hero7Type"].GetInt();
    enemydata[6][1] = receivedD["hero7Level"].GetInt();
    enemydata[6][2] = receivedD["hero7inBoard"].GetInt();
    enemydata[6][3] = receivedD["hero7Index"].GetInt();
    enemydata[6][4] = receivedD["hero7Weapon1"].GetInt();
    enemydata[6][5] = receivedD["hero7Weapon2"].GetInt();
    enemydata[6][6] = receivedD["hero7Weapon3"].GetInt();

    enemydata[7][0] = receivedD["hero8Type"].GetInt();
    enemydata[7][1] = receivedD["hero8Level"].GetInt();
    enemydata[7][2] = receivedD["hero8inBoard"].GetInt();
    enemydata[7][3] = receivedD["hero8Index"].GetInt();
    enemydata[7][4] = receivedD["hero8Weapon1"].GetInt();
    enemydata[7][5] = receivedD["hero8Weapon2"].GetInt();
    enemydata[7][6] = receivedD["hero8Weapon3"].GetInt();

    enemydata[8][0] = receivedD["hero9Type"].GetInt();
    enemydata[8][1] = receivedD["hero9Level"].GetInt();
    enemydata[8][2] = receivedD["hero9inBoard"].GetInt();
    enemydata[8][3] = receivedD["hero9Index"].GetInt();
    enemydata[8][4] = receivedD["hero9Weapon1"].GetInt();
    enemydata[8][5] = receivedD["hero9Weapon2"].GetInt();
    enemydata[8][6] = receivedD["hero9Weapon3"].GetInt();

    enemydata[9][0] = receivedD["hero10Type"].GetInt();
    enemydata[9][1] = receivedD["hero10Level"].GetInt();
    enemydata[9][2] = receivedD["hero10inBoard"].GetInt();
    enemydata[9][3] = receivedD["hero10Index"].GetInt();
    enemydata[9][4] = receivedD["hero10Weapon1"].GetInt();
    enemydata[9][5] = receivedD["hero10Weapon2"].GetInt();
    enemydata[9][6] = receivedD["hero10Weapon3"].GetInt();

    enemydata[10][0] = receivedD["hero11Type"].GetInt();
    enemydata[10][1] = receivedD["hero11Level"].GetInt();
    enemydata[10][2] = receivedD["hero11inBoard"].GetInt();
    enemydata[10][3] = receivedD["hero11Index"].GetInt();
    enemydata[10][4] = receivedD["hero11Weapon1"].GetInt();
    enemydata[10][5] = receivedD["hero11Weapon2"].GetInt();
    enemydata[10][6] = receivedD["hero11Weapon3"].GetInt();

    enemydata[11][0] = receivedD["hero12Type"].GetInt();
    enemydata[11][1] = receivedD["hero12Level"].GetInt();
    enemydata[11][2] = receivedD["hero12inBoard"].GetInt();
    enemydata[11][3] = receivedD["hero12Index"].GetInt();
    enemydata[11][4] = receivedD["hero12Weapon1"].GetInt();
    enemydata[11][5] = receivedD["hero12Weapon2"].GetInt();
    enemydata[11][6] = receivedD["hero12Weapon3"].GetInt();

    enemydata[12][0] = receivedD["hero13Type"].GetInt();
    enemydata[12][1] = receivedD["hero13Level"].GetInt();
    enemydata[12][2] = receivedD["hero13inBoard"].GetInt();
    enemydata[12][3] = receivedD["hero13Index"].GetInt();
    enemydata[12][4] = receivedD["hero13Weapon1"].GetInt();
    enemydata[12][5] = receivedD["hero13Weapon2"].GetInt();
    enemydata[12][6] = receivedD["hero13Weapon3"].GetInt();

    enemydata[13][0] = receivedD["hero14Type"].GetInt();
    enemydata[13][1] = receivedD["hero14Level"].GetInt();
    enemydata[13][2] = receivedD["hero14inBoard"].GetInt();
    enemydata[13][3] = receivedD["hero14Index"].GetInt();
    enemydata[13][4] = receivedD["hero14Weapon1"].GetInt();
    enemydata[13][5] = receivedD["hero14Weapon2"].GetInt();
    enemydata[13][6] = receivedD["hero14Weapon3"].GetInt();


    //小小英雄
    enemyrole_->cur_position.x = receivedD["positionX"].GetFloat();
    enemyrole_->cur_position.y = receivedD["positionY"].GetFloat();
    Gamein = receivedD["Gamein"].GetInt();
}