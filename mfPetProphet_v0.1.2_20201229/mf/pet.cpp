/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#include <algorithm> // std::fill_n, std::min, std::max
#include <cmath>     // round
#include <iomanip>   // std::setw
#include <ios>       // std::left, std::noshowpos, std::showpos
#include <numeric>   // std::accumulate
#include <sstream>   // std::stringstream
#include <string>    // std::string
#include "type.h"    // FruitType

#include "pet.h"

double BasePet::createBaseAttributeValue(int randomSeed, double mean, double deviation, double minimum, double maximum) {
    double value;

    md5RandGen.setSeed(fruitCode + gene, randomSeed);
    distribution.setValue(mean, deviation);
    value = round(distribution.random(md5RandGen));
    value = std::max(minimum, std::min(maximum, value));

    return value;
}

double BasePet::createAttributeValue(int randomSeed, double mean, double deviation) {
    double value;

    md5RandGen.setSeed(fruitCode + gene, randomSeed);
    distribution.setValue(mean, deviation);
    value = distribution.random(md5RandGen);

    if(value > 1) {
        return round(std::min(mean + deviation * 5, value));
    }

    return 0;
}

double BasePet::createAttributeValueByClass(int randomSeed, double base, double mean[5]) {
    double temp1 = base - std::accumulate(mean, mean + 5, 0.0);
    double temp2 = base / 10.0;
    double temp3 = temp2 + std::max(0.0, std::min(temp2, temp1)) / 2.0;
    double temp4 = -temp3;

    return createAttributeValue(randomSeed, temp4, temp3);
}

void BasePet::calcAddElement(bool petElement[8]) {
    int temp1[8] = {0, 0, 0, 0, 0, 0, 0};
    int maxIndex = -1, maxElementIndex = 8 - 1;

    for(int a = 0; a <= maxElementIndex; a++) {
        if(!petElement[a] && a != 0) {
            temp1[++maxIndex] = a;
        }
    }

    for(int a = maxIndex; a > 0; a--) { // sort by ElementCode, store the index in temp1[]
        for(int b = 0; b < a; b++) {
            if(getElementCodeByType((ElementType)temp1[b]).compare(getElementCodeByType((ElementType)temp1[b + 1])) > 0) {
                temp1[b] ^= temp1[b + 1];
                temp1[b + 1] ^= temp1[b];
                temp1[b] ^= temp1[b + 1];
            }
        }
    }

    md5RandGen.setSeed(fruitCode + gene, MONSTER_FRUIT_ELEMENT);
    extraPetElementIndex = md5RandGen.getArrayRandomElement(temp1, maxIndex + 1);
}

int BasePet::getHpUpRate() {
    double rate;

    md5RandGen.setSeed(fruitCode, MONSTER_FRUIT_HP);
    distribution.setValue(15.0, 3.0);
    rate = std::max(15.0 - 3.0 * 3.0, std::min(15.0 + 3.0 * 5.0, distribution.random(md5RandGen)));

    return (int)(rate);
}

double BasePet::getHpPerTurnInBattle() {
    return std::max(1.0, round(hpUpRate * 0.66));
}

int BasePet::getKimochiUpRate() {
    double rate;

    md5RandGen.setSeed(fruitCode, MONSTER_FRUIT_KIMOCHI);
    distribution.setValue(5.0, 2.0);
    rate = std::max(3.0, std::min(7.0, distribution.random(md5RandGen)));

    return (int)(rate);
}

int BasePet::getLoyalUpRate() {
    double rate;

    md5RandGen.setSeed(fruitCode, MONSTER_FRUIT_LOYAL);
    distribution.setValue(4.5, 1.5);
    rate = std::max(2.0, std::min(10.0, distribution.random(md5RandGen)));

    return (int)(rate);
}

double BasePet::getPurifyTimeReduceScale() {
    double rate;

    md5RandGen.setSeed(fruitCode + "base", MONSTER_ITEM_DURATION_FIELD);
    distribution.setValue(0.2, 0.02);
    rate = std::max(0.2 - 0.02 * 3.0, std::min(0.2 + 0.02 * 3.0, distribution.random(md5RandGen)));

    return round(rate * 100.0) / 100.0;
}

int BasePet::getHelpPurifyHoursReduce() {
    double rate;

    md5RandGen.setSeed(fruitCode + "help", MONSTER_ITEM_DURATION_FIELD);
    distribution.setValue(1.35, 1.0);
    rate = std::max(1.0, std::min(3.0, distribution.random(md5RandGen)));

    return (int)(rate);
}

double BasePet::getSatietyUpRate() {
    double rate;

    md5RandGen.setSeed(fruitCode, MONSTER_FRUIT_SATIETY);
    distribution.setValue(1.2, 0.3);
    rate = std::max(0.01, std::min(3.0, distribution.random(md5RandGen)));

    return round(rate * 10.0) / 10.0;
}

double BasePet::calcValue(int randomSeed, double mean[5], double deviation[5]) {
    double value = 0;

    md5RandGen.setSeed(gene, randomSeed);

    for(int a = 0; a <= _level && a < 5; a++) {
        distribution.setValue(mean[a], deviation[a]);
        value += std::min((mean[a] * 10.0), std::max((mean[a] / 10.0), distribution.random(md5RandGen)));
    }

    return round(value);
}

void BasePet::calcElement(bool petElement[8]) {
    bool output[8] = {false, false, false, false, false, false, false, false};
    int maxElementIndex = 8 - 1;

    for(int a = 0; a <= maxElementIndex; a++) {
        output[a] = petElement[a];
    }

    if(fruitType == FruitType::element) { // 元素果實產生的 "特徵"
        calcAddElement(petElement);
        output[extraPetElementIndex] = true;
    }

    for(int a = 0; a <= maxElementIndex; a++) {
        element[a] = output[a];
    }
}

