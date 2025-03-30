/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#include <string>        // std::string
#include <unordered_map> // std::unordered_map

#include "type.h"

std::string MapElementCodeByType[8] = {
    "normal",    // 無 (未定義)
    "dark",      // 闇
    "earth",     // 地
    "fire",      // 火
    "grass",     // 草
    "light",     // 光
    "water",     // 水
    "wind"       // 風
};

std::string MapElementNameByType[8] = {
    "無", // 無 (未定義)
    "闇", // 闇
    "地", // 地
    "火", // 火
    "草", // 草
    "光", // 光
    "水", // 水
    "風"  // 風
};

std::unordered_map<std::string, int> MapElementTypeByCode = {
    {MapElementCodeByType[0], 0},
    {MapElementCodeByType[1], 1},
    {MapElementCodeByType[2], 2},
    {MapElementCodeByType[3], 3},
    {MapElementCodeByType[4], 4},
    {MapElementCodeByType[5], 5},
    {MapElementCodeByType[6], 6},
    {MapElementCodeByType[7], 7}
};

std::unordered_map<std::string, int> MapElementTypeByName = {
    {MapElementNameByType[0], 0},
    {MapElementNameByType[1], 1},
    {MapElementNameByType[2], 2},
    {MapElementNameByType[3], 3},
    {MapElementNameByType[4], 4},
    {MapElementNameByType[5], 5},
    {MapElementNameByType[6], 6},
    {MapElementNameByType[7], 7}
};

std::string getElementCodeByType(ElementType elementType) {
    if((int)elementType < 0 || (int)elementType >= 8)
        elementType = ElementType::normal;

    return MapElementCodeByType[(int)elementType];
}

std::string getElementNameByType(ElementType elementType) {
    if((int)elementType < 0 || (int)elementType >= 8)
        elementType = ElementType::normal;

    return MapElementNameByType[(int)elementType];
}

ElementType getElementTypeByCode(std::string elementCode) {
    /*std::unordered_map<std::string, int>::iterator i = MapElementTypeByCode.find(elementCode);

    if(i != MapElementTypeByCode.end())
        return (ElementType)(i->second);
    else
        return ElementType::normal;*/

    return (ElementType)MapElementTypeByCode[elementCode];
}

ElementType getElementTypeByName(std::string elementName) {
    /*std::unordered_map<std::string, int>::iterator i = MapElementTypeByName.find(elementName);

    if(i != MapElementTypeByName.end())
        return (ElementType)(i->second);
    else
        return ElementType::normal;*/

    return (ElementType)MapElementTypeByName[elementName];
}

std::string MapFruitCodeByType[10] = {
    "empty",     // 沒吃果實 (未定義)
    "battle",    // 戰鬥果實
    "boss",      // 魔王果實
    "element",   // 元素果實
    "hp",        // 再生果實
    "kimochi",   // 開心果實
    "loyal",     // 忠忠果實
    "purify",    // 征服果實
    "satiety",   // 飽飽果實
    "weight"     // 緊身果實
};

std::string MapFruitNameByType[10] = {
    "沒吃果實", // 沒吃果實 (未定義)
    "戰鬥果實", // 戰鬥果實
    "魔王果實", // 魔王果實
    "元素果實", // 元素果實
    "再生果實", // 再生果實
    "開心果實", // 開心果實
    "忠忠果實", // 忠忠果實
    "征服果實", // 征服果實
    "飽飽果實", // 飽飽果實
    "緊身果實"  // 緊身果實
};

std::unordered_map<std::string, int> MapFruitTypeByCode = {
    {MapFruitCodeByType[0], 0},
    {MapFruitCodeByType[1], 1},
    {MapFruitCodeByType[2], 2},
    {MapFruitCodeByType[3], 3},
    {MapFruitCodeByType[4], 4},
    {MapFruitCodeByType[5], 5},
    {MapFruitCodeByType[6], 6},
    {MapFruitCodeByType[7], 7},
    {MapFruitCodeByType[8], 8},
    {MapFruitCodeByType[9], 9}
};

std::unordered_map<std::string, int> MapFruitTypeByName = {
    {MapFruitNameByType[0], 0},
    {MapFruitNameByType[1], 1},
    {MapFruitNameByType[2], 2},
    {MapFruitNameByType[3], 3},
    {MapFruitNameByType[4], 4},
    {MapFruitNameByType[5], 5},
    {MapFruitNameByType[6], 6},
    {MapFruitNameByType[7], 7},
    {MapFruitNameByType[8], 8},
    {MapFruitNameByType[9], 9}
};

