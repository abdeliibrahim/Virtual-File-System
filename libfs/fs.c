#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "disk.h"
#include "fs.h"

/* On packing a struct: 
https://stackoverflow.com/questions/4306186/structure-padding-and-packing */

struct __attribute__((packed)) Superblock {
	uint8_t sig[8];
	// 2 bytes would require a 16 bit int, 1 byte requires 8 bit int
	uint16_t totalBlocks;
	uint16_t rootBlockIndex;
	uint16_t dataBlockStart;
	uint16_t dataBlockCt;
	uint8_t fatBlocks;

	// 1 byte * 4079
	uint8_t padding[4079];


};

struct __attribute__((packed)) FAT {
	uint16_t *flatArray;

};

struct __attribute__((packed)) Entry {
	uint8_t filename[FS_FILENAME_LEN];
	uint32_t fileSize;
	uint16_t firstBlockIn;

	// 1 byte * 10
	uint8_t padding[10];

};
struct __attribute__((packed)) RootDir {
	struct Entry rootDir[FS_FILE_MAX_COUNT];
};


// global Superblock, Root Directory, and FAT
 struct Superblock superblock;
 struct RootDir *rd;
 struct FAT fat;

/* TODO: Phase 1 */

int fs_mount(const char *diskname)
{
	/* TODO: Phase 1 */
	
	// open disk, return -1 if open errors
	if (block_disk_open(diskname))
		return -1;
	
	/* read 0th block from the @disk to the superblock,
	return -1 if errors */
	if (block_read(0, &superblock))
		return -1;

	/* now that the first block is in the superblock,
	check if the signature is correct */
	if (strcmp("ECS150FS", superblock.sig) == -1) {
		fprintf(stderr, "Signature not accepted");
		return -1;
	}

    //Hello THis is ALi

	
	
	

	return 0;
}

int fs_umount(void)
{
	/* TODO: Phase 1 */

	

	return 0;
}


int fs_info(void)
{
	/* TODO: Phase 1 */

	int i, fatFree, rdFree= 0;
	uint8_t fileEmpty = 0;
	
	/* Calculating fat free blocks */
	for(i; i<superblock.dataBlockCt; i++) {
		if(fat.flatArray[i] == 0)
			fatFree++;
	}
	/* Calculating rdir free files. */
	for(i=0; i<FS_FILE_MAX_COUNT; i++) {
		if(rd->rootDir->filename[0] == fileEmpty)
			rdFree++;
	}

	/* On format specifiers for (un)signed integers:
	https://www.geeksforgeeks.org/difference-d-format-specifier-c-language/ */
	printf("FS Info:\n");
	printf("total_block_count=%i\n",superblock.totalBlocks);
	printf("fat_blk_count=%i\n",superblock.fatBlocks);
	printf("redir_blk=%i\n",superblock.rootBlockIndex);
	printf("data_blk=%i\n",superblock.dataBlockStart);
	printf("data_blk_count=%i\n",superblock.dataBlockCt);
	printf("fat_free_ratio=%d/%i\n", fatFree, superblock.dataBlockCt);
	printf("rdir_free_ratio=%d/%i\n", rdFree, FS_FILE_MAX_COUNT);
	


	return 0;

}

int fs_create(const char *filename)
{
	/* TODO: Phase 2 */
	return 0;
}

int fs_delete(const char *filename)
{
	/* TODO: Phase 2 */
	return 0;
}

int fs_ls(void)
{
	/* TODO: Phase 2 */
	return 0;
}

int fs_open(const char *filename)
{
	/* TODO: Phase 3 */
	return 0;
}

int fs_close(int fd)
{
	/* TODO: Phase 3 */
	return 0;
}

int fs_stat(int fd)
{
	/* TODO: Phase 3 */
	return 0;
}

int fs_lseek(int fd, size_t offset)
{
	/* TODO: Phase 3 */
	return 0;
}

int fs_write(int fd, void *buf, size_t count)
{
	/* TODO: Phase 4 */
	return 0;
}

int fs_read(int fd, void *buf, size_t count)
{
	//struct Superblock obj;
	//block_read(fd, sizeof(obj));
	//slide 15 project disc


	/* TODO: Phase 4 */
	return 0;
}

