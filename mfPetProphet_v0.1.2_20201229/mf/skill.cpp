/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#include <algorithm> // std::min, std::max
#include <cmath>     // round
#include <iomanip>   // std::setw
#include <ios>       // std::left
#include <sstream>   // std::stringstream
#include <string>    // std::string

#include "skill.h"

double BaseSkill::calcSkillHitpercent(std::string extraCode, double hitPercentMean, double hitPercentDeviation) {
    double skillHitPercent;

    if(hitPercentMean > 0.9) {
        return 0.0;
    }

    md5RandGen.setSeed(fruitCode + gene + extraCode, SKILL_HIT_PERCENT);
    distribution.setValue(hitPercentDeviation * -1.5, hitPercentDeviation * 3.0);
    skillHitPercent = round(std::min(hitPercentDeviation * 5.0, distribution.random(md5RandGen)) * 100.0);

    if(skillHitPercent > 0) {
        return skillHitPercent / 100.0;
    }

    return 0.0;
}

double BaseSkill::calcSkillSpecial(std::string extraCode, double specialPowerMean, double specialPowerDeviation) {
    double skillSpecial;

    md5RandGen.setSeed(fruitCode + gene + extraCode, SKILL_SPECIAL);
    distribution.setValue(-specialPowerDeviation * 0.2, specialPowerDeviation * 1.2);
    skillSpecial = distribution.random(md5RandGen);

    if(skillSpecial > 0) {
        return std::min(specialPowerDeviation * 5.0, skillSpecial);
    }

    return 0.0;
}

double BaseSkill::getSkillHitPercent(std::string extraCode, double hitPercentMean) {
    const double hitPercentDeviation = 0.02;
    double skillHitPercent;

    md5RandGen.setSeed(gene + extraCode, SKILL_HIT_PERCENT);
    distribution.setValue(hitPercentMean + 0.0000123, hitPercentDeviation);
    skillHitPercent = distribution.random(md5RandGen);

    if(fruitType == FruitType::battle || fruitType == FruitType::boss) {
        skillHitPercent += calcSkillHitpercent(extraCode, hitPercentMean, hitPercentDeviation);
    }

    skillHitPercent = std::max(0.01, std::min(0.99, round(skillHitPercent * 100.0) / 100.0));

    return skillHitPercent;
}

double BaseSkill::getSpecialPower(std::string extraCode, double specialPowerMean, double specialPowerDeviation, double minimum, double maximum, bool canGrow, bool keepDecimals, bool canFruitImpact) {
    double specialPower;

    md5RandGen.setSeed(gene + extraCode, SKILL_SPECIAL);
    distribution.setValue(specialPowerMean, specialPowerDeviation);
    specialPower = distribution.random(md5RandGen);

    if(canGrow) {
        double temp = specialPower - specialPowerMean;

        if(temp > 0) {
            temp = std::min(temp, specialPowerDeviation * 5.0);
            specialPower = specialPowerMean + temp * _level;
        }
    }

    if(canFruitImpact) {
        if(fruitType == FruitType::battle || fruitType == FruitType::boss) {
            specialPower += calcSkillSpecial(extraCode, specialPowerMean, specialPowerDeviation);
        }
    }

    specialPower = std::max(minimum, std::min(maximum, specialPower));

    if(keepDecimals) // x.xx
        return round(specialPower * 100.0) / 100.0;
    else // x.00
        return round(specialPower);
}

double BaseSkill::getPowerMultiplier(std::string extraCode, double MultiplierMean, double MultiplierDeviation) {
    md5RandGen.setSeed(gene + extraCode, SKILL_MULTIPLIER);
    distribution.setValue(MultiplierMean, MultiplierDeviation);

    return std::max(0.0, distribution.random(md5RandGen));
}

double BaseSkill::getPowerAddend(std::string extraCode, double AddendMean, double AddendDeviation) {
    double temp1, temp2;

    md5RandGen.setSeed(gene + extraCode, SKILL_ADDEND);
    distribution.setValue(AddendMean, AddendDeviation);
    temp1 = distribution.random(md5RandGen);
    temp2 = temp1 - AddendMean;

    if(temp2 > 0) {
        temp1 = AddendMean + temp2 * _level;
    }

    return std::max(0.0, temp1);
}

double BaseSkill::getPower(std::string extraCode, double strength, double MultiplierMean, double MultiplierDeviation, double AddendMean, double AddendDeviation, double times) {
    double power;

    power = getPowerMultiplier(extraCode, MultiplierMean, MultiplierDeviation) * std::max(0.0, strength) +
            getPowerAddend(extraCode, AddendMean, AddendDeviation);

    return round(power * times);
}

void BaseSkill::setLevel(int petLevel) {
    int temp = petLevel - 1;

    if(temp < 0)
        temp = 0; // Level 1 = (int)0
    else if(temp > 4)
        temp = 4; // Level 5 = (int)4

    _level = temp;
}

int BaseSkill::getLevel() {
    return _level + 1;
}

void BaseSkill::setAllValue(std::string petGene, int petLevel, FruitType petFruitType, std::string petFruitCode, double petStrength) {
    gene = petGene;
    setLevel(petLevel);
    fruitType = petFruitType;
    fruitCode = petFruitCode;
    strength = petStrength;
}

void AcornAttack::clear() { // 橡果子彈
    hitPercent = 0.0;
    atk = 0.0;
}

