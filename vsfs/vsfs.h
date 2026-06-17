#ifndef VSFS_H
#define VSFS_H

#define BLOCK_SIZE 4096
#define DISK_BLOCKS 64
#define MAGIC_NUMBER 0x123456
#define MAX_INODES 16

struct superblock{
    int magic;
    int num_inodes;
    int num_data_blocks;
};

struct inode{
    int size;
    int type;
    int direct;
    int indirect;
};

struct vsfs_disk{
    struct superblock sb;
    char inode_bitmap[BLOCK_SIZE];
    char data_bitmap[BLOCK_SIZE];
    struct inode inodes[MAX_INODES];
    char data_blocks[DISK_BLOCKS][BLOCK_SIZE];
};

#endif