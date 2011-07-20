/* 
 * File:   main.c
 * Author: Роман
 *
 * Created on 19 Июль 2011 г., 23:26
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
 
inline uint64_t rdtsc()
{
    uint32_t lo, hi;
    /*
    * cpuid will serialize the following rdtsc with respect to all other
    * instructions the processor may be handling.
    */
    __asm__ __volatile__ (
     "xorl %%eax, %%eax\n"
     "cpuid\n"
     "rdtsc\n"
     : "=a" (lo), "=d" (hi)
     :
     : "%ebx", "%ecx");
    return (uint64_t)hi << 32 | lo;
}

int main(int argc, char** argv)
{
    
    uint64_t r;
    int i;
    char command[35];
    
    r=rdtsc();
    sprintf(command,"echo \"Time: %lld \" > ~/time.res",r);
    system(command);
    
    return (EXIT_SUCCESS);
}

