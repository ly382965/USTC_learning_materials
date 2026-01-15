unsigned char inb(unsigned short int port_from)
{
    char value;
    __asm__ __volatile__("inb %w1, %0"
                         : "=a"(value)
                         : "Nd"(port_from));
    return value;
}

void outb(unsigned short int port_to, unsigned char value)
{
    __asm__ __volatile__("outb %b0, %w1" ::"a"(value), "Nd"(port_to));
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
}