typedef void (*func_ptr)(void);

extern void main(void);
extern unsigned int _sidata, _data, _edata, _sbss, _ebss;

void Reset_Handler(void) {
    unsigned int *src = &_sidata;
    unsigned int *dst = &_data;
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }
    main();
}

__attribute__((section(".isr_vector")))
func_ptr vector_table[] = {
    (func_ptr)0x20005000, // Stack Pointer
    (func_ptr)Reset_Handler
};
