#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>

const int MaxLevelsCount = 300000;

using namespace std;

struct LevelDefinition {
    unsigned long long one_star_time;
    unsigned long long two_star_time;
    char usage;
    
    LevelDefinition *next_prefered_one_stars;
    LevelDefinition *next_prefered_two_stars;
};

int main()
{
    unsigned long long levels_count;
    unsigned long long requiered_stars_count;
    
    LevelDefinition levels[MaxLevelsCount];
    LevelDefinition *root_prefered_one_stars = NULL;
    LevelDefinition *root_prefered_two_stars = NULL;
    
    std::cin >> levels_count;
    std::cin >> requiered_stars_count;
    
    scanf("%I64d %I64d", &levels[0].one_star_time, &levels[0].two_star_time);
    levels[0].usage = 0;
    
    levels[0].next_prefered_one_stars = NULL;
    levels[0].next_prefered_two_stars = NULL;
    
    root_prefered_one_stars = &levels[0];
    root_prefered_two_stars = &levels[0];
    
    for (int i = 1; i < levels_count; i++) {
        scanf("%I64d %I64d", &levels[i].one_star_time, &levels[i].two_star_time);
        levels[i].usage = 0;
        
        levels[i].next_prefered_one_stars = NULL;
        levels[i].next_prefered_two_stars = NULL;
        
        if (levels[i].one_star_time < root_prefered_one_stars->one_star_time) {
            levels[i].next_prefered_one_stars = root_prefered_one_stars;
            root_prefered_one_stars = &levels[i];
        }
        else {
            LevelDefinition *previousLevel = NULL;
            LevelDefinition *currentLevel = root_prefered_one_stars;
            while (currentLevel) {
                if (levels[i].one_star_time < currentLevel->one_star_time) {
                    levels[i].next_prefered_one_stars = previousLevel->next_prefered_one_stars;
                    previousLevel->next_prefered_one_stars = &levels[i];
                    break;
                }
                else {
                    previousLevel = currentLevel;
                    currentLevel = currentLevel->next_prefered_one_stars;
                }
            }
            
            if (!currentLevel) {
                previousLevel->next_prefered_one_stars = &levels[i];
            }
        }
        
        if (levels[i].two_star_time < root_prefered_two_stars->two_star_time) {
            levels[i].next_prefered_two_stars = root_prefered_two_stars;
            root_prefered_two_stars = &levels[i];
        }
        else {
            LevelDefinition *previousLevel = NULL;
            LevelDefinition *currentLevel = root_prefered_two_stars;
            while (currentLevel) {
                if (levels[i].two_star_time < currentLevel->two_star_time) {
                    levels[i].next_prefered_two_stars = previousLevel->next_prefered_two_stars;
                    previousLevel->next_prefered_two_stars = &levels[i];
                    break;
                }
                else {
                    previousLevel = currentLevel;
                    currentLevel = currentLevel->next_prefered_two_stars;
                }
            }
            
            if (!currentLevel) {
                previousLevel->next_prefered_two_stars = &levels[i];
            }
        }
    }
    
    LevelDefinition *active_one_stars = root_prefered_one_stars;
    LevelDefinition *active_two_stars = root_prefered_two_stars;
    
    unsigned long long total = 0;
    while(requiered_stars_count) {
        while (active_two_stars && active_two_stars->usage) {
            active_two_stars = active_two_stars->next_prefered_two_stars;
        }
        
        while (active_one_stars && active_one_stars->usage) {
            active_one_stars = active_one_stars->next_prefered_one_stars;
        }
          
        if (!active_one_stars || !active_two_stars) {
            if (active_one_stars) {
                requiered_stars_count -= 1;
                total += active_one_stars->one_star_time;
                active_one_stars->usage = 1;
                active_one_stars = active_one_stars->next_prefered_one_stars;
                while (active_one_stars && active_one_stars->usage) {
                    active_one_stars = active_one_stars->next_prefered_one_stars;
                }
            } 
            else {
                requiered_stars_count -= (requiered_stars_count >= 2) ? 2 : 1;
                total += active_two_stars->two_star_time;
                active_two_stars->usage = 2;
                active_two_stars = active_two_stars->next_prefered_two_stars;
            }
        } 
        else if (requiered_stars_count > 1) {
            if (active_one_stars->one_star_time * 2 < active_two_stars->two_star_time) {
                requiered_stars_count -= 1;
                total += active_one_stars->one_star_time;
                active_one_stars->usage = 1;
                active_one_stars = active_one_stars->next_prefered_one_stars;
            }
            else {
                requiered_stars_count -= 2;
                total += active_two_stars->two_star_time;
                active_two_stars->usage = 2;
                active_two_stars = active_two_stars->next_prefered_two_stars;
            }
        } 
        else {
            if (active_one_stars->one_star_time < active_two_stars->two_star_time) {
                requiered_stars_count = 0;
                total += active_one_stars->one_star_time;
                active_one_stars->usage = 1;
            } 
            else {
                requiered_stars_count = 0;
                total += active_two_stars->two_star_time;
                active_two_stars->usage = 2;
            }
        }
    }
    
    printf("%I64d\n", total);
    for (int i = 0; i < levels_count; i++) {
        printf("%d", levels[i].usage);
    }
    
    return 0;
}