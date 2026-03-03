const std = @import("std");

fn print_rax(val: u64, msg: []const u8) void {
    // x: hexadecimal, 0: preencher com zero, >16: alinhar à direita com 16 dígitos
    std.debug.print("{s: <25} | Hex: 0x{x:0>16}\n", .{ msg, val });
}

pub fn main() !void {
    var r_rax: u64 = 0;

    // No Zig moderno, usamos a sintaxe "={rax}" para indicar que a saída 
    // da operação vai para o registrador RAX.

    // 1. Resetando RAX
    r_rax = asm volatile ("movq $0xFFFFFFFFFFFFFFFF, %%rax"
        : [ret] "={rax}" (-> u64),
    );
    print_rax(r_rax, "Valor Inicial (Todos F)");

    // 2. Alterando AL (8 bits inferiores)
    r_rax = asm volatile (
        \\ movb $0xAA, %%al
        : [ret] "={rax}" (-> u64),
    );
    print_rax(r_rax, "Após alterar AL (0xAA)");

    // 3. Alterando AH (bits 8-15)
    r_rax = asm volatile (
        \\ movb $0xBB, %%ah
        : [ret] "={rax}" (-> u64),
    );
    print_rax(r_rax, "Após alterar AH (0xBB)");

    // 4. Alterando AX (16 bits inferiores)
    r_rax = asm volatile (
        \\ movw $0x1234, %%ax
        : [ret] "={rax}" (-> u64),
    );
    print_rax(r_rax, "Após alterar AX (0x1234)");

    // 5. Alterando EAX (32 bits) - Observar o Zero-Extension
    r_rax = asm volatile (
        \\ movl $0xEEEEEEEE, %%eax
        : [ret] "={rax}" (-> u64),
    );
    print_rax(r_rax, "Após alterar EAX (Zeroing)");
}
