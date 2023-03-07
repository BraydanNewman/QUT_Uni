; n11272031

init:
    ldi r16, 8
    push r16
    ldi r16, 0
    push r16
    ldi r16, 153
    push r16
    ldi r16, 8
    mov r8, r16
    ldi r16, 9
    mov r9, r16
    ldi r16, 10
    mov r10, r16
    ldi r16, 11
    mov r11, r16
    ldi r16, 12
    mov r12, r16
    ldi r16, 13
    mov r13, r16
    ldi r16, 14
    mov r14, r16
    ldi r16, 15
    mov r15, r16
    ldi r16, 0x08
    sts 0x0417, r16
    ldi r16, 0
    rjmp init_done
some_procedure_00:
    sts 0x3401, r8
    ret
some_procedure_01:
    sts 0x3401, r9
    ret
some_procedure_02:
    sts 0x3401, r10
    ret
some_procedure_03:
    sts 0x3401, r11
    ret
some_procedure_04:
    sts 0x3401, r12
    ret
some_procedure_05:
    sts 0x3401, r13
    ret
some_procedure_06:
    sts 0x3401, r14
    ret
some_procedure_07:
    sts 0x3401, r15
    ret
some_procedure_08:
    push r16
    in r16, 0x3F
    push r16
    lds r16, 0x3400
    inc r16
    sts 0x3400, r16
    pop r16
    out 0x3F, r16
    pop r16
    ret
flash_led:
    call toggle_led
    rcall delay_500ms
    call toggle_led
    rcall delay_500ms
    call toggle_led
    rcall delay_500ms
    call toggle_led
    rcall delay_500ms
    call toggle_led
    rcall delay_500ms
    call toggle_led
    ret
delay_500ms:
    push r25
    push r24
    in r24, 0x3F
    push r24
    ldi r25, hi8(2082)
    ldi r24, lo8(2082)
delay_500ms_loop:
    push r24
    push r25
    call delay
    pop r25
    pop r24
    sbiw r24, 1
    brne delay_500ms_loop
    pop r24
    out 0x3F, r24
    pop r24
    pop r25
    ret
init_done:

