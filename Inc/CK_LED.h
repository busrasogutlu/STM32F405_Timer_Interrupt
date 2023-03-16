
#ifndef CK_LED_H_
#define CK_LED_H_

// Changing duty cycle for fix freq. gives shining effect.
#define SHINE_EFFECT1      250
#define SHINE_EFFECT2      500
#define SHINE_EFFECT3      750
#define SHINE_EFFECT4      1000
#define SHINE_EFFECT5      1250
#define SHINE_EFFECT6      1500
#define SHINE_EFFECT7      1750
#define SHINE_EFFECT8      2000

// Changing freq. for fix cycle gives blink effect.
#define BLINK_EFFECT1Hz      1  // 1Hz
#define BLINK_EFFECT3Hz      3  // 3Hz
#define BLINK_EFFECT5Hz      5  // 5Hz
#define BLINK_EFFECT10Hz     10 // 10Hz
#define BLINK_EFFECT25Hz     25 // 25Hz

void CK_LED_Init(void);

void CK_LED_ChangeFrequency(int freq);

void CK_LED_SetDutyCycle(int dty);

void CK_LED_ShineEffect(int cycle);

void CK_LED_BlinkEffect(int freq);


#endif /* CK_LED_H_ */
