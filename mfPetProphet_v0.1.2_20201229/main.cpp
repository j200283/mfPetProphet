/* Project Name:    mfPetProphet
 * Project Version: 0.1.2
 * Update Time:     2020/12/29
 * Author:          The mfPetProphet Team
 * IDE:             Code::Blocks 20.03
 * Compiler:        mingw64 (mingw-w64-x86_64-gcc 10.2.0-6)
 * OS:              Windows 10 (20h2 - 64 bits)
 * Other Tools:     MSYS2 (mingw64)
 */

#include <iostream>
#include "mf/pet.h"

int main() {
    /*Pet p;
    std::string temp; // 避免指令太長被螢幕遮掉，你也能直接一行解決。

    // 方法一: (auto 會自動判斷函數回傳的型別)
    auto petType = getPetTypeByClass("溫泉花");
    std::string petGene = "@monster_21d048aa49c7be6a54f88a65155a2eb7";
    int petLevel = 5;
    auto petFruitType = getFruitTypeByName("戰鬥果實");
    std::string petFruitCode = "FOPW";

    temp = p.getPetInfo(petType, petGene, petLevel, petFruitType, petFruitCode);
    std::cout << temp << std::endl << std::endl;

    // 方法二:
    temp = p.getPetInfo(PetType::baldEagle, "@monster_12345678901234567890123456789012", 5, FruitType::element, "TEST");
    std::cout << temp << std::endl << std::endl;

    // 方法三:
    temp = p.getPetInfo("小丑蝶", "@monster_98765432109876543210987654321098", 5, "再生果實", "LOVE");
    std::cout << temp << std::endl << std::endl;*/

    Pet p;
    PetType petType;
    std::string petGene, petFruitCode, temp;
    FruitType petFruitType;
    bool work = true;

    while(work) {
        while(work) {
            std::cout << "寵物學名: ";
            std::cin >> temp;

            if(std::cin.eof()) { // 使用者按下 Ctrl + Z (結束程式)
                work = false;
                break;
            } else if(temp != "" && ((temp[0] >= 'A' && temp[0] <= 'Z') || (temp[0] >= 'a' && temp[0] <= 'z'))) {
                petType = getPetTypeByCode(temp);
            } else {
                petType = getPetTypeByClass(temp);
            }

            if(petType != PetType::undefined)
                break;
        }

        while(work) {
            std::cout << "寵物代碼: ";
            std::cin >> temp;

            if(std::cin.eof()) { // 使用者按下 Ctrl + Z (結束程式)
                work = false;
                break;
            } else if(temp != "") {
                petGene = temp;
                break;
            }
        }

        if(work) {
            std::cout << "果實種類: ";
            std::cin >> temp;

            if(std::cin.eof()) { // 使用者按下 Ctrl + Z (結束程式)
                work = false;
            } else if(temp != "" && ((temp[0] >= 'A' && temp[0] <= 'Z') || (temp[0] >= 'a' && temp[0] <= 'z'))) {
                petFruitType = getFruitTypeByCode(temp);
            } else {
                petFruitType = getFruitTypeByName(temp);
            }
        }

        if(work) {
            if(petFruitType != FruitType::empty) {
                while(work) {
                    std::cout << "果實代碼: ";
                    std::cin >> temp;

                    if(std::cin.eof()) { // 使用者按下 Ctrl + Z (結束程式)
                        work = false;
                        break;
                    } else if(temp != "") {
                        petFruitCode = temp;
                        break;
                    }
                }
            } else {
                petFruitCode = "";
            }
        }

        if(work) {
            temp = p.getPetInfo(petType, petGene, 5, petFruitType, petFruitCode);

            if(temp != "")
                std::cout << "\n\n" << temp << "\n\n\n";
            else
                std::cout << "\n";
        }
    }

    system("pause");
    return 0;
}
