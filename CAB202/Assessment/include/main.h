extern volatile uint8_t leftSeg;
extern volatile uint8_t rightSeg;
extern volatile uint8_t sequenceSelected;
extern volatile uint8_t nextDuration;
extern volatile uint8_t currentDurationLeft;

typedef enum {
    START,
    SEQUENCING,
    NEXT,
    STOP,
    STOPPED,
    PAUSED,
    ADVANCE,
    TEST,
} sequenceStatus;

volatile sequenceStatus sequenceState;

void setSegSequence(void);
void setNextStep(void);