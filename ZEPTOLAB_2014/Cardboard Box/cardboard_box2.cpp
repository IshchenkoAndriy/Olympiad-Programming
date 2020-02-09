#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>
#include <cstdint>
#include <inttypes.h>

const int MaxLevelsCount = 300000;

using namespace std;

struct LevelDefinition {
    unsigned long long one_star_time;
    unsigned long long two_star_time;
    char usage;
    
    LevelDefinition *next_prefered_one_stars;
    LevelDefinition *prev_prefered_one_stars;

    LevelDefinition *next_prefered_two_stars;
};

LevelDefinition levels[MaxLevelsCount];

int main()
{
    unsigned long long levels_count;
    unsigned long long requiered_stars_count;

    LevelDefinition *head_prefered_one_stars = NULL;
    LevelDefinition *head_prefered_two_stars = NULL;

    LevelDefinition *middle_prefered_one_stars = NULL;
    LevelDefinition *middle_prefered_two_stars = NULL;

    int middle_prefered_one_stars_balancer = 0;
    int middle_prefered_two_stars_balancer = 0;

    LevelDefinition *tail_prefered_one_stars = NULL;
    LevelDefinition *tail_prefered_two_stars = NULL;
    
    std::cin >> levels_count;
    std::cin >> requiered_stars_count;
    
    scanf("%" PRId64 "  %" PRId64, &levels[0].one_star_time, &levels[0].two_star_time);
    levels[0].usage = 0;
    
    levels[0].next_prefered_one_stars = NULL;
    levels[0].prev_prefered_one_stars = NULL;
    levels[0].next_prefered_two_stars = NULL;
    
    head_prefered_one_stars = &levels[0];
    head_prefered_two_stars = &levels[0];
    
    middle_prefered_one_stars = head_prefered_one_stars;
    middle_prefered_two_stars = head_prefered_two_stars;

    tail_prefered_one_stars = head_prefered_one_stars;
    tail_prefered_two_stars = head_prefered_two_stars;

    for (int i = 1; i < levels_count; i++) {
        scanf("%" PRId64 "  %" PRId64, &levels[i].one_star_time, &levels[i].two_star_time);
        levels[i].usage = 0;
        
        levels[i].next_prefered_one_stars = NULL;
        levels[i].prev_prefered_one_stars = NULL;
        levels[i].next_prefered_two_stars = NULL;
        
        if (levels[i].one_star_time < head_prefered_one_stars->one_star_time) {
            levels[i].next_prefered_one_stars = head_prefered_one_stars;
            head_prefered_one_stars->prev_prefered_one_stars = &levels[i];
            head_prefered_one_stars = &levels[i];
        }
        else if (levels[i].one_star_time >= tail_prefered_one_stars->one_star_time) {
            tail_prefered_one_stars->next_prefered_one_stars = &levels[i];
            levels[i].prev_prefered_one_stars = tail_prefered_one_stars;
            tail_prefered_one_stars = &levels[i];
        }
        else {
            LevelDefinition *previousLevel = NULL;
            LevelDefinition *currentLevel = NULL;

            if (levels[i].one_star_time >= middle_prefered_one_stars->one_star_time) {
                currentLevel = middle_prefered_one_stars;
                middle_prefered_one_stars_balancer++;
            } else {
                currentLevel = head_prefered_one_stars;
                middle_prefered_one_stars_balancer--;
            }

            while (currentLevel) {
                if (levels[i].one_star_time < currentLevel->one_star_time) {
                    levels[i].next_prefered_one_stars = previousLevel->next_prefered_one_stars;
                    previousLevel->next_prefered_one_stars = &levels[i];

                    levels[i].prev_prefered_one_stars = previousLevel;
                    currentLevel->prev_prefered_one_stars = &levels[i];
                    break;
                }
                else {
                    previousLevel = currentLevel;
                    currentLevel = currentLevel->next_prefered_one_stars;
                }
            }
            
            if (middle_prefered_one_stars_balancer >= 2) {
                middle_prefered_one_stars = middle_prefered_one_stars->next_prefered_one_stars;
                middle_prefered_one_stars_balancer = 0;
            } 
            else if (middle_prefered_one_stars_balancer <= -2) {
                middle_prefered_one_stars = middle_prefered_one_stars->prev_prefered_one_stars;
                middle_prefered_one_stars_balancer = 0;
            }

            if (!currentLevel) {
                previousLevel->next_prefered_one_stars = &levels[i];
                levels[i].prev_prefered_one_stars = previousLevel;
            }
        }
        
        if (levels[i].two_star_time < head_prefered_two_stars->two_star_time) {
            levels[i].next_prefered_two_stars = head_prefered_two_stars;
            head_prefered_two_stars = &levels[i];
        }
        else if (levels[i].two_star_time >= head_prefered_two_stars->two_star_time) {
            tail_prefered_two_stars->next_prefered_two_stars = &levels[i];
            tail_prefered_two_stars = &levels[i];
        }
        else {
            LevelDefinition *previousLevel = NULL;
            LevelDefinition *currentLevel = (levels[i].two_star_time >= head_prefered_two_stars->two_star_time) ? head_prefered_two_stars : head_prefered_two_stars;
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
    
    LevelDefinition *active_one_stars = head_prefered_one_stars;
    LevelDefinition *active_two_stars = head_prefered_two_stars;
    
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
    
    printf("%" PRId64 "\n", total);
    for (int i = 0; i < levels_count; i++) {
        printf("%d", levels[i].usage);
    }
    
    return 0;
}