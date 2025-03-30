/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#ifndef MF_TYPE_H
#define MF_TYPE_H

#include <string>        // std::string
#include <unordered_map> // std::unordered_map

enum class ElementType {
    normal,    // 無 (未定義)
    dark,      // 闇
    earth,     // 地
    fire,      // 火
    grass,     // 草
    light,     // 光
    water,     // 水
    wind       // 風
};

extern std::string MapElementCodeByType[8];
extern std::string MapElementNameByType[8];
extern std::unordered_map<std::string, int> MapElementTypeByCode;
extern std::unordered_map<std::string, int> MapElementTypeByName;

std::string getElementCodeByType(ElementType elementType);
std::string getElementNameByType(ElementType elementType);
ElementType getElementTypeByCode(std::string elementCode);
ElementType getElementTypeByName(std::string elementName);

enum class FruitType {
    empty,     // 沒吃果實 (未定義)
    battle,    // 戰鬥果實
    boss,      // 魔王果實
    element,   // 元素果實
    hp,        // 再生果實
    kimochi,   // 開心果實
    loyal,     // 忠忠果實
    purify,    // 征服果實
    satiety,   // 飽飽果實
    weight     // 緊身果實
};

extern std::string MapFruitCodeByType[10];
extern std::string MapFruitNameByType[10];
extern std::unordered_map<std::string, int> MapFruitTypeByCode;
extern std::unordered_map<std::string, int> MapFruitTypeByName;

std::string getFruitCodeByType(FruitType fruitType);
std::string getFruitNameByType(FruitType fruitType);
FruitType getFruitTypeByCode(std::string fruitCode);
FruitType getFruitTypeByName(std::string fruitName);

enum class SkillType {
    undefined,               // * 未定義
    acornAttack,             // 橡果子彈
    attractingLight,         // 螢光誘敵
    baldDartAttack,          // 鷹羽飛針
    berserk,                 // 狂暴
    bite,                    // 咬擊
    bodyCharge,              // 衝撞
    boxingQuartet,           // 螢光四重揍
    bubbleAttack,            // 噁噁泡
    bubbleBomb,              // 深水炸彈
    bubbleSpread,            // 噴水特技
    cactusBubbleAttack,      // 惡仙露
    cactusThornRain,         // 仙針雨
    chargeAlert,             // 衝撞警戒
    circleRollCharge,        // 旋風腳刀
    circleRollScrach,        // 旋風金爪
    clawHit,                 // 爪擊
    counterCharge,           // 衝撞反擊
    defenseIncrease,         // 毛皮強化
    defenseIncreaseWool,     // 毛毛膜
    dodgeIncrease,           // 注意力強化
    doubleBox,               // 雙拳擊
    doubleCatClaw,           // 貓爪抓
    doubleClawHit,           // 雙爪擊
    doubleFinSlap,           // 雙翼拍拍
    doubleHandKnife,         // 手風刃
    doubleHeadHit,           // 頭搥
    doubleThornHit,          // 刺棘掌
    dragonSeedAttack,        // 火龍果子
    eagleShout,              // 大地鷹嚎
    eyeShine,                // 金光閃閃
    eyeStrike,               // 目光震憾
    eyesRay,                 // 熱線攻擊
    featherDartAttack,       // 羽毛飛標
    feedHoneySpew,           // 蜂蜜餵食
    fireSpew,                // 兔火球
    fireTailAttack,          // 神龍擺尾
    flyCharge,               // 飛衝突擊
    flyKick,                 // 大腳飛踢
    foxCharm,                // 魅狐秋波
    giant,                   // 巨獸術
    greenTornadoAttack,      // 青羽旋風
    groundHit,               // 搥擊
    groundStrike,            // 飛天破地
    handBeam,                // 熊掌氣功
    handWave,                // 開膛刀波
    hellFire,                // 地獄火
    jumpAttack,              // 泰山壓頂
    jumpKick,                // 跳踢
    jumpingDoubleSlash,      // 水月斬
    jumpingKnife,            // 飛空鍘
    jumpingScratch,          // 飛天爪
    kick,                    // 踢擊
    knittingBallAttack,      // 鋼毛飛球
    leavesAttack,            // 飛葉攻擊
    lightning,               // 金色閃電
    loveEyes,                // 裝可憐
    magicEyes,               // 魔眼催眠
    patelDartAttack,         // 飛花攻擊
    peck,                    // 啄擊
    poisonBite,              // 毒牙咬
    powerIncrease,           // 肌肉強化
    regeneratePhytoncidSpew, // 芬多精
    regeneratePollenSpew,    // 香香花粉
    rockAttack,              // 拋石
    rockDefense,             // 地牙盾
    rollingCharge,           // 旋轉衝撞
    shellDart,               // 貝殼飛盤
    shockwave,               // 跳躍地震
    skunkBite,               // 咬擊(臭鼬)
    slackPollenSpew,         // 懶懶花粉
    sporeSpew,               // 昏睡孢子
    springBubble,            // 溫泉泡泡
    stenchAttack,            // 臭氣
    stingShoot,              // 蜂針射擊
    stinkBubble,             // 臭臭氣
    strawberryAttack,        // 莓雨季節
    sunlightAttack,          // 太陽炫光
    tailAttack,              // 尾鞭
    tannicAttack,            // 單寧酸
    thornRattan,             // 地蕀爪
    tornadoAttack,           // 龍捲風暴
    triplePeck,              // 啄擊(藍鵲)
    tripleSting,             // 蜂蜇
    volcanicEruption,        // 火山爆花
    watermelonAttack,        // 黑子雨
    wingDeterrence,          // 展翼嚇阻
    woolBallAttack           // 鉛毛彈
};

