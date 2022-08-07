; Configures TCA0 to drive buzzer (see Ex 3.6)
ldi r16, 0x11
sts 0x0A01, r16      ; FRQ mode, WO0 enabled
ldi r16, 0x20
sts 0x0A29, r16      ; 16384 counts = ~200 Hz   
ldi r16, 0x01
sts 0x0A00, r16      ; Enable
; End TCA0 configuration

