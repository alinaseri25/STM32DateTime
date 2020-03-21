#ifndef DateTime_H
#define DateTime_H

#include "stm32f1xx_hal.h"
//#include "cmsis_os.h"

const uint8_t milmonth[12]={
	31,28,31,30,31,30,31,31,30,31,30,31
};

typedef enum
{
	Full = 0x00,
	Short
}StrinDyOfWeekSize;

class DateTime
{
	public:
		DateTime(uint16_t _year = 0,uint8_t _month = 1,uint8_t _day = 1,uint8_t _hour = 0,uint8_t _min = 0,uint8_t _sec = 0);
#ifdef HAL_RTC_MODULE_ENABLED
		void setCurrentDateTime(RTC_HandleTypeDef *_hrtc);
#endif
		void setDateTime(uint16_t _year,uint8_t _month,uint8_t _day,uint8_t _hour,uint8_t _min,uint8_t _sec);
		void setDate(uint16_t _year,uint8_t _month,uint8_t _day);
		void setTime(uint8_t _Sec,uint8_t _Min,uint8_t _hour);
		void setUnixTime(uint64_t _UnixTime);
	
		void setYear(uint16_t _year);
		void setMonth(uint8_t _month);
		void setDay(uint8_t _day);
		void setDayOfWeek(uint8_t _dow);
	
		void setHour(uint8_t _hour);
		void setMinute(uint8_t _min);
		void setSecond(uint8_t _sec);
	
#ifdef HAL_RTC_MODULE_ENABLED
		void getCurrentDateTime(RTC_HandleTypeDef *_hrtc);
#endif
		uint16_t getYear();
		uint8_t getMonth();
		uint8_t getDay();
		uint8_t getDayOfWeek();
		const char *getDayOfWeekStr(StrinDyOfWeekSize _SDOWS = Short);
		uint64_t getUnixTime(void);
	
		uint8_t getHour();
		uint8_t getMinute();
		uint8_t getSecond();
	
		int8_t getYearFrom2000();
		
		void setLocalTime(int32_t _LocalOffset);
		int32_t getLocalTime(void);

		void addSecond(uint16_t _sec);
		void addMinute(uint16_t _min);
		void addHour(uint16_t _hour);

		void addDay(uint16_t _day);
		void addMonth(uint16_t _month);
		void addYear(uint16_t _year);
		
		DateTime operator=(DateTime _dt);
		DateTime operator+(DateTime _dt);
		DateTime operator+=(DateTime _dt);
		bool operator==(DateTime _dt);
		bool operator!=(DateTime _dt);
		bool operator<(DateTime _dt);
		bool operator<=(DateTime _dt);
		bool operator>(DateTime _dt);
		bool operator>=(DateTime _dt);

	private:
		void DateTimeToUnix(void);
		void UnixToDateTime(void);
	
		uint8_t Second;
		uint8_t Minute;
		uint8_t Hour;
	
		uint8_t Day;
		uint8_t Month;
		uint16_t Year;
		uint8_t DayofWeek;

		int32_t LocalOffset;
	
		uint64_t UnixDateTime;

};

#endif
