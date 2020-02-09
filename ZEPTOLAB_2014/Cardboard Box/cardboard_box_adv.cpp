#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>
#include <cstdint>
#include <inttypes.h>

const int MaxLevelsCount = 300000;

using namespace std;


struct BinarySkipListItem {
    static const int MaxSkipLists = 24;
    
    unsigned long long value;
    
    char nextSkeepItemCounter[MaxSkipLists];
    BinarySkipListItem *nextSkeepItem[MaxSkipLists];
    
    BinarySkipListItem() {
        for (int i = 0; i < MaxSkipLists; ++i) {
            nextSkeepItem[i] = nullptr;
            nextSkeepItemCounter[i] = 0;
        }
    }
};

struct BinarySkipList {
    BinarySkipListItem *getHead(){
        return head;
    };

    void addItem(BinarySkipListItem *listItem){
        if (!head) {
            head = listItem;
            return;
        }

        BinarySkipListItem *skeepItemHistory[BinarySkipListItem::MaxSkipLists];

        if (listItem->value < head->value) {
            listItem->nextSkeepItem[0] = head;
            for (int i = 1; i < BinarySkipListItem::MaxSkipLists; i++) {
                skeepItemHistory[i] = listItem;

                if (head->nextSkeepItem[i]) {
                    listItem->nextSkeepItem[i] = head->nextSkeepItem[i];
                }
                else {
                    listItem->nextSkeepItem[i] = head;
                }
                
                head->nextSkeepItem[i] = nullptr;

                listItem->nextSkeepItemCounter[i] = head->nextSkeepItemCounter[i];
                head->nextSkeepItemCounter[i] = 0;
            }
            incrementItemCounter(skeepItemHistory);
            head = listItem;
        }
        else if (head && !head->nextSkeepItem[0]) {
            for (int i = 0; i < BinarySkipListItem::MaxSkipLists; ++i) {
                head->nextSkeepItem[i] = listItem;
            }
        } else {
            BinarySkipListItem *currentSkipList = head;
            BinarySkipListItem *previousSkipList = nullptr;

            for (int i = activeSkipListNumber; i >= 0; i--) {
                previousSkipList = currentSkipList;
                while (currentSkipList && listItem->value >= currentSkipList->value) {
                    previousSkipList = currentSkipList;
                    currentSkipList = currentSkipList->nextSkeepItem[i];
                }

                currentSkipList = previousSkipList;
                skeepItemHistory[i] = currentSkipList;
            }
            
            listItem->nextSkeepItem[0] = currentSkipList->nextSkeepItem[0];
            currentSkipList->nextSkeepItem[0] = listItem;
            incrementItemCounter(skeepItemHistory);
        }
    };
        
    BinarySkipList() {
        head = nullptr;
        activeSkipListNumber = 1;
    }
    
    private:
    BinarySkipListItem *head;
    unsigned int activeSkipListNumber;
    
    void incrementItemCounter(BinarySkipListItem *skeepItemHistory[BinarySkipListItem::MaxSkipLists], int itemLevel = 1){
        if (itemLevel >= BinarySkipListItem::MaxSkipLists) {
            return;
        }
        
        skeepItemHistory[itemLevel]->nextSkeepItemCounter[itemLevel]++;
        if (skeepItemHistory[itemLevel]->nextSkeepItemCounter[itemLevel] == 3) {
            if (itemLevel > activeSkipListNumber) {
                activeSkipListNumber = itemLevel;
            }
            
            BinarySkipListItem *middleList = skeepItemHistory[itemLevel]->nextSkeepItem[itemLevel - 1]->nextSkeepItem[itemLevel - 1];
            
            middleList->nextSkeepItem[itemLevel] = skeepItemHistory[itemLevel]->nextSkeepItem[itemLevel];
            middleList->nextSkeepItemCounter[itemLevel] = 1;
            
            skeepItemHistory[itemLevel]->nextSkeepItem[itemLevel] = middleList;
            skeepItemHistory[itemLevel]->nextSkeepItemCounter[itemLevel] = 1;
            
            incrementItemCounter(skeepItemHistory, itemLevel + 1);
        }
    };

};


BinarySkipListItem one_star_time[MaxLevelsCount];
BinarySkipListItem two_star_time[MaxLevelsCount];
char usage[MaxLevelsCount];

int main()
{
    unsigned long long levels_count;
    unsigned long long requiered_stars_count;
    
    BinarySkipList one_star_time_list;
    BinarySkipList two_star_time_list;

    std::cin >> levels_count;
    std::cin >> requiered_stars_count;

    for (int i = 0; i < levels_count; i++) {
        scanf("%" PRId64 "  %" PRId64, &one_star_time[i].value, &two_star_time[i].value);

        usage[i] = 0;

        one_star_time_list.addItem(&one_star_time[i]);
        two_star_time_list.addItem(&two_star_time[i]);
    }
    
    // LevelDefinition *active_one_stars = head_prefered_one_stars;
    // LevelDefinition *active_two_stars = head_prefered_two_stars;
    
    unsigned long long total = 0;
    // while(requiered_stars_count) {
    //     while (active_two_stars && active_two_stars->usage) {
    //         active_two_stars = active_two_stars->next_prefered_two_stars;
    //     }
        
    //     while (active_one_stars && active_one_stars->usage) {
    //         active_one_stars = active_one_stars->next_prefered_one_stars;
    //     }
          
    //     if (!active_one_stars || !active_two_stars) {
    //         if (active_one_stars) {
    //             requiered_stars_count -= 1;
    //             total += active_one_stars->one_star_time;
    //             active_one_stars->usage = 1;
    //             active_one_stars = active_one_stars->next_prefered_one_stars;
    //             while (active_one_stars && active_one_stars->usage) {
    //                 active_one_stars = active_one_stars->next_prefered_one_stars;
    //             }
    //         } 
    //         else {
    //             requiered_stars_count -= (requiered_stars_count >= 2) ? 2 : 1;
    //             total += active_two_stars->two_star_time;
    //             active_two_stars->usage = 2;
    //             active_two_stars = active_two_stars->next_prefered_two_stars;
    //         }
    //     } 
    //     else if (requiered_stars_count > 1) {
    //         if (active_one_stars->one_star_time * 2 < active_two_stars->two_star_time) {
    //             requiered_stars_count -= 1;
    //             total += active_one_stars->one_star_time;
    //             active_one_stars->usage = 1;
    //             active_one_stars = active_one_stars->next_prefered_one_stars;
    //         }
    //         else {
    //             requiered_stars_count -= 2;
    //             total += active_two_stars->two_star_time;
    //             active_two_stars->usage = 2;
    //             active_two_stars = active_two_stars->next_prefered_two_stars;
    //         }
    //     } 
    //     else {
    //         if (active_one_stars->one_star_time < active_two_stars->two_star_time) {
    //             requiered_stars_count = 0;
    //             total += active_one_stars->one_star_time;
    //             active_one_stars->usage = 1;
    //         } 
    //         else {
    //             requiered_stars_count = 0;
    //             total += active_two_stars->two_star_time;
    //             active_two_stars->usage = 2;
    //         }
    //     }
    // }
    
    printf("%" PRId64 "\n", total);
    for (int i = 0; i < levels_count; i++) {
        printf("%u", usage[i]);
    }
    
    return 0;
}