std::string getFruitCodeByType(FruitType fruitType) {
    if((int)fruitType < 0 || (int)fruitType >= 10)
        fruitType = FruitType::empty;

    return MapFruitCodeByType[(int)fruitType];
}

std::string getFruitNameByType(FruitType fruitType) {
    if((int)fruitType < 0 || (int)fruitType >= 10)
        fruitType = FruitType::empty;

    return MapFruitNameByType[(int)fruitType];
}

FruitType getFruitTypeByCode(std::string fruitCode) {
    /*std::unordered_map<std::string, int>::iterator i = MapFruitTypeByCode.find(fruitCode);

    if(i != MapFruitTypeByCode.end())
        return (FruitType)(i->second);
    else
        return FruitType::empty;*/

    return (FruitType)MapFruitTypeByCode[fruitCode];
}

FruitType getFruitTypeByName(std::string fruitName) {
    /*std::unordered_map<std::string, int>::iterator i = MapFruitTypeByName.find(fruitName);

    if(i != MapFruitTypeByName.end())
        return (FruitType)(i->second);
    else
        return FruitType::empty;*/

    return (FruitType)MapFruitTypeByName[fruitName];
}

std::string MapSkillCodeByType[88] = {
    "undefined",               // * 未定義
    "acornAttack",             // 橡果子彈
    "attractingLight",         // 螢光誘敵
    "baldDartAttack",          // 鷹羽飛針
    "berserk",                 // 狂暴
    "bite",                    // 咬擊
    "bodyCharge",              // 衝撞
    "boxingQuartet",           // 螢光四重揍
    "bubbleAttack",            // 噁噁泡
    "bubbleBomb",              // 深水炸彈
    "bubbleSpread",            // 噴水特技
    "cactusBubbleAttack",      // 惡仙露
    "cactusThornRain",         // 仙針雨
    "chargeAlert",             // 衝撞警戒
    "circleRollCharge",        // 旋風腳刀
    "circleRollScrach",        // 旋風金爪
    "clawHit",                 // 爪擊
    "counterCharge",           // 衝撞反擊
    "defenseIncrease",         // 毛皮強化
    "defenseIncreaseWool",     // 毛毛膜
    "dodgeIncrease",           // 注意力強化
    "doubleBox",               // 雙拳擊
    "doubleCatClaw",           // 貓爪抓
    "doubleClawHit",           // 雙爪擊
    "doubleFinSlap",           // 雙翼拍拍
    "doubleHandKnife",         // 手風刃
    "doubleHeadHit",           // 頭搥
    "doubleThornHit",          // 刺棘掌
    "dragonSeedAttack",        // 火龍果子
    "eagleShout",              // 大地鷹嚎
    "eyeShine",                // 金光閃閃
    "eyeStrike",               // 目光震憾
    "eyesRay",                 // 熱線攻擊
    "featherDartAttack",       // 羽毛飛標
    "feedHoneySpew",           // 蜂蜜餵食
    "fireSpew",                // 兔火球
    "fireTailAttack",          // 神龍擺尾
    "flyCharge",               // 飛衝突擊
    "flyKick",                 // 大腳飛踢
    "foxCharm",                // 魅狐秋波
    "giant",                   // 巨獸術
    "greenTornadoAttack",      // 青羽旋風
    "groundHit",               // 搥擊
    "groundStrike",            // 飛天破地
    "handBeam",                // 熊掌氣功
    "handWave",                // 開膛刀波
    "hellFire",                // 地獄火
    "jumpAttack",              // 泰山壓頂
    "jumpKick",                // 跳踢
    "jumpingDoubleSlash",      // 水月斬
    "jumpingKnife",            // 飛空鍘
    "jumpingScratch",          // 飛天爪
    "kick",                    // 踢擊
    "knittingBallAttack",      // 鋼毛飛球
    "leavesAttack",            // 飛葉攻擊
    "lightning",               // 金色閃電
    "loveEyes",                // 裝可憐
    "magicEyes",               // 魔眼催眠
    "patelDartAttack",         // 飛花攻擊
    "peck",                    // 啄擊
    "poisonBite",              // 毒牙咬
    "powerIncrease",           // 肌肉強化
    "regeneratePhytoncidSpew", // 芬多精
    "regeneratePollenSpew",    // 香香花粉
    "rockAttack",              // 拋石
    "rockDefense",             // 地牙盾
    "rollingCharge",           // 旋轉衝撞
    "shellDart",               // 貝殼飛盤
    "shockwave",               // 跳躍地震
    "skunkBite",               // 咬擊(臭鼬)
    "slackPollenSpew",         // 懶懶花粉
    "sporeSpew",               // 昏睡孢子
    "springBubble",            // 溫泉泡泡
    "stenchAttack",            // 臭氣
    "stingShoot",              // 蜂針射擊
    "stinkBubble",             // 臭臭氣
    "strawberryAttack",        // 莓雨季節
    "sunlightAttack",          // 太陽炫光
    "tailAttack",              // 尾鞭
    "tannicAttack",            // 單寧酸
    "thornRattan",             // 地蕀爪
    "tornadoAttack",           // 龍捲風暴
    "triplePeck",              // 啄擊(藍鵲)
    "tripleSting",             // 蜂蜇
    "volcanicEruption",        // 火山爆花
    "watermelonAttack",        // 黑子雨
    "wingDeterrence",          // 展翼嚇阻
    "woolBallAttack"           // 鉛毛彈
};

