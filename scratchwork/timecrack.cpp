#include <stdlib.h>
#include <string>
#include <time.h>
#include <stdio.h>

std::string curiousClock(std::string someTime, std::string leavingTime) {
    struct tm reversestruct{};
    struct tm leavingstruct{};
    strptime(someTime.c_str(), "%Y-%m-%d %H:%M", &reversestruct);
    //reversestruct.tm_isdst = -1;
    strptime(leavingTime.c_str(), "%Y-%m-%d %H:%M", &leavingstruct);
    //leavingstruct.tm_isdst = -1;
    
    
    printf("%d %d %d %d %d\n", reversestruct.tm_year,
          reversestruct.tm_mon,
          reversestruct.tm_mday,
          reversestruct.tm_hour,
          reversestruct.tm_min);
    printf("%d %d %d %d %d\n", leavingstruct.tm_year,
          leavingstruct.tm_mon,
          leavingstruct.tm_mday,
          leavingstruct.tm_hour,
          leavingstruct.tm_min);
    
    time_t reverse = mktime(&reversestruct);
    
        printf("%d %d %d %d %d\n", reversestruct.tm_year,
          reversestruct.tm_mon,
          reversestruct.tm_mday,
          reversestruct.tm_hour,
          reversestruct.tm_min);
    printf("%d %d %d %d %d\n", leavingstruct.tm_year,
          leavingstruct.tm_mon,
          leavingstruct.tm_mday,
          leavingstruct.tm_hour,
          leavingstruct.tm_min);
    
    time_t leaving = mktime(&leavingstruct);
    
        printf("%d %d %d %d %d\n", reversestruct.tm_year,
          reversestruct.tm_mon,
          reversestruct.tm_mday,
          reversestruct.tm_hour,
          reversestruct.tm_min);
    printf("%d %d %d %d %d\n", leavingstruct.tm_year,
          leavingstruct.tm_mon,
          leavingstruct.tm_mday,
          leavingstruct.tm_hour,
          leavingstruct.tm_min);
    
    printf("%lu\n", leaving);
    
    if(reverse >= leaving) {
        printf("%lu %lu\n", reverse, leaving);
        return leavingTime;
    } else {
        printf("%lu %lu\n", reverse, leaving);
        time_t returntime = reverse-(leaving-reverse);
        //returntime -= 60*4;
        char *ret = (char *)malloc(17);
        strftime(ret,17,"%Y-%m-%d %H:%M",localtime(&returntime));
        return ret;
    }
}

int main() {
	curiousClock("2016-08-26 22:40","2016-08-26 22:41");
}

