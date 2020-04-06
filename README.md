# STM32DateTime

to use this lib you should be enable C99 Mode and Add --cpp to misc controls (in options for target --> C/C++ tab)

then you can add library to your project and use it (this Lib created on FreeRTOS and you can remove #include "cmsis_os.h" and replace osDelay to use without FreeRTOS)

#include "DateTime.h"

DateTime _dt;


and then use :

		DateTime(uint16_t _year = 0,uint8_t _month = 1,uint8_t _day = 1,uint8_t _hour = 0,uint8_t _min = 0,uint8_t _sec = 0);
#ifdef HAL_RTC_MODULE_ENABLED
		void setCurrentDateTime(RTC_HandleTypeDef *_hrtc);
#endif
		void setDateTime(uint16_t _year,uint8_t _month,uint8_t _day,uint8_t _hour,uint8_t _min,uint8_t _sec);
		void setDate(uint16_t _year,uint8_t _month,uint8_t _day);
		void setTime(uint8_t _Sec,uint8_t _Min,uint8_t _hour);
		void setUnixTime(uint64_t _UnixTime,bool _IsUTCTime = false);
	
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
		const char *getDayOfWeekStr(StringDyOfWeekSize _SDOWS = Short);
		uint64_t getUnixTime(bool _IsUTCTime = false);
	
		uint8_t getHour();
		uint8_t getMinute();
		uint8_t getSecond();
	
		int8_t getYearFrom2000();
		
		void setLocalTime(int32_t _LocalOffset);
		int32_t getLocalTime(void);
		
		uint32_t getSecsInDay(void);

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
