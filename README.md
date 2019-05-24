# STM32DateTime

to use this lib you should be enable C99 Mode and Add --cpp to misc controls (in options for target --> C/C++ tab)

then you can add library to your project and use it (this Lib created on FreeRTOS and you can remove #include "cmsis_os.h" and replace osDelay to use without FreeRTOS)

#include "DateTime.h"

DateTime _dt;


and then use :

		DateTime(int16_t _year = 0,int8_t _month = 1,int8_t _day = 1,int8_t _hour = 0,int8_t _min = 0,int8_t _sec = 0);
		void setCurrentDateTime(RTC_HandleTypeDef *_hrtc);
		void setDateTime(int16_t _year,int8_t _month,int8_t _day,int8_t _hour,int8_t _min,int8_t _sec);
		void setDate(uint16_t _year,int8_t _month,int8_t _day);
		void setTime(int8_t _Sec,int8_t _Min,int8_t _hour);
		void setUnixTime(uint64_t _UnixTime);
	
		void setYear(int16_t _year);
		void setMonth(int8_t _month);
		void setDay(int8_t _day);
		void setDayOfWeek(int8_t _dow);
	
		void setHour(int8_t _hour);
		void setMinute(int8_t _min);
		void setSecond(int8_t _sec);
	
		void getCurrentDateTime(RTC_HandleTypeDef *_hrtc);
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
		
		void setLocalTime(int8_t _hour,int8_t _min,bool _sign);
		bool getLocalTime(int8_t *_hour,int8_t *_min);

		void addSecond(int16_t _sec);
		void addMinute(int16_t _min);
		void addHour(int16_t _hour);

		void addDay(int16_t _day);
		void addMonth(int16_t _month);
		void addYear(int16_t _year);
		
		DateTime operator=(DateTime _dt);
		DateTime operator+(DateTime _dt);
		DateTime operator+=(DateTime _dt);
		bool operator==(DateTime _dt);
		bool operator!=(DateTime _dt);
		bool operator<(DateTime _dt);
		bool operator<=(DateTime _dt);
		bool operator>(DateTime _dt);
		bool operator>=(DateTime _dt);