std::string MapSkillNameByType[88] = {
    "未定義",     // * 未定義
    "橡果子彈",   // 橡果子彈
    "螢光誘敵",   // 螢光誘敵
    "鷹羽飛針",   // 鷹羽飛針
    "狂暴",       // 狂暴
    "咬擊",       // 咬擊
    "衝撞",       // 衝撞
    "螢光四重揍", // 螢光四重揍
    "噁噁泡",     // 噁噁泡
    "深水炸彈",   // 深水炸彈
    "噴水特技",   // 噴水特技
    "惡仙露",     // 惡仙露
    "仙針雨",     // 仙針雨
    "衝撞警戒",   // 衝撞警戒
    "旋風腳刀",   // 旋風腳刀
    "旋風金爪",   // 旋風金爪
    "爪擊",       // 爪擊
    "衝撞反擊",   // 衝撞反擊
    "毛皮強化",   // 毛皮強化
    "毛毛膜",     // 毛毛膜
    "注意力強化", // 注意力強化
    "雙拳擊",     // 雙拳擊
    "貓爪抓",     // 貓爪抓
    "雙爪擊",     // 雙爪擊
    "雙翼拍拍",   // 雙翼拍拍
    "手風刃",     // 手風刃
    "頭搥",       // 頭搥
    "刺棘掌",     // 刺棘掌
    "火龍果子",   // 火龍果子
    "大地鷹嚎",   // 大地鷹嚎
    "金光閃閃",   // 金光閃閃
    "目光震憾",   // 目光震憾
    "熱線攻擊",   // 熱線攻擊
    "羽毛飛標",   // 羽毛飛標
    "蜂蜜餵食",   // 蜂蜜餵食
    "兔火球",     // 兔火球
    "神龍擺尾",   // 神龍擺尾
    "飛衝突擊",   // 飛衝突擊
    "大腳飛踢",   // 大腳飛踢
    "魅狐秋波",   // 魅狐秋波
    "巨獸術",     // 巨獸術
    "青羽旋風",   // 青羽旋風
    "搥擊",       // 搥擊
    "飛天破地",   // 飛天破地
    "熊掌氣功",   // 熊掌氣功
    "開膛刀波",   // 開膛刀波
    "地獄火",     // 地獄火
    "泰山壓頂",   // 泰山壓頂
    "跳踢",       // 跳踢
    "水月斬",     // 水月斬
    "飛空鍘",     // 飛空鍘
    "飛天爪",     // 飛天爪
    "踢擊",       // 踢擊
    "鋼毛飛球",   // 鋼毛飛球
    "飛葉攻擊",   // 飛葉攻擊
    "金色閃電",   // 金色閃電
    "裝可憐",     // 裝可憐
    "魔眼催眠",   // 魔眼催眠
    "飛花攻擊",   // 飛花攻擊
    "啄擊",       // 啄擊
    "毒牙咬",     // 毒牙咬
    "肌肉強化",   // 肌肉強化
    "芬多精",     // 芬多精
    "香香花粉",   // 香香花粉
    "拋石",       // 拋石
    "地牙盾",     // 地牙盾
    "旋轉衝撞",   // 旋轉衝撞
    "貝殼飛盤",   // 貝殼飛盤
    "跳躍地震",   // 跳躍地震
    "咬擊(臭鼬)", // 咬擊(臭鼬)
    "懶懶花粉",   // 懶懶花粉
    "昏睡孢子",   // 昏睡孢子
    "溫泉泡泡",   // 溫泉泡泡
    "臭氣",       // 臭氣
    "蜂針射擊",   // 蜂針射擊
    "臭臭氣",     // 臭臭氣
    "莓雨季節",   // 莓雨季節
    "太陽炫光",   // 太陽炫光
    "尾鞭",       // 尾鞭
    "單寧酸",     // 單寧酸
    "地蕀爪",     // 地蕀爪
    "龍捲風暴",   // 龍捲風暴
    "啄擊(藍鵲)", // 啄擊(藍鵲)
    "蜂蜇",       // 蜂蜇
    "火山爆花",   // 火山爆花
    "黑子雨",     // 黑子雨
    "展翼嚇阻",   // 展翼嚇阻
    "鉛毛彈"      // 鉛毛彈
};