extern std::string MapSkillCodeByType[88];
extern std::string MapSkillNameByType[88];
extern std::unordered_map<std::string, int> MapSkillTypeByCode;
extern std::unordered_map<std::string, int> MapSkillTypeByName;

std::string getSkillCodeByType(SkillType skillType);
std::string getSkillNameByType(SkillType skillType);
SkillType getSkillTypeByCode(std::string skillCode);
SkillType getSkillTypeByName(std::string skillName);

enum class PetType {
    undefined,          // * 未定義
    baldEagle,          // 白頭蒼鷹
    blackBear,          // 白紋黑熊
    blackCat,           // 哈斯貓
    blackRabbit,        // 黑毛兔
    blackWidow,         // 黑寡婦 *未開放
    blueBrowCaffer,     // 藍眉野牛
    blueMagpie,         // 藍鵲
    cactusSpirit,       // 鴨嘴仙人掌
    catShark,           // 貓鯊
    clownButterfly,     // 小丑蝶
    cobra,              // 眼鏡蛇
    corollaBee,         // 花冠蜂
    cottonCandyBee,     // 花糖蜂
    darkBear,           // 月夜熊
    dragonFruitChicken, // 火龍果雞
    eggplantChicken,    // 小茄雞
    fireDragon,         // 赤焰火龍
    firefly,            // 螢火蟲
    flowerMantis,       // 魔眼螳螂
    forestFox,          // 野森狐
    forestPolatouche,   // 山林飛鼠
    goldenBallCat,      // 金球貓
    grassChicken,       // 小草雞
    hamimelonChicken,   // 哈蜜瓜雞 *未開放
    hornRabbit,         // 火角兔
    leafRaccoon,        // 葉子浣熊
    magmaFlower,        // 溫泉花
    mushroomChicken,    // 香菇雞
    orangeDeer,         // 橘子麋鹿
    plainTiger,         // 草原虎
    purpleBrowCaffer,   // 黃金雷牛
    rafflesiaSpirit,    // 大王花
    redradishChicken,   // 紅蘿蔔雞 *未開放
    rockMonster,        // 魔岩精
    roseBee,            // 沙漠玫蜂
    saplingChicken,     // 樹苗雞
    shellPolatouche,    // 貝殼飛鼠
    skunk,              // 臭鼬
    strawberryChicken,  // 草莓雞
    sunflowerSpirit,    // 向日葵
    swardSheep,         // 草皮羊
    umbrellaLizard,     // 毒傘蜥 *未開放
    walrus,             // 長牙海象
    watermelonChicken,  // 西瓜雞
    waveTurtle,         // 功夫海龜
    whiteOwl,           // 貓頭鷹
    whiteRabbit,        // 小白兔
    whiteSeal,          // 小海豹
    whiteSheep,         // 白綿羊
    whiteTiger,         // 劍齒白虎
    whiteradishChicken, // 白蘿蔔雞 *未開放
    yellowChicken       // 小黃雞
};

extern std::string MapPetCodeByType[53];
extern std::string MapPetClassByType[53];
extern std::unordered_map<std::string, int> MapPetTypeByCode;
extern std::unordered_map<std::string, int> MapPetTypeByClass;

std::string getPetCodeByType(PetType petType);
std::string getPetClassByType(PetType petType);
PetType getPetTypeByCode(std::string petCode);
PetType getPetTypeByClass(std::string petClass);

enum class RandomSeed {
    MAX_HP,
    STRENGTH,
    SPEED,
    DEFENSE,
    SKILL_WEIGHT,
    GENDER,
    RESISTANCE,
    SKILL_MULTIPLIER,
    SKILL_ADDEND,
    SKILL_HIT_PERCENT,
    SKILL_SPECIAL,
    ITEM_IMPRESSION,
    MEDICAL_IMPRESSION,
    MONSTER_HEIGHT,
    MONSTER_ITEM_DURATION,
    MONSTER_ITEM_DURATION_FIELD,
    MONSTER_FRUIT_KIMOCHI,
    MONSTER_FRUIT_SATIETY,
    MONSTER_FRUIT_LOYAL,
    MONSTER_FRUIT_HP,
    MONSTER_FRUIT_ELEMENT
};

#endif // MF_TYPE_H
