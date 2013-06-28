/*
 * Copyright (C) by Grant Foudree <grant907@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * NOTICE:
 *  This was copied from the Minix OS project minix\sys\sys\bootblock.h
 *  The license for the copied data below is as follows:
 *
 *
    License

    Copyright (c) 1987, 1997, 2006, Vrije Universiteit, Amsterdam,
    The Netherlands All rights reserved. Redistribution and use of the MINIX 3
    operating system in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

        * Neither the name of the Vrije Universiteit nor the names of the
        software authors or contributors may be used to endorse or promote
        products derived from this software without specific prior written
        permission.

        * Any deviations from these conditions require written permission
        from the copyright holder in advance


    Disclaimer

     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
     CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
     INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
     MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
     NO EVENT SHALL PRENTICE HALL OR ANY AUTHORS OR CONTRIBUTORS BE LIABLE
     FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
     WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
     OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
     ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


    Aggregated Software

    In addition to MINIX 3 itself, the distribution CD-ROM and this Website
    contain additional software that is not part of MINIX 3 and is not
    covered by this license. The licensing conditions for this additional
    software are stated in the various packages. In particular, some of the
    additional software falls under the GPL, and you must take care to
    observe the conditions of the GPL with respect to this software. As
    clearly stated in Article 2 of the GPL, when GPL and nonGPL software are
    distributed together on the same medium, this aggregation does not cause
    the license of either part to apply to the other part.


    Acknowledgements

    This product includes software developed by the University of
    California, Berkeley and its contributors.

    This product includes software developed by Softweyr LLC, the
    University of California, Berkeley, and its contributors.


 */

/*
 * Layout of boot records:
 *
 *	Byte range	Use	Description
 *	----------	---	-----------
 *
 *	0 - 2		FMP	JMP xxx, NOP
 *	3 - 10		FP	OEM Name
 *
 *	11 - 61		FMP	FAT12/16 BPB
 *				Whilst not strictly necessary for MBR,
 *				GRUB reserves this area
 *
 *	11 - 89		P	FAT32 BPB
 *				(are we ever going to boot off this?)
 *
 *
 *	62 - 217	FMP	Boot code
 *
 *	90 - 217	P	FAT32 boot code
 *
 *	218 - 223	M	Win95b/98/me "drive time"
 *		http://www.geocities.com/thestarman3/asm/mbr/95BMEMBR.htm#MYST
 *				only changed if all 6 bytes are 0
 *
 *	224 - 436	FMP	boot code (continued)
 *
 *	437 - 439	M	WinNT/2K/XP MBR "boot language"
 *		http://www.geocities.com/thestarman3/asm/mbr/Win2kmbr.htm
 *				not needed by us
 *
 *	400 - 439	MP	NetBSD: mbr_bootsel
 *
 *	424 - 439	M	NetBSD: bootptn_guid (in GPT PMBR only)
 *
 *	440 - 443	M	WinNT/2K/XP Drive Serial Number (NT DSN)
 *		http://www.geocities.com/thestarman3/asm/mbr/Win2kmbr.htm
 *
 *	444 - 445	FMP	bootcode or unused
 *				NetBSD: mbr_bootsel_magic
 *
 *	446 - 509	M	partition table
 *
 *	510 - 511	FMP	magic number (0xAA55)
 *
 *	Use:
 *	----
 *	F	Floppy boot sector
 *	M	Master Boot Record
 *	P	Partition Boot record
 *
 */
#ifndef BPB_H
#define BPB_H

#include <stdint.h>

/*
 * (x86) BIOS Parameter Block for FAT12
 */
struct mbr_bpbFAT12 {
    uint16_t	bpbBytesPerSec;	/* bytes per sector */
    uint8_t		bpbSecPerClust;	/* sectors per cluster */
    uint16_t	bpbResSectors;	/* number of reserved sectors */
    uint8_t		bpbFATs;	/* number of FATs */
    uint16_t	bpbRootDirEnts;	/* number of root directory entries */
    uint16_t	bpbSectors;	/* total number of sectors */
    uint8_t		bpbMedia;	/* media descriptor */
    uint16_t	bpbFATsecs;	/* number of sectors per FAT */
    uint16_t	bpbSecPerTrack;	/* sectors per track */
    uint16_t	bpbHeads;	/* number of heads */
    uint16_t	bpbHiddenSecs;	/* # of hidden sectors */
} __attribute__ ((packed));