std::unordered_map<std::string, int> MapSkillTypeByCode = {
    {MapSkillCodeByType[0], 0},
    {MapSkillCodeByType[1], 1},
    {MapSkillCodeByType[2], 2},
    {MapSkillCodeByType[3], 3},
    {MapSkillCodeByType[4], 4},
    {MapSkillCodeByType[5], 5},
    {MapSkillCodeByType[6], 6},
    {MapSkillCodeByType[7], 7},
    {MapSkillCodeByType[8], 8},
    {MapSkillCodeByType[9], 9},
    {MapSkillCodeByType[10], 10},
    {MapSkillCodeByType[11], 11},
    {MapSkillCodeByType[12], 12},
    {MapSkillCodeByType[13], 13},
    {MapSkillCodeByType[14], 14},
    {MapSkillCodeByType[15], 15},
    {MapSkillCodeByType[16], 16},
    {MapSkillCodeByType[17], 17},
    {MapSkillCodeByType[18], 18},
    {MapSkillCodeByType[19], 19},
    {MapSkillCodeByType[20], 20},
    {MapSkillCodeByType[21], 21},
    {MapSkillCodeByType[22], 22},
    {MapSkillCodeByType[23], 23},
    {MapSkillCodeByType[24], 24},
    {MapSkillCodeByType[25], 25},
    {MapSkillCodeByType[26], 26},
    {MapSkillCodeByType[27], 27},
    {MapSkillCodeByType[28], 28},
    {MapSkillCodeByType[29], 29},
    {MapSkillCodeByType[30], 30},
    {MapSkillCodeByType[31], 31},
    {MapSkillCodeByType[32], 32},
    {MapSkillCodeByType[33], 33},
    {MapSkillCodeByType[34], 34},
    {MapSkillCodeByType[35], 35},
    {MapSkillCodeByType[36], 36},
    {MapSkillCodeByType[37], 37},
    {MapSkillCodeByType[38], 38},
    {MapSkillCodeByType[39], 39},
    {MapSkillCodeByType[40], 40},
    {MapSkillCodeByType[41], 41},
    {MapSkillCodeByType[42], 42},
    {MapSkillCodeByType[43], 43},
    {MapSkillCodeByType[44], 44},
    {MapSkillCodeByType[45], 45},
    {MapSkillCodeByType[46], 46},
    {MapSkillCodeByType[47], 47},
    {MapSkillCodeByType[48], 48},
    {MapSkillCodeByType[49], 49},
    {MapSkillCodeByType[50], 50},
    {MapSkillCodeByType[51], 51},
    {MapSkillCodeByType[52], 52},
    {MapSkillCodeByType[53], 53},
    {MapSkillCodeByType[54], 54},
    {MapSkillCodeByType[55], 55},
    {MapSkillCodeByType[56], 56},
    {MapSkillCodeByType[57], 57},
    {MapSkillCodeByType[58], 58},
    {MapSkillCodeByType[59], 59},
    {MapSkillCodeByType[60], 60},
    {MapSkillCodeByType[61], 61},
    {MapSkillCodeByType[62], 62},
    {MapSkillCodeByType[63], 63},
    {MapSkillCodeByType[64], 64},
    {MapSkillCodeByType[65], 65},
    {MapSkillCodeByType[66], 66},
    {MapSkillCodeByType[67], 67},
    {MapSkillCodeByType[68], 68},
    {MapSkillCodeByType[69], 69},
    {MapSkillCodeByType[70], 70},
    {MapSkillCodeByType[71], 71},
    {MapSkillCodeByType[72], 72},
    {MapSkillCodeByType[73], 73},
    {MapSkillCodeByType[74], 74},
    {MapSkillCodeByType[75], 75},
    {MapSkillCodeByType[76], 76},
    {MapSkillCodeByType[77], 77},
    {MapSkillCodeByType[78], 78},
    {MapSkillCodeByType[79], 79},
    {MapSkillCodeByType[80], 80},
    {MapSkillCodeByType[81], 81},
    {MapSkillCodeByType[82], 82},
    {MapSkillCodeByType[83], 83},
    {MapSkillCodeByType[84], 84},
    {MapSkillCodeByType[85], 85},
    {MapSkillCodeByType[86], 86},
    {MapSkillCodeByType[87], 87}
};

