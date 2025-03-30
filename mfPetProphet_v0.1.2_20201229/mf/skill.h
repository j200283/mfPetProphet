/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#ifndef MF_SKILL_H
#define MF_SKILL_H

#include <string>  // std::string
#include "type.h"  // FruitType, SkillType
#include "utils.h" // MD5RandomGenerator, NormalDistribution

class BaseSkill {
private:
    MD5RandomGenerator md5RandGen;
    NormalDistribution distribution;
    int _level;

    enum { // const random seed
        //MAX_HP = 0,
        //STRENGTH = 1,
        //SPEED = 2,
        //DEFENSE = 3,
        //SKILL_WEIGHT = 4,
        //GENDER = 5,
        //RESISTANCE = 6,
        SKILL_MULTIPLIER = 7,
        SKILL_ADDEND = 8,
        SKILL_HIT_PERCENT = 9,
        SKILL_SPECIAL = 10//,
        //ITEM_IMPRESSION = 11,
        //MEDICAL_IMPRESSION = 12,
        //MONSTER_HEIGHT = 13,
        //MONSTER_ITEM_DURATION = 14,
        //MONSTER_ITEM_DURATION_FIELD = 15,
        //MONSTER_FRUIT_KIMOCHI = 16,
        //MONSTER_FRUIT_SATIETY = 17,
        //MONSTER_FRUIT_LOYAL = 18,
        //MONSTER_FRUIT_HP = 19,
        //MONSTER_FRUIT_ELEMENT = 20
    };

    double calcSkillHitpercent(std::string extraCode, double hitPercentMean, double hitPercentDeviation); // battle & boss fruit function
    double calcSkillSpecial(std::string extraCode, double specialPowerMean, double specialPowerDeviation); // battle & boss fruit function

protected:
    double getSkillHitPercent(std::string extraCode, double hitPercentMean);
    double getSpecialPower(std::string extraCode, double specialPowerMean, double specialPowerDeviation, double minimum, double maximum, bool canGrow, bool keepDecimals, bool canFruitImpact);
    double getPowerMultiplier(std::string extraCode, double MultiplierMean, double MultiplierDeviation);
    double getPowerAddend(std::string extraCode, double AddendMean, double AddendDeviation);
    double getPower(std::string extraCode, double strength, double MultiplierMean, double MultiplierDeviation, double AddendMean, double AddendDeviation, double times);

public:
    std::string gene = ""; // gene prefix = "@monster_"
    FruitType fruitType = FruitType::empty;
    std::string fruitCode = "";
    double strength;

    void setLevel(int petLevel);
    int getLevel();
    void setAllValue(std::string petGene, int petLevel, FruitType petFruitType, std::string petFruitCode, double petStrength);
};