void AcornAttack::calculate() { // 橡果子彈
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = getPower(code, strength, 1.0, 0.2, 15.0, 2.0, 1.0);
}

std::string AcornAttack::toString(double usePercent) { // 橡果子彈
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void AttractingLight::clear() { // 螢光誘敵
    hitPercent = 0.0;
    atk = 0.0;
    attractIncrease = 0.0;
    dodgeIncrease = 0.0;
}

void AttractingLight::calculate() { // 螢光誘敵
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    attractIncrease = getSpecialPower(code + "/attract", 0.66, 0.05, 0.01, 0.99, true, true, true);
    dodgeIncrease = getSpecialPower(code + "/dodge", 0.5, 0.03, 0.01, 0.99, true, true, true);
}

std::string AttractingLight::toString(double usePercent) { // 螢光誘敵
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (閃避: +" << dodgeIncrease * 100 << "%   誘敵: +" << attractIncrease * 100 << "%)";

    return ss.str();
}

void BaldDartAttack::clear() { // 鷹羽飛針
    hitPercent = 0.0;
    atk = 0.0;
}

void BaldDartAttack::calculate() { // 鷹羽飛針
    hitPercent = getSkillHitPercent(code, 0.72);
    atk = getPower(code, strength, 0.8, 0.08, 5.0, 2.0, 2.0);
}

std::string BaldDartAttack::toString(double usePercent) { // 鷹羽飛針
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void Berserk::clear() { // 狂暴
    hitPercent = 0.0;
    atk = 0.0;
    powerIncrease = 0.0;
    criticalIncrease = 0.0;
    defenseDecrease = 0.0;
    dodgeDecrease = 0.0;
}

void Berserk::calculate() { // 狂暴
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    powerIncrease = getSpecialPower(code + "/power", 0.2, 0.02, 0.01, 3.0, true, true, true);
    criticalIncrease = getSpecialPower(code + "/critical", 0.32, 0.02, 0.01, 0.99, true, true, true);
    defenseDecrease = getSpecialPower(code + "/defense", 0.32, 0.015, 0.01, 3.0, true, true, false);
    dodgeDecrease = getSpecialPower(code + "/dodge", 0.08, 0.015, 0.01, 3.0, true, true, false);
}

std::string Berserk::toString(double usePercent) { // 狂暴
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (力量: +" << powerIncrease * 100 << "%   爆擊: +" << criticalIncrease * 100 << "%   防禦: -" << defenseDecrease * 100 << "%   迴避: -" << dodgeDecrease * 100 << "%)";

    return ss.str();
}

void Bite::clear() { // 咬擊
    hitPercent = 0.0;
    atk = 0.0;
}

void Bite::calculate() { // 咬擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string Bite::toString(double usePercent) { // 咬擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void BodyCharge::clear() { // 衝撞
    hitPercent = 0.0;
    atk = 0.0;
}

void BodyCharge::calculate() { // 衝撞
    hitPercent = getSkillHitPercent(code, 0.79);
    atk = getPower(code, strength, 1.2, 0.12, 15.0, 2.0, 1.0);
}

std::string BodyCharge::toString(double usePercent) { // 衝撞
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void BoxingQuartet::clear() { // 螢光四重揍
    hitPercent = 0.0;
    atk = 0.0;
}

void BoxingQuartet::calculate() { // 螢光四重揍
    hitPercent = getSkillHitPercent(code, 0.80);
    atk = getPower(code, strength, 1.2, 0.12, 20.0, 3.0, 1.0);
}

std::string BoxingQuartet::toString(double usePercent) { // 螢光四重揍
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void BubbleAttack::clear() { // 噁噁泡
    hitPercent = 0.0;
    atk = 0.0;
    powerIncrease = 0.0;
    hitDecrease = 0.0;
    dodgeDecrease = 0.0;
}

void BubbleAttack::calculate() { // 噁噁泡
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 0.1, 0.01, 2.0, 1.0, 1.0);
    powerIncrease = getSpecialPower(code + "/power", 0.08, 0.02, 0.01, 0.99, false, true, false);
    hitDecrease = getSpecialPower(code + "/hit", 0.2, 0.02, 0.01, 0.99, true, true, true);
    dodgeDecrease = getSpecialPower(code + "/dodge", 0.2, 0.02, 0.01, 0.99, true, true, true);
}

std::string BubbleAttack::toString(double usePercent) { // 噁噁泡
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (力量: +" << powerIncrease * 100 << "%   命中: -" << hitDecrease * 100 << "%   閃避: -" << dodgeDecrease * 100 << "%)";

    return ss.str();
}

void BubbleBomb::clear() { // 深水炸彈
    hitPercent = 0.0;
    atk = 0.0;
    speedDecrease = 0.0;
    dodgeDecrease = 0.0;
}

void BubbleBomb::calculate() { // 深水炸彈
    hitPercent = getSkillHitPercent(code, 0.84);
    atk = getPower(code, strength, 0.35, 0.035, 5.0, 1.0, 3.0);
    speedDecrease = getSpecialPower(code, 0.5, 0.05, 0.01, 0.99, true, true, true);
    //dodgeDecrease = round((speedDecrease * 0.58) * 100.0) / 100.0;
    dodgeDecrease = getSpecialPower(code, 0.5 * 0.58, 0.05 * 0.58, 0.01 * 0.58, 0.99 * 0.58, true, true, true);
}

std::string BubbleBomb::toString(double usePercent) { // 深水炸彈
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (速度: -" << speedDecrease * 100 << "%   閃避: -" << dodgeDecrease * 100 << "%)";

    return ss.str();
}

void BubbleSpread::clear() { // 噴水特技
    hitPercent = 0.0;
    atk = 0.0;
    speedDecrease = 0.0;
    dodgeDecrease = 0.0;
}

void BubbleSpread::calculate() { // 噴水特技
    hitPercent = getSkillHitPercent(code, 0.76);
    atk = 0.0;
    speedDecrease = getSpecialPower(code, 0.5, 0.05, 0.01, 0.99, true, true, true);
    //dodgeDecrease = round((speedDecrease * 0.58) * 100.0) / 100.0;
    dodgeDecrease = getSpecialPower(code, 0.5 * 0.58, 0.05 * 0.58, 0.01 * 0.58, 0.99 * 0.58, true, true, true);
}

std::string BubbleSpread::toString(double usePercent) { // 噴水特技
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (速度: -" << speedDecrease * 100 << "%   閃避: -" << dodgeDecrease * 100 << "%)";

    return ss.str();
}

void CactusBubbleAttack::clear() { // 惡仙露
    hitPercent = 0.0;
    atk = 0.0;
}

void CactusBubbleAttack::calculate() { // 惡仙露
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 0.5, 0.05, 16.0, 2.5, 1.0);
}

std::string CactusBubbleAttack::toString(double usePercent) { // 惡仙露
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void CactusThornRain::clear() { // 仙針雨
    hitPercent = 0.0;
    atk = 0.0;
}

void CactusThornRain::calculate() { // 仙針雨
    hitPercent = getSkillHitPercent(code, 0.75);
    atk = getPower(code, strength, 0.1, 0.01, 5.0, 0.32, 16.0);
}

std::string CactusThornRain::toString(double usePercent) { // 仙針雨
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void ChargeAlert::clear() { // 衝撞警戒 (衝撞反擊)
    hitPercent = 0.0;
    atk = 0.0;
    counterChargeAtk = 0.0;
}

void ChargeAlert::calculate() { // 衝撞警戒 (衝撞反擊)
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    counterChargeAtk = getPower(passiveCode, strength, 1.2, 0.12, 15.0, 2.0, 1.0);
}

std::string ChargeAlert::toString(double usePercent) { // 衝撞警戒 (衝撞反擊)
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (反擊: " << counterChargeAtk << ")";

    return ss.str();
}

void CircleRollCharge::clear() { // 旋風腳刀
    hitPercent = 0.0;
    atk = 0.0;
}

void CircleRollCharge::calculate() { // 旋風腳刀
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = getPower(code, strength, 0.5, 0.035, 15.0, 2.0, 1.0);
}

std::string CircleRollCharge::toString(double usePercent) { // 旋風腳刀
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void CircleRollScrach::clear() { // 旋風金爪
    hitPercent = 0.0;
    atk = 0.0;
}

void CircleRollScrach::calculate() { // 旋風金爪
    hitPercent = getSkillHitPercent(code, 0.78);
    atk = getPower(code, strength, 0.65, 0.05, 12.0, 2.0, 1.0);
}

std::string CircleRollScrach::toString(double usePercent) { // 旋風金爪
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void ClawHit::clear() { // 爪擊
    hitPercent = 0.0;
    atk = 0.0;
}

void ClawHit::calculate() { // 爪擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string ClawHit::toString(double usePercent) { // 爪擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DefenseIncrease::clear() { // 毛皮強化
    hitPercent = 0.0;
    atk = 0.0;
    defenseIncrease = 0.0;
}

void DefenseIncrease::calculate() { // 毛皮強化
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    defenseIncrease = getSpecialPower(code, 0.84, 0.06, 0.01, 3.00, false, true, true);
}

std::string DefenseIncrease::toString(double usePercent) { // 毛皮強化
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (防禦: +" << defenseIncrease * 100 << "%)";

    return ss.str();
}

void DefenseIncreaseWool::clear() { // 毛毛膜
    hitPercent = 0.0;
    atk = 0.0;
    defenseIncrease = 0.0;
}

void DefenseIncreaseWool::calculate() { // 毛毛膜
    hitPercent = getSkillHitPercent(code, 0.84);
    atk = 0.0;
    defenseIncrease = getSpecialPower(code, 0.41, 0.025, 0.01, 0.99, true, true, true);
}

std::string DefenseIncreaseWool::toString(double usePercent) { // 毛毛膜
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (防禦: +" << defenseIncrease * 100 << "%)";

    return ss.str();
}

void DodgeIncrease::clear() { // 注意力強化
    hitPercent = 0.0;
    atk = 0.0;
    dodgeIncrease = 0.0;
}

void DodgeIncrease::calculate() { // 注意力強化
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    dodgeIncrease = getSpecialPower(code, 0.294, 0.021, 0.01, 3.00, false, true, true);
}

std::string DodgeIncrease::toString(double usePercent) { // 注意力強化
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (閃避: +" << dodgeIncrease * 100 << "%)";

    return ss.str();
}

void DoubleBox::clear() { // 雙拳擊
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleBox::calculate() { // 雙拳擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string DoubleBox::toString(double usePercent) { // 雙拳擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DoubleCatClaw::clear() { // 貓爪抓
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleCatClaw::calculate() { // 貓爪抓
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string DoubleCatClaw::toString(double usePercent) { // 貓爪抓
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DoubleClawHit::clear() { // 雙爪擊
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleClawHit::calculate() { // 雙爪擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string DoubleClawHit::toString(double usePercent) { // 雙爪擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DoubleFinSlap::clear() { // 雙翼拍拍
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleFinSlap::calculate() { // 雙翼拍拍
    hitPercent = getSkillHitPercent(code, 0.88);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string DoubleFinSlap::toString(double usePercent) { // 雙翼拍拍
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DoubleHandKnife::clear() { // 手風刃
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleHandKnife::calculate() { // 手風刃
    hitPercent = getSkillHitPercent(code, 0.72);
    atk = getPower(code, strength, 0.4, 0.03, 15.0, 2.0, 2.0);
}

std::string DoubleHandKnife::toString(double usePercent) { // 手風刃
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DoubleHeadHit::clear() { // 頭搥
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleHeadHit::calculate() { // 頭搥
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = getPower(code, strength, 1.2, 0.12, 15.0, 2.0, 1.0);
}

std::string DoubleHeadHit::toString(double usePercent) { // 頭搥
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DoubleThornHit::clear() { // 刺棘掌
    hitPercent = 0.0;
    atk = 0.0;
}

void DoubleThornHit::calculate() { // 刺棘掌
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string DoubleThornHit::toString(double usePercent) { // 刺棘掌
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void DragonSeedAttack::clear() { // 火龍果子
    hitPercent = 0.0;
    atk = 0.0;
}

void DragonSeedAttack::calculate() { // 火龍果子
    hitPercent = getSkillHitPercent(code, 0.75);
    atk = getPower(code, strength, 0.1, 0.01, 6.0, 0.45, 11.0);
}

std::string DragonSeedAttack::toString(double usePercent) { // 火龍果子
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void EagleShout::clear() { // 大地鷹嚎
    hitPercent = 0.0;
    atk = 0.0;
    powerIncrease = 0.0;
}

void EagleShout::calculate() { // 大地鷹嚎
    hitPercent = getSkillHitPercent(code, 0.84);
    atk = 0.0;
    powerIncrease = getSpecialPower(code, 0.26, 0.025, 0.01, 0.99, true, true, true);
}

std::string EagleShout::toString(double usePercent) { // 大地鷹嚎
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (力量: +" << powerIncrease * 100 << "%)";

    return ss.str();
}

void EyeShine::clear() { // 金光閃閃
    hitPercent = 0.0;
    atk = 0.0;
    hitDecrease = 0.0;
}

void EyeShine::calculate() { // 金光閃閃
    hitPercent = getSkillHitPercent(code, 0.80);
    atk = getPower(code, strength, 0.3, 0.05, 6.0, 2.0, 2.0);
    hitDecrease = getSpecialPower(code, 0.22, 0.02, 0.01, 0.99, true, true, true);
}

std::string EyeShine::toString(double usePercent) { // 金光閃閃
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (命中: -" << hitDecrease * 100 << "%)";

    return ss.str();
}

void EyeStrike::clear() { // 目光震憾
    hitPercent = 0.0;
    atk = 0.0;
}

void EyeStrike::calculate() { // 目光震憾
    hitPercent = getSkillHitPercent(code, 0.80);
    atk = 0.0;
}

std::string EyeStrike::toString(double usePercent) { // 目光震憾
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void EyesRay::clear() { // 熱線攻擊
    hitPercent = 0.0;
    atk = 0.0;
    burn = 0.0;
}

void EyesRay::calculate() { // 熱線攻擊
    hitPercent = getSkillHitPercent(code, 0.74);
    atk = getPower(code, strength, 0.5, 0.05, 15.0, 2.0, 2.0);
    burn = getSpecialPower(code, 8.0, 1.5, 1.0, 30.0, true, false, true);
}

std::string EyesRay::toString(double usePercent) { // 熱線攻擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (灼傷: " << burn << ")";

    return ss.str();
}

void FeatherDartAttack::clear() { // 羽毛飛標
    hitPercent = 0.0;
    atk = 0.0;
}

void FeatherDartAttack::calculate() { // 羽毛飛標
    hitPercent = getSkillHitPercent(code, 0.65);
    atk = getPower(code, strength, 0.3, 0.03, 5.0, 1.0, 4.0);
}

std::string FeatherDartAttack::toString(double usePercent) { // 羽毛飛標
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void FeedHoneySpew::clear() { // 蜂蜜餵食
    hitPercent = 0.0;
    atk = 0.0;
    regen = 0.0;
}

void FeedHoneySpew::calculate() { // 蜂蜜餵食
    hitPercent = getSkillHitPercent(code, 0.96);
    atk = 0.0;
    regen = getSpecialPower(code, 36.0, 3.0, 1.0, 80.0, true, false, true);
}

std::string FeedHoneySpew::toString(double usePercent) { // 蜂蜜餵食
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (回復: " << regen << ")";

    return ss.str();
}

void FireSpew::clear() { // 兔火球
    hitPercent = 0.0;
    atk = 0.0;
}

void FireSpew::calculate() { // 兔火球
    hitPercent = getSkillHitPercent(code, 0.84);
    atk = getPower(code, strength, 0.7, 0.07, 40.0, 7.5, 1.0);
}

std::string FireSpew::toString(double usePercent) { // 兔火球
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void FireTailAttack::clear() { // 神龍擺尾
    hitPercent = 0.0;
    atk = 0.0;
}

void FireTailAttack::calculate() { // 神龍擺尾
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string FireTailAttack::toString(double usePercent) { // 神龍擺尾
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void FlyCharge::clear() { // 飛衝突擊
    hitPercent = 0.0;
    atk = 0.0;
}

void FlyCharge::calculate() { // 飛衝突擊
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = getPower(code, strength, 1.0, 0.1, 20.0, 2.0, 1.0);
}

std::string FlyCharge::toString(double usePercent) { // 飛衝突擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void FlyKick::clear() { // 大腳飛踢
    hitPercent = 0.0;
    atk = 0.0;
}

void FlyKick::calculate() { // 大腳飛踢
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = getPower(code, strength, 1.0, 0.1, 20.0, 2.0, 1.0);
}

std::string FlyKick::toString(double usePercent) { // 大腳飛踢
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void FoxCharm::clear() { // 魅狐秋波
    hitPercent = 0.0;
    atk = 0.0;
}

void FoxCharm::calculate() { // 魅狐秋波
    hitPercent = getSkillHitPercent(code, 0.92);
    atk = 0.0;
}

std::string FoxCharm::toString(double usePercent) { // 魅狐秋波
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void Giant::clear() { // 巨獸術
    hitPercent = 0.0;
    atk = 0.0;
    powerIncrease = 0.0;
    defenseIncrease = 0.0;
    dodgeDecrease = 0.0;
}

void Giant::calculate() { // 巨獸術
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    powerIncrease = getSpecialPower(code + "/power", 0.3, 0.03, 0.01, 3.00, true, true, true);
    defenseIncrease = getSpecialPower(code + "/defense", 0.24, 0.02, 0.01, 3.00, true, true, true);
    dodgeDecrease = getSpecialPower(code + "/dodge", 0.28, 0.03, 0.01, 3.00, true, true, false);
}

std::string Giant::toString(double usePercent) { // 巨獸術
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (力量: +" << powerIncrease * 100 << "%   防禦: +" << defenseIncrease * 100 << "%   閃避: -" << dodgeDecrease * 100 << "%)";

    return ss.str();
}

void GreenTornadoAttack::clear() { // 青羽旋風
    hitPercent = 0.0;
    atk = 0.0;
}

void GreenTornadoAttack::calculate() { // 青羽旋風
    hitPercent = getSkillHitPercent(code, 0.80);
    atk = getPower(code, strength, 0.3, 0.03, 60.0, 5.0, 1.0);
}

std::string GreenTornadoAttack::toString(double usePercent) { // 青羽旋風
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void GroundHit::clear() { // 搥擊
    hitPercent = 0.0;
    atk = 0.0;
}

void GroundHit::calculate() { // 搥擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string GroundHit::toString(double usePercent) { // 搥擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void GroundStrike::clear() { // 飛天破地
    hitPercent = 0.0;
    atk = 0.0;
}

void GroundStrike::calculate() { // 飛天破地
    hitPercent = getSkillHitPercent(code, 0.81);
    atk = getPower(code, strength, 1.4, 0.14, 26.0, 3.0, 1.0);
}

std::string GroundStrike::toString(double usePercent) { // 飛天破地
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void HandBeam::clear() { // 熊掌氣功
    hitPercent = 0.0;
    atk = 0.0;
}

void HandBeam::calculate() { // 熊掌氣功
    hitPercent = getSkillHitPercent(code, 0.74);
    atk = getPower(code, strength, 1.2, 0.12, 25.0, 3.0, 1.0);
}

std::string HandBeam::toString(double usePercent) { // 熊掌氣功
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void HandWave::clear() { // 開膛刀波
    hitPercent = 0.0;
    atk = 0.0;
}

void HandWave::calculate() { // 開膛刀波
    hitPercent = getSkillHitPercent(code, 0.88);
    atk = getPower(code, strength, 1.0, 0.1, 20.0, 2.5, 1.0);
}

std::string HandWave::toString(double usePercent) { // 開膛刀波
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void HellFire::clear() { // 地獄火
    hitPercent = 0.0;
    atk = 0.0;
}

void HellFire::calculate() { // 地獄火
    hitPercent = getSkillHitPercent(code, 0.60);
    atk = getPower(code, strength, 0.1, 0.01, 1.25, 0.16, 34.0);
}

std::string HellFire::toString(double usePercent) { // 地獄火
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void JumpAttack::clear() { // 泰山壓頂
    hitPercent = 0.0;
    atk = 0.0;
}

void JumpAttack::calculate() { // 泰山壓頂
    hitPercent = getSkillHitPercent(code, 0.72);
    atk = getPower(code, strength, 1.4, 0.14, 18.0, 2.0, 1.0);
}

std::string JumpAttack::toString(double usePercent) { // 泰山壓頂
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void JumpKick::clear() { // 跳踢
    hitPercent = 0.0;
    atk = 0.0;
}

void JumpKick::calculate() { // 跳踢
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string JumpKick::toString(double usePercent) { // 跳踢
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void JumpingDoubleSlash::clear() { // 水月斬
    hitPercent = 0.0;
    atk = 0.0;
}

void JumpingDoubleSlash::calculate() { // 水月斬
    hitPercent = getSkillHitPercent(code, 0.76);
    atk = getPower(code, strength, 1.4, 0.12, 18.0, 2.0, 1.0);
}

std::string JumpingDoubleSlash::toString(double usePercent) { // 水月斬
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void JumpingKnife::clear() { // 飛空鍘
    hitPercent = 0.0;
    atk = 0.0;
}

void JumpingKnife::calculate() { // 飛空鍘
    hitPercent = getSkillHitPercent(code, 0.77);
    atk = getPower(code, strength, 1.2, 0.1, 24.0, 2.5, 1.0);
}

std::string JumpingKnife::toString(double usePercent) { // 飛空鍘
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void JumpingScratch::clear() { // 飛天爪
    hitPercent = 0.0;
    atk = 0.0;
}

void JumpingScratch::calculate() { // 飛天爪
    hitPercent = getSkillHitPercent(code, 0.72);
    atk = getPower(code, strength, 1.4, 0.14, 18.0, 2.0, 1.0);
}

std::string JumpingScratch::toString(double usePercent) { // 飛天爪
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void Kick::clear() { // 踢擊
    hitPercent = 0.0;
    atk = 0.0;
}

void Kick::calculate() { // 踢擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string Kick::toString(double usePercent) { // 踢擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void KnittingBallAttack::clear() { // 鋼毛飛球
    hitPercent = 0.0;
    atk = 0.0;
}

void KnittingBallAttack::calculate() { // 鋼毛飛球
    hitPercent = getSkillHitPercent(code, 0.78);
    atk = getPower(code, strength, 0.5, 0.05, 45.0, 5.0, 1.0);
}

std::string KnittingBallAttack::toString(double usePercent) { // 鋼毛飛球
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void LeavesAttack::clear() { // 飛葉攻擊
    hitPercent = 0.0;
    atk = 0.0;
}

void LeavesAttack::calculate() { // 飛葉攻擊
    hitPercent = getSkillHitPercent(code, 0.70);
    atk = getPower(code, strength, 0.1, 0.01, 3.0, 0.3, 15.0);
}

std::string LeavesAttack::toString(double usePercent) { // 飛葉攻擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void Lightning::clear() { // 金色閃電
    hitPercent = 0.0;
    atk = 0.0;
}

void Lightning::calculate() { // 金色閃電
    hitPercent = getSkillHitPercent(code, 0.54);
    atk = getPower(code, strength, 0.3, 0.03, 6.0, 2.0, 3.0);
}

std::string Lightning::toString(double usePercent) { // 金色閃電
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void LoveEyes::clear() { // 裝可憐
    hitPercent = 0.0;
    atk = 0.0;
}

void LoveEyes::calculate() { // 裝可憐
    hitPercent = getSkillHitPercent(code, 0.50);
    atk = 0.0;
}

std::string LoveEyes::toString(double usePercent) { // 裝可憐
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void MagicEyes::clear() { // 魔眼催眠
    hitPercent = 0.0;
    atk = 0.0;
}

void MagicEyes::calculate() { // 魔眼催眠
    hitPercent = getSkillHitPercent(code, 0.71);
    atk = 0.0;
}

std::string MagicEyes::toString(double usePercent) { // 魔眼催眠
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void PatelDartAttack::clear() { // 飛花攻擊
    hitPercent = 0.0;
    atk = 0.0;
}

void PatelDartAttack::calculate() { // 飛花攻擊
    hitPercent = getSkillHitPercent(code, 0.68);
    atk = getPower(code, strength, 0.5, 0.05, 20.0, 2.0, 2.0);
}

std::string PatelDartAttack::toString(double usePercent) { // 飛花攻擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void Peck::clear() { // 啄擊
    hitPercent = 0.0;
    atk = 0.0;
}

void Peck::calculate() { // 啄擊
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string Peck::toString(double usePercent) { // 啄擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void PoisonBite::clear() { // 毒牙咬
    hitPercent = 0.0;
    atk = 0.0;
    poison = 0.0;
}

void PoisonBite::calculate() { // 毒牙咬
    hitPercent = getSkillHitPercent(code, 0.72);
    atk = getPower(code, strength, 1.0, 0.1, 5.0, 1.0, 1.0);
    poison = getSpecialPower(code, 18.0, 2.0, 1.0, 80.0, true, false, true);
}

std::string PoisonBite::toString(double usePercent) { // 毒牙咬
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (中毒: " << poison << ")";

    return ss.str();
}

void PowerIncrease::clear() { // 肌肉強化
    hitPercent = 0.0;
    atk = 0.0;
    powerIncrease = 0.0;
}

void PowerIncrease::calculate() { // 肌肉強化
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    powerIncrease = getSpecialPower(code, 0.42, 0.03, 0.01, 3.00, false, true, true);
}

std::string PowerIncrease::toString(double usePercent) { // 肌肉強化
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (力量: +" << powerIncrease * 100 << "%)";

    return ss.str();
}

void RegeneratePhytoncidSpew::clear() { // 芬多精
    hitPercent = 0.0;
    atk = 0.0;
    regen = 0.0;
}

void RegeneratePhytoncidSpew::calculate() { // 芬多精
    hitPercent = getSkillHitPercent(code, 0.88);
    atk = 0.0;
    regen = getSpecialPower(code, 15.0, 2.5, 1.0, 30.0, true, false, true);
}

std::string RegeneratePhytoncidSpew::toString(double usePercent) { // 芬多精
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (回復: " << regen << ")";

    return ss.str();
}

void RegeneratePollenSpew::clear() { // 香香花粉
    hitPercent = 0.0;
    atk = 0.0;
    regen = 0.0;
}

void RegeneratePollenSpew::calculate() { // 香香花粉
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = 0.0;
    regen = getSpecialPower(code, 14.0, 2.0, 1.0, 30.0, true, false, true);
}

std::string RegeneratePollenSpew::toString(double usePercent) { // 香香花粉
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (回復: " << regen << ")";

    return ss.str();
}

void RockAttack::clear() { // 拋石
    hitPercent = 0.0;
    atk = 0.0;
}

void RockAttack::calculate() { // 拋石
    hitPercent = getSkillHitPercent(code, 0.77);
    atk = getPower(code, strength, 1.4, 0.12, 15.0, 2.5, 1.0);
}

std::string RockAttack::toString(double usePercent) { // 拋石
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void RockDefense::clear() { // 地牙盾
    hitPercent = 0.0;
    atk = 0.0;
    defenseIncrease = 0.0;
}

void RockDefense::calculate() { // 地牙盾
    hitPercent = getSkillHitPercent(code, 1.00);
    atk = 0.0;
    defenseIncrease = getSpecialPower(code, 3.66, 0.3, 0.01, 9.00, false, true, true);
}

std::string RockDefense::toString(double usePercent) { // 地牙盾
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (防禦: +" << defenseIncrease * 100 << "%)";

    return ss.str();
}

void RollingCharge::clear() { // 旋轉衝撞
    hitPercent = 0.0;
    atk = 0.0;
}

void RollingCharge::calculate() { // 旋轉衝撞
    hitPercent = getSkillHitPercent(code, 0.77);
    atk = getPower(code, strength, 1.2, 0.12, 15.0, 2.0, 1.0);
}

std::string RollingCharge::toString(double usePercent) { // 旋轉衝撞
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void ShellDart::clear() { // 貝殼飛盤
    hitPercent = 0.0;
    atk = 0.0;
}

void ShellDart::calculate() { // 貝殼飛盤
    hitPercent = getSkillHitPercent(code, 0.75);
    atk = getPower(code, strength, 0.5, 0.05, 12.0, 2.5, 1.0);
}

std::string ShellDart::toString(double usePercent) { // 貝殼飛盤
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void Shockwave::clear() { // 跳躍地震
    hitPercent = 0.0;
    atk = 0.0;
}

void Shockwave::calculate() { // 跳躍地震
    hitPercent = getSkillHitPercent(code, 0.66);
    atk = 0.0;
}

std::string Shockwave::toString(double usePercent) { // 跳躍地震
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void SkunkBite::clear() { // 咬擊(臭鼬)
    hitPercent = 0.0;
    atk = 0.0;
}

void SkunkBite::calculate() { // 咬擊(臭鼬)
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string SkunkBite::toString(double usePercent) { // 咬擊(臭鼬)
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void SlackPollenSpew::clear() { // 懶懶花粉
    hitPercent = 0.0;
    atk = 0.0;
}

void SlackPollenSpew::calculate() { // 懶懶花粉
    hitPercent = getSkillHitPercent(code, 0.96);
    atk = 0.0;
}

std::string SlackPollenSpew::toString(double usePercent) { // 懶懶花粉
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void SporeSpew::clear() { // 昏睡孢子
    hitPercent = 0.0;
    atk = 0.0;
}

void SporeSpew::calculate() { // 昏睡孢子
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = 0.0;
}

std::string SporeSpew::toString(double usePercent) { // 昏睡孢子
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void SpringBubble::clear() { // 溫泉泡泡
    hitPercent = 0.0;
    atk = 0.0;
    regen = 0.0;
}

void SpringBubble::calculate() { // 溫泉泡泡
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = 0.0;
    regen = getSpecialPower(code, 7.0, 1.0, 1.0, 20.0, true, false, true);
}

std::string SpringBubble::toString(double usePercent) { // 溫泉泡泡
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (回復: " << regen << ")";

    return ss.str();
}

void StenchAttack::clear() { // 臭氣
    hitPercent = 0.0;
    atk = 0.0;
    lose = 0.0;
}

void StenchAttack::calculate() { // 臭氣
    hitPercent = getSkillHitPercent(code, 0.54);
    atk = 0.0;
    lose = getSpecialPower(code, 14.0, 1.4, 5.0, 30.0, true, false, true);
}

std::string StenchAttack::toString(double usePercent) { // 臭氣
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (損失: " << lose << ")";

    return ss.str();
}

void StingShoot::clear() { // 蜂針射擊
    hitPercent = 0.0;
    atk = 0.0;
    poison = 0.0;
}

void StingShoot::calculate() { // 蜂針射擊
    hitPercent = getSkillHitPercent(code, 0.76);
    atk = getPower(code, strength, 1.0, 0.1, 14.0, 2.0, 1.0);
    poison = getSpecialPower(code, 15.0, 3.0, 1.0, 30.0, true, false, true);
}

std::string StingShoot::toString(double usePercent) { // 蜂針射擊
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (中毒: " << poison << ")";

    return ss.str();
}

void StinkBubble::clear() { // 臭臭氣
    hitPercent = 0.0;
    atk = 0.0;
    powerDecrease = 0.0;
    speedDecrease = 0.0;
}

void StinkBubble::calculate() { // 臭臭氣
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = 0.0;
    powerDecrease = getSpecialPower(code + "/power", 0.5, 0.05, 0.01, 0.99, true, true, true);
    speedDecrease = getSpecialPower(code + "/speed", 0.3, 0.03, 0.01, 0.99, true, true, true);
}

std::string StinkBubble::toString(double usePercent) { // 臭臭氣
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (力量: -" << powerDecrease * 100 << "%   速度: -" << speedDecrease * 100 << "%)";

    return ss.str();
}

void StrawberryAttack::clear() { // 莓雨季節
    hitPercent = 0.0;
    atk = 0.0;
}

void StrawberryAttack::calculate() { // 莓雨季節
    hitPercent = getSkillHitPercent(code, 0.72);
    atk = getPower(code, strength, 0.1, 0.01, 5.5, 0.5, 12.0);
}

std::string StrawberryAttack::toString(double usePercent) { // 莓雨季節
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void SunlightAttack::clear() { // 太陽炫光
    hitPercent = 0.0;
    atk = 0.0;
    speedDecrease = 0.0;
    hitDecrease = 0.0;
}

void SunlightAttack::calculate() { // 太陽炫光
    hitPercent = getSkillHitPercent(code, 0.80);
    atk = 0.0;
    speedDecrease = getSpecialPower(code, 0.2, 0.015, 0.01, 0.99, true, true, true);
    hitDecrease = speedDecrease;
}

std::string SunlightAttack::toString(double usePercent) { // 太陽炫光
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk << " (速度: -" << speedDecrease * 100 << "%   命中: -" << hitDecrease * 100 << "%)";

    return ss.str();
}

void TailAttack::clear() { // 尾鞭
    hitPercent = 0.0;
    atk = 0.0;
}

void TailAttack::calculate() { // 尾鞭
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string TailAttack::toString(double usePercent) { // 尾鞭
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void TannicAttack::clear() { // 單寧酸
    hitPercent = 0.0;
    atk = 0.0;
}

void TannicAttack::calculate() { // 單寧酸
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 0.5, 0.05, 15.0, 2.0, 1.0);
}

std::string TannicAttack::toString(double usePercent) { // 單寧酸
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void ThornRattan::clear() { // 地蕀爪
    hitPercent = 0.0;
    atk = 0.0;
}

void ThornRattan::calculate() { // 地蕀爪
    hitPercent = getSkillHitPercent(code, 0.84);
    atk = getPower(code, strength, 0.5, 0.03, 9.0, 3.0, 3.0);
}

std::string ThornRattan::toString(double usePercent) { // 地蕀爪
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void TornadoAttack::clear() { // 龍捲風暴
    hitPercent = 0.0;
    atk = 0.0;
}

void TornadoAttack::calculate() { // 龍捲風暴
    hitPercent = getSkillHitPercent(code, 0.80);
    atk = getPower(code, strength, 0.6, 0.06, 50.0, 5.0, 1.0);
}

std::string TornadoAttack::toString(double usePercent) { // 龍捲風暴
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void TriplePeck::clear() { // 啄擊(藍鵲)
    hitPercent = 0.0;
    atk = 0.0;
}

void TriplePeck::calculate() { // 啄擊(藍鵲)
    hitPercent = getSkillHitPercent(code, 0.89);
    atk = getPower(code, strength, 1.0, 0.1, 15.0, 2.0, 1.0);
}

std::string TriplePeck::toString(double usePercent) { // 啄擊(藍鵲)
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void TripleSting::clear() { // 蜂蜇
    hitPercent = 0.0;
    atk = 0.0;
}

void TripleSting::calculate() { // 蜂蜇
    hitPercent = getSkillHitPercent(code, 0.88);
    atk = getPower(code, strength, 1.2, 0.1, 10.0, 2.0, 1.0);
}

std::string TripleSting::toString(double usePercent) { // 蜂蜇
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void VolcanicEruption::clear() { // 火山爆花
    hitPercent = 0.0;
    atk = 0.0;
}

void VolcanicEruption::calculate() { // 火山爆花
    hitPercent = getSkillHitPercent(code, 0.82);
    atk = getPower(code, strength, 0.8, 0.08, 50.0, 6.0, 1.0);
}

std::string VolcanicEruption::toString(double usePercent) { // 火山爆花
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void WatermelonAttack::clear() { // 黑子雨
    hitPercent = 0.0;
    atk = 0.0;
}

void WatermelonAttack::calculate() { // 黑子雨
    hitPercent = getSkillHitPercent(code, 0.76);
    atk = getPower(code, strength, 0.1, 0.01, 7.0, 0.5, 9.0);
}

std::string WatermelonAttack::toString(double usePercent) { // 黑子雨
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void WingDeterrence::clear() { // 展翼嚇阻
    hitPercent = 0.0;
    atk = 0.0;
}

void WingDeterrence::calculate() { // 展翼嚇阻
    hitPercent = getSkillHitPercent(code, 0.50);
    atk = 0.0;
}

std::string WingDeterrence::toString(double usePercent) { // 展翼嚇阻
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}

void WoolBallAttack::clear() { // 鉛毛彈
    hitPercent = 0.0;
    atk = 0.0;
}

void WoolBallAttack::calculate() { // 鉛毛彈
    hitPercent = getSkillHitPercent(code, 0.78);
    atk = getPower(code, strength, 0.5, 0.05, 45.0, 5.0, 1.0);
}

std::string WoolBallAttack::toString(double usePercent) { // 鉛毛彈
    std::stringstream ss;

    ss << std::left << std::setw(12) << getSkillNameByType(skillType) + ": " << "(" << getElementNameByType(elementType) << ")  "
       << usePercent * 100 << "%   " << hitPercent * 100 << "%   " << atk;

    return ss.str();
}