std::unordered_map<std::string, int> MapSkillTypeByName = {
    {MapSkillNameByType[0], 0},
    {MapSkillNameByType[1], 1},
    {MapSkillNameByType[2], 2},
    {MapSkillNameByType[3], 3},
    {MapSkillNameByType[4], 4},
    {MapSkillNameByType[5], 5},
    {MapSkillNameByType[6], 6},
    {MapSkillNameByType[7], 7},
    {MapSkillNameByType[8], 8},
    {MapSkillNameByType[9], 9},
    {MapSkillNameByType[10], 10},
    {MapSkillNameByType[11], 11},
    {MapSkillNameByType[12], 12},
    {MapSkillNameByType[13], 13},
    {MapSkillNameByType[14], 14},
    {MapSkillNameByType[15], 15},
    {MapSkillNameByType[16], 16},
    {MapSkillNameByType[17], 17},
    {MapSkillNameByType[18], 18},
    {MapSkillNameByType[19], 19},
    {MapSkillNameByType[20], 20},
    {MapSkillNameByType[21], 21},
    {MapSkillNameByType[22], 22},
    {MapSkillNameByType[23], 23},
    {MapSkillNameByType[24], 24},
    {MapSkillNameByType[25], 25},
    {MapSkillNameByType[26], 26},
    {MapSkillNameByType[27], 27},
    {MapSkillNameByType[28], 28},
    {MapSkillNameByType[29], 29},
    {MapSkillNameByType[30], 30},
    {MapSkillNameByType[31], 31},
    {MapSkillNameByType[32], 32},
    {MapSkillNameByType[33], 33},
    {MapSkillNameByType[34], 34},
    {MapSkillNameByType[35], 35},
    {MapSkillNameByType[36], 36},
    {MapSkillNameByType[37], 37},
    {MapSkillNameByType[38], 38},
    {MapSkillNameByType[39], 39},
    {MapSkillNameByType[40], 40},
    {MapSkillNameByType[41], 41},
    {MapSkillNameByType[42], 42},
    {MapSkillNameByType[43], 43},
    {MapSkillNameByType[44], 44},
    {MapSkillNameByType[45], 45},
    {MapSkillNameByType[46], 46},
    {MapSkillNameByType[47], 47},
    {MapSkillNameByType[48], 48},
    {MapSkillNameByType[49], 49},
    {MapSkillNameByType[50], 50},
    {MapSkillNameByType[51], 51},
    {MapSkillNameByType[52], 52},
    {MapSkillNameByType[53], 53},
    {MapSkillNameByType[54], 54},
    {MapSkillNameByType[55], 55},
    {MapSkillNameByType[56], 56},
    {MapSkillNameByType[57], 57},
    {MapSkillNameByType[58], 58},
    {MapSkillNameByType[59], 59},
    {MapSkillNameByType[60], 60},
    {MapSkillNameByType[61], 61},
    {MapSkillNameByType[62], 62},
    {MapSkillNameByType[63], 63},
    {MapSkillNameByType[64], 64},
    {MapSkillNameByType[65], 65},
    {MapSkillNameByType[66], 66},
    {MapSkillNameByType[67], 67},
    {MapSkillNameByType[68], 68},
    {MapSkillNameByType[69], 69},
    {MapSkillNameByType[70], 70},
    {MapSkillNameByType[71], 71},
    {MapSkillNameByType[72], 72},
    {MapSkillNameByType[73], 73},
    {MapSkillNameByType[74], 74},
    {MapSkillNameByType[75], 75},
    {MapSkillNameByType[76], 76},
    {MapSkillNameByType[77], 77},
    {MapSkillNameByType[78], 78},
    {MapSkillNameByType[79], 79},
    {MapSkillNameByType[80], 80},
    {MapSkillNameByType[81], 81},
    {MapSkillNameByType[82], 82},
    {MapSkillNameByType[83], 83},
    {MapSkillNameByType[84], 84},
    {MapSkillNameByType[85], 85},
    {MapSkillNameByType[86], 86},
    {MapSkillNameByType[87], 87}
};

