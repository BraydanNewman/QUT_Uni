void next(void);
void descramble(volatile uint8_t* a);
uint32_t decode(const char a, const char b, const char c, const char d);
static const unsigned char base64_table[65];
extern volatile uint32_t state;
uint8_t indexInTable(const char a);