void BasePet::calcResistanceMap(double resistanceMean[8][5], double resistanceDeviation[8][5]) {
    int output[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int temp1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int temp2;
    int maxResistanceIndex = 8 - 1;

    for(int a = maxResistanceIndex; a > 0; a--) { // sort resistanceCode, store the index in temp1[]
        for(int b = 0; b < a; b++) {
            if(getElementCodeByType((ElementType)temp1[b]).compare(getElementCodeByType((ElementType)temp1[b + 1])) > 0) {
                temp1[b] ^= temp1[b + 1];
                temp1[b + 1] ^= temp1[b];
                temp1[b] ^= temp1[b + 1];
            }
        }
    }

    md5RandGen.setSeed(gene, RESISTANCE);

    for(int a = 0; a <= _level; a++) { // calculate resistance map
        for(int b = 0; b <= maxResistanceIndex; b++) {
            if(resistanceMean[temp1[b]][a] != 0.0 && resistanceDeviation[temp1[b]][a] != 0.0) {
                distribution.setValue(resistanceMean[temp1[b]][a], resistanceDeviation[temp1[b]][a]);
                temp2 = (int) distribution.random(md5RandGen);

                if(resistanceMean[temp1[b]][a] > 0.0) {
                    temp2 = std::max(0, temp2);
                } else {
                    temp2 = std::min(0, temp2);
                }

                output[temp1[b]] += temp2;
            }
        }
    }

    for(int a = 0; a <= maxResistanceIndex; a++) { // limit resistance map value between +100 to -99
        resistance[temp1[a]] = std::min(100, std::max(-99, output[temp1[a]]));
    }

    if(resistance[extraPetElementIndex] < 0) {
        resistance[extraPetElementIndex] = 0; // 元素果實產生的特徵不會有負抗性
    }

    if(fruitType != FruitType::empty) {
        double fruitResistanceMean, fruitResistanceDeviation;
        int maxIndex = -1, temp3;

        switch(fruitType) {
        case FruitType::battle:
            fruitResistanceMean = -55.0;
            fruitResistanceDeviation = 5.0;
            break;
        case FruitType::boss:
            fruitResistanceMean = -55.0;
            fruitResistanceDeviation = 5.0;
            break;
        case FruitType::element:
            fruitResistanceMean = -42.0;
            fruitResistanceDeviation = 3.0;
            break;
        case FruitType::hp:
            fruitResistanceMean = -55.0;
            fruitResistanceDeviation = 5.0;
            break;
        case FruitType::purify:
            fruitResistanceMean = -33.0;
            fruitResistanceDeviation = 3.0;
            break;
        case FruitType::weight:
            fruitResistanceMean = -36.0;
            fruitResistanceDeviation = 3.0;
            break;
        default: // kimochi || loyal || satiety
            fruitResistanceMean = -20.0;
            fruitResistanceDeviation = 2.5;
            break;
        }

        for(int a = 0; a <= maxResistanceIndex; a++) {
            if(resistanceMean[a][0] >= 0.0 && a != extraPetElementIndex && a != 0) {
                temp1[++maxIndex] = a;
            }
        }

        for(int a = maxIndex; a > 0; a--) { // sort resistanceCode, store the index in temp1[]
            for(int b = 0; b < a; b++) {
                if(getElementCodeByType((ElementType)temp1[b]).compare(getElementCodeByType((ElementType)temp1[b + 1])) > 0) {
                    temp1[b] ^= temp1[b + 1];
                    temp1[b + 1] ^= temp1[b];
                    temp1[b] ^= temp1[b + 1];
                }
            }
        }

        if(maxIndex >= 0) {
            md5RandGen.setSeed(fruitCode + gene, RESISTANCE);
            distribution.setValue(fruitResistanceMean, fruitResistanceDeviation);
            temp2 = md5RandGen.getArrayRandomElement(temp1, maxIndex + 1);
            temp3 = distribution.random(md5RandGen);
            temp3 = std::min((int)(fruitResistanceMean + fruitResistanceDeviation * 4), temp3);
            temp3 = std::min(100, std::max(-99, temp3)); // limit resistance value between +100 to -99
            resistance[temp2] = std::min(100, std::max(-99, resistance[temp2] + temp3)); // limit resistance value between +100 to -99
        }
    }
}

double BasePet::calcMaxHp(double maxHpMean[5], double maxHpDeviation[5]) {
    double maxHp = calcValue(MAX_HP, maxHpMean, maxHpDeviation);

    if(fruitType == FruitType::battle || fruitType == FruitType::boss) {
        maxHp += createAttributeValue(MAX_HP, 36.0, 6.0);
    }

    return maxHp;
}

double BasePet::calcStrength(double strengthMean[5], double strengthDeviation[5]) {
    double strength = calcValue(STRENGTH, strengthMean, strengthDeviation);

    if(fruitType == FruitType::battle || fruitType == FruitType::boss) {
        strength += createAttributeValueByClass(STRENGTH, 45.0, strengthMean);
    }

    return strength;
}

double BasePet::calcSpeed(double speedMean[5], double speedDeviation[5]) {
    double speed = calcValue(SPEED, speedMean, speedDeviation);

    if(fruitType == FruitType::battle || fruitType == FruitType::boss) {
        speed += createAttributeValue(SPEED, -3.0, 3.0);
    } else if(fruitType == FruitType::weight) {
        speed += createBaseAttributeValue(SPEED, 3.0, 1.5, 1,9);
    }

    return speed;
}

double BasePet::calcDefense(double defenseMean[5], double defenseDeviation[5]) {
    double defense = calcValue(DEFENSE, defenseMean, defenseDeviation);

    if(fruitType == FruitType::battle || fruitType == FruitType::boss) {
        defense += createAttributeValue(DEFENSE, -6.0, 8.0);
    } else if(fruitType == FruitType::element) {
        defense += createBaseAttributeValue(DEFENSE, 3.0, 1.4, 0.0, 15.0);
    } else if(fruitType == FruitType::weight) {
        defense += createBaseAttributeValue(DEFENSE, 2.0, 1.25, 0.0, 9.0);
    }

    return defense;
}

double BasePet::calcSpeedEffectAddon(double speed) {
    double speedEffectAddon, temp = speed - 33.5;

    if(temp > 0.0) {
        speedEffectAddon = pow(temp / 700.0, 0.9);
    } else {
        speedEffectAddon = temp / 300.0;
    }

    speedEffectAddon = round(speedEffectAddon * 1000.0) / 1000.0;
    speedEffectAddon = std::max(-0.035, std::min(0.06, speedEffectAddon));

    return speedEffectAddon;
}

void BasePet::getPercent(std::string extraCode[4], double skillWeight[4][5]) {
    double output[4] = {0.0, 0.0, 0.0, 0.0};
    int temp[4] = {0, 1, 2, 3};
    int maxSkillIndex = 4 - 1;
    double totalWeight = 0.0;

    for(int a = maxSkillIndex; a > 0; a--) { // sort extraCode[], store the index in temp[]
        for(int b = 0; b < a; b++) {
            if(extraCode[temp[b]].compare(extraCode[temp[b + 1]]) > 0) {
                temp[b] ^= temp[b + 1];
                temp[b + 1] ^= temp[b];
                temp[b] ^= temp[b + 1];
            }
        }
    }

    md5RandGen.setSeed(gene, SKILL_WEIGHT);

    for(int a = 0; a <= _level; a++) { // calculate NormalDistribution by weight
        for(int b = 0; b <= maxSkillIndex; b++) {
            if(skillWeight[temp[b]][a] != 0.0) {
                distribution.setValue(skillWeight[temp[b]][a] * 10, skillWeight[temp[b]][a]);
                output[temp[b]] += distribution.random(md5RandGen);
            }
        }
    }

    for(int a = 0; a <= maxSkillIndex; a++) { // calculate totalWeight
        totalWeight += output[a];
    }

    if(totalWeight != 0.0) {
        for(int a = 0; a <= maxSkillIndex; a++) { // calculate percent[]
            percent[a] = round(output[a] / totalWeight * 100.0) / 100.0;
        }
    } else {
        std::fill_n(percent, 4, 0.0);
    }
}

void BasePet::calcElementAndResistance(bool petElement[8], double resistanceMean[8][5], double resistanceDeviation[8][5]) {
    calcElement(petElement); // 元素果實產生的 "特徵" 會影響 "抗性"，因此在這優先計算
    calcResistanceMap(resistanceMean, resistanceDeviation);
}

void BasePet::calculate() {
    if(fruitType == FruitType::hp) {
        hpUpRate = getHpUpRate();
        hpPerTurnInBattle = getHpPerTurnInBattle();
    } else {
        hpUpRate = 0.0;
        hpPerTurnInBattle = 0.0;
    }

    if(fruitType == FruitType::kimochi) {
        kimochiUpRate = getKimochiUpRate();
    } else {
        kimochiUpRate = 0.0;
    }

    if(fruitType == FruitType::loyal) {
        loyalUpRate = getLoyalUpRate();
    } else {
        loyalUpRate = 0.0;
    }

    if(fruitType == FruitType::purify) {
        purifyTimeReduceScale = getPurifyTimeReduceScale();
        helpPurifyHoursReduce = getHelpPurifyHoursReduce();
    } else {
        purifyTimeReduceScale = 0.0;
        helpPurifyHoursReduce = 0.0;
    }

    if(fruitType == FruitType::satiety) {
        satietyUpRate = getSatietyUpRate();
    } else {
        satietyUpRate = 0.0;
    }

    if(fruitType == FruitType::weight) {
        isWeightControlled = true;
    } else {
        isWeightControlled = false;
    }
}

std::string BasePet::toString(std::string petClass, std::string skillInfo, bool petElement[7]) {
    std::stringstream ss;
    bool status;
    int maxElementIndex = 8 - 1;
    int maxResistanceIndex = 8 - 1;

    ss << std::left << std::setw(12) << "學名: " << petClass << "\n"
       << std::left << std::setw(12) << "基因: " << gene;

    if(fruitType != FruitType::empty) {
        ss << "\n" << std::left << std::setw(12) << "果實種類: " << getFruitNameByType(fruitType)
           << "\n" << std::left << std::setw(12) << "果實代碼: " << fruitCode;
    }

    ss << "\n" << std::left << std::setw(12) << "等級: " << getLevel()
       << "\n" << std::left << std::setw(12) << "生命: " << maxHp
       << "\n" << std::left << std::setw(12) << "力量: " << strength << "    防禦: " << defense << "    速度: " << speed << " (基礎: " << speedEffectAddon * 100 << "%)";

    if(skillInfo != "") {
        ss << "\n" << skillInfo;
    }

    for(int a = 0, status = true; a <= maxElementIndex; a++) {
        if(element[a]) {
            if(status) {
                ss << "\n" << std::left << std::setw(12) << "特徵: ";
                status = false;
            } else {
                ss << "    ";
            }

            ss << getElementNameByType((ElementType)a);
        }
    }

    ss << std::showpos; // 非負數顯示 "+" (正號)

    for(int a = 0, status = true; a <= maxResistanceIndex; a++) {
        if(resistance[a] != 0) {
            if(status) {
                ss << "\n" << std::left << std::setw(12) << "抗性: ";
                status = false;
            } else {
                ss << "   ";
            }

            if(resistance[a] < 100) {
                ss << getElementNameByType((ElementType)a) << " " << resistance[a];
            } else {
                ss << getElementNameByType((ElementType)a) << " (吸收)";
            }
        }
    }

    ss << std::noshowpos; // 非負數不顯示正號
    status = true;

    if(hpUpRate != 0.0 || hpPerTurnInBattle != 0.0) {
        if(status) {
            ss << "\n" << std::left << std::setw(12) << "備註: ";
        } else {
            ss << "\n" << "            ";
        }

        ss << "HP 每小時 +" << hpUpRate;
        ss << "\n" << "            " << "戰鬥中 HP 每回合 +" << hpPerTurnInBattle;
    }

    if(kimochiUpRate != 0.0) {
        if(status) {
            ss << "\n" << std::left << std::setw(12) << "備註: ";
        } else {
            ss << "\n" << "            ";
        }

        ss << "心情 每小時 +" << kimochiUpRate;
    }

    if(loyalUpRate != 0.0) {
        if(status) {
            ss << "\n" << std::left << std::setw(12) << "備註: ";
        } else {
            ss << "\n" << "            ";
        }

        ss << "好感度 每小時 +" << loyalUpRate;
    }

    if(purifyTimeReduceScale != 0.0 || helpPurifyHoursReduce != 0.0) {
        if(status) {
            ss << "\n" << std::left << std::setw(12) << "備註: ";
        } else {
            ss << "\n" << "            ";
        }

        ss << "征服原野時間縮減 " << round(purifyTimeReduceScale * 100.0) << "%";
        ss << "\n" << "            " << "主人幫忙征服的縮減時間 " << helpPurifyHoursReduce << "小時";
    }

    if(satietyUpRate != 0.0) {
        if(status) {
            ss << "\n" << std::left << std::setw(12) << "備註: ";
        } else {
            ss << "\n" << "            ";
        }

        ss << "飽食度 每小時 +" << satietyUpRate;
    }

    if(isWeightControlled) {
        if(status) {
            ss << "\n" << std::left << std::setw(12) << "備註: ";
        } else {
            ss << "\n" << "            ";
        }

        ss << "寵物永遠不會太瘦或過胖";
    }

    ss << "\n" << std::left << std::setw(12) << "分數: " << score;

    return ss.str();
}

void BasePet::setRandomPetGene(std::string randomString) {
    md5.calculate((const char*)randomString.c_str());
    gene = "@monster_" + md5.getHashString();
}

void BasePet::setLevel(int petLevel) {
    int temp = petLevel - 1;

    if(temp < 0)
        temp = 0; // Level 1 = (int)0
    else if(temp > 4)
        temp = 4; // Level 5 = (int)4

    _level = temp;
}

int BasePet::getLevel() {
    return _level + 1;
}

void BasePet::setAllValue(std::string petGene, int petLevel, FruitType petFruitType, std::string petFruitCode) {
    gene = petGene;
    setLevel(petLevel);
    fruitType = petFruitType;
    fruitCode = petFruitCode;
}

void BaldEagle::calcScore() { // 白頭蒼鷹
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BaldEagle::calculate() { // 白頭蒼鷹
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        eagleShoutSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        eagleShoutSkill.calculate();
    } else {
        eagleShoutSkill.clear();
    }

    if(percent[2] > 0.0) {
        baldDartAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        baldDartAttackSkill.calculate();
    } else {
        baldDartAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BaldEagle::toString() { // 白頭蒼鷹
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << eagleShoutSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << baldDartAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void BlackBear::calcScore() { // 白紋黑熊
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BlackBear::calculate() { // 白紋黑熊
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        doubleClawHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleClawHitSkill.calculate();
    } else {
        doubleClawHitSkill.clear();
    }

    if(percent[1] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        berserkSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        berserkSkill.calculate();
    } else {
        berserkSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BlackBear::toString() { // 白紋黑熊
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << doubleClawHitSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bodyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << berserkSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void BlackCat::calcScore() { // 哈斯貓
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BlackCat::calculate() { // 哈斯貓
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        doubleCatClawSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleCatClawSkill.calculate();
    } else {
        doubleCatClawSkill.clear();
    }

    if(percent[1] > 0.0) {
        jumpingScratchSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpingScratchSkill.calculate();
    } else {
        jumpingScratchSkill.clear();
    }

    if(percent[2] > 0.0) {
        loveEyesSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        loveEyesSkill.calculate();
    } else {
        loveEyesSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BlackCat::toString() { // 哈斯貓
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << doubleCatClawSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpingScratchSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << loveEyesSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void BlackRabbit::calcScore() { // 黑毛兔
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BlackRabbit::calculate() { // 黑毛兔
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        kickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        kickSkill.calculate();
    } else {
        kickSkill.clear();
    }

    if(percent[2] > 0.0) {
        groundStrikeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        groundStrikeSkill.calculate();
    } else {
        groundStrikeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BlackRabbit::toString() { // 黑毛兔
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << kickSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << groundStrikeSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void BlackWidow::calcScore() { // 黑寡婦
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BlackWidow::calculate() { // 黑寡婦
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);
    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BlackWidow::toString() { // 黑寡婦
    return BasePet::toString(getPetClassByType(petType), "", petElement);
}

void BlueBrowCaffer::calcScore() { // 藍眉野牛
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BlueBrowCaffer::calculate() { // 藍眉野牛
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        jumpKickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpKickSkill.calculate();
    } else {
        jumpKickSkill.clear();
    }

    if(percent[1] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        shockwaveSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        shockwaveSkill.calculate();
    } else {
        shockwaveSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BlueBrowCaffer::toString() { // 藍眉野牛
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << jumpKickSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bodyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << shockwaveSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void BlueMagpie::calcScore() { // 藍鵲
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void BlueMagpie::calculate() { // 藍鵲
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        triplePeckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        triplePeckSkill.calculate();
    } else {
        triplePeckSkill.clear();
    }

    if(percent[2] > 0.0) {
        wingDeterrenceSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        wingDeterrenceSkill.calculate();
    } else {
        wingDeterrenceSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string BlueMagpie::toString() { // 藍鵲
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << triplePeckSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << wingDeterrenceSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void CactusSpirit::calcScore() { // 鴨嘴仙人掌
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void CactusSpirit::calculate() { // 鴨嘴仙人掌
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        doubleThornHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleThornHitSkill.calculate();
    } else {
        doubleThornHitSkill.clear();
    }

    if(percent[1] > 0.0) {
        cactusBubbleAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        cactusBubbleAttackSkill.calculate();
    } else {
        cactusBubbleAttackSkill.clear();
    }

    if(percent[2] > 0.0) {
        cactusThornRainSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        cactusThornRainSkill.calculate();
    } else {
        cactusThornRainSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string CactusSpirit::toString() { // 鴨嘴仙人掌
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << doubleThornHitSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << cactusBubbleAttackSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << cactusThornRainSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void CatShark::calcScore() { // 貓鯊
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void CatShark::calculate() { // 貓鯊
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        kickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        kickSkill.calculate();
    } else {
        kickSkill.clear();
    }

    if(percent[1] > 0.0) {
        bubbleAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bubbleAttackSkill.calculate();
    } else {
        bubbleAttackSkill.clear();
    }

    if(percent[2] > 0.0) {
        jumpingScratchSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpingScratchSkill.calculate();
    } else {
        jumpingScratchSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string CatShark::toString() { // 貓鯊
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << kickSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bubbleAttackSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpingScratchSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void ClownButterfly::calcScore() { // 小丑蝶
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void ClownButterfly::calculate() { // 小丑蝶
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        regeneratePollenSpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        regeneratePollenSpewSkill.calculate();
    } else {
        regeneratePollenSpewSkill.clear();
    }

    if(percent[2] > 0.0) {
        flyKickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyKickSkill.calculate();
    } else {
        flyKickSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string ClownButterfly::toString() { // 小丑蝶
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << regeneratePollenSpewSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyKickSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void Cobra::calcScore() { // 眼鏡蛇
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void Cobra::calculate() { // 眼鏡蛇
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        poisonBiteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        poisonBiteSkill.calculate();
    } else {
        poisonBiteSkill.clear();
    }

    if(percent[2] > 0.0) {
        eyeStrikeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        eyeStrikeSkill.calculate();
    } else {
        eyeStrikeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string Cobra::toString() { // 眼鏡蛇
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << poisonBiteSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << eyeStrikeSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void CorollaBee::calcScore() { // 花冠蜂
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void CorollaBee::calculate() { // 花冠蜂
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        tripleStingSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        tripleStingSkill.calculate();
    } else {
        tripleStingSkill.clear();
    }

    if(percent[1] > 0.0) {
        feedHoneySpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        feedHoneySpewSkill.calculate();
    } else {
        feedHoneySpewSkill.clear();
    }

    if(percent[2] > 0.0) {
        stingShootSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        stingShootSkill.calculate();
    } else {
        stingShootSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string CorollaBee::toString() { // 花冠蜂
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << tripleStingSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << feedHoneySpewSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << stingShootSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void CottonCandyBee::calcScore() { // 花糖蜂
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void CottonCandyBee::calculate() { // 花糖蜂
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        tripleStingSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        tripleStingSkill.calculate();
    } else {
        tripleStingSkill.clear();
    }

    if(percent[1] > 0.0) {
        slackPollenSpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        slackPollenSpewSkill.calculate();
    } else {
        slackPollenSpewSkill.clear();
    }

    if(percent[2] > 0.0) {
        stingShootSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        stingShootSkill.calculate();
    } else {
        stingShootSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string CottonCandyBee::toString() { // 花糖蜂
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << tripleStingSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << slackPollenSpewSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << stingShootSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void DarkBear::calcScore() { // 月夜熊
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void DarkBear::calculate() { // 月夜熊
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        doubleClawHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleClawHitSkill.calculate();
    } else {
        doubleClawHitSkill.clear();
    }

    if(percent[1] > 0.0) {
        berserkSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        berserkSkill.calculate();
    } else {
        berserkSkill.clear();
    }

    if(percent[2] > 0.0) {
        handBeamSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        handBeamSkill.calculate();
    } else {
        handBeamSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string DarkBear::toString() { // 月夜熊
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << doubleClawHitSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << berserkSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << handBeamSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void DragonFruitChicken::calcScore() { // 火龍果雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void DragonFruitChicken::calculate() { // 火龍果雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        dragonSeedAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        dragonSeedAttackSkill.calculate();
    } else {
        dragonSeedAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string DragonFruitChicken::toString() { // 火龍果雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << dragonSeedAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void EggplantChicken::calcScore() { // 小茄雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void EggplantChicken::calculate() { // 小茄雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        tannicAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        tannicAttackSkill.calculate();
    } else {
        tannicAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string EggplantChicken::toString() { // 小茄雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << tannicAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void FireDragon::calcScore() { // 赤焰火龍
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void FireDragon::calculate() { // 赤焰火龍
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        fireTailAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        fireTailAttackSkill.calculate();
    } else {
        fireTailAttackSkill.clear();
    }

    if(percent[1] > 0.0) {
        giantSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        giantSkill.calculate();
    } else {
        giantSkill.clear();
    }

    if(percent[2] > 0.0) {
        hellFireSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        hellFireSkill.calculate();
    } else {
        hellFireSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string FireDragon::toString() { // 赤焰火龍
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << fireTailAttackSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << giantSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << hellFireSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void Firefly::calcScore() { // 螢火蟲
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void Firefly::calculate() { // 螢火蟲
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        attractingLightSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        attractingLightSkill.calculate();
    } else {
        attractingLightSkill.clear();
    }

    if(percent[2] > 0.0) {
        boxingQuartetSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        boxingQuartetSkill.calculate();
    } else {
        boxingQuartetSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string Firefly::toString() { // 螢火蟲
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << attractingLightSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << boxingQuartetSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void FlowerMantis::calcScore() { // 魔眼螳螂
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void FlowerMantis::calculate() { // 魔眼螳螂
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        handWaveSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        handWaveSkill.calculate();
    } else {
        handWaveSkill.clear();
    }

    if(percent[1] > 0.0) {
        jumpingKnifeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpingKnifeSkill.calculate();
    } else {
        jumpingKnifeSkill.clear();
    }

    if(percent[2] > 0.0) {
        magicEyesSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        magicEyesSkill.calculate();
    } else {
        magicEyesSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string FlowerMantis::toString() { // 魔眼螳螂
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << handWaveSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpingKnifeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << magicEyesSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void ForestFox::calcScore() { // 野森狐
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void ForestFox::calculate() { // 野森狐
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        clawHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        clawHitSkill.calculate();
    } else {
        clawHitSkill.clear();
    }

    if(percent[2] > 0.0) {
        foxCharmSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        foxCharmSkill.calculate();
    } else {
        foxCharmSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string ForestFox::toString() { // 野森狐
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << clawHitSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << foxCharmSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void ForestPolatouche::calcScore() { // 山林飛鼠
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void ForestPolatouche::calculate() { // 山林飛鼠
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        acornAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        acornAttackSkill.calculate();
    } else {
        acornAttackSkill.clear();
    }

    if(percent[1] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[2] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string ForestPolatouche::toString() { // 山林飛鼠
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << acornAttackSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << biteSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void GoldenBallCat::calcScore() { // 金球貓
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void GoldenBallCat::calculate() { // 金球貓
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        tailAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        tailAttackSkill.calculate();
    } else {
        tailAttackSkill.clear();
    }

    if(percent[1] > 0.0) {
        eyeShineSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        eyeShineSkill.calculate();
    } else {
        eyeShineSkill.clear();
    }

    if(percent[2] > 0.0) {
        circleRollScrachSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        circleRollScrachSkill.calculate();
    } else {
        circleRollScrachSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string GoldenBallCat::toString() { // 金球貓
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << tailAttackSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << eyeShineSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << circleRollScrachSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void GrassChicken::calcScore() { // 小草雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void GrassChicken::calculate() { // 小草雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string GrassChicken::toString() { // 小草雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void HamimelonChicken::calcScore() { // 哈蜜瓜雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void HamimelonChicken::calculate() { // 哈蜜瓜雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string HamimelonChicken::toString() { // 哈蜜瓜雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << peckSkill.toString(percent[1]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void HornRabbit::calcScore() { // 火角兔
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void HornRabbit::calculate() { // 火角兔
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        fireSpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        fireSpewSkill.calculate();
    } else {
        fireSpewSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string HornRabbit::toString() { // 火角兔
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << fireSpewSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void LeafRaccoon::calcScore() { // 葉子浣熊
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void LeafRaccoon::calculate() { // 葉子浣熊
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        knittingBallAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        knittingBallAttackSkill.calculate();
    } else {
        knittingBallAttackSkill.clear();
    }

    if(percent[1] > 0.0) {
        clawHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        clawHitSkill.calculate();
    } else {
        clawHitSkill.clear();
    }

    if(percent[2] > 0.0) {
        rollingChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        rollingChargeSkill.calculate();
    } else {
        rollingChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string LeafRaccoon::toString() { // 葉子浣熊
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << knittingBallAttackSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << clawHitSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << rollingChargeSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void MagmaFlower::calcScore() { // 溫泉花
    score = percent[0] * std::max(0.01, std::min(0.99, eyesRaySkill.hitPercent + speedEffectAddon /* 基礎命中率 */)) * (eyesRaySkill.atk + eyesRaySkill.burn * (2 * 0.8) /*攻擊次數 x 有效機率*/) +
            percent[1] * std::max(0.01, std::min(0.99, springBubbleSkill.hitPercent + speedEffectAddon /* 基礎命中率 */)) * (springBubbleSkill.regen * 3) +
            percent[2] * std::max(0.01, std::min(0.99, volcanicEruptionSkill.hitPercent + speedEffectAddon /* 基礎命中率 */)) * volcanicEruptionSkill.atk +
            defense * 0.45 /* 0.75(遊戲預設的防禦倍率) x 0.6 = 0.45 */ +
            maxHp / 12.0 /* 1傷害 x 12回合 = 需要12生命 */ +
            60 /*敵人傷害期望值*/ * speedEffectAddon /* 基礎迴避率 */;

    score = round(score * 10.0) / 10.0;
}

void MagmaFlower::calculate() { // 溫泉花
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        eyesRaySkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        eyesRaySkill.calculate();
    } else {
        eyesRaySkill.clear();
    }

    if(percent[1] > 0.0) {
        springBubbleSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        springBubbleSkill.calculate();
    } else {
        springBubbleSkill.clear();
    }

    if(percent[2] > 0.0) {
        volcanicEruptionSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        volcanicEruptionSkill.calculate();
    } else {
        volcanicEruptionSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string MagmaFlower::toString() { // 溫泉花
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << eyesRaySkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << springBubbleSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << volcanicEruptionSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void MushroomChicken::calcScore() { // 香菇雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void MushroomChicken::calculate() { // 香菇雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[2] > 0.0) {
        sporeSpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        sporeSpewSkill.calculate();
    } else {
        sporeSpewSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string MushroomChicken::toString() { // 香菇雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << peckSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << sporeSpewSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void OrangeDeer::calcScore() { // 橘子麋鹿
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void OrangeDeer::calculate() { // 橘子麋鹿
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        jumpAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpAttackSkill.calculate();
    } else {
        jumpAttackSkill.clear();
    }

    if(percent[2] > 0.0) {
        leavesAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        leavesAttackSkill.calculate();
    } else {
        leavesAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string OrangeDeer::toString() { // 橘子麋鹿
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << bodyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpAttackSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << leavesAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void PlainTiger::calcScore() { // 草原虎
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void PlainTiger::calculate() { // 草原虎
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        kickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        kickSkill.calculate();
    } else {
        kickSkill.clear();
    }

    if(percent[1] > 0.0) {
        jumpingScratchSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpingScratchSkill.calculate();
    } else {
        jumpingScratchSkill.clear();
    }

    if(percent[2] > 0.0) {
        powerIncreaseSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        powerIncreaseSkill.calculate();
    } else {
        powerIncreaseSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string PlainTiger::toString() { // 草原虎
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << kickSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpingScratchSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << powerIncreaseSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void PurpleBrowCaffer::calcScore() { // 黃金雷牛
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void PurpleBrowCaffer::calculate() { // 黃金雷牛
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        jumpKickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpKickSkill.calculate();
    } else {
        jumpKickSkill.clear();
    }

    if(percent[1] > 0.0) {
        doubleBoxSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleBoxSkill.calculate();
    } else {
        doubleBoxSkill.clear();
    }

    if(percent[2] > 0.0) {
        lightningSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        lightningSkill.calculate();
    } else {
        lightningSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string PurpleBrowCaffer::toString() { // 黃金雷牛
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << jumpKickSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << doubleBoxSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << lightningSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void RafflesiaSpirit::calcScore() { // 大王花
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void RafflesiaSpirit::calculate() { // 大王花
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        thornRattanSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        thornRattanSkill.calculate();
    } else {
        thornRattanSkill.clear();
    }

    if(percent[2] > 0.0) {
        stinkBubbleSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        stinkBubbleSkill.calculate();
    } else {
        stinkBubbleSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string RafflesiaSpirit::toString() { // 大王花
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << thornRattanSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << stinkBubbleSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void RedradishChicken::calcScore() { // 紅蘿蔔雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void RedradishChicken::calculate() { // 紅蘿蔔雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string RedradishChicken::toString() { // 紅蘿蔔雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bodyChargeSkill.toString(percent[1]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void RockMonster::calcScore() { // 魔岩精
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void RockMonster::calculate() { // 魔岩精
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        groundHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        groundHitSkill.calculate();
    } else {
        groundHitSkill.clear();
    }

    if(percent[1] > 0.0) {
        rockAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        rockAttackSkill.calculate();
    } else {
        rockAttackSkill.clear();
    }

    if(percent[2] > 0.0) {
        rockDefenseSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        rockDefenseSkill.calculate();
    } else {
        rockDefenseSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string RockMonster::toString() { // 魔岩精
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << groundHitSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << rockAttackSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << rockDefenseSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void RoseBee::calcScore() { // 沙漠玫蜂
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void RoseBee::calculate() { // 沙漠玫蜂
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyKickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyKickSkill.calculate();
    } else {
        flyKickSkill.clear();
    }

    if(percent[1] > 0.0) {
        tripleStingSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        tripleStingSkill.calculate();
    } else {
        tripleStingSkill.clear();
    }

    if(percent[2] > 0.0) {
        slackPollenSpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        slackPollenSpewSkill.calculate();
    } else {
        slackPollenSpewSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string RoseBee::toString() { // 沙漠玫蜂
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyKickSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << tripleStingSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << slackPollenSpewSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void SaplingChicken::calcScore() { // 樹苗雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void SaplingChicken::calculate() { // 樹苗雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        regeneratePhytoncidSpewSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        regeneratePhytoncidSpewSkill.calculate();
    } else {
        regeneratePhytoncidSpewSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string SaplingChicken::toString() { // 樹苗雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << regeneratePhytoncidSpewSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void ShellPolatouche::calcScore() { // 貝殼飛鼠
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void ShellPolatouche::calculate() { // 貝殼飛鼠
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        shellDartSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        shellDartSkill.calculate();
    } else {
        shellDartSkill.clear();
    }

    if(percent[2] > 0.0) {
        tornadoAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        tornadoAttackSkill.calculate();
    } else {
        tornadoAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string ShellPolatouche::toString() { // 貝殼飛鼠
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << shellDartSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << tornadoAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void Skunk::calcScore() { // 臭鼬
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void Skunk::calculate() { // 臭鼬
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        skunkBiteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        skunkBiteSkill.calculate();
    } else {
        skunkBiteSkill.clear();
    }

    if(percent[1] > 0.0) {
        doubleHeadHitSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleHeadHitSkill.calculate();
    } else {
        doubleHeadHitSkill.clear();
    }

    if(percent[2] > 0.0) {
        stenchAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        stenchAttackSkill.calculate();
    } else {
        stenchAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string Skunk::toString() { // 臭鼬
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << skunkBiteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << doubleHeadHitSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << stenchAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void StrawberryChicken::calcScore() { // 草莓雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void StrawberryChicken::calculate() { // 草莓雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        strawberryAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        strawberryAttackSkill.calculate();
    } else {
        strawberryAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string StrawberryChicken::toString() { // 草莓雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << strawberryAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void SunflowerSpirit::calcScore() { // 向日葵
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void SunflowerSpirit::calculate() { // 向日葵
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        patelDartAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        patelDartAttackSkill.calculate();
    } else {
        patelDartAttackSkill.clear();
    }

    if(percent[1] > 0.0) {
        sunlightAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        sunlightAttackSkill.calculate();
    } else {
        sunlightAttackSkill.clear();
    }

    if(percent[2] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string SunflowerSpirit::toString() { // 向日葵
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << patelDartAttackSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << sunlightAttackSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void SwardSheep::calcScore() { // 草皮羊
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void SwardSheep::calculate() { // 草皮羊
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        defenseIncreaseSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        defenseIncreaseSkill.calculate();
    } else {
        defenseIncreaseSkill.clear();
    }

    if(percent[2] > 0.0) {
        jumpAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpAttackSkill.calculate();
    } else {
        jumpAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string SwardSheep::toString() { // 草皮羊
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << bodyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << defenseIncreaseSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void UmbrellaLizard::calcScore() { // 毒傘蜥
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void UmbrellaLizard::calculate() { // 毒傘蜥
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);
    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string UmbrellaLizard::toString() { // 毒傘蜥
    return BasePet::toString(getPetClassByType(petType), "", petElement);
}

void Walrus::calcScore() { // 長牙海象
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void Walrus::calculate() { // 長牙海象
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        bubbleBombSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bubbleBombSkill.calculate();
    } else {
        bubbleBombSkill.clear();
    }

    if(percent[2] > 0.0) {
        chargeAlertSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        chargeAlertSkill.calculate();
    } else {
        chargeAlertSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string Walrus::toString() { // 長牙海象
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << bodyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bubbleBombSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << chargeAlertSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WatermelonChicken::calcScore() { // 西瓜雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WatermelonChicken::calculate() { // 西瓜雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        watermelonAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        watermelonAttackSkill.calculate();
    } else {
        watermelonAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WatermelonChicken::toString() { // 西瓜雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bodyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << watermelonAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WaveTurtle::calcScore() { // 功夫海龜
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WaveTurtle::calculate() { // 功夫海龜
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        doubleHandKnifeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleHandKnifeSkill.calculate();
    } else {
        doubleHandKnifeSkill.clear();
    }

    if(percent[1] > 0.0) {
        jumpingDoubleSlashSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpingDoubleSlashSkill.calculate();
    } else {
        jumpingDoubleSlashSkill.clear();
    }

    if(percent[2] > 0.0) {
        circleRollChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        circleRollChargeSkill.calculate();
    } else {
        circleRollChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WaveTurtle::toString() { // 功夫海龜
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << doubleHandKnifeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpingDoubleSlashSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << circleRollChargeSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WhiteOwl::calcScore() { // 貓頭鷹
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WhiteOwl::calculate() { // 貓頭鷹
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        featherDartAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        featherDartAttackSkill.calculate();
    } else {
        featherDartAttackSkill.clear();
    }

    if(percent[2] > 0.0) {
        greenTornadoAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        greenTornadoAttackSkill.calculate();
    } else {
        greenTornadoAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WhiteOwl::toString() { // 貓頭鷹
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << flyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << featherDartAttackSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << greenTornadoAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WhiteRabbit::calcScore() { // 小白兔
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WhiteRabbit::calculate() { // 小白兔
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        biteSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        biteSkill.calculate();
    } else {
        biteSkill.clear();
    }

    if(percent[1] > 0.0) {
        kickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        kickSkill.calculate();
    } else {
        kickSkill.clear();
    }

    if(percent[2] > 0.0) {
        dodgeIncreaseSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        dodgeIncreaseSkill.calculate();
    } else {
        dodgeIncreaseSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WhiteRabbit::toString() { // 小白兔
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << biteSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << kickSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << dodgeIncreaseSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WhiteSeal::calcScore() { // 小海豹
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WhiteSeal::calculate() { // 小海豹
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        doubleFinSlapSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        doubleFinSlapSkill.calculate();
    } else {
        doubleFinSlapSkill.clear();
    }

    if(percent[1] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[2] > 0.0) {
        bubbleSpreadSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bubbleSpreadSkill.calculate();
    } else {
        bubbleSpreadSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WhiteSeal::toString() { // 小海豹
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << doubleFinSlapSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bodyChargeSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bubbleSpreadSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WhiteSheep::calcScore() { // 白綿羊
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WhiteSheep::calculate() { // 白綿羊
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    if(percent[1] > 0.0) {
        defenseIncreaseWoolSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        defenseIncreaseWoolSkill.calculate();
    } else {
        defenseIncreaseWoolSkill.clear();
    }

    if(percent[2] > 0.0) {
        woolBallAttackSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        woolBallAttackSkill.calculate();
    } else {
        woolBallAttackSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WhiteSheep::toString() { // 白綿羊
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << bodyChargeSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << defenseIncreaseWoolSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << woolBallAttackSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WhiteTiger::calcScore() { // 劍齒白虎
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WhiteTiger::calculate() { // 劍齒白虎
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        kickSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        kickSkill.calculate();
    } else {
        kickSkill.clear();
    }

    if(percent[1] > 0.0) {
        jumpingScratchSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        jumpingScratchSkill.calculate();
    } else {
        jumpingScratchSkill.clear();
    }

    if(percent[2] > 0.0) {
        powerIncreaseSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        powerIncreaseSkill.calculate();
    } else {
        powerIncreaseSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WhiteTiger::toString() { // 劍齒白虎
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << kickSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << jumpingScratchSkill.toString(percent[1]);
    }

    if(percent[2] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << powerIncreaseSkill.toString(percent[2]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void WhiteradishChicken::calcScore() { // 白蘿蔔雞
    score = 0.0;

    score = round(score * 10.0) / 10.0;
}

void WhiteradishChicken::calculate() { // 白蘿蔔雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        bodyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        bodyChargeSkill.calculate();
    } else {
        bodyChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string WhiteradishChicken::toString() { // 白蘿蔔雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << bodyChargeSkill.toString(percent[1]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

void YellowChicken::calcScore() { // 小黃雞
    score = percent[0] * std::max(0.01, std::min(0.99, peckSkill.hitPercent + speedEffectAddon /* 基礎命中率 */)) * peckSkill.atk +
            percent[1] * std::max(0.01, std::min(0.99, flyChargeSkill.hitPercent + speedEffectAddon /* 基礎命中率 */)) * flyChargeSkill.atk +
            defense * 0.45 /* 0.75(遊戲預設的防禦倍率) x 0.6 = 0.45 */ +
            maxHp / 12.0 /* 1傷害 x 12回合 = 需要12生命 */ +
            60 /*敵人傷害期望值*/ * speedEffectAddon /* 基礎迴避率 */;

    score = round(score * 10.0) / 10.0;
}

void YellowChicken::calculate() { // 小黃雞
    maxHp =  calcMaxHp(maxHpMean, maxHpDeviation);
    strength =  calcStrength(strengthMean, strengthDeviation);
    defense =  calcDefense(defenseMean, defenseDeviation);
    speed =  calcSpeed(speedMean, speedDeviation);
    speedEffectAddon = calcSpeedEffectAddon(speed);

    getPercent(extraCode, skillDeviation);

    if(percent[0] > 0.0) {
        peckSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        peckSkill.calculate();
    } else {
        peckSkill.clear();
    }

    if(percent[1] > 0.0) {
        flyChargeSkill.setAllValue(gene, getLevel(), fruitType, fruitCode, strength);
        flyChargeSkill.calculate();
    } else {
        flyChargeSkill.clear();
    }

    calcElementAndResistance(petElement, resistanceMean, resistanceDeviation);
    BasePet::calculate();
    calcScore();
}

std::string YellowChicken::toString() { // 小黃雞
    std::stringstream ss;
    bool status = true;

    if(percent[0] > 0.0) {
        ss << peckSkill.toString(percent[0]);
        status = false;
    }

    if(percent[1] > 0.0) {
        (status == true) ? (void)(status = false) : (void)(ss << "\n");
        ss << flyChargeSkill.toString(percent[1]);
    }

    return BasePet::toString(getPetClassByType(petType), ss.str(), petElement);
}

std::string Pet::getPetInfo(PetType petType, std::string petGene, int petLevel, FruitType petFruitType, std::string petFruitCode) {
    switch(petType) {
    case PetType::baldEagle: { // 白頭蒼鷹
        BaldEagle monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::blackBear: { // 白紋黑熊
        BlackBear monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::blackCat: { // 哈斯貓
        BlackCat monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::blackRabbit: { // 黑毛兔
        BlackRabbit monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::blackWidow: { // 黑寡婦
        BlackWidow monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::blueBrowCaffer: { // 藍眉野牛
        BlueBrowCaffer monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::blueMagpie: { // 藍鵲
        BlueMagpie monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::cactusSpirit: { // 鴨嘴仙人掌
        CactusSpirit monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::catShark: { // 貓鯊
        CatShark monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::clownButterfly: { // 小丑蝶
        ClownButterfly monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::cobra: { // 眼鏡蛇
        Cobra monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::corollaBee: { // 花冠蜂
        CorollaBee monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::cottonCandyBee: { // 花糖蜂
        CottonCandyBee monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::darkBear: { // 月夜熊
        DarkBear monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::dragonFruitChicken: { // 火龍果雞
        DragonFruitChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::eggplantChicken: { // 小茄雞
        EggplantChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::fireDragon: { // 赤焰火龍
        FireDragon monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::firefly: { // 螢火蟲
        Firefly monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::flowerMantis: { // 魔眼螳螂
        FlowerMantis monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::forestFox: { // 野森狐
        ForestFox monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::forestPolatouche: { // 山林飛鼠
        ForestPolatouche monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::goldenBallCat: { // 金球貓
        GoldenBallCat monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::grassChicken: { // 小草雞
        GrassChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::hamimelonChicken: { // 哈蜜瓜雞
        HamimelonChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::hornRabbit: { // 火角兔
        HornRabbit monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::leafRaccoon: { // 葉子浣熊
        LeafRaccoon monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::magmaFlower: { // 溫泉花
        MagmaFlower monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::mushroomChicken: { // 香菇雞
        MushroomChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::orangeDeer: { // 橘子麋鹿
        OrangeDeer monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::plainTiger: { // 草原虎
        PlainTiger monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::purpleBrowCaffer: { // 黃金雷牛
        PurpleBrowCaffer monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::rafflesiaSpirit: { // 大王花
        RafflesiaSpirit monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::redradishChicken: { // 紅蘿蔔雞
        RedradishChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::rockMonster: { // 魔岩精
        RockMonster monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::roseBee: { // 沙漠玫蜂
        RoseBee monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::saplingChicken: { // 樹苗雞
        SaplingChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::shellPolatouche: { // 貝殼飛鼠
        ShellPolatouche monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::skunk: { // 臭鼬
        Skunk monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::strawberryChicken: { // 草莓雞
        StrawberryChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::sunflowerSpirit: { // 向日葵
        SunflowerSpirit monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::swardSheep: { // 草皮羊
        SwardSheep monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::umbrellaLizard: { // 毒傘蜥
        UmbrellaLizard monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::walrus: { // 長牙海象
        Walrus monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::watermelonChicken: { // 西瓜雞
        WatermelonChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::waveTurtle: { // 功夫海龜
        WaveTurtle monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::whiteOwl: { // 貓頭鷹
        WhiteOwl monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::whiteRabbit: { // 小白兔
        WhiteRabbit monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::whiteSeal: { // 小海豹
        WhiteSeal monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::whiteSheep: { // 白綿羊
        WhiteSheep monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::whiteTiger: { // 劍齒白虎
        WhiteTiger monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::whiteradishChicken: { // 白蘿蔔雞
        WhiteradishChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    case PetType::yellowChicken: { // 小黃雞
        YellowChicken monster;

        monster.setAllValue(petGene, petLevel, petFruitType, petFruitCode);
        monster.calculate();

        return monster.toString();
    }
    default:
        return "";
    }
}

std::string Pet::getPetInfo(std::string petClass, std::string petGene, int petLevel, std::string petFruitName, std::string petFruitCode) {
    return getPetInfo(getPetTypeByClass(petClass), petGene, petLevel, getFruitTypeByName(petFruitName), petFruitCode);
}