class AcornAttack : public BaseSkill { // 橡果子彈
private:
    std::string code = "/" + getSkillCodeByType(SkillType::acornAttack);

public:
    SkillType skillType = SkillType::acornAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class AttractingLight : public BaseSkill { // 螢光誘敵
private:
    std::string code = "/" + getSkillCodeByType(SkillType::attractingLight);

public:
    SkillType skillType = SkillType::attractingLight;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, attractIncrease, dodgeIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class BaldDartAttack : public BaseSkill { // 鷹羽飛針
private:
    std::string code = "/" + getSkillCodeByType(SkillType::baldDartAttack);

public:
    SkillType skillType = SkillType::baldDartAttack;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Berserk : public BaseSkill { // 狂暴
private:
    std::string code = "/" + getSkillCodeByType(SkillType::berserk);

public:
    SkillType skillType = SkillType::berserk;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, powerIncrease, criticalIncrease, defenseDecrease, dodgeDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Bite : public BaseSkill { // 咬擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::bite);

public:
    SkillType skillType = SkillType::bite;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class BodyCharge : public BaseSkill { // 衝撞
private:
    std::string code = "/" + getSkillCodeByType(SkillType::bodyCharge);

public:
    SkillType skillType = SkillType::bodyCharge;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class BoxingQuartet : public BaseSkill { // 螢光四重揍
private:
    std::string code = "/" + getSkillCodeByType(SkillType::boxingQuartet);

public:
    SkillType skillType = SkillType::boxingQuartet;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class BubbleAttack : public BaseSkill { // 噁噁泡
private:
    std::string code = "/" + getSkillCodeByType(SkillType::bubbleAttack);

public:
    SkillType skillType = SkillType::bubbleAttack;
    ElementType elementType = ElementType::water;
    double hitPercent, atk, powerIncrease, hitDecrease, dodgeDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class BubbleBomb : public BaseSkill { // 深水炸彈
private:
    std::string code = "/" + getSkillCodeByType(SkillType::bubbleBomb);

public:
    SkillType skillType = SkillType::bubbleBomb;
    ElementType elementType = ElementType::water;
    double hitPercent, atk, speedDecrease, dodgeDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class BubbleSpread : public BaseSkill { // 噴水特技
private:
    std::string code = "/" + getSkillCodeByType(SkillType::bubbleSpread);

public:
    SkillType skillType = SkillType::bubbleSpread;
    ElementType elementType = ElementType::water;
    double hitPercent, atk, speedDecrease, dodgeDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class CactusBubbleAttack : public BaseSkill { // 惡仙露
private:
    std::string code = "/" + getSkillCodeByType(SkillType::cactusBubbleAttack);

public:
    SkillType skillType = SkillType::cactusBubbleAttack;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class CactusThornRain : public BaseSkill { // 仙針雨
private:
    std::string code = "/" + getSkillCodeByType(SkillType::cactusThornRain);

public:
    SkillType skillType = SkillType::cactusThornRain;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class ChargeAlert : public BaseSkill { // 衝撞警戒 (衝撞反擊)
private:
    std::string code = "/" + getSkillCodeByType(SkillType::chargeAlert); // 計算 衝撞警戒 的 命中率 會用到
    std::string passiveCode = "/" + getSkillCodeByType(SkillType::counterCharge); // 計算 衝撞反擊 的 攻擊力(反擊) 會用到

public:
    SkillType skillType = SkillType::chargeAlert;
    SkillType passiveSkillType = SkillType::counterCharge;
    ElementType elementType = ElementType::normal; // 衝撞警戒 與 被動技-衝撞反擊 都是 無 屬性
    double hitPercent, atk, counterChargeAtk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class CircleRollCharge : public BaseSkill { // 旋風腳刀
private:
    std::string code = "/" + getSkillCodeByType(SkillType::circleRollCharge);

public:
    SkillType skillType = SkillType::circleRollCharge;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class CircleRollScrach : public BaseSkill { // 旋風金爪
private:
    std::string code = "/" + getSkillCodeByType(SkillType::circleRollScrach);

public:
    SkillType skillType = SkillType::circleRollScrach;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class ClawHit : public BaseSkill { // 爪擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::clawHit);

public:
    SkillType skillType = SkillType::clawHit;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DefenseIncrease : public BaseSkill { // 毛皮強化
private:
    std::string code = "/" + getSkillCodeByType(SkillType::defenseIncrease);

public:
    SkillType skillType = SkillType::defenseIncrease;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, defenseIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DefenseIncreaseWool : public BaseSkill { // 毛毛膜
private:
    std::string code = "/" + getSkillCodeByType(SkillType::defenseIncreaseWool);

public:
    SkillType skillType = SkillType::defenseIncreaseWool;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, defenseIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DodgeIncrease : public BaseSkill { // 注意力強化
private:
    std::string code = "/" + getSkillCodeByType(SkillType::dodgeIncrease);

public:
    SkillType skillType = SkillType::dodgeIncrease;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, dodgeIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleBox : public BaseSkill { // 雙拳擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleBox);

public:
    SkillType skillType = SkillType::doubleBox;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleCatClaw : public BaseSkill { // 貓爪抓
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleCatClaw);

public:
    SkillType skillType = SkillType::doubleCatClaw;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleClawHit : public BaseSkill { // 雙爪擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleClawHit);

public:
    SkillType skillType = SkillType::doubleClawHit;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleFinSlap : public BaseSkill { // 雙翼拍拍
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleFinSlap);

public:
    SkillType skillType = SkillType::doubleFinSlap;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleHandKnife : public BaseSkill { // 手風刃
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleHandKnife);

public:
    SkillType skillType = SkillType::doubleHandKnife;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleHeadHit : public BaseSkill { // 頭搥
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleHeadHit);

public:
    SkillType skillType = SkillType::doubleHeadHit;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DoubleThornHit : public BaseSkill { // 刺棘掌
private:
    std::string code = "/" + getSkillCodeByType(SkillType::doubleThornHit);

public:
    SkillType skillType = SkillType::doubleThornHit;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class DragonSeedAttack : public BaseSkill { // 火龍果子
private:
    std::string code = "/" + getSkillCodeByType(SkillType::dragonSeedAttack);

public:
    SkillType skillType = SkillType::dragonSeedAttack;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class EagleShout : public BaseSkill { // 大地鷹嚎
private:
    std::string code = "/" + getSkillCodeByType(SkillType::eagleShout);

public:
    SkillType skillType = SkillType::eagleShout;
    ElementType elementType = ElementType::earth;
    double hitPercent, atk, powerIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class EyeShine : public BaseSkill { // 金光閃閃
private:
    std::string code = "/" + getSkillCodeByType(SkillType::eyeShine);

public:
    SkillType skillType = SkillType::eyeShine;
    ElementType elementType = ElementType::light;
    double hitPercent, atk, hitDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class EyeStrike : public BaseSkill { // 目光震憾
private:
    std::string code = "/" + getSkillCodeByType(SkillType::eyeStrike);

public:
    SkillType skillType = SkillType::eyeStrike;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class EyesRay : public BaseSkill { // 熱線攻擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::eyesRay);

public:
    SkillType skillType = SkillType::eyesRay;
    ElementType elementType = ElementType::light;
    double hitPercent, atk, burn;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FeatherDartAttack : public BaseSkill { // 羽毛飛標
private:
    std::string code = "/" + getSkillCodeByType(SkillType::featherDartAttack);

public:
    SkillType skillType = SkillType::featherDartAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FeedHoneySpew : public BaseSkill { // 蜂蜜餵食
private:
    std::string code = "/" + getSkillCodeByType(SkillType::feedHoneySpew);

public:
    SkillType skillType = SkillType::feedHoneySpew;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk, regen;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FireSpew : public BaseSkill { // 兔火球
private:
    std::string code = "/" + getSkillCodeByType(SkillType::fireSpew);

public:
    SkillType skillType = SkillType::fireSpew;
    ElementType elementType = ElementType::fire;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FireTailAttack : public BaseSkill { // 神龍擺尾
private:
    std::string code = "/" + getSkillCodeByType(SkillType::fireTailAttack);

public:
    SkillType skillType = SkillType::fireTailAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FlyCharge : public BaseSkill { // 飛衝突擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::flyCharge);

public:
    SkillType skillType = SkillType::flyCharge;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FlyKick : public BaseSkill { // 大腳飛踢
private:
    std::string code = "/" + getSkillCodeByType(SkillType::flyKick);

public:
    SkillType skillType = SkillType::flyKick;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class FoxCharm : public BaseSkill { // 魅狐秋波
private:
    std::string code = "/" + getSkillCodeByType(SkillType::foxCharm);

public:
    SkillType skillType = SkillType::foxCharm;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Giant : public BaseSkill { // 巨獸術
private:
    std::string code = "/" + getSkillCodeByType(SkillType::giant);

public:
    SkillType skillType = SkillType::giant;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, powerIncrease, defenseIncrease, dodgeDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class GreenTornadoAttack : public BaseSkill { // 青羽旋風
private:
    std::string code = "/" + getSkillCodeByType(SkillType::greenTornadoAttack);

public:
    SkillType skillType = SkillType::greenTornadoAttack;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class GroundHit : public BaseSkill { // 搥擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::groundHit);

public:
    SkillType skillType = SkillType::groundHit;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class GroundStrike : public BaseSkill { // 飛天破地
private:
    std::string code = "/" + getSkillCodeByType(SkillType::groundStrike);

public:
    SkillType skillType = SkillType::groundStrike;
    ElementType elementType = ElementType::earth;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class HandBeam : public BaseSkill { // 熊掌氣功
private:
    std::string code = "/" + getSkillCodeByType(SkillType::handBeam);

public:
    SkillType skillType = SkillType::handBeam;
    ElementType elementType = ElementType::water;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class HandWave : public BaseSkill { // 開膛刀波
private:
    std::string code = "/" + getSkillCodeByType(SkillType::handWave);

public:
    SkillType skillType = SkillType::handWave;
    ElementType elementType = ElementType::earth;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class HellFire : public BaseSkill { // 地獄火
private:
    std::string code = "/" + getSkillCodeByType(SkillType::hellFire);

public:
    SkillType skillType = SkillType::hellFire;
    ElementType elementType = ElementType::fire;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class JumpAttack : public BaseSkill { // 泰山壓頂
private:
    std::string code = "/" + getSkillCodeByType(SkillType::jumpAttack);

public:
    SkillType skillType = SkillType::jumpAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class JumpKick : public BaseSkill { // 跳踢
private:
    std::string code = "/" + getSkillCodeByType(SkillType::jumpKick);

public:
    SkillType skillType = SkillType::jumpKick;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class JumpingDoubleSlash : public BaseSkill { // 水月斬
private:
    std::string code = "/" + getSkillCodeByType(SkillType::jumpingDoubleSlash);

public:
    SkillType skillType = SkillType::jumpingDoubleSlash;
    ElementType elementType = ElementType::water;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class JumpingKnife : public BaseSkill { // 飛空鍘
private:
    std::string code = "/" + getSkillCodeByType(SkillType::jumpingKnife);

public:
    SkillType skillType = SkillType::jumpingKnife;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class JumpingScratch : public BaseSkill { // 飛天爪
private:
    std::string code = "/" + getSkillCodeByType(SkillType::jumpingScratch);

public:
    SkillType skillType = SkillType::jumpingScratch;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Kick : public BaseSkill { // 踢擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::kick);

public:
    SkillType skillType = SkillType::kick;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class KnittingBallAttack : public BaseSkill { // 鋼毛飛球
private:
    std::string code = "/" + getSkillCodeByType(SkillType::knittingBallAttack);

public:
    SkillType skillType = SkillType::knittingBallAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class LeavesAttack : public BaseSkill { // 飛葉攻擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::leavesAttack);

public:
    SkillType skillType = SkillType::leavesAttack;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Lightning : public BaseSkill { // 金色閃電
private:
    std::string code = "/" + getSkillCodeByType(SkillType::lightning);

public:
    SkillType skillType = SkillType::lightning;
    ElementType elementType = ElementType::light;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class LoveEyes : public BaseSkill { // 裝可憐
private:
    std::string code = "/" + getSkillCodeByType(SkillType::loveEyes);

public:
    SkillType skillType = SkillType::loveEyes;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class MagicEyes : public BaseSkill { // 魔眼催眠
private:
    std::string code = "/" + getSkillCodeByType(SkillType::magicEyes);

public:
    SkillType skillType = SkillType::magicEyes;
    ElementType elementType = ElementType::dark;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class PatelDartAttack : public BaseSkill { // 飛花攻擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::patelDartAttack);

public:
    SkillType skillType = SkillType::patelDartAttack;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Peck : public BaseSkill { // 啄擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::peck);

public:
    SkillType skillType = SkillType::peck;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class PoisonBite : public BaseSkill { // 毒牙咬
private:
    std::string code = "/" + getSkillCodeByType(SkillType::poisonBite);

public:
    SkillType skillType = SkillType::poisonBite;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, poison;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class PowerIncrease : public BaseSkill { // 肌肉強化
private:
    std::string code = "/" + getSkillCodeByType(SkillType::powerIncrease);

public:
    SkillType skillType = SkillType::powerIncrease;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, powerIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class RegeneratePhytoncidSpew : public BaseSkill { // 芬多精
private:
    std::string code = "/" + getSkillCodeByType(SkillType::regeneratePhytoncidSpew);

public:
    SkillType skillType = SkillType::regeneratePhytoncidSpew;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk, regen;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class RegeneratePollenSpew : public BaseSkill { // 香香花粉
private:
    std::string code = "/" + getSkillCodeByType(SkillType::regeneratePollenSpew);

public:
    SkillType skillType = SkillType::regeneratePollenSpew;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk, regen;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class RockAttack : public BaseSkill { // 拋石
private:
    std::string code = "/" + getSkillCodeByType(SkillType::rockAttack);

public:
    SkillType skillType = SkillType::rockAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class RockDefense : public BaseSkill { // 地牙盾
private:
    std::string code = "/" + getSkillCodeByType(SkillType::rockDefense);

public:
    SkillType skillType = SkillType::rockDefense;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, defenseIncrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class RollingCharge : public BaseSkill { // 旋轉衝撞
private:
    std::string code = "/" + getSkillCodeByType(SkillType::rollingCharge);

public:
    SkillType skillType = SkillType::rollingCharge;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class ShellDart : public BaseSkill { // 貝殼飛盤
private:
    std::string code = "/" + getSkillCodeByType(SkillType::shellDart);

public:
    SkillType skillType = SkillType::shellDart;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class Shockwave : public BaseSkill { // 跳躍地震
private:
    std::string code = "/" + getSkillCodeByType(SkillType::shockwave);

public:
    SkillType skillType = SkillType::shockwave;
    ElementType elementType = ElementType::earth;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class SkunkBite : public BaseSkill { // 咬擊(臭鼬)
private:
    std::string code = "/" + getSkillCodeByType(SkillType::skunkBite);

public:
    SkillType skillType = SkillType::skunkBite;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class SlackPollenSpew : public BaseSkill { // 懶懶花粉
private:
    std::string code = "/" + getSkillCodeByType(SkillType::slackPollenSpew);

public:
    SkillType skillType = SkillType::slackPollenSpew;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class SporeSpew : public BaseSkill { // 昏睡孢子
private:
    std::string code = "/" + getSkillCodeByType(SkillType::sporeSpew);

public:
    SkillType skillType = SkillType::sporeSpew;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class SpringBubble : public BaseSkill { // 溫泉泡泡
private:
    std::string code = "/" + getSkillCodeByType(SkillType::springBubble);

public:
    SkillType skillType = SkillType::springBubble;
    ElementType elementType = ElementType::water;
    double hitPercent, atk, regen;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class StenchAttack : public BaseSkill { // 臭氣
private:
    std::string code = "/" + getSkillCodeByType(SkillType::stenchAttack);

public:
    SkillType skillType = SkillType::stenchAttack;
    ElementType elementType = ElementType::dark;
    double hitPercent, atk, lose;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class StingShoot : public BaseSkill { // 蜂針射擊
private:
    std::string code = "/" + getSkillCodeByType(SkillType::stingShoot);

public:
    SkillType skillType = SkillType::stingShoot;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk, poison;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class StinkBubble : public BaseSkill { // 臭臭氣
private:
    std::string code = "/" + getSkillCodeByType(SkillType::stinkBubble);

public:
    SkillType skillType = SkillType::stinkBubble;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk, powerDecrease, speedDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class StrawberryAttack : public BaseSkill { // 莓雨季節
private:
    std::string code = "/" + getSkillCodeByType(SkillType::strawberryAttack);

public:
    SkillType skillType = SkillType::strawberryAttack;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class SunlightAttack : public BaseSkill { // 太陽炫光
private:
    std::string code = "/" + getSkillCodeByType(SkillType::sunlightAttack);

public:
    SkillType skillType = SkillType::sunlightAttack;
    ElementType elementType = ElementType::light;
    double hitPercent, atk, speedDecrease, hitDecrease;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class TailAttack : public BaseSkill { // 尾鞭
private:
    std::string code = "/" + getSkillCodeByType(SkillType::tailAttack);

public:
    SkillType skillType = SkillType::tailAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class TannicAttack : public BaseSkill { // 單寧酸
private:
    std::string code = "/" + getSkillCodeByType(SkillType::tannicAttack);

public:
    SkillType skillType = SkillType::tannicAttack;
    ElementType elementType = ElementType::water;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class ThornRattan : public BaseSkill { // 地蕀爪
private:
    std::string code = "/" + getSkillCodeByType(SkillType::thornRattan);

public:
    SkillType skillType = SkillType::thornRattan;
    ElementType elementType = ElementType::earth;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class TornadoAttack : public BaseSkill { // 龍捲風暴
private:
    std::string code = "/" + getSkillCodeByType(SkillType::tornadoAttack);

public:
    SkillType skillType = SkillType::tornadoAttack;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class TriplePeck : public BaseSkill { // 啄擊(藍鵲)
private:
    std::string code = "/" + getSkillCodeByType(SkillType::triplePeck);

public:
    SkillType skillType = SkillType::triplePeck;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class TripleSting : public BaseSkill { // 蜂蜇
private:
    std::string code = "/" + getSkillCodeByType(SkillType::tripleSting);

public:
    SkillType skillType = SkillType::tripleSting;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class VolcanicEruption : public BaseSkill { // 火山爆花
private:
    std::string code = "/" + getSkillCodeByType(SkillType::volcanicEruption);

public:
    SkillType skillType = SkillType::volcanicEruption;
    ElementType elementType = ElementType::fire;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class WatermelonAttack : public BaseSkill { // 黑子雨
private:
    std::string code = "/" + getSkillCodeByType(SkillType::watermelonAttack);

public:
    SkillType skillType = SkillType::watermelonAttack;
    ElementType elementType = ElementType::grass;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class WingDeterrence : public BaseSkill { // 展翼嚇阻
private:
    std::string code = "/" + getSkillCodeByType(SkillType::wingDeterrence);

public:
    SkillType skillType = SkillType::wingDeterrence;
    ElementType elementType = ElementType::wind;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

class WoolBallAttack : public BaseSkill { // 鉛毛彈
private:
    std::string code = "/" + getSkillCodeByType(SkillType::woolBallAttack);

public:
    SkillType skillType = SkillType::woolBallAttack;
    ElementType elementType = ElementType::normal;
    double hitPercent, atk;

    void clear();
    void calculate();
    std::string toString(double usePercent);
};

#endif // MF_SKILL_H