/*
 * (x86) BIOS Parameter Block for FAT16
 */
struct mbr_bpbFAT16 {
    uint16_t	bpbBytesPerSec;	/* bytes per sector */
    uint8_t		bpbSecPerClust;	/* sectors per cluster */
    uint16_t	bpbResSectors;	/* number of reserved sectors */
    uint8_t		bpbFATs;	/* number of FATs */
    uint16_t	bpbRootDirEnts;	/* number of root directory entries */
    uint16_t	bpbSectors;	/* total number of sectors */
    uint8_t		bpbMedia;	/* media descriptor */
    uint16_t	bpbFATsecs;	/* number of sectors per FAT */
    uint16_t	bpbSecPerTrack;	/* sectors per track */
    uint16_t	bpbHeads;	/* number of heads */
    uint32_t	bpbHiddenSecs;	/* # of hidden sectors */
    uint32_t	bpbHugeSectors;	/* # of sectors if bpbSectors == 0 */
    uint8_t		bsDrvNum;	/* Int 0x13 drive number (e.g. 0x80) */
    uint8_t		bsReserved1;	/* Reserved; set to 0 */
    uint8_t		bsBootSig;	/* 0x29 if next 3 fields are present */
    uint8_t		bsVolID[4];	/* Volume serial number */
    uint8_t		bsVolLab[11];	/* Volume label */
    uint8_t		bsFileSysType[8];
                    /* "FAT12   ", "FAT16   ", "FAT     " */
} __attribute__ ((packed));

/*
 * (x86) BIOS Parameter Block for FAT32
 */
struct mbr_bpbFAT32 {
    uint16_t	bpbBytesPerSec;	/* bytes per sector */
    uint8_t		bpbSecPerClust;	/* sectors per cluster */
    uint16_t	bpbResSectors;	/* number of reserved sectors */
    uint8_t		bpbFATs;	/* number of FATs */
    uint16_t	bpbRootDirEnts;	/* number of root directory entries */
    uint16_t	bpbSectors;	/* total number of sectors */
    uint8_t		bpbMedia;	/* media descriptor */
    uint16_t	bpbFATsecs;	/* number of sectors per FAT */
    uint16_t	bpbSecPerTrack;	/* sectors per track */
    uint16_t	bpbHeads;	/* number of heads */
    uint32_t	bpbHiddenSecs;	/* # of hidden sectors */
    uint32_t	bpbHugeSectors;	/* # of sectors if bpbSectors == 0 */
    uint32_t	bpbBigFATsecs;	/* like bpbFATsecs for FAT32 */
    uint16_t	bpbExtFlags;	/* extended flags: */
#define	MBR_FAT32_FATNUM	0x0F	/*   mask for numbering active FAT */
#define	MBR_FAT32_FATMIRROR	0x80	/*   FAT is mirrored (as previously) */
    uint16_t	bpbFSVers;	/* filesystem version */
#define	MBR_FAT32_FSVERS	0	/*   currently only 0 is understood */
    uint32_t	bpbRootClust;	/* start cluster for root directory */
    uint16_t	bpbFSInfo;	/* filesystem info structure sector */
    uint16_t	bpbBackup;	/* backup boot sector */
    uint8_t		bsReserved[12];	/* Reserved for future expansion */
    uint8_t		bsDrvNum;	/* Int 0x13 drive number (e.g. 0x80) */
    uint8_t		bsReserved1;	/* Reserved; set to 0 */
    uint8_t		bsBootSig;	/* 0x29 if next 3 fields are present */
    uint8_t		bsVolID[4];	/* Volume serial number */
    uint8_t		bsVolLab[11];	/* Volume label */
    uint8_t		bsFileSysType[8]; /* "FAT32   " */
} __attribute__ ((packed));

#endif // BPB_H
