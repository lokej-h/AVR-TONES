#ifndef LCD_TIME
#define LCD_TIME

#define TRUE 1
#define FALSE 0

#define CONVERT_TO_INT(x) (int)(x - '0')
#define CONVERT_TO_CHAR(x) (x + '0')

typedef struct {
	int sec ;
	int min ;
	int hour;
	int day ;
	int month;
	int year ;
	// int am ;
}current_time;

current_time ct;

void init_time();

void timeTick();

char* get_date_as_str(char* date);

char* get_time_as_str(char* time);

void update_seconds();

inline void colon_off();

inline void colon_on();

void lcd_write_time();

void js_test();

void timeChange(int button);

#endif // LCD_TIME