std::string getSkillCodeByType(SkillType skillType) {
    if((int)skillType < 0 || (int)skillType >= 88)
        skillType = SkillType::undefined;

    return MapSkillCodeByType[(int)skillType];
}

std::string getSkillNameByType(SkillType skillType) {
    if((int)skillType < 0 || (int)skillType >= 88)
        skillType = SkillType::undefined;

    return MapSkillNameByType[(int)skillType];
}

SkillType getSkillTypeByCode(std::string skillCode) {
    /*std::unordered_map<std::string, int>::iterator i = MapSkillTypeByCode.find(skillCode);

    if(i != MapSkillTypeByCode.end())
        return (SkillType)(i->second);
    else
        return SkillType::undefined;*/

    return (SkillType)MapSkillTypeByCode[skillCode];
}

SkillType getSkillTypeByName(std::string skillName) {
    /*std::unordered_map<std::string, int>::iterator i = MapSkillTypeByName.find(skillName);

    if(i != MapSkillTypeByName.end())
        return (SkillType)(i->second);
    else
        return SkillType::undefined;*/

    return (SkillType)MapSkillTypeByName[skillName];
}

std::string MapPetCodeByType[53] = {
    "undefined",          // * 未定義
    "baldEagle",          // 白頭蒼鷹
    "blackBear",          // 白紋黑熊
    "blackCat",           // 哈斯貓
    "blackRabbit",        // 黑毛兔
    "blackWidow",         // 黑寡婦 *未開放
    "blueBrowCaffer",     // 藍眉野牛
    "blueMagpie",         // 藍鵲
    "cactusSpirit",       // 鴨嘴仙人掌
    "catShark",           // 貓鯊
    "clownButterfly",     // 小丑蝶
    "cobra",              // 眼鏡蛇
    "corollaBee",         // 花冠蜂
    "cottonCandyBee",     // 花糖蜂
    "darkBear",           // 月夜熊
    "dragonFruitChicken", // 火龍果雞
    "eggplantChicken",    // 小茄雞
    "fireDragon",         // 赤焰火龍
    "firefly",            // 螢火蟲
    "flowerMantis",       // 魔眼螳螂
    "forestFox",          // 野森狐
    "forestPolatouche",   // 山林飛鼠
    "goldenBallCat",      // 金球貓
    "grassChicken",       // 小草雞
    "hamimelonChicken",   // 哈蜜瓜雞 *未開放
    "hornRabbit",         // 火角兔
    "leafRaccoon",        // 葉子浣熊
    "magmaFlower",        // 溫泉花
    "mushroomChicken",    // 香菇雞
    "orangeDeer",         // 橘子麋鹿
    "plainTiger",         // 草原虎
    "purpleBrowCaffer",   // 黃金雷牛
    "rafflesiaSpirit",    // 大王花
    "redradishChicken",   // 紅蘿蔔雞 *未開放
    "rockMonster",        // 魔岩精
    "roseBee",            // 沙漠玫蜂
    "saplingChicken",     // 樹苗雞
    "shellPolatouche",    // 貝殼飛鼠
    "skunk",              // 臭鼬
    "strawberryChicken",  // 草莓雞
    "sunflowerSpirit",    // 向日葵
    "swardSheep",         // 草皮羊
    "umbrellaLizard",     // 毒傘蜥 *未開放
    "walrus",             // 長牙海象
    "watermelonChicken",  // 西瓜雞
    "waveTurtle",         // 功夫海龜
    "whiteOwl",           // 貓頭鷹
    "whiteRabbit",        // 小白兔
    "whiteSeal",          // 小海豹
    "whiteSheep",         // 白綿羊
    "whiteTiger",         // 劍齒白虎
    "whiteradishChicken", // 白蘿蔔雞 *未開放
    "yellowChicken"       // 小黃雞
};

