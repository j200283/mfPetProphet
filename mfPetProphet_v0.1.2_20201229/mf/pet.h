/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#ifndef MF_PET_H
#define MF_PET_H

#include <string>  // std::string
#include "skill.h" // 引用技能
#include "type.h"  // ElementType, FruitType, PetType, SkillType
#include "utils.h" // MD5obj, MD5RandomGenerator, NormalDistribution

class BasePet {
private:
    MD5obj md5;
    MD5RandomGenerator md5RandGen;
    NormalDistribution distribution;
    int _level = 4; // _level = 4 when pet is Lv5

    enum { // const random seed
        MAX_HP = 0,
        STRENGTH = 1,
        SPEED = 2,
        DEFENSE = 3,
        SKILL_WEIGHT = 4,
        //GENDER = 5,
        RESISTANCE = 6,
        //SKILL_MULTIPLIER = 7,
        //SKILL_ADDEND = 8,
        SKILL_HIT_PERCENT = 9,
        //SKILL_SPECIAL = 10,
        //ITEM_IMPRESSION = 11,
        //MEDICAL_IMPRESSION = 12,
        //MONSTER_HEIGHT = 13,
        //MONSTER_ITEM_DURATION = 14,
        MONSTER_ITEM_DURATION_FIELD = 15,
        MONSTER_FRUIT_KIMOCHI = 16,
        MONSTER_FRUIT_SATIETY = 17,
        MONSTER_FRUIT_LOYAL = 18,
        MONSTER_FRUIT_HP = 19,
        MONSTER_FRUIT_ELEMENT = 20
    };

    int extraPetElementIndex = 0; // 0 is (int)ElementType::normal

    double createBaseAttributeValue(int randomSeed, double mean, double deviation, double minimum, double maximum); // base fruit function
    double createAttributeValue(int randomSeed, double mean, double deviation); // battle & boss fruit function
    double createAttributeValueByClass(int randomSeed, double base, double mean[5]); // battle & boss fruit function
    void calcAddElement(bool petElement[8]); // element fruit function
    int getHpUpRate(); // hp fruit function
    double getHpPerTurnInBattle(); // hp fruit function
    int getKimochiUpRate(); // kimochi fruit function
    int getLoyalUpRate(); // loyal fruit function
    double getPurifyTimeReduceScale(); // purify fruit function
    int getHelpPurifyHoursReduce(); // purify fruit function
    double getSatietyUpRate(); // satiety fruit function

    double calcValue(int randomSeed, double mean[5], double deviation[5]);
    void calcElement(bool petElement[8]);
    void calcResistanceMap(double resistanceMean[8][5], double resistanceDeviation[8][5]);

protected:
    double calcMaxHp(double maxHpMean[5], double maxHpDeviation[5]);
    double calcStrength(double strengthMean[5], double strengthDeviation[5]);
    double calcSpeed(double speedMean[5], double speedDeviation[5]);
    double calcDefense(double defenseMean[5], double defenseDeviation[5]);
    double calcSpeedEffectAddon(double speed);

    void getPercent(std::string extraCode[4], double skillWeight[4][5]);
    void calcElementAndResistance(bool petElement[8], double resistanceMean[8][5], double resistanceDeviation[8][5]);
    void calculate();
    std::string toString(std::string petClass, std::string skillInfo, bool petElement[7]);

public:
    std::string gene = ""; // gene prefix = "@monster_"
    FruitType fruitType = FruitType::empty;
    std::string fruitCode = "";

    double maxHp;
    double strength;
    double defense;
    double speed;
    double speedEffectAddon;
    double percent[4];
    bool element[8];
    int resistance[8];
    double score;

    int hpUpRate;
    double hpPerTurnInBattle;
    int kimochiUpRate;
    int loyalUpRate;
    double purifyTimeReduceScale;
    int helpPurifyHoursReduce;
    double satietyUpRate;
    bool isWeightControlled;

    void setRandomPetGene(std::string randomString); // Set random pet gene with random string
    void setLevel(int petLevel);
    int getLevel();
    void setAllValue(std::string petGene, int petLevel, FruitType petFruitType, std::string petFruitCode);
};

