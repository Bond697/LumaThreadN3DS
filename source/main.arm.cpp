#include "types.h"
#include "process9.h"
#include "rt.h"

#include <string.h>
#include <stdlib.h>


u32 fh[8];

bool KeysPressed(u32 keymask);
u16 GetKeysDown();
void RunningThread();
void FileSeek(u32* file_handle, s64 offset);


int main() __attribute__ ((naked, section (".init")));
int main()
{
    __asm("push {r4-r7 , lr}      \n\t"
          "sub sp, sp, #8         \n\t"
	      "bl call_cp15		      \n\t"
          );

    __asm("MOV     R3, #63                    \n\t"
          "STR     R3, [SP]                   \n\t"
          "LDR     R3, =0xFFFFFFFE            \n\t"
          "STR     R3, [SP, #4]               \n\t"
          "LDR     R0, =0x1FFFFFC             \n\t"
          "LDR     R1, =_Z13RunningThreadv    \n\t"
          "MOV     R2, #0                     \n\t"
          "LDR     R7, =CreateThread          \n\t"
          "LDR     R3, =0x1FFFFF8             \n\t"
          "BLX     R7                         \n\t"
          );

    __asm("add sp, sp, #8         \n\t"
          "pop {r4-r7}            \n\t"
          "pop {r0}               \n\t"
          "mov lr, r0             \n\t"
          "ldr r0, =0x080E3448    \n\t"  //80CB3C8 o3ds
          "ldr r1, =0x08085270    \n\t"  //8085274
          "bx r1                  \n\t"
          );

}


void RunningThread()
{
    memset(fh, 0, sizeof(fh));
    u32 bytes;

    while (1)
    {
        if ( KeysPressed(KEY_L | KEY_A) )
        {
            
			FileOpen(fh, L"sdmc:/dump_arm9.bin", MODE_WRITE | MODE_CREATE);
			FileWrite(fh, &bytes, (u32*)0x8000000, 0x180000, 1);
			FileClose(fh);

			memset(fh, 0, 0x20);

            FileOpen(fh, L"sdmc:/dump_axi.bin", MODE_WRITE | MODE_CREATE);
            FileWrite(fh, &bytes, (u32*)0x1FF80000, 0x80000, 1);
            FileClose(fh);

            memset(fh, 0, 0x20);

            FileOpen(fh, L"sdmc:/dump_axi_new.bin", MODE_WRITE | MODE_CREATE);
            FileWrite(fh, &bytes, (u32*)0x1F000000, 0x400000, 1);
            FileClose(fh);

			memset(fh, 0, 0x20);

			FileOpen(fh, L"sdmc:/dump_fcram.bin", MODE_WRITE | MODE_CREATE);
			FileWrite(fh, &bytes, (u32*)0x20000000, 0x10000000, 1);
			FileClose(fh);

        }
        __asm("ldr r0, =0x80000    \n\t"
              "mov r1, #0          \n\t"
              "svc 0x0A            \n\t");
    }
    __asm("svc 0x09");
}


u16 GetKeysDown()
{
    return PAD_REG ^ KEY_MASK;
}


bool KeysPressed(u32 keymask)
{
    return !(PAD_REG & keymask);
}


void FileSeek(u32* file_handle, s64 offset)
{
    *(s64*)&file_handle[4] = offset;
}