std::string MapPetClassByType[53] = {
    "未定義",     // * 未定義
    "白頭蒼鷹",   // 白頭蒼鷹
    "白紋黑熊",   // 白紋黑熊
    "哈斯貓",     // 哈斯貓
    "黑毛兔",     // 黑毛兔
    "黑寡婦",     // 黑寡婦 *未開放
    "藍眉野牛",   // 藍眉野牛
    "藍鵲",       // 藍鵲
    "鴨嘴仙人掌", // 鴨嘴仙人掌
    "貓鯊",       // 貓鯊
    "小丑蝶",     // 小丑蝶
    "眼鏡蛇",     // 眼鏡蛇
    "花冠蜂",     // 花冠蜂
    "花糖蜂",     // 花糖蜂
    "月夜熊",     // 月夜熊
    "火龍果雞",   // 火龍果雞
    "小茄雞",     // 小茄雞
    "赤焰火龍",   // 赤焰火龍
    "螢火蟲",     // 螢火蟲
    "魔眼螳螂",   // 魔眼螳螂
    "野森狐",     // 野森狐
    "山林飛鼠",   // 山林飛鼠
    "金球貓",     // 金球貓
    "小草雞",     // 小草雞
    "哈蜜瓜雞",   // 哈蜜瓜雞 *未開放
    "火角兔",     // 火角兔
    "葉子浣熊",   // 葉子浣熊
    "溫泉花",     // 溫泉花
    "香菇雞",     // 香菇雞
    "橘子麋鹿",   // 橘子麋鹿
    "草原虎",     // 草原虎
    "黃金雷牛",   // 黃金雷牛
    "大王花",     // 大王花
    "紅蘿蔔雞",   // 紅蘿蔔雞 *未開放
    "魔岩精",     // 魔岩精
    "沙漠玫蜂",   // 沙漠玫蜂
    "樹苗雞",     // 樹苗雞
    "貝殼飛鼠",   // 貝殼飛鼠
    "臭鼬",       // 臭鼬
    "草莓雞",     // 草莓雞
    "向日葵",     // 向日葵
    "草皮羊",     // 草皮羊
    "毒傘蜥",     // 毒傘蜥 *未開放
    "長牙海象",   // 長牙海象
    "西瓜雞",     // 西瓜雞
    "功夫海龜",   // 功夫海龜
    "貓頭鷹",     // 貓頭鷹
    "小白兔",     // 小白兔
    "小海豹",     // 小海豹
    "白綿羊",     // 白綿羊
    "劍齒白虎",   // 劍齒白虎
    "白蘿蔔雞",   // 白蘿蔔雞 *未開放
    "小黃雞"      // 小黃雞
};

std::unordered_map<std::string, int> MapPetTypeByCode = {
    {MapPetCodeByType[0], 0},
    {MapPetCodeByType[1], 1},
    {MapPetCodeByType[2], 2},
    {MapPetCodeByType[3], 3},
    {MapPetCodeByType[4], 4},
    {MapPetCodeByType[5], 5},
    {MapPetCodeByType[6], 6},
    {MapPetCodeByType[7], 7},
    {MapPetCodeByType[8], 8},
    {MapPetCodeByType[9], 9},
    {MapPetCodeByType[10], 10},
    {MapPetCodeByType[11], 11},
    {MapPetCodeByType[12], 12},
    {MapPetCodeByType[13], 13},
    {MapPetCodeByType[14], 14},
    {MapPetCodeByType[15], 15},
    {MapPetCodeByType[16], 16},
    {MapPetCodeByType[17], 17},
    {MapPetCodeByType[18], 18},
    {MapPetCodeByType[19], 19},
    {MapPetCodeByType[20], 20},
    {MapPetCodeByType[21], 21},
    {MapPetCodeByType[22], 22},
    {MapPetCodeByType[23], 23},
    {MapPetCodeByType[24], 24},
    {MapPetCodeByType[25], 25},
    {MapPetCodeByType[26], 26},
    {MapPetCodeByType[27], 27},
    {MapPetCodeByType[28], 28},
    {MapPetCodeByType[29], 29},
    {MapPetCodeByType[30], 30},
    {MapPetCodeByType[31], 31},
    {MapPetCodeByType[32], 32},
    {MapPetCodeByType[33], 33},
    {MapPetCodeByType[34], 34},
    {MapPetCodeByType[35], 35},
    {MapPetCodeByType[36], 36},
    {MapPetCodeByType[37], 37},
    {MapPetCodeByType[38], 38},
    {MapPetCodeByType[39], 39},
    {MapPetCodeByType[40], 40},
    {MapPetCodeByType[41], 41},
    {MapPetCodeByType[42], 42},
    {MapPetCodeByType[43], 43},
    {MapPetCodeByType[44], 44},
    {MapPetCodeByType[45], 45},
    {MapPetCodeByType[46], 46},
    {MapPetCodeByType[47], 47},
    {MapPetCodeByType[48], 48},
    {MapPetCodeByType[49], 49},
    {MapPetCodeByType[50], 50},
    {MapPetCodeByType[51], 51},
    {MapPetCodeByType[52], 52}

};

