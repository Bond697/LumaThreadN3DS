#ifndef PROC9_H
#define PROC9_H


const Handle CURRENT_PROCESS_PSEUDOHANDLE   = 0xFFFF8001;
const Handle CURRENT_THREAD_PSEUDOHANDLE    = 0xFFFF8000;

const u32 CURRENT_THREAD_OBJECT_PTR         = 0x8000040;
const u32 CURRENT_PROCESS_OBJECT_PTR        = 0x8000044;
const u32 CURRENT_SCHEDULER_OBJECT_PTR      = 0x8000048;


enum ResetType
{
    RESET_TYPE_ONESHOT  = 0x0,
    RESET_TYPE_STICKY   = 0x1,
    RESET_TYPE_PULSE    = 0x2,
    RESET_TYPE_MAX_BIT  = 0x80000000,
};

enum FileMode
{
    MODE_READ      = BIT(0),  
    MODE_WRITE     = BIT(1),  
    MODE_CREATE    = BIT(2)   
};


struct arm9FILE {

    u32     s1;
    u32     s2;
    u32     s3;
    void*   s4;
    s64     offset;
    u32     s5;
    u32     s6;

};


extern "C" {
 
    Result FileOpen(u32* handle, wchar_t* path, bit32 openflags);
    Result FileClose(u32* handle);
    Result FileWrite(u32* handle, u32* bytes_written, void* buf, u32 size, bit32 flushflag);
    Result FileRead(u32* handle, u32* bytes_read, void* buf, u32 size);
    Result FileGetSize(u32* handle, s32* size);

    Result CreateThread(Handle* hthread, ThreadFn entrypoint, u32 arg, u32 stacktop, u32 threadpriority, u32 processorid);
    
}


#endif