class BaldEagle : public BasePet { // 白頭蒼鷹
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {32.0, 3.0, 4.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {28.0, 3.0, 3.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge),      // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::eagleShout),     // 大地鷹嚎
        "/" + getSkillCodeByType(SkillType::baldDartAttack), // 鷹羽飛針
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 飛衝突擊
        { 0.0, 15.0,  5.0, 10.0, 10.0}, // 大地鷹嚎
        { 0.0,  0.0, 30.0, 10.0, 10.0}, // 鷹羽飛針
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {10.0,  2.0,  2.0,  2.0,  1.0}, // 水
        {-5.0, -1.0, -1.0, -1.0, -1.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::baldEagle; // 白頭蒼鷹

    FlyCharge flyChargeSkill;           // 飛衝突擊
    EagleShout eagleShoutSkill;         // 大地鷹嚎
    BaldDartAttack baldDartAttackSkill; // 鷹羽飛針

    void calcScore();
    void calculate();
    std::string toString();
};

class BlackBear : public BasePet { // 白紋黑熊
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {33.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::doubleClawHit), // 雙爪擊
        "/" + getSkillCodeByType(SkillType::bodyCharge),    // 衝撞
        "/" + getSkillCodeByType(SkillType::berserk),       // 狂暴
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 雙爪擊
        { 0.0, 60.0,  0.0, 10.0, 10.0}, // 衝撞
        { 0.0,  0.0, 20.0, 10.0, 10.0}, // 狂暴
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 無
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 闇
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 地
        {-5.0, -2.0, -2.0, 0.0, 0.0}, // 火
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 草
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 光
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 水
        { 5.0,  2.0,  2.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::blackBear; // 白紋黑熊

    DoubleClawHit doubleClawHitSkill; // 雙爪擊
    BodyCharge bodyChargeSkill;       // 衝撞
    Berserk berserkSkill;             // 狂暴

    void calcScore();
    void calculate();
    std::string toString();
};

class BlackCat : public BasePet { // 哈斯貓
private:
    double maxHpMean[5] = {190.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {28.0, 3.0, 4.0, 6.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 3.0, 4.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::doubleCatClaw),  // 貓爪抓
        "/" + getSkillCodeByType(SkillType::jumpingScratch), // 飛天爪
        "/" + getSkillCodeByType(SkillType::loveEyes),       // 裝可憐
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 貓爪抓
        {  0.0, 50.0,  0.0, 10.0, 10.0}, // 飛天爪
        {  0.0,  0.0, 20.0, 10.0, 10.0}, // 裝可憐
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::blackCat; // 哈斯貓

    DoubleCatClaw doubleCatClawSkill;   // 貓爪抓
    JumpingScratch jumpingScratchSkill; // 飛天爪
    LoveEyes loveEyesSkill;             // 裝可憐

    void calcScore();
    void calculate();
    std::string toString();
};

class BlackRabbit : public BasePet { // 黑毛兔
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {28.0, 3.0, 5.0, 6.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {28.0, 4.0, 4.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),         // 咬擊
        "/" + getSkillCodeByType(SkillType::kick),         // 踢擊
        "/" + getSkillCodeByType(SkillType::groundStrike), // 飛天破地
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,   0.0,  0.0, 20.0, 20.0}, // 咬擊
        {  0.0, 100.0,  0.0, 20.0, 20.0}, // 踢擊
        {  0.0,   0.0, 50.0, 20.0, 20.0}, // 飛天破地
        {  0.0,   0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        true,  // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::blackRabbit; // 黑毛兔

    Bite biteSkill;                 // 咬擊
    Kick kickSkill;                 // 踢擊
    GroundStrike groundStrikeSkill; // 飛天破地

    void calcScore();
    void calculate();
    std::string toString();
};

class BlackWidow : public BasePet { // 黑寡婦
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {32.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 3.0, 3.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 2.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "",
        "",
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        true,  // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::blackWidow; // 黑寡婦

    void calcScore();
    void calculate();
    std::string toString();
};

class BlueBrowCaffer : public BasePet { // 藍眉野牛
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {32.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::jumpKick),   // 跳踢
        "/" + getSkillCodeByType(SkillType::bodyCharge), // 衝撞
        "/" + getSkillCodeByType(SkillType::shockwave),  // 跳躍地震
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 跳踢
        {  0.0, 50.0,  0.0, 10.0, 10.0}, // 衝撞
        {  0.0,  0.0, 20.0, 10.0, 10.0}, // 跳躍地震
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {-5.0, -2.0, -2.0, -2.0, -2.0}, // 水
        { 5.0,  2.0,  2.0,  2.0,  2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        true,  // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::blueBrowCaffer; // 藍眉野牛

    JumpKick jumpKickSkill;     // 跳踢
    BodyCharge bodyChargeSkill; // 衝撞
    Shockwave shockwaveSkill;   // 跳躍地震

    void calcScore();
    void calculate();
    std::string toString();
};

class BlueMagpie : public BasePet { // 藍鵲
private:
    double maxHpMean[5] = {190.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {28.0, 3.0, 3.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge),      // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::triplePeck),     // 啄擊(藍鵲)
        "/" + getSkillCodeByType(SkillType::wingDeterrence), // 展翼嚇阻
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0, 0.0, 10.0, 10.0}, // 飛衝突擊
        { 0.0, 70.0, 0.0, 10.0, 10.0}, // 啄擊(藍鵲)
        { 0.0,  0.0, 8.0, 10.0, 10.0}, // 展翼嚇阻
        { 0.0,  0.0, 0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 水
        {-5.0, -1.0, -1.0, -1.0, -1.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::blueMagpie; // 藍鵲

    FlyCharge flyChargeSkill;           // 飛衝突擊
    TriplePeck triplePeckSkill;         // 啄擊(藍鵲)
    WingDeterrence wingDeterrenceSkill; // 展翼嚇阻

    void calcScore();
    void calculate();
    std::string toString();
};

class CactusSpirit : public BasePet { // 鴨嘴仙人掌
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::doubleThornHit),     // 刺棘掌
        "/" + getSkillCodeByType(SkillType::cactusBubbleAttack), // 惡仙露
        "/" + getSkillCodeByType(SkillType::cactusThornRain),    // 仙針雨
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 刺棘掌
        {  0.0, 40.0,  0.0, 10.0, 10.0}, // 惡仙露
        {  0.0,  0.0, 20.0, 10.0, 10.0}, // 仙針雨
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::cactusSpirit; // 鴨嘴仙人掌

    DoubleThornHit doubleThornHitSkill;         // 刺棘掌
    CactusBubbleAttack cactusBubbleAttackSkill; // 惡仙露
    CactusThornRain cactusThornRainSkill;       // 仙針雨

    void calcScore();
    void calculate();
    std::string toString();
};

class CatShark : public BasePet { // 貓鯊
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 4.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::kick),           // 踢擊
        "/" + getSkillCodeByType(SkillType::bubbleAttack),   // 噁噁泡
        "/" + getSkillCodeByType(SkillType::jumpingScratch), // 飛天爪
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 踢擊
        {  0.0, 30.0,  0.0, 10.0, 10.0}, // 噁噁泡
        {  0.0,  0.0, 50.0, 10.0, 10.0}, // 飛天爪
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        true,  // 水
        false  // 風
    };

public:
    PetType petType = PetType::catShark; // 貓鯊

    Kick kickSkill;                     // 踢擊
    BubbleAttack bubbleAttackSkill;     // 噁噁泡
    JumpingScratch jumpingScratchSkill; // 飛天爪

    void calcScore();
    void calculate();
    std::string toString();
};

class ClownButterfly : public BasePet { // 小丑蝶
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {25.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),                 // 咬擊
        "/" + getSkillCodeByType(SkillType::regeneratePollenSpew), // 香香花粉
        "/" + getSkillCodeByType(SkillType::flyKick),              // 大腳飛踢
        ""
    };

    double skillDeviation[4][5] = {
        {80.0,  0.0,  0.0, 20.0, 20.0}, // 咬擊
        { 0.0, 10.0, 10.0, 20.0, 20.0}, // 香香花粉
        { 0.0,  0.0, 10.0, 20.0, 20.0}, // 大腳飛踢
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {-5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::clownButterfly; // 小丑蝶

    Bite biteSkill;                                 // 咬擊
    RegeneratePollenSpew regeneratePollenSpewSkill; // 香香花粉
    FlyKick flyKickSkill;                           // 大腳飛踢

    void calcScore();
    void calculate();
    std::string toString();
};

class Cobra : public BasePet { // 眼鏡蛇
private:
    double maxHpMean[5] = {190.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {26.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),       // 咬擊
        "/" + getSkillCodeByType(SkillType::poisonBite), // 毒牙咬
        "/" + getSkillCodeByType(SkillType::eyeStrike),  // 目光震憾
        ""
    };

    double skillDeviation[4][5] = {
        {50.0,  0.0, 10.0,  0.0, 20.0}, // 咬擊
        { 0.0, 10.0, 10.0,  0.0, 20.0}, // 毒牙咬
        { 0.0,  0.0,  0.0, 15.0, 20.0}, // 目光震憾
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-5.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 水
        { 0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::cobra; // 眼鏡蛇

    Bite biteSkill;             // 咬擊
    PoisonBite poisonBiteSkill; // 毒牙咬
    EyeStrike eyeStrikeSkill;   // 目光震憾

    void calcScore();
    void calculate();
    std::string toString();
};

class CorollaBee : public BasePet { // 花冠蜂
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 3.0, 4.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::tripleSting),   // 蜂蜇
        "/" + getSkillCodeByType(SkillType::feedHoneySpew), // 蜂蜜餵食
        "/" + getSkillCodeByType(SkillType::stingShoot),    // 蜂針射擊
        ""
    };

    double skillDeviation[4][5] = {
        {80.0,  0.0,  0.0, 20.0, 20.0}, // 蜂蜇
        { 0.0, 20.0, 15.0, 20.0, 20.0}, // 蜂蜜餵食
        { 0.0,  0.0, 50.0, 20.0, 20.0}, // 蜂針射擊
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        { -5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::corollaBee; // 花冠蜂

    TripleSting tripleStingSkill;     // 蜂蜇
    FeedHoneySpew feedHoneySpewSkill; // 蜂蜜餵食
    StingShoot stingShootSkill;       // 蜂針射擊

    void calcScore();
    void calculate();
    std::string toString();
};

class CottonCandyBee : public BasePet { // 花糖蜂
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 3.0, 4.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::tripleSting),     // 蜂蜇
        "/" + getSkillCodeByType(SkillType::slackPollenSpew), // 懶懶花粉
        "/" + getSkillCodeByType(SkillType::stingShoot),      // 蜂針射擊
        ""
    };

    double skillDeviation[4][5] = {
        {80.0,  0.0,  0.0, 20.0, 20.0}, // 蜂蜇
        { 0.0, 20.0, 15.0, 20.0, 20.0}, // 懶懶花粉
        { 0.0,  0.0, 50.0, 20.0, 20.0}, // 蜂針射擊
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        { -5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::cottonCandyBee; // 花糖蜂

    TripleSting tripleStingSkill;         // 蜂蜇
    SlackPollenSpew slackPollenSpewSkill; // 懶懶花粉
    StingShoot stingShootSkill;           // 蜂針射擊

    void calcScore();
    void calculate();
    std::string toString();
};

class DarkBear : public BasePet { // 月夜熊
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {33.0, 3.0, 4.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::doubleClawHit), // 雙爪擊
        "/" + getSkillCodeByType(SkillType::berserk),       // 狂暴
        "/" + getSkillCodeByType(SkillType::handBeam),      // 熊掌氣功
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 雙爪擊
        {  0.0, 10.0,  8.0, 10.0, 10.0}, // 狂暴
        {  0.0,  0.0, 38.0, 10.0, 10.0}, // 熊掌氣功
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  5.0,  2.0,  1.0,  1.0,  1.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -5.0, -2.0, -2.0, -2.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {  5.0,  2.0,  1.0,  1.0,  1.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 2.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        true,  // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::darkBear; // 月夜熊

    DoubleClawHit doubleClawHitSkill; // 雙爪擊
    Berserk berserkSkill;             // 狂暴
    HandBeam handBeamSkill;           // 熊掌氣功

    void calcScore();
    void calculate();
    std::string toString();
};

class DragonFruitChicken : public BasePet { // 火龍果雞
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {28.0, 3.0, 3.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {3.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),             // 啄擊
        "/" + getSkillCodeByType(SkillType::flyCharge),        // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::dragonSeedAttack), // 火龍果子
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 啄擊
        {  0.0, 60.0,  0.0, 10.0, 10.0}, // 飛衝突擊
        {  0.0,  0.0, 20.0, 10.0, 10.0}, // 火龍果子
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::dragonFruitChicken; // 火龍果雞

    Peck peckSkill;                         // 啄擊
    FlyCharge flyChargeSkill;               // 飛衝突擊
    DragonSeedAttack dragonSeedAttackSkill; // 火龍果子

    void calcScore();
    void calculate();
    std::string toString();
};

class EggplantChicken : public BasePet { // 小茄雞
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),         // 啄擊
        "/" + getSkillCodeByType(SkillType::flyCharge),    // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::tannicAttack), // 單寧酸
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 啄擊
        {  0.0, 50.0,  0.0, 20.0, 20.0}, // 飛衝突擊
        {  0.0,  0.0, 20.0, 20.0, 20.0}, // 單寧酸
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::eggplantChicken; // 小茄雞

    Peck peckSkill;                 // 啄擊
    FlyCharge flyChargeSkill;       // 飛衝突擊
    TannicAttack tannicAttackSkill; // 單寧酸

    void calcScore();
    void calculate();
    std::string toString();
};

class FireDragon : public BasePet { // 赤焰火龍
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {35.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {12.0, 3.0, 3.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {20.0, 2.0, 2.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::fireTailAttack), // 神龍擺尾
        "/" + getSkillCodeByType(SkillType::giant),          // 巨獸術
        "/" + getSkillCodeByType(SkillType::hellFire),       // 地獄火
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 15.0, 10.0}, // 神龍擺尾
        { 0.0, 35.0,  0.0, 15.0, 10.0}, // 巨獸術
        { 0.0,  0.0, 20.0, 15.0, 10.0}, // 地獄火
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,   0.0,   0.0,   0.0,   0.0}, // 無
        {  0.0,   0.0, -10.0, -10.0, -10.0}, // 闇
        {  0.0,   0.0,   0.0,   0.0,   0.0}, // 地
        { 20.0,  20.0,  20.0,  20.0,  20.0}, // 火
        {  0.0,   0.0,   0.0,   0.0,   0.0}, // 草
        {  0.0,   0.0,   0.0,   0.0,   0.0}, // 光
        {-15.0, -15.0, -10.0, -10.0, -10.0}, // 水
        {  0.0,   0.0,   0.0,   0.0,   0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 2.0, 2.0, 2.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {5.0, 5.0, 5.0, 5.0, 5.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 2.0, 2.0, 2.0, 2.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        true,  // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::fireDragon; // 赤焰火龍

    FireTailAttack fireTailAttackSkill; // 神龍擺尾
    Giant giantSkill;                   // 巨獸術
    HellFire hellFireSkill;             // 地獄火

    void calcScore();
    void calculate();
    std::string toString();
};

class Firefly : public BasePet { // 螢火蟲
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {28.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge),       // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::attractingLight), // 螢光誘敵
        "/" + getSkillCodeByType(SkillType::boxingQuartet),   // 螢光四重揍
        ""
    };

    double skillDeviation[4][5] = {
        {140.0,  0.0,  0.0, 15.0, 15.0}, // 飛衝突擊
        {  0.0, 20.0,  0.0, 15.0, 15.0}, // 螢光誘敵
        {  0.0,  0.0, 30.0, 15.0, 15.0}, // 螢光四重揍
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        { -5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        true,  // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::firefly; // 螢火蟲

    FlyCharge flyChargeSkill;             // 飛衝突擊
    AttractingLight attractingLightSkill; // 螢光誘敵
    BoxingQuartet boxingQuartetSkill;     // 螢光四重揍

    void calcScore();
    void calculate();
    std::string toString();
};

class FlowerMantis : public BasePet { // 魔眼螳螂
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {30.0, 3.0, 3.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::handWave),     // 開膛刀波
        "/" + getSkillCodeByType(SkillType::jumpingKnife), // 飛空鍘
        "/" + getSkillCodeByType(SkillType::magicEyes),    // 魔眼催眠
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 開膛刀波
        { 0.0, 75.0,  0.0, 10.0, 10.0}, // 飛空鍘
        { 0.0,  0.0, 60.0, 10.0, 10.0}, // 魔眼催眠
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {-5.0, -2.0, -2.0, -2.0, -2.0}, // 地
        {-5.0, -2.0,  0.0,  0.0,  0.0}, // 火
        {10.0,  5.0,  2.0,  2.0,  2.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        { 0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 地
        {2.0, 1.0, 0.0, 0.0, 0.0}, // 火
        {2.0, 2.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::flowerMantis; // 魔眼螳螂

    HandWave handWaveSkill;         // 開膛刀波
    JumpingKnife jumpingKnifeSkill; // 飛空鍘
    MagicEyes magicEyesSkill;       // 魔眼催眠

    void calcScore();
    void calculate();
    std::string toString();
};

class ForestFox : public BasePet { // 野森狐
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 4.0, 5.0, 7.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),     // 咬擊
        "/" + getSkillCodeByType(SkillType::clawHit),  // 爪擊
        "/" + getSkillCodeByType(SkillType::foxCharm), // 魅狐秋波
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 咬擊
        {  0.0, 80.0,  0.0, 20.0, 20.0}, // 爪擊
        {  0.0,  0.0, 60.0, 20.0, 20.0}, // 魅狐秋波
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::forestFox; // 野森狐

    Bite biteSkill;         // 咬擊
    ClawHit clawHitSkill;   // 爪擊
    FoxCharm foxCharmSkill; // 魅狐秋波

    void calcScore();
    void calculate();
    std::string toString();
};

class ForestPolatouche : public BasePet { // 山林飛鼠
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 4.0, 6.0, 7.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::acornAttack), // 橡果子彈
        "/" + getSkillCodeByType(SkillType::bite),        // 咬擊
        "/" + getSkillCodeByType(SkillType::flyCharge),   // 飛衝突擊
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 橡果子彈
        {  0.0, 80.0,  0.0, 20.0, 20.0}, // 咬擊
        {  0.0,  0.0, 50.0, 20.0, 20.0}, // 飛衝突擊
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {-5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::forestPolatouche; // 山林飛鼠

    AcornAttack acornAttackSkill; // 橡果子彈
    Bite biteSkill;               // 咬擊
    FlyCharge flyChargeSkill;     // 飛衝突擊

    void calcScore();
    void calculate();
    std::string toString();
};

class GoldenBallCat : public BasePet { // 金球貓
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {32.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 3.0, 3.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 2.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::tailAttack),       // 尾鞭
        "/" + getSkillCodeByType(SkillType::eyeShine),         // 金光閃閃
        "/" + getSkillCodeByType(SkillType::circleRollScrach), // 旋風金爪
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 尾鞭
        {  0.0, 25.0,  0.0, 10.0, 10.0}, // 金光閃閃
        {  0.0,  0.0, 50.0, 10.0, 10.0}, // 旋風金爪
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {-5.0, -2.0, -1.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {10.0,  5.0,  2.0,  2.0,  2.0}, // 光
        {-5.0, -2.0, -1.0, -1.0, -1.0}, // 水
        { 0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {2.0, 1.0, 1.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {2.0, 2.0, 1.0, 1.0, 1.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        true,  // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::goldenBallCat; // 金球貓

    TailAttack tailAttackSkill;             // 尾鞭
    EyeShine eyeShineSkill;                 // 金光閃閃
    CircleRollScrach circleRollScrachSkill; // 旋風金爪

    void calcScore();
    void calculate();
    std::string toString();
};

class GrassChicken : public BasePet { // 小草雞
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),      // 啄擊
        "/" + getSkillCodeByType(SkillType::flyCharge), // 飛衝突擊
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {30.0,  0.0, 20.0, 20.0, 20.0}, // 啄擊
        { 0.0, 20.0, 20.0, 20.0, 20.0}, // 飛衝突擊
        { 0.0,  0.0,  0.0,  0.0,  0.0},
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::grassChicken; // 小草雞

    Peck peckSkill;           // 啄擊
    FlyCharge flyChargeSkill; // 飛衝突擊

    void calcScore();
    void calculate();
    std::string toString();
};

class HamimelonChicken : public BasePet { // 哈蜜瓜雞
private:
    double maxHpMean[5] = {270.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 6.0, 6.0, 15.0, 15.0};

    double strengthMean[5] = {34.0, 4.0, 4.0, 10.0, 10.0};
    double strengthDeviation[5] = {3.0, 2.0, 2.0, 4.0, 4.0};

    double defenseMean[5] = {13.0, 2.0, 2.0, 2.0, 2.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 1.0};

    double speedMean[5] = {28.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {3.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge), // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::peck),      // 啄擊
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {30.0, 20.0,  0.0, 20.0, 0.0}, // 飛衝突擊
        { 0.0,  0.0, 20.0, 20.0, 0.0}, // 啄擊
        { 0.0,  0.0,  0.0,  0.0, 0.0},
        { 0.0,  0.0,  0.0,  0.0, 0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {10.0, 2.0, 2.0, 2.0, 0.0}, // 草
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        { 0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {3.0, 1.0, 1.0, 1.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::hamimelonChicken; // 哈蜜瓜雞

    FlyCharge flyChargeSkill; // 飛衝突擊
    Peck peckSkill;           // 啄擊

    void calcScore();
    void calculate();
    std::string toString();
};

class HornRabbit : public BasePet { // 火角兔
private:
    double maxHpMean[5] = {210.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 3.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {28.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {3.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),      // 咬擊
        "/" + getSkillCodeByType(SkillType::flyCharge), // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::fireSpew),  // 兔火球
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 15.0, 15.0}, // 咬擊
        { 0.0, 60.0,  0.0, 15.0, 15.0}, // 飛衝突擊
        { 0.0,  0.0, 50.0, 15.0, 15.0}, // 兔火球
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 15.0,  2.0,  2.0,  2.0,  2.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {-15.0, -2.0, -2.0, -2.0, -2.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        true,  // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::hornRabbit; // 火角兔

    Bite biteSkill;           // 咬擊
    FlyCharge flyChargeSkill; // 飛衝突擊
    FireSpew fireSpewSkill;   // 兔火球

    void calcScore();
    void calculate();
    std::string toString();
};

class LeafRaccoon : public BasePet { // 葉子浣熊
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {35.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::knittingBallAttack), // 鋼毛飛球
        "/" + getSkillCodeByType(SkillType::clawHit),            // 爪擊
        "/" + getSkillCodeByType(SkillType::rollingCharge),      // 旋轉衝撞
        ""
    };

    double skillDeviation[4][5] = {
        {60.0,  0.0,  0.0, 20.0, 20.0}, // 鋼毛飛球
        { 0.0, 30.0, 10.0,  0.0, 20.0}, // 爪擊
        { 0.0,  0.0,  0.0, 20.0, 20.0}, // 旋轉衝撞
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-5.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        { 0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::leafRaccoon; // 葉子浣熊

    KnittingBallAttack knittingBallAttackSkill; // 鋼毛飛球
    ClawHit clawHitSkill;                       // 爪擊
    RollingCharge rollingChargeSkill;           // 旋轉衝撞

    void calcScore();
    void calculate();
    std::string toString();
};

class MagmaFlower : public BasePet { // 溫泉花
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::eyesRay),          // 熱線攻擊
        "/" + getSkillCodeByType(SkillType::springBubble),     // 溫泉泡泡
        "/" + getSkillCodeByType(SkillType::volcanicEruption), // 火山爆花
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 熱線攻擊
        { 0.0, 30.0,  0.0, 10.0, 10.0}, // 溫泉泡泡
        { 0.0,  0.0, 60.0, 10.0, 10.0}, // 火山爆花
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 地
        {  5.0,  2.0,  2.0,  2.0,  2.0}, // 火
        {  5.0,  2.0,  0.0,  0.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        true,  // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::magmaFlower; // 溫泉花

    EyesRay eyesRaySkill;                   // 熱線攻擊
    SpringBubble springBubbleSkill;         // 溫泉泡泡
    VolcanicEruption volcanicEruptionSkill; // 火山爆花

    void calcScore();
    void calculate();
    std::string toString();
};

class MushroomChicken : public BasePet { // 香菇雞
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge), // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::peck),      // 啄擊
        "/" + getSkillCodeByType(SkillType::sporeSpew), // 昏睡孢子
        ""
    };

    double skillDeviation[4][5] = {
        {20.0,  0.0, 20.0, 20.0, 20.0}, // 飛衝突擊
        { 0.0, 20.0, 20.0, 20.0, 20.0}, // 啄擊
        { 0.0,  0.0, 10.0, 20.0, 20.0}, // 昏睡孢子
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::mushroomChicken; // 香菇雞

    FlyCharge flyChargeSkill; // 飛衝突擊
    Peck peckSkill;           // 啄擊
    SporeSpew sporeSpewSkill; // 昏睡孢子

    void calcScore();
    void calculate();
    std::string toString();
};

class OrangeDeer : public BasePet { // 橘子麋鹿
private:
    double maxHpMean[5] = {250.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bodyCharge),   // 衝撞
        "/" + getSkillCodeByType(SkillType::jumpAttack),   // 泰山壓頂
        "/" + getSkillCodeByType(SkillType::leavesAttack), // 飛葉攻擊
        ""
    };

    double skillDeviation[4][5] = {
        {20.0,  0.0,  0.0, 15.0, 15.0}, // 衝撞
        { 0.0, 20.0,  0.0, 15.0, 15.0}, // 泰山壓頂
        { 0.0,  0.0, 10.0, 15.0, 15.0}, // 飛葉攻擊
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::orangeDeer; // 橘子麋鹿

    BodyCharge bodyChargeSkill;     // 衝撞
    JumpAttack jumpAttackSkill;     // 泰山壓頂
    LeavesAttack leavesAttackSkill; // 飛葉攻擊

    void calcScore();
    void calculate();
    std::string toString();
};

class PlainTiger : public BasePet { // 草原虎
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {35.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::kick),           // 踢擊
        "/" + getSkillCodeByType(SkillType::jumpingScratch), // 飛天爪
        "/" + getSkillCodeByType(SkillType::powerIncrease),  // 肌肉強化
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 踢擊
        {  0.0, 50.0,  0.0, 20.0, 20.0}, // 飛天爪
        {  0.0,  0.0, 10.0, 20.0, 20.0}, // 肌肉強化
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::plainTiger; // 草原虎

    Kick kickSkill;                     // 踢擊
    JumpingScratch jumpingScratchSkill; // 飛天爪
    PowerIncrease powerIncreaseSkill;   // 肌肉強化

    void calcScore();
    void calculate();
    std::string toString();
};

class PurpleBrowCaffer : public BasePet { // 黃金雷牛
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {32.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {24.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::jumpKick),  // 跳踢
        "/" + getSkillCodeByType(SkillType::doubleBox), // 雙拳擊
        "/" + getSkillCodeByType(SkillType::lightning), // 金色閃電
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 25.0}, // 跳踢
        {  0.0, 80.0,  0.0, 10.0, 25.0}, // 雙拳擊
        {  0.0,  0.0, 15.0, 10.0, 25.0}, // 金色閃電
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        true,  // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::purpleBrowCaffer; // 黃金雷牛

    JumpKick jumpKickSkill;   // 跳踢
    DoubleBox doubleBoxSkill; // 雙拳擊
    Lightning lightningSkill; // 金色閃電

    void calcScore();
    void calculate();
    std::string toString();
};

class RafflesiaSpirit : public BasePet { // 大王花
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {33.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),        // 咬擊
        "/" + getSkillCodeByType(SkillType::thornRattan), // 地蕀爪
        "/" + getSkillCodeByType(SkillType::stinkBubble), // 臭臭氣
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 15.0, 10.0}, // 咬擊
        { 0.0, 60.0,  0.0, 15.0, 10.0}, // 地蕀爪
        { 0.0,  0.0, 10.0, 15.0, 10.0}, // 臭臭氣
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::rafflesiaSpirit; // 大王花

    Bite biteSkill;               // 咬擊
    ThornRattan thornRattanSkill; // 地蕀爪
    StinkBubble stinkBubbleSkill; // 臭臭氣

    void calcScore();
    void calculate();
    std::string toString();
};

class RedradishChicken : public BasePet { // 紅蘿蔔雞
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 6.0, 6.0, 15.0, 15.0};

    double strengthMean[5] = {30.0, 4.0, 4.0, 10.0, 10.0};
    double strengthDeviation[5] = {3.0, 2.0, 2.0, 4.0, 4.0};

    double defenseMean[5] = {12.0, 2.0, 2.0, 2.0, 2.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 1.0};

    double speedMean[5] = {30.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {3.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),       // 啄擊
        "/" + getSkillCodeByType(SkillType::bodyCharge), // 衝撞
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {30.0,  0.0,  0.0,  0.0,  0.0}, // 啄擊
        { 0.0, 10.0, 10.0, 10.0,  0.0}, // 衝撞
        { 0.0,  0.0,  0.0,  0.0,  0.0},
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {3.0, 1.0, 1.0, 1.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::redradishChicken; // 紅蘿蔔雞

    Peck peckSkill;             // 啄擊
    BodyCharge bodyChargeSkill; // 衝撞

    void calcScore();
    void calculate();
    std::string toString();
};

class RockMonster : public BasePet { // 魔岩精
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {34.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {12.0, 3.0, 4.0, 4.0, 5.0};
    double defenseDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double speedMean[5] = {22.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::groundHit),   // 搥擊
        "/" + getSkillCodeByType(SkillType::rockAttack),  // 拋石
        "/" + getSkillCodeByType(SkillType::rockDefense), // 地牙盾
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 搥擊
        { 0.0, 70.0,  0.0, 10.0, 10.0}, // 拋石
        { 0.0,  0.0, 25.0, 10.0, 10.0}, // 地牙盾
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 10.0,  5.0,  2.0,  2.0,  2.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { -5.0, -5.0, -2.0, -2.0, -2.0}, // 水
        { -5.0, -2.0, -2.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 2.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 2.0, 1.0, 1.0, 1.0}, // 水
        {2.0, 1.0, 1.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        true,  // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::rockMonster; // 魔岩精

    GroundHit groundHitSkill;     // 搥擊
    RockAttack rockAttackSkill;   // 拋石
    RockDefense rockDefenseSkill; // 地牙盾

    void calcScore();
    void calculate();
    std::string toString();
};

class RoseBee : public BasePet { // 沙漠玫蜂
private:
    double maxHpMean[5] = {190.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {28.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyKick),         // 大腳飛踢
        "/" + getSkillCodeByType(SkillType::tripleSting),     // 蜂蜇
        "/" + getSkillCodeByType(SkillType::slackPollenSpew), // 懶懶花粉
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 大腳飛踢
        { 0.0, 70.0,  0.0, 10.0, 10.0}, // 蜂蜇
        { 0.0,  0.0, 20.0, 10.0, 10.0}, // 懶懶花粉
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {-5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        true,  // 火
        false, // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::roseBee; // 沙漠玫蜂

    FlyKick flyKickSkill;                 // 大腳飛踢
    TripleSting tripleStingSkill;         // 蜂蜇
    SlackPollenSpew slackPollenSpewSkill; // 懶懶花粉

    void calcScore();
    void calculate();
    std::string toString();
};

class SaplingChicken : public BasePet { // 樹苗雞
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),                    // 啄擊
        "/" + getSkillCodeByType(SkillType::flyCharge),               // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::regeneratePhytoncidSpew), // 芬多精
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 啄擊
        { 0.0, 60.0,  0.0, 10.0, 10.0}, // 飛衝突擊
        { 0.0,  0.0, 20.0, 10.0, 10.0}, // 芬多精
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::saplingChicken; // 樹苗雞

    Peck peckSkill;                                       // 啄擊
    FlyCharge flyChargeSkill;                             // 飛衝突擊
    RegeneratePhytoncidSpew regeneratePhytoncidSpewSkill; // 芬多精

    void calcScore();
    void calculate();
    std::string toString();
};

class ShellPolatouche : public BasePet { // 貝殼飛鼠
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 4.0, 6.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge),     // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::shellDart),     // 貝殼飛盤
        "/" + getSkillCodeByType(SkillType::tornadoAttack), // 龍捲風暴
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 飛衝突擊
        {  0.0, 30.0, 20.0, 10.0, 10.0}, // 貝殼飛盤
        {  0.0,  0.0, 30.0, 10.0, 10.0}, // 龍捲風暴
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 水
        {-5.0, -2.0, -2.0, -2.0, -2.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {2.0, 1.0, 1.0, 1.0, 1.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        true,  // 水
        true   // 風
    };

public:
    PetType petType = PetType::shellPolatouche; // 貝殼飛鼠

    FlyCharge flyChargeSkill;         // 飛衝突擊
    ShellDart shellDartSkill;         // 貝殼飛盤
    TornadoAttack tornadoAttackSkill; // 龍捲風暴

    void calcScore();
    void calculate();
    std::string toString();
};

class Skunk : public BasePet { // 臭鼬
private:
    double maxHpMean[5] = {190.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {28.0, 3.0, 3.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {32.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::skunkBite),     // 咬擊(臭鼬)
        "/" + getSkillCodeByType(SkillType::doubleHeadHit), // 頭搥
        "/" + getSkillCodeByType(SkillType::stenchAttack),  // 臭氣
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 20.0}, // 咬擊(臭鼬)
        { 0.0, 60.0,  0.0, 10.0, 20.0}, // 頭搥
        { 0.0,  0.0, 15.0, 10.0, 20.0}, // 臭氣
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        true,  // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::skunk; // 臭鼬

    SkunkBite skunkBiteSkill;         // 咬擊(臭鼬)
    DoubleHeadHit doubleHeadHitSkill; // 頭搥
    StenchAttack stenchAttackSkill;   // 臭氣

    void calcScore();
    void calculate();
    std::string toString();
};

class StrawberryChicken : public BasePet { // 草莓雞
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 3.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),             // 啄擊
        "/" + getSkillCodeByType(SkillType::flyCharge),        // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::strawberryAttack), // 莓雨季節
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 啄擊
        {  0.0, 50.0,  0.0, 20.0, 20.0}, // 飛衝突擊
        {  0.0,  0.0, 20.0, 20.0, 20.0}, // 莓雨季節
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::strawberryChicken; // 草莓雞

    Peck peckSkill;                         // 啄擊
    FlyCharge flyChargeSkill;               // 飛衝突擊
    StrawberryAttack strawberryAttackSkill; // 莓雨季節

    void calcScore();
    void calculate();
    std::string toString();
};

class SunflowerSpirit : public BasePet { // 向日葵
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {25.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {24.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::patelDartAttack), // 飛花攻擊
        "/" + getSkillCodeByType(SkillType::sunlightAttack),  // 太陽炫光
        "/" + getSkillCodeByType(SkillType::flyCharge),       // 飛衝突擊
        ""
    };

    double skillDeviation[4][5] = {
        {80.0,  0.0,  0.0, 10.0, 10.0}, // 飛花攻擊
        { 0.0, 10.0, 15.0, 20.0, 20.0}, // 太陽炫光
        { 0.0,  0.0, 50.0, 20.0, 20.0}, // 飛衝突擊
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::sunflowerSpirit; // 向日葵

    PatelDartAttack patelDartAttackSkill; // 飛花攻擊
    SunlightAttack sunlightAttackSkill;   // 太陽炫光
    FlyCharge flyChargeSkill;             // 飛衝突擊

    void calcScore();
    void calculate();
    std::string toString();
};

class SwardSheep : public BasePet { // 草皮羊
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bodyCharge),      // 衝撞
        "/" + getSkillCodeByType(SkillType::defenseIncrease), // 毛皮強化
        "/" + getSkillCodeByType(SkillType::jumpAttack),      // 泰山壓頂
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 衝撞
        {  0.0, 20.0,  0.0, 20.0, 20.0}, // 毛皮強化
        {  0.0,  0.0, 20.0, 20.0, 20.0}, // 泰山壓頂
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::swardSheep; // 草皮羊

    BodyCharge bodyChargeSkill;           // 衝撞
    DefenseIncrease defenseIncreaseSkill; // 毛皮強化
    JumpAttack jumpAttackSkill;           // 泰山壓頂

    void calcScore();
    void calculate();
    std::string toString();
};

class UmbrellaLizard : public BasePet { // 毒傘蜥
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {32.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 3.0, 3.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 2.0, 3.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "",
        "",
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        true,  // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::umbrellaLizard; // 毒傘蜥

    void calcScore();
    void calculate();
    std::string toString();
};

class Walrus : public BasePet { // 長牙海象
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {35.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {22.0, 3.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {1.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bodyCharge),  // 衝撞
        "/" + getSkillCodeByType(SkillType::bubbleBomb),  // 深水炸彈
        "/" + getSkillCodeByType(SkillType::chargeAlert), // 衝撞警戒(衝撞反擊)
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 12.0, 12.0}, // 衝撞
        {  0.0, 25.0,  0.0, 12.0, 12.0}, // 深水炸彈
        {  0.0,  0.0, 15.0, 12.0, 12.0}, // 衝撞警戒(衝撞反擊)
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 地
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        true,  // 水
        false  // 風
    };

public:
    PetType petType = PetType::walrus; // 長牙海象

    BodyCharge bodyChargeSkill;   // 衝撞
    BubbleBomb bubbleBombSkill;   // 深水炸彈
    ChargeAlert chargeAlertSkill; // 衝撞警戒(衝撞反擊)

    void calcScore();
    void calculate();
    std::string toString();
};

class WatermelonChicken : public BasePet { // 西瓜雞
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),             // 啄擊
        "/" + getSkillCodeByType(SkillType::bodyCharge),       // 衝撞
        "/" + getSkillCodeByType(SkillType::watermelonAttack), // 黑子雨
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 啄擊
        {  0.0, 50.0,  0.0, 20.0, 20.0}, // 衝撞
        {  0.0,  0.0, 10.0, 20.0, 20.0}, // 黑子雨
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        {  5.0,  2.0,  2.0,  2.0,  2.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        true,  // 水
        false  // 風
    };

public:
    PetType petType = PetType::watermelonChicken; // 西瓜雞

    Peck peckSkill;                         // 啄擊
    BodyCharge bodyChargeSkill;             // 衝撞
    WatermelonAttack watermelonAttackSkill; // 黑子雨

    void calcScore();
    void calculate();
    std::string toString();
};

class WaveTurtle : public BasePet { // 功夫海龜
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 4.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::doubleHandKnife),    // 手風刃
        "/" + getSkillCodeByType(SkillType::jumpingDoubleSlash), // 水月斬
        "/" + getSkillCodeByType(SkillType::circleRollCharge),   // 旋風腳刀
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 手風刃
        {  0.0, 50.0,  0.0, 10.0, 10.0}, // 水月斬
        {  0.0,  0.0, 30.0, 10.0, 10.0}, // 旋風腳刀
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-5.0, -2.0, -2.0, -2.0, -2.0}, // 火
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        { 0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 5.0,  2.0,  2.0,  2.0,  2.0}, // 水
        { 0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        true,  // 水
        false  // 風
    };

public:
    PetType petType = PetType::waveTurtle; // 功夫海龜

    DoubleHandKnife doubleHandKnifeSkill;       // 手風刃
    JumpingDoubleSlash jumpingDoubleSlashSkill; // 水月斬
    CircleRollCharge circleRollChargeSkill;     // 旋風腳刀

    void calcScore();
    void calculate();
    std::string toString();
};

class WhiteOwl : public BasePet { // 貓頭鷹
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {30.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {28.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::flyCharge),          // 飛衝突擊
        "/" + getSkillCodeByType(SkillType::featherDartAttack),  // 羽毛飛標
        "/" + getSkillCodeByType(SkillType::greenTornadoAttack), // 青羽旋風
        ""
    };

    double skillDeviation[4][5] = {
        {30.0,  0.0,  0.0,  0.0, 20.0}, // 飛衝突擊
        { 0.0, 20.0,  0.0, 10.0, 20.0}, // 羽毛飛標
        { 0.0,  0.0, 10.0,  0.0, 20.0}, // 青羽旋風
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 無
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 闇
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 地
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 火
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 草
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 光
        { 0.0,  0.0,  0.0, 0.0, 0.0}, // 水
        {-5.0, -1.0, -1.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {2.0, 1.0, 1.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        true   // 風
    };

public:
    PetType petType = PetType::whiteOwl; // 貓頭鷹

    FlyCharge flyChargeSkill;                   // 飛衝突擊
    FeatherDartAttack featherDartAttackSkill;   // 羽毛飛標
    GreenTornadoAttack greenTornadoAttackSkill; // 青羽旋風

    void calcScore();
    void calculate();
    std::string toString();
};

class WhiteRabbit : public BasePet { // 小白兔
private:
    double maxHpMean[5] = {180.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 6.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {28.0, 3.0, 4.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bite),          // 咬擊
        "/" + getSkillCodeByType(SkillType::kick),          // 踢擊
        "/" + getSkillCodeByType(SkillType::dodgeIncrease), // 注意力強化
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,   0.0,  0.0, 20.0, 20.0}, // 咬擊
        {  0.0, 100.0,  0.0, 20.0, 20.0}, // 踢擊
        {  0.0,   0.0, 20.0, 20.0, 20.0}, // 注意力強化
        {  0.0,   0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::whiteRabbit; // 小白兔

    Bite biteSkill;                   // 咬擊
    Kick kickSkill;                   // 踢擊
    DodgeIncrease dodgeIncreaseSkill; // 注意力強化

    void calcScore();
    void calculate();
    std::string toString();
};

class WhiteSeal : public BasePet { // 小海豹
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 2.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::doubleFinSlap), // 雙翼拍拍
        "/" + getSkillCodeByType(SkillType::bodyCharge),    // 衝撞
        "/" + getSkillCodeByType(SkillType::bubbleSpread),  // 噴水特技
        ""
    };

    double skillDeviation[4][5] = {
        {90.0,  0.0,  0.0, 10.0, 10.0}, // 雙翼拍拍
        { 0.0, 60.0,  0.0, 10.0, 10.0}, // 衝撞
        { 0.0,  0.0, 30.0, 10.0, 10.0}, // 噴水特技
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 無
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 闇
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 地
        {-10.0, -2.0, -2.0, -2.0, -2.0}, // 火
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 草
        {  0.0,  0.0,  0.0,  0.0,  0.0}, // 光
        { 10.0,  2.0,  2.0,  2.0,  2.0}, // 水
        {  0.0,  0.0,  0.0,  0.0,  0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {2.0, 1.0, 1.0, 1.0, 1.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        true,  // 水
        false  // 風
    };

public:
    PetType petType = PetType::whiteSeal; // 小海豹

    DoubleFinSlap doubleFinSlapSkill; // 雙翼拍拍
    BodyCharge bodyChargeSkill;       // 衝撞
    BubbleSpread bubbleSpreadSkill;   // 噴水特技

    void calcScore();
    void calculate();
    std::string toString();
};

class WhiteSheep : public BasePet { // 白綿羊
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {29.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 3.0, 3.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 3.0, 3.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::bodyCharge),          // 衝撞
        "/" + getSkillCodeByType(SkillType::defenseIncreaseWool), // 毛毛膜
        "/" + getSkillCodeByType(SkillType::woolBallAttack),      // 鉛毛彈
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 10.0, 10.0}, // 衝撞
        {  0.0, 20.0,  0.0, 10.0, 10.0}, // 毛毛膜
        {  0.0,  0.0, 40.0, 10.0, 10.0}, // 鉛毛彈
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::whiteSheep; // 白綿羊

    BodyCharge bodyChargeSkill;                   // 衝撞
    DefenseIncreaseWool defenseIncreaseWoolSkill; // 毛毛膜
    WoolBallAttack woolBallAttackSkill;           // 鉛毛彈

    void calcScore();
    void calculate();
    std::string toString();
};

class WhiteTiger : public BasePet { // 劍齒白虎
private:
    double maxHpMean[5] = {220.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {35.0, 3.0, 3.0, 4.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 2.0, 3.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 2.0, 2.0};

    double speedMean[5] = {30.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::kick),           // 踢擊
        "/" + getSkillCodeByType(SkillType::jumpingScratch), // 飛天爪
        "/" + getSkillCodeByType(SkillType::powerIncrease),  // 肌肉強化
        ""
    };

    double skillDeviation[4][5] = {
        {100.0,  0.0,  0.0, 20.0, 20.0}, // 踢擊
        {  0.0, 50.0,  0.0, 20.0, 20.0}, // 飛天爪
        {  0.0,  0.0, 10.0, 20.0, 20.0}, // 肌肉強化
        {  0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::whiteTiger; // 劍齒白虎

    Kick kickSkill;                     // 踢擊
    JumpingScratch jumpingScratchSkill; // 飛天爪
    PowerIncrease powerIncreaseSkill;   // 肌肉強化

    void calcScore();
    void calculate();
    std::string toString();
};

class WhiteradishChicken : public BasePet { // 白蘿蔔雞
private:
    double maxHpMean[5] = {240.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 6.0, 6.0, 15.0, 15.0};

    double strengthMean[5] = {30.0, 4.0, 4.0, 10.0, 10.0};
    double strengthDeviation[5] = {3.0, 2.0, 2.0, 4.0, 4.0};

    double defenseMean[5] = {12.0, 2.0, 2.0, 2.0, 2.0};
    double defenseDeviation[5] = {2.0, 1.0, 1.0, 1.0, 1.0};

    double speedMean[5] = {30.0, 2.0, 2.0, 3.0, 3.0};
    double speedDeviation[5] = {3.0, 1.0, 1.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),       // 啄擊
        "/" + getSkillCodeByType(SkillType::bodyCharge), // 衝撞
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {30.0,  0.0,  0.0,  0.0, 0.0}, // 啄擊
        { 0.0, 10.0, 10.0, 10.0, 0.0}, // 衝撞
        { 0.0,  0.0,  0.0,  0.0, 0.0},
        { 0.0,  0.0,  0.0,  0.0, 0.0}
    };

    double resistanceMean[8][5] = {
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {10.0, 2.0, 2.0, 2.0, 0.0}, // 草
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        { 0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        { 0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {3.0, 1.0, 1.0, 1.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        true,  // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::whiteradishChicken; // 白蘿蔔雞

    Peck peckSkill;             // 啄擊
    BodyCharge bodyChargeSkill; // 衝撞

    void calcScore();
    void calculate();
    std::string toString();
};

class YellowChicken : public BasePet { // 小黃雞
private:
    double maxHpMean[5] = {200.0, 30.0, 30.0, 30.0, 30.0};
    double maxHpDeviation[5] = {10.0, 3.0, 3.0, 3.0, 3.0};

    double strengthMean[5] = {27.0, 3.0, 4.0, 5.0, 6.0};
    double strengthDeviation[5] = {2.0, 2.0, 2.0, 2.0, 2.0};

    double defenseMean[5] = {10.0, 2.0, 3.0, 5.0, 4.0};
    double defenseDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    double speedMean[5] = {25.0, 2.0, 3.0, 4.0, 4.0};
    double speedDeviation[5] = {2.0, 1.0, 2.0, 2.0, 2.0};

    std::string extraCode[4] = {
        "/" + getSkillCodeByType(SkillType::peck),      // 啄擊
        "/" + getSkillCodeByType(SkillType::flyCharge), // 飛衝突擊
        "",
        ""
    };

    double skillDeviation[4][5] = {
        {20.0,  0.0, 20.0, 20.0, 20.0}, // 啄擊
        { 0.0, 10.0, 20.0, 20.0, 20.0}, // 飛衝突擊
        { 0.0,  0.0,  0.0,  0.0,  0.0},
        { 0.0,  0.0,  0.0,  0.0,  0.0}
    };

    double resistanceMean[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    double resistanceDeviation[8][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 無
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 闇
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 地
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 火
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 草
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 光
        {0.0, 0.0, 0.0, 0.0, 0.0}, // 水
        {0.0, 0.0, 0.0, 0.0, 0.0}  // 風
    };

    bool petElement[8] = {
        false, // 無
        false, // 闇
        false, // 地
        false, // 火
        false, // 草
        false, // 光
        false, // 水
        false  // 風
    };

public:
    PetType petType = PetType::yellowChicken; // 小黃雞

    Peck peckSkill;           // 啄擊
    FlyCharge flyChargeSkill; // 飛衝突擊

    void calcScore();
    void calculate();
    std::string toString();
};

class Pet {
public:
    std::string getPetInfo(PetType petType, std::string petGene, int petLevel, FruitType petFruitType, std::string petFruitCode);
    std::string getPetInfo(std::string petClass, std::string petGene, int petLevel, std::string petFruitName, std::string petFruitCode);

};

#endif // MF_PET_H