std::unordered_map<std::string, int> MapPetTypeByClass = {
    {MapPetClassByType[0], 0},
    {MapPetClassByType[1], 1},
    {MapPetClassByType[2], 2},
    {MapPetClassByType[3], 3},
    {MapPetClassByType[4], 4},
    {MapPetClassByType[5], 5},
    {MapPetClassByType[6], 6},
    {MapPetClassByType[7], 7},
    {MapPetClassByType[8], 8},
    {MapPetClassByType[9], 9},
    {MapPetClassByType[10], 10},
    {MapPetClassByType[11], 11},
    {MapPetClassByType[12], 12},
    {MapPetClassByType[13], 13},
    {MapPetClassByType[14], 14},
    {MapPetClassByType[15], 15},
    {MapPetClassByType[16], 16},
    {MapPetClassByType[17], 17},
    {MapPetClassByType[18], 18},
    {MapPetClassByType[19], 19},
    {MapPetClassByType[20], 20},
    {MapPetClassByType[21], 21},
    {MapPetClassByType[22], 22},
    {MapPetClassByType[23], 23},
    {MapPetClassByType[24], 24},
    {MapPetClassByType[25], 25},
    {MapPetClassByType[26], 26},
    {MapPetClassByType[27], 27},
    {MapPetClassByType[28], 28},
    {MapPetClassByType[29], 29},
    {MapPetClassByType[30], 30},
    {MapPetClassByType[31], 31},
    {MapPetClassByType[32], 32},
    {MapPetClassByType[33], 33},
    {MapPetClassByType[34], 34},
    {MapPetClassByType[35], 35},
    {MapPetClassByType[36], 36},
    {MapPetClassByType[37], 37},
    {MapPetClassByType[38], 38},
    {MapPetClassByType[39], 39},
    {MapPetClassByType[40], 40},
    {MapPetClassByType[41], 41},
    {MapPetClassByType[42], 42},
    {MapPetClassByType[43], 43},
    {MapPetClassByType[44], 44},
    {MapPetClassByType[45], 45},
    {MapPetClassByType[46], 46},
    {MapPetClassByType[47], 47},
    {MapPetClassByType[48], 48},
    {MapPetClassByType[49], 49},
    {MapPetClassByType[50], 50},
    {MapPetClassByType[51], 51},
    {MapPetClassByType[52], 52}
};

std::string getPetCodeByType(PetType petType) {
    if((int)petType < 0 || (int)petType >= 53)
        petType = PetType::undefined;

    return MapPetCodeByType[(int)petType];
}

std::string getPetClassByType(PetType petType) {
    if((int)petType < 0 || (int)petType >= 53)
        petType = PetType::undefined;

    return MapPetClassByType[(int)petType];
}

PetType getPetTypeByCode(std::string petCode) {
    /*std::unordered_map<std::string, int>::iterator i = MapPetTypeByCode.find(petCode);

    if(i != MapPetTypeByCode.end())
        return (PetType)(i->second);
    else
        return PetType::undefined;*/

    return (PetType)MapPetTypeByCode[petCode];
}

PetType getPetTypeByClass(std::string petClass) {
    /*std::unordered_map<std::string, int>::iterator i = MapPetTypeByClass.find(petClass);

    if(i != MapPetTypeByClass.end())
        return (PetType)(i->second);
    else
        return PetType::undefined;*/

    return (PetType)MapPetTypeByClass[petClass];
}
