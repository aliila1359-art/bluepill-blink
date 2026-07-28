// تعریف آدرس‌های رجیستری STM32F103 بدون نیاز به فایل‌های خارجی
#define RCC_APB2ENR   (*(volatile unsigned int*) 0x40021018)
#define GPIOC_CRH     (*(volatile unsigned int*) 0x40011004)
#define GPIOC_BSRR    (*(volatile unsigned int*) 0x40011010)

void delay(volatile unsigned int count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    // فعال‌سازی کلاک پورت C (بیت 4 رجیستری APB2ENR)
    RCC_APB2ENR |= (1 << 4);

    // تنظیم پین PC13 به عنوان خروجی (پاک کردن بیت‌های 20 تا 23 و قرار دادن مقدار 2)
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    while (1) {
        // روشن کردن LED (صفر کردن پین 13 با استفاده از بخش ریست BSRR)
        GPIOC_BSRR = (1 << (13 + 16));
        delay(500000);

        // خاموش کردن LED (یک کردن پین 13)
        GPIOC_BSRR = (1 << 13);
        delay(500000);
    }
}
