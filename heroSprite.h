#pragma once
#include"cocos2d.h"
USING_NS_CC;
#define ALL_TYPE 5


class Hero :public Sprite {
private:
    int blood;//Ѫ��
    int magic;//����
    int level;//�Ǽ�(1-3)
    int camp;//1��ʾ�ҷ���Ӫ��0��ʾ�з���Ӫ
    int heroType;//Ӣ������(1-ALL_TYPE)
    int weapon;//������ʽ(1ΪԶ�̣�0Ϊ��ս��
    int power;//������
    bool inBattle;  // ��־�Ƿ���ս��״̬(1Ϊ����ս��״̬)
    bool inBoard = 0;//����Ƿ�λ�������ϣ�1��ʾ�������ϣ�0��ʾ�ڱ�սϯ��
    int seatIndex = -1;   //seat���±�
    int Die = 0;   //1��ʾ����
    int exist = 1;  //1��ʾ����
public:
    Hero();
    // ������ͬ���͵�Ӣ��
    static Hero* createHero(int heroType, const Vec2& position, int camp);
    // �ƶ�����
    void move(Vec2 destination);
    // �ϳɷ���
    static void mergeHeroes(std::vector<Hero*>& all_heroes);

    // Getter �� Setter ����
    int getLevel() const;
    void upgrade(int newLevel);
    int getType()const;
    void updateHeroColor();
    // ����ս��״̬
    void enterBattle();

    // �˳�ս��״̬
    void exitBattle();

    // �Ƿ���ս��״̬
    bool isInBattle() const;

    // ��������
    void enterBoard();

    // �˳�����
    void exitBoard();

    // �Ƿ�������
    bool isInBoard() const;

    // ����һ������ԭ�ж������¶����� Spawn
    static Spawn* addAdditionalActionToSpawn(Spawn* originalSpawn, FiniteTimeAction* additionalAction);

    // ��������
    static void attack();
    //��ȡ��ս����Զ��
    int getWeapon() const;


    // ��������������ָ��Ŀ��
    void attack(Hero* target);

    // ��һ�����߳���ģ�⹥��
    void attackInThread(Hero* target);

    // ����Ѫ������
    void decreaseHealth(int amount);

    // ��������
    void die();

    // ��ȡ��Ӫ
    int getCamp() const;

    // ��ȡѪ��
    int getBlood() const;

    //����λ���±�
    void setIndex(int index);

    // ����Ӣ����Ч��
    void Setexist(int ee) {
        exist = ee;
    }

    //��ȡӢ����Ч��
    int Getexist() {
        return exist;
    }

    // ��ȡӢ������
    int GetheroType() {
        return heroType;
    }

    int getLevel() {
        return level;
    }

    //��ȡλ��
    int GetIndex() {
        return seatIndex;
    }
};
