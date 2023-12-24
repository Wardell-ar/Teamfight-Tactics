#pragma once
#include"cocos2d.h"
USING_NS_CC;
#define ALL_TYPE 6


class Hero :public Sprite {
private:
    int blood;//Ѫ��
    int max_blood;
    int each_magic;
    int magic;//����
    int level;//�Ǽ�(1-3)
    int camp;//1��ʾ�ҷ���Ӫ��0��ʾ�з���Ӫ
    int heroType;//Ӣ������(1-ALL_TYPE)
    int weapon;//������ʽ(1ΪԶ�̣�0Ϊ��ս��
    int power;//������
    bool inBoard = 0;//����Ƿ�λ�������ϣ�1��ʾ�������ϣ�0��ʾ�ڱ�սϯ��
    int seatIndex = -1;   //seat���±�
    int Die = 0;   //1��ʾ����
    int click = 0;   //���ڵ���ж�
    ProgressTimer* healthBar;//Ѫ����
    ProgressTimer* magicBar;//������
public:
    Hero();
    // ������ͬ���͵�Ӣ��
    static Hero* createHero(int heroType, const Vec2& position, int camp);
    // �ƶ�����
    void move(Vec2 destination);
    // �ϳɷ���
    static void mergeHeroes();

    // Getter �� Setter ����
    int getLevel() const;
    void upgrade(int newLevel);
    int getType()const;
   

    // ��������
    void enterBoard();

    // �˳�����
    void exitBoard();

    // �Ƿ�������
    bool isInBoard() const;
    
    //��ȡ��ս����Զ��
    int getWeapon() const;


    // ��������������ָ��Ŀ��
    void attack(Hero* target);

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

    //�ж��Ƿ񱻵��
    int IsClicked() {
        return click;
    }

    //���õ��
    void SetClicked(int c) {
        click = c;
    }

    //����Borad����ֵ
    void SetBoard(int b) {
        inBoard = b;
    }

    int isDead() {
        return Die;
    }

    void setDie(int d) {
        Die = d;
    }

    int getMaxBlood() {
        return max_blood;
    }

    void setBlood(int b) {
        blood = b;
    }

    void setMagic(int m) {
        magic = m;
    }

    void updatebloodandmagic();
};