#include <stdio.h>
#include <stdint.h>

void print_rax(uint64_t val, const char* msg) {
    printf("%-25s | Hex: 0x%016lx\n", msg, val);
}

int main() {
    uint64_t r_rax;

    // 1. Resetando RAX para um valor base (todos bits em 1)
    asm ("movq $0xFFFFFFFFFFFFFFFF, %%rax" : : : "rax");
    asm ("movq %%rax, %0" : "=r" (r_rax));
    print_rax(r_rax, "Valor Inicial (Todos F)");

    // 2. Alterando AL (8 bits inferiores) para 0xAA
    asm ("movb $0xAA, %%al" : : : "rax");
    asm ("movq %%rax, %0" : "=r" (r_rax));
    print_rax(r_rax, "Após alterar AL (0xAA)");

    // 3. Alterando AH (bits 8-15) para 0xBB
    asm ("movb $0xBB, %%ah" : : : "rax");
    asm ("movq %%rax, %0" : "=r" (r_rax));
    print_rax(r_rax, "Após alterar AH (0xBB)");

    // 4. Alterando AX (16 bits inferiores) para 0x1234
    // Isso deve sobrescrever o que fizemos no AL e AH
    asm ("movw $0x1234, %%ax" : : : "rax");
    asm ("movq %%rax, %0" : "=r" (r_rax));
    print_rax(r_rax, "Após alterar AX (0x1234)");

    // 5. Curiosidade: O que acontece se alterar EAX (32 bits)?
    // No x86_64, mover para um registrador de 32 bits ZERA os 32 bits superiores!
    asm ("movl $0xEEEEEEEE, %%eax" : : : "rax");
    asm ("movq %%rax, %0" : "=r" (r_rax));
    print_rax(r_rax, "Após alterar EAX (Zeroing)");

    return 0;
}
