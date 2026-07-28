#include "stm32f1xx.h"

// یک تاخیر ساده نرم‌افزاری
void delay(volatile uint32_t count) {
    while (count--) {
        __NOP();
    }
}

int main(void) {
    // فعال‌سازی کلاک برای پورت C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // تنظیم پین PC13 به عنوان خروجی پوش-پول (Push-Pull Output) با سرعت 2MHz
    // در رجیستری CRH، پین 13 مربوط به بیت‌های 20 تا 23 است
    GPIOC->CRH &= ~(0xF << 20); // پاک کردن تنظیمات قبلی
    GPIOC->CRH |=  (0x2 << 20); // خروجی با سرعت 2MHz

    while (1) {
        // روشن کردن LED (در برد بلوپیل معمولاً با صفر شدن منطقی پین PC13 روشن می‌شود)
        GPIOC->BSRR = (1 << (13 + 16)); // ریست کردن بیت 13 (Low)
        delay(500000);

        // خاموش کردن LED (یک شدن منطقی پین PC13)
        GPIOC->BSRR = (1 << 13); // ست کردن بیت 13 (High)
        delay(500000);
    }
}
